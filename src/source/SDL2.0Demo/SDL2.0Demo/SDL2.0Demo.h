
// SDL2.0Demo.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSDL20DemoApp: 
// �йش����ʵ�֣������ SDL2.0Demo.cpp
//

class CSDL20DemoApp : public CWinApp
{
public:
	CSDL20DemoApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSDL20DemoApp theApp;