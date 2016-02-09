#include "stdafx.h"
#include "locale.h"

//函数功能 按照空格讲字符串切分并返回一个字符串数组
CString* splitS(CString s)
{
	TCHAR* old_locale = _tcsdup(_tsetlocale(LC_CTYPE, NULL));
	_tsetlocale(LC_CTYPE, _T("chs"));//设置地域信息为中国，处理中文乱码的问题

	CString *trainInfos = new CString[7];//保存返回的字符串数组
	CString reg =CString(" ");//设置按照空格切分
	int index = 0,j=0;
	for (int i = 0; i < s.GetLength(); i++)
	{
		if (s.GetAt(i) == reg)//每次遇到空格
		{
			trainInfos[index++] = s.Mid(j, (i - j));//讲空格的位置很上次记录的空格之间的字符串截下
			j = i+1;
		}
	}
	trainInfos[index] = s.Mid(j, s.GetLength() - j);//最后一次的

	_tsetlocale(LC_CTYPE, old_locale);
	free(old_locale);//释放地域设置
	return trainInfos;
	
}

CString *fileRead(int *num)
{
	TCHAR* old_locale = _tcsdup(_tsetlocale(LC_CTYPE, NULL));
	_tsetlocale(LC_CTYPE, _T("chs"));

	CStdioFile csf_read(_T("res/ticketInfo.txt"), CStdioFile::modeCreate | CStdioFile::modeNoTruncate | CStdioFile::modeReadWrite);

	CString *trainInfos = new CString[10000];
	*num = 0;
	while (csf_read.ReadString(trainInfos[*num]))
	{
		*num++;
	}
	csf_read.Close();

	_tsetlocale(LC_CTYPE, old_locale);
	free(old_locale);
	return trainInfos;
}

//函数功能：判断传入的时间是否超过了当前时间
bool myOverTime(CString stime)
{
	/*
		Èç¹ûµ±Ç°Ê±¼ä³¬¹ýÁË²ÎÊýÊ±¼ä£¬Ôò·µ»Øturu
	*/
	if (stime.GetLength() < 5)//判断时间字符串是否合法
	{
		return false;
	}
	int t = 0;
	t += ((char)stime.GetAt(0) - '0') * 10 * 60 + ((char)stime.GetAt(1) - '0') * 60 + ((char)stime.GetAt(3) - '0') * 10 + ((char)stime.GetAt(4) - '0');//讲
	CTime ct=CTime::GetCurrentTime();
	int currentTime = ct.GetHour() * 60 + ct.GetMinute();
	if (t <= currentTime)
		return true;
	else
	{
		return false;
	}
}

CString cat(CString *com)
{
	TCHAR* old_locale = _tcsdup(_tsetlocale(LC_CTYPE, NULL));
	_tsetlocale(LC_CTYPE, _T("chs"));

	CString s;
	for (int i = 0; i < 6; i++)
		s.Append(com[i] + " ");
	s.Append(com[6]);

	_tsetlocale(LC_CTYPE, old_locale);
	free(old_locale);
	return s;
}