// AddDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "TicketManager.h"
#include "AddDlg.h"
#include "afxdialogex.h"
#include "locale.h"
#include "TicketInfo.h"
#include "funcs.h"

// AddDlg 对话框

IMPLEMENT_DYNAMIC(AddDlg, CDialogEx)

AddDlg::AddDlg(CWnd* pParent /*=NULL*/)
: CDialogEx(AddDlg::IDD, pParent)
, m_edit_txt_id(0)
, m_edit_txt_startTime(_T(""))
, m_edit_txt_startStation(_T(""))
, m_edit_txt_stopStaion(_T(""))
, m_edit_txt_tripTime(_T(""))
	, m_edit_txt_numOfPassenger(0)
{

}

AddDlg::~AddDlg()
{
}

void AddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_ID, m_edit_id);
	DDX_Text(pDX, IDC_EDIT_ID, m_edit_txt_id);
	DDV_MinMaxInt(pDX, m_edit_txt_id, 0, 100000);
	DDX_Control(pDX, IDC_EDIT_STARTTIME, m_edit_startTime);
	DDX_Text(pDX, IDC_EDIT_STARTTIME, m_edit_txt_startTime);
	DDV_MaxChars(pDX, m_edit_txt_startTime, 5);
	DDX_Control(pDX, IDC_EDIT_STARTSTATION, m_edit_startStation);
	DDX_Text(pDX, IDC_EDIT_STARTSTATION, m_edit_txt_startStation);
	DDV_MaxChars(pDX, m_edit_txt_startStation, 20);
	DDX_Control(pDX, IDC_EDIT_STOPSTATION, m_edit_stopStation);
	DDX_Text(pDX, IDC_EDIT_STOPSTATION, m_edit_txt_stopStaion);
	DDV_MaxChars(pDX, m_edit_txt_stopStaion, 20);
	DDX_Control(pDX, IDC_EDIT_TRIPTIME, m_edit_tripTime);
	DDX_Text(pDX, IDC_EDIT_TRIPTIME, m_edit_txt_tripTime);
	DDV_MaxChars(pDX, m_edit_txt_tripTime, 30);
	DDX_Control(pDX, IDC_EDIT_NUMOFPASSENGER, m_edit_numOfPassenger);
	DDX_Text(pDX, IDC_EDIT_NUMOFPASSENGER, m_edit_txt_numOfPassenger);
	DDV_MinMaxInt(pDX, m_edit_txt_numOfPassenger, 0, 10000);
}


BEGIN_MESSAGE_MAP(AddDlg, CDialogEx)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &AddDlg::OnBnClickedButtonAdd)
END_MESSAGE_MAP()


// AddDlg 消息处理程序


void AddDlg::OnBnClickedButtonAdd()
{
	// TODO:  在此添加控件通知处理程序代码

	UpdateData(TRUE);
	//设置地域信息，处理中文
	TCHAR* old_locale = _tcsdup(_tsetlocale(LC_CTYPE, NULL));
	_tsetlocale(LC_CTYPE, _T("chs"));
	


	CString id, startTime, startStation, stopStation, tripTime, numOfPassenger;
	//转换格式
	id.Format(_T("%d"), m_edit_txt_id);
	numOfPassenger.Format(_T("%d"), m_edit_txt_numOfPassenger);
	//判断相同的id是否已经存在----未完成！
	
	CStdioFile csf_read(_T("res/ticketInfo.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeReadWrite);
	CString trainInfos[10000];
	int num = 0;
	
	while (csf_read.ReadString(trainInfos[num]))
	{
		num++;
	}
	
	for (int i = 0; i < num; i++)
	{
		CString *com = splitS(trainInfos[i]);
		
		if (com[0] == id)
		{
			MessageBox(_T("id已经存在！录入失败！"));
			return;
		}
	}
	csf_read.Close();
	

	

	CString strToWrite=NULL;
	

	//判断输入是否合法
	if (m_edit_txt_id == 0 || m_edit_txt_startTime == "" || m_edit_txt_startStation == "" || m_edit_txt_stopStaion == "")
	{
		MessageBox(_T("输入的内容中不能为空！！！\n请重新输入"));
		return;
	}
	if (m_edit_txt_numOfPassenger <= 0)
	{
		MessageBox(_T("乘客数量不能小于或者等于0！！！\n请重新输入"));
		return;
	}

	//将editControl的内容连接到一个字符串
	strToWrite.Append(id + " " + m_edit_txt_startTime + " "+m_edit_txt_startStation+" "+m_edit_txt_stopStaion+" "
		+m_edit_txt_tripTime+" "+numOfPassenger+" "+"0");
	MessageBox(strToWrite+"录入完成！");

	//写入文件
	CStdioFile csf_write(_T("res/ticketInfo.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate|CStdioFile::modeReadWrite);
	csf_write.SeekToEnd();//向文件末尾添加内容
	csf_write.WriteString(strToWrite+"\n");
	csf_write.Flush();
	csf_write.Close();

	//地域信息设置释放
	_tsetlocale(LC_CTYPE, old_locale);
	free(old_locale);

}
