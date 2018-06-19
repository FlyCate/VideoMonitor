#include "stdafx.h"
#include "Sdl2Handle.h"
#include <stdio.h>
//初始化SDL
bool CSdl2Handle::SdlInit()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER))
	{
		return false;
	}

	return true;
}
//反初始化SDL
void CSdl2Handle::SdlUnInit()
{
	SDL_Quit();
}

CSdl2Handle::CSdl2Handle()
{
	//显示窗口
	SDL_Window *  m_pWnd = NULL;
	//图片渲染器
	SDL_Renderer* m_pRender = NULL;
	//图片装载器
	SDL_Texture*  m_pTexture = NULL;
	//标志窗口是否本层创建
	m_IsSdlCreate = true;
}
CSdl2Handle::~CSdl2Handle()
{
	SdlClose();
}
bool CSdl2Handle::SdlOpen(void *pWndHandle, const char *pTitle, int iWidth, int iHeight)
{
	bool bRet = true;
	do
	{
		if (!pWndHandle)
		{
			m_pWnd = SDL_CreateWindow(pTitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, iWidth, iHeight,
				SDL_WINDOW_OPENGL);
			if (!m_pWnd)
			{
				printf("SDL: 创建窗口失败 - 错误信息:%s\n", SDL_GetError());
				bRet = false;
				break;
			}
		}
		else
		{
			m_pWnd = SDL_CreateWindowFrom(pWndHandle);
			if (!m_pWnd)
			{
				printf("SDL: 创建窗口失败 - 错误信息:%s\n", SDL_GetError());
				bRet = false;
				break;
			}
			m_IsSdlCreate = false;
		}
		m_pRender = SDL_CreateRenderer(m_pWnd, -1, 0);

		m_pTexture = SDL_CreateTexture(m_pRender, SDL_PIXELFORMAT_IYUV, SDL_TEXTUREACCESS_STREAMING, iWidth, iHeight);

		m_Rect.x = 0;
		m_Rect.y = 0;
		m_Rect.w = iWidth;
		m_Rect.h = iHeight;

	} while (0);

	return bRet;
}

void CSdl2Handle::SdlClose()
{
	if (m_pTexture)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = NULL;
	}
	if (m_pRender)
	{
		SDL_DestroyRenderer(m_pRender);
		m_pRender = NULL;
	}
	if (m_pWnd)
	{
		//SDL本身创建 销毁
		if (m_IsSdlCreate)
		{
			SDL_DestroyWindow(m_pWnd);
		}
	}
}

void CSdl2Handle::SdlDisplayFrame(uint8_t*pszData[], int iLinesize[], int iFlag)
{
	//一帧YV12数据填充到 图片装载器中 颜色反了 可能 U和V反了
	if (iFlag)
	{
		SDL_UpdateYUVTexture(m_pTexture, &m_Rect,
			(const Uint8 *)pszData[0], iLinesize[0],
			(const Uint8 *)pszData[2], iLinesize[2],
			(const Uint8 *)pszData[1], iLinesize[1]);
	}
	else
	{
		SDL_UpdateYUVTexture(m_pTexture, &m_Rect,
			(const Uint8 *)pszData[0], iLinesize[0],
			(const Uint8 *)pszData[1], iLinesize[1],
			(const Uint8 *)pszData[2], iLinesize[2]);
	}
	//清屏
	SDL_RenderClear(m_pRender);
	//装载器数据渲染到窗口
	SDL_RenderCopy(m_pRender, m_pTexture, NULL, &m_Rect);
	//刷新
	SDL_RenderPresent(m_pRender);
}

//YUV显示BMP图片
bool CSdl2Handle::SdlDisplayBmp(char *pFilePath)
{
	SDL_Surface *pBmp = NULL;
	pBmp = SDL_LoadBMP(pFilePath);
	if (pBmp == NULL)
	{
		printf("SDL_LoadBMP failed: %s", SDL_GetError());
		return false;
	}
	SDL_Texture*  pTmpTexture = NULL;
	pTmpTexture = SDL_CreateTextureFromSurface(m_pRender, pBmp);
	//清屏
	SDL_RenderClear(m_pRender);
	//装载器数据渲染到窗口
	SDL_RenderCopy(m_pRender, pTmpTexture, NULL, &m_Rect);
	//刷新
	SDL_RenderPresent(m_pRender);

	//销毁临时
	SDL_FreeSurface(pBmp);
	SDL_DestroyTexture(pTmpTexture);
	return true;
}