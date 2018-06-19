#include "CFFMpeg.h"
#include "MyListener.h"
#include "DataManagerRTP.h"
#include <tchar.h>
#include <windows.h>

#define __STDC_CONSTANT_MACROS

extern "C" { FILE __iob_func[3] = { *stdin,*stdout,*stderr }; }

int ReadFile(const char * pFileName, char *& pBuff, int & nBuflen)
{
	FILE * fp = fopen(pFileName, "rb");
	if (!fp)
	{
		printf("打开文件失败！\n", pFileName);
		return -1;
	}

	fseek(fp, 0, SEEK_END);
	nBuflen = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	pBuff = new char[nBuflen + 1];
	memset(pBuff, 0, nBuflen + 1);

	fread(pBuff, 1, nBuflen, fp);
	fclose(fp);

	return nBuflen;
}

int WriteFile(const char * pFileName, const char * pBuff, int nBuflen)
{
	FILE * fp = fopen(pFileName, "wb");
	if (!fp)
	{
		printf("打开文件失败！\n", pFileName);
		return -1;
	}

	fwrite(pBuff, 1, nBuflen, fp);
	fclose(fp);

	return nBuflen;
}

#define IS_H264_HEADER(x, i) ((x[i] == 0) && (x[i+1] == 0) && (x[i+2] == 0) && (x[i+3] == 1)) || ((x[i] == 0) && (x[i+1] == 0) && (x[i+2] == 1))

int GetH264FrameFromBuff(const char * pSrcbuff, const int nSrclen, char *& pFramebuff, int & nFramelen)
{
	bool bFindFirst = false;
	int  nFramePos = 0;

	for (int i = 0; i < nSrclen - 4; i++)
	{
		if (IS_H264_HEADER(pSrcbuff, i))
		{
			if (bFindFirst == false)
			{
				pFramebuff = (char *)&pSrcbuff[i];
				nFramePos = i;
				i += 4;
				bFindFirst = true;
			}
			else
			{
				nFramelen = i - nFramePos;
				break;
			}
		}
	}

	if ((bFindFirst == true) && (nFramelen == 0))
	{
		nFramelen = nSrclen - nFramePos;
	}

	return nFramelen;
}

int _tmain(int argc, _TCHAR* argv[])
{
	printf("ss\n");
	MyListener listener;
	CFFMpeg mpeg(&listener);

	//mpeg.OpenInput(NULL,"rtsp://172.20.36.169/myData.264");
//	int nRet = mpeg.OpenInput("264", "C:\\Users\\Administrator\\Desktop\\live\\live555Pro\\Debug\\myData.264");
// 	int nRet = mpeg.OpenInput("mpeg4", "E:\\workspace\\V2.0\\src\\Product\\Source\\ABS_RestServer\\Tool\\LowerPlatform\\Release\\Data\\VideoSliceData.mp4");
// 	if (nRet == 0)
// 	{
// 		mpeg.FindAV();
// 		mpeg.Process();
// 		mpeg.CloseInput();
// 	}

	CDataManagerRTP dataManager;
	int nRet = mpeg.DecoderInit(&dataManager, 720, 480, "h264");
	if (nRet != 0)
	{
		printf("解码器初始化失败！\n");
		system("pause");
		return -1;
	}

	char * pBuff = nullptr;
	int nBuflen = 0;
	nRet = ReadFile("C:\\Users\\Administrator\\Desktop\\live\\live555Pro\\Debug\\myData.264", pBuff, nBuflen);
	if (nRet > 0)
	{
		char * pPos = pBuff;
		int nPos = 0;
		
		do 
		{
			char * pFramebuff = nullptr;
			int nFramelen = 0;
			GetH264FrameFromBuff(pPos + nPos, nBuflen - nPos, pFramebuff, nFramelen);
			nPos += nFramelen;

			dataManager.PushData(pFramebuff, nFramelen);
		} while (nPos < nBuflen);

		mpeg.DecoderProcess();
		mpeg.DecoderFini();

		delete[] pBuff;
	}

	system("pause");
	return 0;
}