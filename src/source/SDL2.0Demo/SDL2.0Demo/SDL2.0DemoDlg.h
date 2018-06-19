
// SDL2.0DemoDlg.h : 头文件
//

#pragma once

#include "Sdl2Handle.h"

// CSDL20DemoDlg 对话框
class CSDL20DemoDlg : public CDialogEx
{
// 构造
public:
	CSDL20DemoDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SDL20DEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

private:
	CSdl2Handle m_SDLHandel1;
	CSdl2Handle m_SDLHandel2;

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDraw1();
	afx_msg void OnBnClickedButtonDraw2();
};
