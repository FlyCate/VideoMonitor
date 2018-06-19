
// SDL2.0DemoDlg.h : ͷ�ļ�
//

#pragma once

#include "Sdl2Handle.h"

// CSDL20DemoDlg �Ի���
class CSDL20DemoDlg : public CDialogEx
{
// ����
public:
	CSDL20DemoDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SDL20DEMO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

private:
	CSdl2Handle m_SDLHandel1;
	CSdl2Handle m_SDLHandel2;

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonDraw1();
	afx_msg void OnBnClickedButtonDraw2();
};
