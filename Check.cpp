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
//------------获取完整的一帧数据－－－－－－－－－－－－－
BOOL CCheck::IsFull()
{

	int DataLen=DataMem.GetDataLen();//得到缓冲区中总的数据长度

	BOOL eFlag=FALSE;
	int count=0;

	//AfxMessageBox("CCheck::GetFull()");

	for(int i=0;i<DataLen;i++)
	{
		char data;

		if(m_nDataLen>199) //数据超长放弃,将m_sFullData复位（199bits）
		{
			m_nDataLen=0;
			m_bFlag=FALSE;
			break;
		}

		DataMem.ReadData(&data,1);
		switch(data)
		{
		case'$'://找到帧头
			/*if(!m_bFlag)*/
			m_bFlag=TRUE;//有帧头
			m_nDataLen=0;//m_sFullData复位
			m_sFullData[m_nDataLen]=data;//写入数据
			m_nDataLen++;
			//AfxMessageBox("找到帧头");
			break;
		case'\r':
			if(!m_bFlag) break;//没有帧头不写入
			eFlag=TRUE;//找到回车
			count=i;
			m_sFullData[m_nDataLen]=data;
			m_nDataLen++;
			break;
		case'\n':
			if(!m_bFlag) break;//没有帧头不写入

			if(!eFlag) //没有回车标志
			{
				m_sFullData[m_nDataLen]=data;
				m_nDataLen++;
				break;
			}
			else//有回车标志
			{
				if(i-count==1)//是上个字符为回车
				{
					eFlag=FALSE;
					m_sFullData[m_nDataLen]=data;
					m_nDataLen++;
					m_bFlag=FALSE;
					return TRUE;//已经取到完整的一帧
				}
				eFlag=FALSE;
				m_sFullData[m_nDataLen]=data;
				m_nDataLen++;
				break;
			}
		default:
			if(!m_bFlag) break;//没有帧头不写入
			m_sFullData[m_nDataLen]=data;
			m_nDataLen++;
		}
	}

	return FALSE;//没有取到完整的一帧数据

}

//-------------检验数据和-----------------------------------------
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
		//AfxMessageBox("没有找到*");
		return FALSE;
	}

	for(i=0;i<2;i++)
	{
		char ch=m_sFullData[m_nDataLen-4+i];
		if(('0'<=ch)&(ch<='9'))	 
		{
			sum1=sum1+(ch-48)*(((1-i)<<4)+i);
				
			//str.Format("初步校验和是%d",sum1);
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
//				AfxMessageBox("数据格式不对");
				m_nDataLen=0;
				m_bFlag=FALSE;
				return FALSE;
			}
		}
	}

	/*str.Format("校验和是%d",sum1);
	AfxMessageBox(str);*/

	for(int j=2;j<m_nDataLen-5;j++)//从$后开始校验，傅翔改20090629
	{
		sum=sum^m_sFullData[j];
	}
		
	/*str.Format("计算和是%d",sum);
	AfxMessageBox(str);*/

	if(sum!=sum1)
	{
		m_nDataLen=0;
		m_bFlag=FALSE;
		return FALSE;
	}
	return TRUE;
}

//-------------将数据放入循环缓存区-----------------------------------------
int CCheck::WriteData(char *buf,DWORD dwLen)
{
	return DataMem.WriteData(buf,dwLen);//将接收到的数据放入循环缓冲区中
}

//----------------------------------------------------------------

void CCheck::GetFullData(char *dest,DWORD &dwLen)
{
	dwLen=m_nDataLen; 
	memcpy(dest,m_sFullData,m_nDataLen*sizeof(char));
	return ;
}

//--------------数据帧长度--------------------------------------------------

int CCheck::GetLen()
{
	return m_nDataLen;
}
