#pragma once


// QuitDlg �Ի���

class QuitDlg : public CDialogEx
{
	DECLARE_DYNAMIC(QuitDlg)

public:
	QuitDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~QuitDlg();

// �Ի�������
	enum { IDD = IDD_DIALOG_QUIT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString m_edit_quit_id;
	int m_edit_quit_num;
	afx_msg void OnBnClickedButtonQuit();
};
