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

	BOOL IsFull();//�Ƿ�����һ֡����
	BOOL IsCorrect();//����֡У���Ƿ���ȷ
public:
	int GetLen();//����֡����
	int WriteData(char *buf,DWORD dwLen);//��Ҫ��������ݴ���ѭ��������
	void GetFullData(char *dest,DWORD &dwLen);//��ȡ������һ֡����
	char m_sFullData[200];//������һ֡����
	int m_nDataLen;//֡�����ݳ���
	BOOL m_bFlag;//�Ƿ��С�$'
private:
	
	CCycleMem<char,2000,sizeof(char)> DataMem;//���ԭ����
	
	

};

#endif // !defined(AFX_CHECK_H__DEC99DDF_8295_4948_8CF9_500420EA452A__INCLUDED_)
