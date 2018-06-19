#ifndef _SDL2HANDLE_H_ 
#define _SDL2HANDLE_H_
//����SDL2.0ʵ�ֵ�ͼƬ��Ⱦ��
//SDL_Window����ʹ��SDL��ʱ�򵯳����Ǹ����ڡ���SDL2.0�汾�У����Դ���������ڡ�
//SDL_Texture������ʾYUV���ݡ�һ��SDL_Texture��Ӧһ֡YUV���ݡ�
//SDL_Renderer������ȾSDL_Texture��SDL_Window��
//SDL_Rect����ȷ��SDL_Texture��ʾ��λ�á�ע�⣺һ��SDL_Texture����ָ�������ͬ��SDL_Rect�������Ϳ�����SDL_Window��ͬλ����ʾ��ͬ�����ݣ�ʹ��SDL_RenderCopy()��������
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
	//��ʾһ֡YV12���� iLinesize YUVÿ������ ÿ�����ݿ�� ��һ������ͼƬ���
	void SdlDisplayFrame(uint8_t *pszData[], int iLinesize[], int iFlag);
	//YUV��ʾBMPͼƬ
	bool SdlDisplayBmp(char *pFilePath);
public:
	static bool SdlInit();
	static void SdlUnInit();
private:
	//��ʾ����
	SDL_Window *  m_pWnd;
	//ͼƬ��Ⱦ��
	SDL_Renderer* m_pRender;
	//ͼƬװ����
	SDL_Texture*  m_pTexture;
	//��ʾλ��(һ�����ڿ����ж����ʾλ�ã���ǰ֧��һ��)
	SDL_Rect	  m_Rect;
	//��־�����Ƿ񱾲㴴��
	bool		  m_IsSdlCreate;
};

#endif