#include "SDLVideo.h"


CSDLVideo::CSDLVideo(void)
{

}


CSDLVideo::~CSDLVideo(void)
{
}


int CSDLVideo::OpenVideo(int width, int height,AVPixelFormat pix_fmt)
{	
	printf("Open Video Called");
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER)) {  
		printf( "Could not initialize SDL - %s\n", SDL_GetError()); 
		return 1;
	} 
	//设置显示模式
	const SDL_VideoInfo *vi = SDL_GetVideoInfo();
	//Half of the Desktop's width and height.
	//screen_w = vi->current_w/2;
	//screen_h = vi->current_h/2;
	screen_w= width;
	screen_h = height;
	screen = SDL_SetVideoMode(screen_w, screen_h, 0,0);
	if(!screen) {  
		printf("SDL: could not set video mode - exiting:%s\n",SDL_GetError());  
		return 1;	
	}
	
	pFrameYUV=av_frame_alloc();



	this->width= width;
	this->height = height;
	this->pix_fmt = pix_fmt;
	bmp = SDL_CreateYUVOverlay(width, height,SDL_YV12_OVERLAY, screen); 
	printf("bmp seted \n");
	rect.x = 0;    
	rect.y = 0;    
	rect.w = screen_w;    
	rect.h = screen_h;  	
	img_convert_ctx = sws_getContext(width, height, pix_fmt, width, height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL); 
	
	SDL_WM_SetCaption("Simplest FFmpeg Grab Desktop",NULL);
	return 0;
}


void CSDLVideo::ShowAVFrame(AVFrame* pFrame)
{
	SDL_LockYUVOverlay(bmp);
	pFrameYUV->data[0]=bmp->pixels[0];
	pFrameYUV->data[1]=bmp->pixels[2];
	pFrameYUV->data[2]=bmp->pixels[1];     
	pFrameYUV->linesize[0]=bmp->pitches[0];
	pFrameYUV->linesize[1]=bmp->pitches[2];   
	pFrameYUV->linesize[2]=bmp->pitches[1];
	sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0, height, pFrameYUV->data, pFrameYUV->linesize);


	SDL_UnlockYUVOverlay(bmp); 
						
	SDL_DisplayYUVOverlay(bmp, &rect); 
}
