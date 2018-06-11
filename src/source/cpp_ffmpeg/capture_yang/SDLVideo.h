#pragma once

#ifdef _WIN32
//Windows
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
#include "SDL/SDL.h"
};
#else
//Linux...
#ifdef __cplusplus
extern "C"
{
#endif
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavdevice/avdevice.h>
#include <SDL/SDL.h>
#ifdef __cplusplus
};
#endif
#endif
class CSDLVideo
{
public:
	CSDLVideo(void);
	~CSDLVideo(void);
private:
	
	//Video Information
	int width,height;
	AVPixelFormat pix_fmt;

	//Window Informaction
	int screen_w,screen_h;
	SDL_Surface *screen; 
	SDL_Overlay *bmp; 

	//Converter
	struct SwsContext *img_convert_ctx;
	AVFrame* pFrameYUV;
	SDL_Rect rect;
public:
	int OpenVideo(int width, int height,AVPixelFormat pix_fmt);
	void ShowAVFrame(AVFrame* frame);
};

