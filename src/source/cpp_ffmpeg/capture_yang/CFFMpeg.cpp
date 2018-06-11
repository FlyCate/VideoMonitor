#include "CFFMpeg.h"


CFFMpeg::CFFMpeg(PacketListener* listener)
{
	this->listener = listener;
	
	av_register_all();
	avformat_network_init();
	pFormatCtx = avformat_alloc_context();
	
	//Open File
	//char filepath[]="src01_480x272_22.h265";
	//avformat_open_input(&pFormatCtx,filepath,NULL,NULL)

	//Register Device
	avdevice_register_all();
	//Windows

	//初始化SDL
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {  
		printf( "Could not initialize SDL - %s\n", SDL_GetError()); 
		
	} 

}


CFFMpeg::~CFFMpeg(void)
{
}


int CFFMpeg::OpenInput(char* format, char* fname)
{
	AVDictionary* options = NULL;
	//Set some options
	//grabbing frame rate
	//av_dict_set(&options,"framerate","5",0);
	//The distance from the left edge of the screen or desktop
	//av_dict_set(&options,"offset_x","20",0);
	//The distance from the top edge of the screen or desktop
	//av_dict_set(&options,"offset_y","40",0);
	//Video frame size. The default is to capture the full screen
	//av_dict_set(&options,"video_size","640x480",0);
	//查找输入流
	if(format != NULL){
		ifmt=av_find_input_format(format);
	}else{
		ifmt = NULL;
	}
	//读取输入流，结果存在pFormatCtx中
	if(avformat_open_input(&pFormatCtx,fname,ifmt,&options)!=0){
		printf("Couldn't open input stream.\n");
		return -1;
	}
	return 0;
}

/**
	找到Audio和Video的流编号，并获取相应的解码器
	
*/
void CFFMpeg::FindAV(void)
{
	if(avformat_find_stream_info(pFormatCtx,NULL)<0)
	{
		printf("Couldn't find stream information.\n");
		return ;
	}
	videoindex=-1;
	audioindex = -1;
	//遍历所有的流，并找到视频流
	for(int i=0; i<pFormatCtx->nb_streams; i++){ 
		if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_VIDEO)
		{
			videoindex=i;
			break;
		}

	}
	for(int i=0; i<pFormatCtx->nb_streams; i++){ 
		if(pFormatCtx->streams[i]->codec->codec_type==AVMEDIA_TYPE_AUDIO)
		{
			audioindex=i;
			break;
		}
	}

	//如果没找到，报错返回
	if(videoindex==-1)
	{
		printf("Didn't find a video stream.\n");
		pVideoCodecCtx =NULL;
		pVideoCodec = NULL;
		//return;
	}else{
		//记住视频解码器
		pVideoCodecCtx=pFormatCtx->streams[videoindex]->codec;
		pVideoCodec=avcodec_find_decoder(pVideoCodecCtx->codec_id);
		if(pVideoCodec==NULL)
		{
			printf("Video Codec not found.\n");
			//return;
		}else{
			printf("video codec %s %d \r\n",pVideoCodec->name,pVideoCodec->id);
			//打开解码器
			if(avcodec_open2(pVideoCodecCtx, pVideoCodec,NULL)<0)
			{
				printf("Could not open codec.\n");
			}else{
				listener->onVideoSize(pVideoCodecCtx->width,pVideoCodecCtx->height,pVideoCodecCtx->pix_fmt);
			}

		}
	}

	//如果没找到，报错返回
	if(audioindex==-1)
	{
		printf("Didn't find a audio stream.\n");
		pAudioCodecCtx = NULL;
		pAudioCodec = NULL;
		//return;
	}else{
		//记住音频解码器
		pAudioCodecCtx=pFormatCtx->streams[audioindex]->codec;
		pAudioCodec=avcodec_find_decoder(pAudioCodecCtx->codec_id);
		if(pAudioCodec==NULL)
		{
			printf("Audio Codec not found.\n");
			//return;
		}else{
			printf("audio codec %s %d \r\n",pAudioCodec->name,pAudioCodec->id);
			if(avcodec_open2(pAudioCodecCtx, pAudioCodec,NULL)<0)
			{
				printf("Could not open codec.\n");
			}
		}
	}




}

int thread_exit=0;
int sfp_refresh_thread(void *opaque)
{
	printf("sfp_refresh_thread called\r\n");
	thread_exit=0;
	while (!thread_exit) {
		SDL_Event event;
		event.type = SFM_REFRESH_EVENT;
		//printf("send %d\n",event.type);
		SDL_PushEvent(&event);
		SDL_Delay(40);
	}
	thread_exit=0;
	//Break
	SDL_Event event;
	event.type = SFM_BREAK_EVENT;
	SDL_PushEvent(&event);

	return 0;
}
void CFFMpeg::Process()
{
	AVPacket *packet=(AVPacket *)av_malloc(sizeof(AVPacket));
	
	
	pAudioFrame=av_frame_alloc();
	pVideoFrame=av_frame_alloc();
	
	SDL_Thread *video_tid = SDL_CreateThread(sfp_refresh_thread,NULL);
		//Event Loop
	SDL_Event event;

	printf("SFM_REFRESH_EVENT = %d\r\n",SFM_REFRESH_EVENT);
	
	for (;;) {
		//Wait
		SDL_WaitEvent(&event);
		//printf("event %d\n",event.type);
		if(event.type==SFM_REFRESH_EVENT){
			//------------------------------
			if(av_read_frame(pFormatCtx, packet)>=0){
				listener->onRecvPacket(packet);
				
				if(packet->stream_index==videoindex){
					_ProcessVideoPacket(packet);
				}else if(packet->stream_index == audioindex){
					_ProcessAudioPacket(packet);
				}
				av_free_packet(packet);
			}else{
				//Exit Thread
				thread_exit=1;
			}
		}else if(event.type==SDL_QUIT){
			thread_exit=1;
		}else if(event.type==SFM_BREAK_EVENT){
			break;
		}

	}

}


void CFFMpeg::_ProcessVideoPacket(AVPacket* packet)
{
	int got_picture = -1;
	int ret = avcodec_decode_video2(pVideoCodecCtx, pVideoFrame, &got_picture, packet);
	if(ret < 0){
		printf("Decode Video Error.\n");
		return;
	}
	if(got_picture){
		listener->onVideoFrame(pVideoFrame);
	}
}

void CFFMpeg::_ProcessAudioPacket(AVPacket* packet)
{
	int got_picture = -1;
	int ret = avcodec_decode_audio4(pAudioCodecCtx, pAudioFrame, &got_picture, packet);
	if(ret < 0){
		printf("Decode Audio Error.\n");
		return;
	}
	if(got_picture){
		listener->onAudioFrame(pAudioFrame);
	}
}


void CFFMpeg::CloseInput(void)
{
	
	//av_free(pFrameYUV);
	if(pAudioCodecCtx!=NULL){
		avcodec_close(pAudioCodecCtx);
	}
	if(pVideoCodecCtx!=NULL){
		avcodec_close(pVideoCodecCtx);
	}

	avformat_close_input(&pFormatCtx);
}
