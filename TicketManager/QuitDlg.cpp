// QuitDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TicketManager.h"
#include "QuitDlg.h"
#include "afxdialogex.h"
#include "locale.h"
#include "funcs.h"
// QuitDlg �Ի���

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


// QuitDlg ��Ϣ�������


void QuitDlg::OnBnClickedButtonQuit()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	TCHAR* old_locale = _tcsdup(_tsetlocale(LC_CTYPE, NULL));
	_tsetlocale(LC_CTYPE, _T("chs"));

	UpdateData(TRUE);
	//��ȡ�ļ�
	CStdioFile csf_read(_T("res/ticketInfo.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeRead);
	CString trainInfos[10000];
	int num = 0;
	while (csf_read.ReadString(trainInfos[num]))
	{
		num++;
	}
	csf_read.Close();

	//Ѱ��id���ж��Ƿ������Ʊ
	bool foundId = false;
	for (int i = 0; i < num; i++)
	{
		CString* com = splitS(trainInfos[i]);
		
		if (com[0] == m_edit_quit_id)
		{
			if (myOverTime(com[1]))
			{
				MessageBox(_T("���೵�Ѿ�����\n�޷���Ʊ~"));
				foundId = true;
				return;
			}

			int ticketOrderd = _ttoi(com[6]);
			if (ticketOrderd - m_edit_quit_num < 0)
			{
				MessageBox(_T("��Ʊ����̫�࣬���������룡"));
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
			MessageBox(csQuit + _T(" ��Ʊ��Ʊ�ɹ���"));
			foundId = true;
			return;
		}

	}
	if (!foundId)
	{
		MessageBox(_T("���˰��û���ҵ�����ȷ�ϣ�"));
	}

	_tsetlocale(LC_CTYPE, old_locale);
	free(old_locale);
}
