#pragma once
#include "afxwin.h"
#include "afxcmn.h"
// QueryDlg �Ի���

class QueryDlg : public CDialogEx
{
	DECLARE_DYNAMIC(QueryDlg)

public:
	QueryDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~QueryDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_QUERY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_query;
	CString m_edit_txt_query;
	CListCtrl m_listCtrl_Query;
	afx_msg void OnBnClickedButtonQuery();
	bool hasViewList;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSale();
	afx_msg void OnHdnItemclickListQuery(NMHDR *pNMHDR, LRESULT *pResult);
	int m_edit_ticket_num;
};
