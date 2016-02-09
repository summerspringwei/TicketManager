// QueryDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TicketManager.h"
#include "QueryDlg.h"
#include "afxdialogex.h"
#include "funcs.h"
#include "locale.h"

// QueryDlg �Ի���

IMPLEMENT_DYNAMIC(QueryDlg, CDialogEx)

QueryDlg::QueryDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(QueryDlg::IDD, pParent)
	, m_edit_txt_query(_T(""))
	, m_edit_ticket_num(0)
{

}

QueryDlg::~QueryDlg()
{
}

void QueryDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_QUERY, m_edit_query);
	DDX_Text(pDX, IDC_EDIT_QUERY, m_edit_txt_query);
	DDX_Control(pDX, IDC_LIST_QUERY, m_listCtrl_Query);
	DDX_Text(pDX, IDC_EDIT_TICKETNUM, m_edit_ticket_num);
	DDV_MinMaxInt(pDX, m_edit_ticket_num, 1, 10000);
}


BEGIN_MESSAGE_MAP(QueryDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_QUERY, &QueryDlg::OnBnClickedButtonQuery)
	ON_BN_CLICKED(IDC_BUTTON_SALE, &QueryDlg::OnBnClickedButtonSale)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &QueryDlg::OnHdnItemclickListQuery)
END_MESSAGE_MAP()


// QueryDlg ��Ϣ�������


void QueryDlg::OnBnClickedButtonQuery()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	//��������
	TCHAR* old_locale = _tcsdup(_tsetlocale(LC_CTYPE, NULL));
	_tsetlocale(LC_CTYPE, _T("chs"));

	if (!hasViewList)
	{
		CRect rect;
		m_listCtrl_Query.GetClientRect(rect);
		CString title[8] = { _T("���"), _T("����ʱ��"), _T("���վ"), _T("�յ�վ"), _T("�г�ʱ��"), _T("�����"), _T("�Ѷ�Ʊ����"), _T("״̬") };

		for (int i = 0; i < 8; i++)
		{
			m_listCtrl_Query.InsertColumn(i, title[i], 0, rect.Width() / 8, i);
		}
	}
	if (hasViewList)
		m_listCtrl_Query.DeleteAllItems();


	CStdioFile csf_read(_T("res/ticketInfo.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeReadWrite);
	int numOfline = 0;
	csf_read.SeekToBegin();
	CString trainInfo[10000];
	while ((csf_read.ReadString(trainInfo[numOfline])))
	{
		numOfline++;
	}
	csf_read.Close();//�ļ���ȡ�������ر�
	//�������ѯ��������ϵ������listCtr
	int kl = 0;
	for (int i = 0; i < numOfline; i++)
	{
		CString *com = splitS(trainInfo[i]);
		if (com[0] == m_edit_txt_query || com[3] == m_edit_txt_query)
		{
			m_listCtrl_Query.InsertItem(kl, com[0]);
			
			for (int j = 1; j < 7; j++)
			{
				m_listCtrl_Query.SetItemText(kl, j, com[j]);
			}
			if (myOverTime(com[1]))
				m_listCtrl_Query.SetItemText(kl, 7, _T("�ѷ�����"));
			else
			{
				m_listCtrl_Query.SetItemText(kl, 7, _T("δ����"));
			}
			kl++;
		}
	}
	if (kl == 0)
		MessageBox(_T("δ��ѯ�������"));
	//ʼ�ո����ȱ�ѡ�еı���
	m_listCtrl_Query.ModifyStyle(0L, LVS_SHOWSELALWAYS);
	m_listCtrl_Query.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	hasViewList = true;
	
	_tsetlocale(LC_CTYPE, old_locale);
	free(old_locale);
}


BOOL QueryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	hasViewList = false;
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}


void QueryDlg::OnBnClickedButtonSale()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	TCHAR* old_locale = _tcsdup(_tsetlocale(LC_CTYPE, NULL));
	_tsetlocale(LC_CTYPE, _T("chs"));

	UpdateData(TRUE);

	CString str;
	int lineSelect = -1;
	for (int i = 0; i<m_listCtrl_Query.GetItemCount(); i++)
	{
		if (m_listCtrl_Query.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
		{
			lineSelect = i;
		}
	}
	CString idSelect = m_listCtrl_Query.GetItemText(lineSelect, 0);
	
	//��ȡ�ļ�
	CStdioFile csf_read(_T("res/ticketInfo.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeRead);
	CString trainInfos[10000];
	int num = 0;
	while (csf_read.ReadString(trainInfos[num]))
	{
		num++;
	}
	csf_read.Close();
	
	//�ж��Ƿ������Ʊ
	for (int i = 0; i < num; i++)
	{
		CString *com = splitS(trainInfos[i]);

		if (com[0] == idSelect)
		{
			int numOfPassenger = _ttoi(com[5]);
			int ticketOrdered = _ttoi(com[6]);
			//�����Ʊ�㹻����û�г���ʱ�䣬���¹�Ʊ����
			if (myOverTime(com[1]))
			{
				MessageBox(_T("������İ���Ѿ�������\n������ѡ��~"));
				return;
			}
			if (ticketOrdered + m_edit_ticket_num <= numOfPassenger&&!myOverTime(com[1]))
			{
				ticketOrdered += m_edit_ticket_num;
				com[6].Format(_T("%d"), ticketOrdered);
				trainInfos[i]= cat(com);
				//д���ļ�


				CStdioFile  csf_write( _T("res/ticketInfo.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeReadWrite);
				for (int j = 0; j < num; j++)
				{
					csf_write.WriteString(trainInfos[j]+"\n");
				}
				csf_write.Flush();
				csf_write.Close();
				CString csBuy;
				csBuy.Format(_T("%d"), m_edit_ticket_num);
				MessageBox(csBuy + _T("��Ʊ����ɹ���"));
				return;
			}
			else if (numOfPassenger<ticketOrdered)
			{
				MessageBox(_T("��Ʊ����̫��,����������"));
				return;
			}
			else
			{
				MessageBox(_T("�Ѿ�û����Ʊ��=_="));
				return;
			}
		}
	}

	_tsetlocale(LC_CTYPE, old_locale);
	free(old_locale);
}


void QueryDlg::OnHdnItemclickListQuery(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	MessageBox(_T("�����ˡ���"));
}
