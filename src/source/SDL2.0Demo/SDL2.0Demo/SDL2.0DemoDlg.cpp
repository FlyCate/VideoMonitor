
// SDL2.0DemoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SDL2.0Demo.h"
#include "SDL2.0DemoDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSDL20DemoDlg �Ի���



CSDL20DemoDlg::CSDL20DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SDL20DEMO_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSDL20DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSDL20DemoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_DRAW1, &CSDL20DemoDlg::OnBnClickedButtonDraw1)
	ON_BN_CLICKED(IDC_BUTTON_DRAW2, &CSDL20DemoDlg::OnBnClickedButtonDraw2)
END_MESSAGE_MAP()


// CSDL20DemoDlg ��Ϣ�������

BOOL CSDL20DemoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	RECT rect;
	GetDlgItem(IDC_STATIC_DRAW_PIC1)->GetWindowRect(&rect);
	m_SDLHandel1.SdlInit();
	m_SDLHandel1.SdlOpen(GetDlgItem(IDC_STATIC_DRAW_PIC1)->GetSafeHwnd(), "lesson 1", rect.right - rect.left, rect.bottom - rect.top);
	GetDlgItem(IDC_STATIC_DRAW_PIC2)->GetWindowRect(&rect);
	m_SDLHandel2.SdlOpen(GetDlgItem(IDC_STATIC_DRAW_PIC2)->GetSafeHwnd(), "lesson 2", rect.right - rect.left, rect.bottom - rect.top);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CSDL20DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSDL20DemoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CSDL20DemoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CSDL20DemoDlg::OnBnClickedButtonDraw1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_SDLHandel1.SdlDisplayBmp("1.bmp");
}


void CSDL20DemoDlg::OnBnClickedButtonDraw2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_SDLHandel2.SdlDisplayBmp("2.bmp");
}
