#pragma once
class TicketInfo
{
public:
	TicketInfo();
	~TicketInfo();
	int id;
	CString startTime;
	CString startStation;
	CString stopStation;
	double tripTime;
	int numOfPassenger;
	int tickedOrdered;
	CString* readInfos(CStdioFile csf,int *num);

	
};

