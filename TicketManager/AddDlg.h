#pragma once
#include "afxwin.h"


// AddDlg 对话框

class AddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(AddDlg)

public:
	AddDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~AddDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_ADD };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_edit_id;
	int m_edit_txt_id;
	CEdit m_edit_startTime;
	CString m_edit_txt_startTime;
	CEdit m_edit_startStation;
	CString m_edit_txt_startStation;
	CEdit m_edit_stopStation;
	CString m_edit_txt_stopStaion;
	CEdit m_edit_tripTime;
	CString m_edit_txt_tripTime;
	CEdit m_edit_numOfPassenger;
	int m_edit_txt_numOfPassenger;
	afx_msg void OnBnClickedButtonAdd();
};
