// Check.cpp: implementation of the CCheck class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Check.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCheck::CCheck()
{
	m_bFlag=FALSE;
	//m_sFullData=_T("");
	m_nDataLen=0;
}

CCheck::~CCheck()
{

}
//------------��ȡ������һ֡���ݣ�������������������������
BOOL CCheck::IsFull()
{

	int DataLen=DataMem.GetDataLen();//�õ����������ܵ����ݳ���

	BOOL eFlag=FALSE;
	int count=0;

	//AfxMessageBox("CCheck::GetFull()");

	for(int i=0;i<DataLen;i++)
	{
		char data;

		if(m_nDataLen>199) //���ݳ�������,��m_sFullData��λ��199bits��
		{
			m_nDataLen=0;
			m_bFlag=FALSE;
			break;
		}

		DataMem.ReadData(&data,1);
		switch(data)
		{
		case'$'://�ҵ�֡ͷ
			/*if(!m_bFlag)*/
			m_bFlag=TRUE;//��֡ͷ
			m_nDataLen=0;//m_sFullData��λ
			m_sFullData[m_nDataLen]=data;//д������
			m_nDataLen++;
			//AfxMessageBox("�ҵ�֡ͷ");
			break;
		case'\r':
			if(!m_bFlag) break;//û��֡ͷ��д��
			eFlag=TRUE;//�ҵ��س�
			count=i;
			m_sFullData[m_nDataLen]=data;
			m_nDataLen++;
			break;
		case'\n':
			if(!m_bFlag) break;//û��֡ͷ��д��

			if(!eFlag) //û�лس���־
			{
				m_sFullData[m_nDataLen]=data;
				m_nDataLen++;
				break;
			}
			else//�лس���־
			{
				if(i-count==1)//���ϸ��ַ�Ϊ�س�
				{
					eFlag=FALSE;
					m_sFullData[m_nDataLen]=data;
					m_nDataLen++;
					m_bFlag=FALSE;
					return TRUE;//�Ѿ�ȡ��������һ֡
				}
				eFlag=FALSE;
				m_sFullData[m_nDataLen]=data;
				m_nDataLen++;
				break;
			}
		default:
			if(!m_bFlag) break;//û��֡ͷ��д��
			m_sFullData[m_nDataLen]=data;
			m_nDataLen++;
		}
	}

	return FALSE;//û��ȡ��������һ֡����

}

//-------------�������ݺ�-----------------------------------------
BOOL CCheck::IsCorrect()
{
	int sum=m_sFullData[1];
	int sum1=0;
	CString str;
	int i=0;

	if(m_nDataLen<8 || m_sFullData[m_nDataLen-5]!='*')
	{
		m_nDataLen=0;
		m_bFlag=FALSE;
		//AfxMessageBox("û���ҵ�*");
		return FALSE;
	}

	for(i=0;i<2;i++)
	{
		char ch=m_sFullData[m_nDataLen-4+i];
		if(('0'<=ch)&(ch<='9'))	 
		{
			sum1=sum1+(ch-48)*(((1-i)<<4)+i);
				
			//str.Format("����У�����%d",sum1);
			//AfxMessageBox(str);
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
//				AfxMessageBox("���ݸ�ʽ����");
				m_nDataLen=0;
				m_bFlag=FALSE;
				return FALSE;
			}
		}
	}

	/*str.Format("У�����%d",sum1);
	AfxMessageBox(str);*/

	for(int j=2;j<m_nDataLen-5;j++)//��$��ʼУ�飬�����20090629
	{
		sum=sum^m_sFullData[j];
	}
		
	/*str.Format("�������%d",sum);
	AfxMessageBox(str);*/

	if(sum!=sum1)
	{
		m_nDataLen=0;
		m_bFlag=FALSE;
		return FALSE;
	}
	return TRUE;
}

//-------------�����ݷ���ѭ��������-----------------------------------------
int CCheck::WriteData(char *buf,DWORD dwLen)
{
	return DataMem.WriteData(buf,dwLen);//�����յ������ݷ���ѭ����������
}

//----------------------------------------------------------------

void CCheck::GetFullData(char *dest,DWORD &dwLen)
{
	dwLen=m_nDataLen; 
	memcpy(dest,m_sFullData,m_nDataLen*sizeof(char));
	return ;
}

//--------------����֡����--------------------------------------------------

int CCheck::GetLen()
{
	return m_nDataLen;
}
