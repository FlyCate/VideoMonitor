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
#include "PacketListener.h"


//Refresh Event
#define SFM_REFRESH_EVENT  (SDL_USEREVENT + 1)

#define SFM_BREAK_EVENT  (SDL_USEREVENT + 2)

class CFFMpeg
{
public:
	CFFMpeg(PacketListener* listener);
	~CFFMpeg(void);
private:
	PacketListener* listener;//我们的监听器接口

	AVFormatContext	*pFormatCtx;
	int	videoindex; // videoindex 流的索引即在pFormatCtx->streams数组中的索引
	int audioindex;
	AVCodecContext	*pVideoCodecCtx;
	AVCodec			*pVideoCodec;
	AVCodecContext	*pAudioCodecCtx;
	AVCodec			*pAudioCodec;
	SDL_Thread *video_tid;

	AVInputFormat *ifmt;

	AVFrame	*pVideoFrame;
	AVFrame	*pAudioFrame;

public:
	int OpenInput(char* format, char* fname);
	void FindAV(void);
	void Process();
private:
	void _ProcessVideoPacket(AVPacket* packet);
	void _ProcessAudioPacket(AVPacket* packet);
public:
	void CloseInput(void);
};

