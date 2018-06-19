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
	PacketListener* listener;//���ǵļ������ӿ�

	AVFormatContext	*pFormatCtx;
	int	videoindex; // videoindex ������������pFormatCtx->streams�����е�����
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
	//�����ļ� ��������ʽ
	int OpenInput(char* format, char* fname);
	int FindAV();
	void Process();
	void CloseInput(void);

	//ͨ����������ȡ��ʽ
	int DecoderInit(const CDataManagerBase * dataManager, const long lWidth, const long lHeight, const char * szFormat, const long lFrame = 25);
	void DecoderProcess();
	void DecoderFini();

private:
	void _ProcessVideoPacket(AVPacket* packet);
	void _ProcessAudioPacket(AVPacket* packet);
};

