#include "stdafx.h"
#include "TicketInfo.h"


TicketInfo::TicketInfo()
{
}


TicketInfo::~TicketInfo()
{
}
CString* TicketInfo::readInfos(CStdioFile csf,int *num)
{
	CString *trainInfos = new CString[10000];
	while ((csf.ReadString(trainInfos[(*num)++])))
	{
		
	}
	csf.Close();
	return trainInfos;
}