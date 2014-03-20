// Check.h: interface for the CCheck class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECK_H__DEC99DDF_8295_4948_8CF9_500420EA452A__INCLUDED_)
#define AFX_CHECK_H__DEC99DDF_8295_4948_8CF9_500420EA452A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "cyclemem.h"

class CCheck  
{
public:
	CCheck();
	virtual ~CCheck();

	BOOL IsFull();//是否完整一帧数据
	BOOL IsCorrect();//数据帧校验是否正确
public:
	int GetLen();//数据帧长度
	int WriteData(char *buf,DWORD dwLen);//将要检验的数据存入循环缓冲区
	void GetFullData(char *dest,DWORD &dwLen);//获取完整的一帧数据
	char m_sFullData[200];//完整的一帧数据
	int m_nDataLen;//帧的数据长度
	BOOL m_bFlag;//是否有‘$'
private:
	
	CCycleMem<char,2000,sizeof(char)> DataMem;//存放原数据
	
	

};

#endif // !defined(AFX_CHECK_H__DEC99DDF_8295_4948_8CF9_500420EA452A__INCLUDED_)
