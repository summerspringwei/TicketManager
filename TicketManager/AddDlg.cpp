// AddDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "TicketManager.h"
#include "AddDlg.h"
#include "afxdialogex.h"
#include "locale.h"
#include "TicketInfo.h"
#include "funcs.h"

// AddDlg �Ի���

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


// AddDlg ��Ϣ�������


void AddDlg::OnBnClickedButtonAdd()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������

	UpdateData(TRUE);
	//���õ�����Ϣ����������
	TCHAR* old_locale = _tcsdup(_tsetlocale(LC_CTYPE, NULL));
	_tsetlocale(LC_CTYPE, _T("chs"));
	


	CString id, startTime, startStation, stopStation, tripTime, numOfPassenger;
	//ת����ʽ
	id.Format(_T("%d"), m_edit_txt_id);
	numOfPassenger.Format(_T("%d"), m_edit_txt_numOfPassenger);
	//�ж���ͬ��id�Ƿ��Ѿ�����----δ��ɣ�
	
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
			MessageBox(_T("id�Ѿ����ڣ�¼��ʧ�ܣ�"));
			return;
		}
	}
	csf_read.Close();
	

	

	CString strToWrite=NULL;
	

	//�ж������Ƿ�Ϸ�
	if (m_edit_txt_id == 0 || m_edit_txt_startTime == "" || m_edit_txt_startStation == "" || m_edit_txt_stopStaion == "")
	{
		MessageBox(_T("����������в���Ϊ�գ�����\n����������"));
		return;
	}
	if (m_edit_txt_numOfPassenger <= 0)
	{
		MessageBox(_T("�˿���������С�ڻ��ߵ���0������\n����������"));
		return;
	}

	//��editControl���������ӵ�һ���ַ���
	strToWrite.Append(id + " " + m_edit_txt_startTime + " "+m_edit_txt_startStation+" "+m_edit_txt_stopStaion+" "
		+m_edit_txt_tripTime+" "+numOfPassenger+" "+"0");
	MessageBox(strToWrite+"¼����ɣ�");

	//д���ļ�
	CStdioFile csf_write(_T("res/ticketInfo.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate|CStdioFile::modeReadWrite);
	csf_write.SeekToEnd();//���ļ�ĩβ�������
	csf_write.WriteString(strToWrite+"\n");
	csf_write.Flush();
	csf_write.Close();

	//������Ϣ�����ͷ�
	_tsetlocale(LC_CTYPE, old_locale);
	free(old_locale);

}
