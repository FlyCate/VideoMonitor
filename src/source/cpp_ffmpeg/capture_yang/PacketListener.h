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

 class  PacketListener
{
public:
	PacketListener(void);
	~PacketListener(void);
	virtual  void onRecvPacket(AVPacket* packet);
	virtual void onVideoFrame(AVFrame* frame);
	virtual void onAudioFrame(AVFrame* frame);
	virtual void onVideoSize(int width, int height,AVPixelFormat format);
 };

