
// TicketManagerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxcmn.h"


// CTicketManagerDlg �Ի���
class CTicketManagerDlg : public CDialogEx
{
// ����
public:
	CTicketManagerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_TICKETMANAGER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnMenuAdd();
	CListCtrl m_listCtrl_view_main;
	afx_msg void OnMenuViewMain();
	bool hasViewMain;
	afx_msg void OnMenuAbout();
	afx_msg void OnMenuQueryId();
	afx_msg void OnMuneQueryStopstation();
	afx_msg void OnMenuSale();
	afx_msg void OnMenuQuit();
};
