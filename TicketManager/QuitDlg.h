#pragma once


// QuitDlg 对话框

class QuitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(QuitDlg)

public:
	QuitDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~QuitDlg();

// 对话框数据
	enum { IDD = IDD_DIALOG_QUIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_edit_quit_id;
	int m_edit_quit_num;
	afx_msg void OnBnClickedButtonQuit();
};
