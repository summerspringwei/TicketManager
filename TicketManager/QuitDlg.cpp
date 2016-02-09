// QuitDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TicketManager.h"
#include "QuitDlg.h"
#include "afxdialogex.h"
#include "locale.h"
#include "funcs.h"
// QuitDlg 对话框

IMPLEMENT_DYNAMIC(QuitDlg, CDialogEx)

QuitDlg::QuitDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(QuitDlg::IDD, pParent)
	, m_edit_quit_id(_T(""))
	, m_edit_quit_num(0)
{

}

QuitDlg::~QuitDlg()
{
}

void QuitDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_QUIT_ID, m_edit_quit_id);
	DDX_Text(pDX, IDC_EDIT_QUIT_NUM, m_edit_quit_num);
}


BEGIN_MESSAGE_MAP(QuitDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_QUIT, &QuitDlg::OnBnClickedButtonQuit)
END_MESSAGE_MAP()


// QuitDlg 消息处理程序


void QuitDlg::OnBnClickedButtonQuit()
{
	// TODO:  在此添加控件通知处理程序代码

	TCHAR* old_locale = _tcsdup(_tsetlocale(LC_CTYPE, NULL));
	_tsetlocale(LC_CTYPE, _T("chs"));

	UpdateData(TRUE);
	//读取文件
	CStdioFile csf_read(_T("res/ticketInfo.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeRead);
	CString trainInfos[10000];
	int num = 0;
	while (csf_read.ReadString(trainInfos[num]))
	{
		num++;
	}
	csf_read.Close();

	//寻找id并判断是否可以退票
	bool foundId = false;
	for (int i = 0; i < num; i++)
	{
		CString* com = splitS(trainInfos[i]);
		
		if (com[0] == m_edit_quit_id)
		{
			if (myOverTime(com[1]))
			{
				MessageBox(_T("本班车已经发出\n无法退票~"));
				foundId = true;
				return;
			}

			int ticketOrderd = _ttoi(com[6]);
			if (ticketOrderd - m_edit_quit_num < 0)
			{
				MessageBox(_T("退票数量太多，请重新输入！"));
				return;
			}


			ticketOrderd = ticketOrderd - m_edit_quit_num;
			com[6].Format(_T("%d"), ticketOrderd);
			trainInfos[i] = cat(com);
			
			int rec = i;
			CStdioFile  csf_write(_T("res/ticketInfo.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeReadWrite);
			for (int j = 0; j < num; j++)
			{
				csf_write.WriteString(trainInfos[j]);
				if(rec==num-1)
					continue;
				csf_write.WriteString(_T("\n"));
			}
			csf_write.Flush();
			csf_write.Close();
			
			CString csQuit;
			csQuit.Format(_T("%d"), m_edit_quit_num);
			MessageBox(csQuit + _T(" 张票退票成功！"));
			foundId = true;
			return;
		}

	}
	if (!foundId)
	{
		MessageBox(_T("所退班次没有找到，请确认！"));
	}

	_tsetlocale(LC_CTYPE, old_locale);
	free(old_locale);
}
