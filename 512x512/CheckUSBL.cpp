// CheckUSBL.cpp: implementation of the CCheckUSBL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "CheckUSBL.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCheckUSBL::CCheckUSBL()
{

}

CCheckUSBL::~CCheckUSBL()
{

}

BOOL CCheckUSBL::IsCorrect()
{
	int sum=m_sFullData[1];
	int sum1=0;
	CString str;
	int i=0;

	if(m_sFullData[0] !='$'|| m_sFullData[m_nDataLen-5]!='*')
	{
		m_nDataLen=0;
		m_bFlag=FALSE;
		return FALSE;
	}

	for(i=0;i<2;i++)
	{
		char ch=m_sFullData[m_nDataLen-4+i];
		if(('0'<=ch)&(ch<='9'))	 
		{
			sum1=sum1+(ch-48)*(((1-i)<<4)+i);

		}

		else
		{
			if((('a'<=ch)&(ch<='f'))||(('A'<=ch)&(ch<='F')))
			{
				int tmp =i;
				ch = *CharUpper(&ch);
				i=tmp;
				sum1=sum1+(ch-55)*(((1-i)<<4)+i);
			}

			else
			{
				m_nDataLen=0;
				m_bFlag=FALSE;
				return FALSE;
			}
		}
	}

	for(int j=2;j<m_nDataLen-5 ;j++)//从$后开始校验，傅翔改20090629
	{
		sum=sum^m_sFullData[j];
	}
		
	if(sum!=sum1)
	{
		m_nDataLen=0;
		m_bFlag=FALSE;
		return FALSE;
	}
	return TRUE;
}
