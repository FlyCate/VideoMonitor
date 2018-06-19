#ifndef _SDL2HANDLE_H_ 
#define _SDL2HANDLE_H_
//基于SDL2.0实现的图片渲染器
//SDL_Window就是使用SDL的时候弹出的那个窗口。在SDL2.0版本中，可以创建多个窗口。
//SDL_Texture用于显示YUV数据。一个SDL_Texture对应一帧YUV数据。
//SDL_Renderer用于渲染SDL_Texture至SDL_Window。
//SDL_Rect用于确定SDL_Texture显示的位置。注意：一个SDL_Texture可以指定多个不同的SDL_Rect，这样就可以在SDL_Window不同位置显示相同的内容（使用SDL_RenderCopy()函数）。
extern "C"
{
#include "SDL.h"  
};
class CSdl2Handle
{
public:
	CSdl2Handle();
	~CSdl2Handle();
	bool SdlOpen(void *pWndHandle, const char *pTitle, int iWidth, int iHeight);
	void SdlClose();
	//显示一帧YV12数据 iLinesize YUV每个分量 每行数据宽度 不一定等于图片宽度
	void SdlDisplayFrame(uint8_t *pszData[], int iLinesize[], int iFlag);
	//YUV显示BMP图片
	bool SdlDisplayBmp(char *pFilePath);
public:
	static bool SdlInit();
	static void SdlUnInit();
private:
	//显示窗口
	SDL_Window *  m_pWnd;
	//图片渲染器
	SDL_Renderer* m_pRender;
	//图片装载器
	SDL_Texture*  m_pTexture;
	//显示位置(一个窗口可以有多个显示位置，当前支持一个)
	SDL_Rect	  m_Rect;
	//标志窗口是否本层创建
	bool		  m_IsSdlCreate;
};

#endif