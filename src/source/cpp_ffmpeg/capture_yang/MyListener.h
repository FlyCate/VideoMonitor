#pragma once
#include "packetlistener.h"
#include "SDLVideo.h"
class MyListener :
	public PacketListener
{
public:
	MyListener(void);
	~MyListener(void);
	virtual void onVideoFrame(AVFrame* frame);
	virtual void onVideoSize(int width, int height,AVPixelFormat format);
	CSDLVideo* win;
};

