#include "SDLVideo.h"


CSDLVideo::CSDLVideo(void)
{
	m_pYUVBuf = nullptr;
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
	rect.x = 0;
	rect.y = 0;
	rect.w = screen_w;
	rect.h = screen_h;

	if (pix_fmt != AV_PIX_FMT_YUV420P)
	{
		img_convert_ctx = sws_getContext(width, height, pix_fmt, width, height, AV_PIX_FMT_YUV420P, SWS_BICUBIC, NULL, NULL, NULL);
	}
	SDL_WM_SetCaption("Simplest FFmpeg Grab Desktop",NULL);

	if (m_pYUVBuf != nullptr)
	{
		delete m_pYUVBuf;
		m_pYUVBuf = nullptr;
	}

	m_pYUVBuf = new char[width * height * 3 / 2];

	return 0;
}

int WriteFile(const char * pFileName, const char * pBuff, int nBuflen);

void CSDLVideo::ShowAVFrame(AVFrame* pFrame)
{
	SDL_LockYUVOverlay(bmp);

	if (pix_fmt != AV_PIX_FMT_YUV420P)
	{
		pFrameYUV->data[0] = bmp->pixels[0];
		pFrameYUV->data[1] = bmp->pixels[2];
		pFrameYUV->data[2] = bmp->pixels[1];
		pFrameYUV->linesize[0] = bmp->pitches[0];
		pFrameYUV->linesize[1] = bmp->pitches[2];
		pFrameYUV->linesize[2] = bmp->pitches[1];
		sws_scale(img_convert_ctx, (const unsigned char* const*)pFrame->data, pFrame->linesize, 0, height, pFrameYUV->data, pFrameYUV->linesize);
	}
	else
	{
		int nUpos = width * height;
		int nVpos = width * height + width * height / 4;
		for (int i = 0; i < height; i++)
		{
			memcpy(m_pYUVBuf + i * width, pFrame->data[0] + i * pFrame->linesize[0], width);
			if (i < height / 2)
			{
				memcpy(m_pYUVBuf + nUpos + i * width / 2, pFrame->data[1] + i * pFrame->linesize[1], width / 2);
				memcpy(m_pYUVBuf + nVpos + i * width / 2, pFrame->data[2] + i * pFrame->linesize[2], width / 2);
			}
		}

		//WriteFile("2.rgb", m_pYUVBuf, width * height * 3 / 2);
		bmp->pixels[0] = (Uint8 *)m_pYUVBuf;
		bmp->pixels[2] = (Uint8 *)m_pYUVBuf + nUpos;
		bmp->pixels[1] = (Uint8 *)m_pYUVBuf + nVpos;
		bmp->pitches[0] = width;
		bmp->pitches[2] = width / 2;
		bmp->pitches[1] = width / 2;
	}

	SDL_UnlockYUVOverlay(bmp); 
						
	SDL_DisplayYUVOverlay(bmp, &rect); 
}
