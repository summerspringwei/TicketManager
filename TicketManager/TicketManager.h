
// TicketManager.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTicketManagerApp: 
// �йش����ʵ�֣������ TicketManager.cpp
//

class CTicketManagerApp : public CWinApp
{
public:
	CTicketManagerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTicketManagerApp theApp;