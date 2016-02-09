
// TicketManagerDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CTicketManagerDlg �Ի���



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


// CTicketManagerDlg ��Ϣ�������

BOOL CTicketManagerDlg::OnInitDialog()
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	hasViewMain = false;


	CRect rect;
	m_listCtrl_view_main.GetClientRect(&rect);
	CString title[8] = { _T("���"), _T("����ʱ��"), _T("���վ"), _T("�յ�վ"), _T("�г�ʱ��"), _T("�����"), _T("�Ѷ�Ʊ����"), _T("״̬") };

	for (int i = 0; i < 8; i++)
	{
		m_listCtrl_view_main.InsertColumn(i, title[i], 0, rect.Width() / 8, i);
	}
	//ʼ�ո����ȱ�ѡ�еı���
	m_listCtrl_view_main.ModifyStyle(0L, LVS_SHOWSELALWAYS);
	m_listCtrl_view_main.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTicketManagerDlg::OnPaint()
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
HCURSOR CTicketManagerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CTicketManagerDlg::OnMenuAdd()
{
	// TODO:  �ڴ���������������
	AddDlg addDlg;
	addDlg.DoModal();
}


void CTicketManagerDlg::OnMenuViewMain()
{
	// TODO:  �ڴ���������������

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
			m_listCtrl_view_main.SetItemText(i, 7, _T("�ѷ�����"));
		else
		{
			m_listCtrl_view_main.SetItemText(i, 7, _T("δ����"));
		}
	}
	
	_tsetlocale(LC_CTYPE, old_locale);
	free(old_locale);
}


void CTicketManagerDlg::OnMenuAbout()
{
	// TODO:  �ڴ���������������
	CAboutDlg cad;
	cad.DoModal();
}


void CTicketManagerDlg::OnMenuQueryId()
{
	// TODO:  �ڴ���������������
	QueryDlg qd;
	qd.DoModal();
}


void CTicketManagerDlg::OnMuneQueryStopstation()
{
	// TODO:  �ڴ���������������
	QueryDlg qd;
	qd.DoModal();
}


void CTicketManagerDlg::OnMenuSale()
{
	// TODO:  �ڴ���������������
	QueryDlg qd;
	qd.DoModal();
}


void CTicketManagerDlg::OnMenuQuit()
{
	// TODO:  �ڴ���������������
	QuitDlg qd;
	qd.DoModal();
}
