
// TicketManagerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TicketManager.h"
#include "TicketManagerDlg.h"
#include "afxdialogex.h"
#include "AddDlg.h"
#include "QueryDlg.h"
#include "locale.h"
#include "funcs.h"
#include "QuitDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTicketManagerDlg 对话框



CTicketManagerDlg::CTicketManagerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTicketManagerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTicketManagerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VIEW_MAIN, m_listCtrl_view_main);
}

BEGIN_MESSAGE_MAP(CTicketManagerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_COMMAND(ID_MENU_ADD, &CTicketManagerDlg::OnMenuAdd)
	ON_COMMAND(ID_MENU_VIEW_MAIN, &CTicketManagerDlg::OnMenuViewMain)
	ON_COMMAND(ID_MENU_ABOUT, &CTicketManagerDlg::OnMenuAbout)
	ON_COMMAND(ID_MENU_QUERY_ID, &CTicketManagerDlg::OnMenuQueryId)
	ON_COMMAND(ID_MUNE_QUERY_STOPSTATION, &CTicketManagerDlg::OnMuneQueryStopstation)
	ON_COMMAND(ID_MENU_SALE, &CTicketManagerDlg::OnMenuSale)
	ON_COMMAND(ID_MENU_QUIT, &CTicketManagerDlg::OnMenuQuit)
END_MESSAGE_MAP()


// CTicketManagerDlg 消息处理程序

BOOL CTicketManagerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO:  在此添加额外的初始化代码

	hasViewMain = false;


	CRect rect;
	m_listCtrl_view_main.GetClientRect(&rect);
	CString title[8] = { _T("班次"), _T("发车时间"), _T("起点站"), _T("终点站"), _T("行车时间"), _T("额定载量"), _T("已订票人数"), _T("状态") };

	for (int i = 0; i < 8; i++)
	{
		m_listCtrl_view_main.InsertColumn(i, title[i], 0, rect.Width() / 8, i);
	}
	//始终高亮度被选中的表项
	m_listCtrl_view_main.ModifyStyle(0L, LVS_SHOWSELALWAYS);
	m_listCtrl_view_main.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CTicketManagerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CTicketManagerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CTicketManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTicketManagerDlg::OnMenuAdd()
{
	// TODO:  在此添加命令处理程序代码
	AddDlg addDlg;
	addDlg.DoModal();
}


void CTicketManagerDlg::OnMenuViewMain()
{
	// TODO:  在此添加命令处理程序代码

	TCHAR* old_locale = _tcsdup(_tsetlocale(LC_CTYPE, NULL));
	_tsetlocale(LC_CTYPE, _T("chs"));

	m_listCtrl_view_main.DeleteAllItems();

	int num = 0;
	CString trainInfos[1000];
	CStdioFile csf_read(_T("res/ticketInfo.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeRead);
	
	while (csf_read.ReadString(trainInfos[num])){
		num++;
	}
	csf_read.Close();
	for (int i = 0; i < num; i++)
	{
		CString *com = splitS(trainInfos[i]);
		m_listCtrl_view_main.InsertItem(i, com[0]);
		for (int j = 1; j < 7; j++)
		{
			m_listCtrl_view_main.SetItemText(i, j, com[j]);
		}
		if (myOverTime(com[1]))
			m_listCtrl_view_main.SetItemText(i, 7, _T("已发车！"));
		else
		{
			m_listCtrl_view_main.SetItemText(i, 7, _T("未发车"));
		}
	}
	
	_tsetlocale(LC_CTYPE, old_locale);
	free(old_locale);
}


void CTicketManagerDlg::OnMenuAbout()
{
	// TODO:  在此添加命令处理程序代码
	CAboutDlg cad;
	cad.DoModal();
}


void CTicketManagerDlg::OnMenuQueryId()
{
	// TODO:  在此添加命令处理程序代码
	QueryDlg qd;
	qd.DoModal();
}


void CTicketManagerDlg::OnMuneQueryStopstation()
{
	// TODO:  在此添加命令处理程序代码
	QueryDlg qd;
	qd.DoModal();
}


void CTicketManagerDlg::OnMenuSale()
{
	// TODO:  在此添加命令处理程序代码
	QueryDlg qd;
	qd.DoModal();
}


void CTicketManagerDlg::OnMenuQuit()
{
	// TODO:  在此添加命令处理程序代码
	QuitDlg qd;
	qd.DoModal();
}
