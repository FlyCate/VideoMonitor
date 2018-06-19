#pragma once
#ifdef _WIN32
//Windows
extern "C"
{
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libswscale/swscale.h"
#include "libavdevice/avdevice.h"
//#include "SDL/SDL.h"
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
#include "DataManagerBase.h"


//Refresh Event
#define SFM_REFRESH_EVENT  (SDL_USEREVENT + 1)

#define SFM_BREAK_EVENT  (SDL_USEREVENT + 2)

class CFFMpeg
{
public:
	CFFMpeg(PacketListener* listener);
	~CFFMpeg(void);

private:
	CFFMpeg();

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

	int thread_exit;
	long m_lFrame;
	CDataManagerBase * m_pDataManager;

public:
	//输入文件 网络流方式
	int OpenInput(char* format, char* fname);
	int FindAV();
	void Process();
	void CloseInput(void);

	//通过其他流获取方式
	int DecoderInit(const CDataManagerBase * dataManager, const long lWidth, const long lHeight, const char * szFormat, const long lFrame = 25);
	void DecoderProcess();
	void DecoderFini();

private:
	void _ProcessVideoPacket(AVPacket* packet);
	void _ProcessAudioPacket(AVPacket* packet);
};

