// QueryDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TicketManager.h"
#include "QueryDlg.h"
#include "afxdialogex.h"
#include "funcs.h"
#include "locale.h"

// QueryDlg 对话框

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


// QueryDlg 消息处理程序


void QueryDlg::OnBnClickedButtonQuery()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	//处理中文
	TCHAR* old_locale = _tcsdup(_tsetlocale(LC_CTYPE, NULL));
	_tsetlocale(LC_CTYPE, _T("chs"));

	if (!hasViewList)
	{
		CRect rect;
		m_listCtrl_Query.GetClientRect(rect);
		CString title[8] = { _T("班次"), _T("发车时间"), _T("起点站"), _T("终点站"), _T("行车时间"), _T("额定载量"), _T("已订票人数"), _T("状态") };

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
	csf_read.Close();//文件读取结束，关闭
	//查找与查询内容相符合的输出到listCtr
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
				m_listCtrl_Query.SetItemText(kl, 7, _T("已发车！"));
			else
			{
				m_listCtrl_Query.SetItemText(kl, 7, _T("未发出"));
			}
			kl++;
		}
	}
	if (kl == 0)
		MessageBox(_T("未查询到结果！"));
	//始终高亮度被选中的表项
	m_listCtrl_Query.ModifyStyle(0L, LVS_SHOWSELALWAYS);
	m_listCtrl_Query.SetExtendedStyle(LVS_EX_FULLROWSELECT);

	hasViewList = true;
	
	_tsetlocale(LC_CTYPE, old_locale);
	free(old_locale);
}


BOOL QueryDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	hasViewList = false;
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void QueryDlg::OnBnClickedButtonSale()
{
	// TODO:  在此添加控件通知处理程序代码
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
	
	//读取文件
	CStdioFile csf_read(_T("res/ticketInfo.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeRead);
	CString trainInfos[10000];
	int num = 0;
	while (csf_read.ReadString(trainInfos[num]))
	{
		num++;
	}
	csf_read.Close();
	
	//判断是否可以买票
	for (int i = 0; i < num; i++)
	{
		CString *com = splitS(trainInfos[i]);

		if (com[0] == idSelect)
		{
			int numOfPassenger = _ttoi(com[5]);
			int ticketOrdered = _ttoi(com[6]);
			//如果余票足够并且没有超过时间，更新购票人数
			if (myOverTime(com[1]))
			{
				MessageBox(_T("所购买的班次已经发车！\n请重新选购~"));
				return;
			}
			if (ticketOrdered + m_edit_ticket_num <= numOfPassenger&&!myOverTime(com[1]))
			{
				ticketOrdered += m_edit_ticket_num;
				com[6].Format(_T("%d"), ticketOrdered);
				trainInfos[i]= cat(com);
				//写回文件


				CStdioFile  csf_write( _T("res/ticketInfo.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeReadWrite);
				for (int j = 0; j < num; j++)
				{
					csf_write.WriteString(trainInfos[j]+"\n");
				}
				csf_write.Flush();
				csf_write.Close();
				CString csBuy;
				csBuy.Format(_T("%d"), m_edit_ticket_num);
				MessageBox(csBuy + _T("张票购买成功！"));
				return;
			}
			else if (numOfPassenger<ticketOrdered)
			{
				MessageBox(_T("购票数量太多,请重新输入"));
				return;
			}
			else
			{
				MessageBox(_T("已经没有余票！=_="));
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
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	MessageBox(_T("单机了。。"));
}
