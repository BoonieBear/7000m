// FileData.cpp: implementation of the CFileData class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "FileDataN.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CFileData::CFileData()
{
	Init("", FILESIZE, 200,WRITESIZE);	
}
//-----------------------------------------------------------------------
CFileData::CFileData(CString fileType,DWORD fileSize,DWORD MAXLen,DWORD WriteLen)
{
	Init(fileType, fileSize, MAXLen,WriteLen);
		
}
//---------------------------------------------------------------------------
//fileType--�ļ����Ŀ�ͷ�ַ�
//fileSize--�ļ�����󳤶ȣ����������ļ�
//MAXLen----һ��д�������ֽ���
//WriteLen--���д���ۼƳ��ȳ���WriteLen��д�����
void CFileData::Init(CString fileType, DWORD fileSize, DWORD MAXLen,DWORD WriteLen)
{
	m_sFileType=fileType;
	m_sFileName=_T("");
	m_dFileSize=fileSize;
	m_dMaxLen=MAXLen;
	if(WriteLen<(MAXWRITENUM+1)*WRITESIZE)
		m_dWriteLen=WriteLen;
	else
		m_dWriteLen=(MAXWRITENUM+1)*WRITESIZE;

	m_fFile = NULL;

	CString str=_T("");
	CTime nowtime;
	nowtime = CTime::GetCurrentTime();
	str.Format("%d%02d%02d%02d%02d%02d",nowtime.GetYear(),nowtime.GetMonth(),nowtime.GetDay(),
		nowtime.GetHour(),nowtime.GetMinute(),nowtime.GetSecond());
	m_sFileType+=str;//�ļ�����ʱ��

	m_dLpOffset=0;    //����ݴ滺����
	m_nFileSeries=1;  //�ļ��������кŴ�1��ʼ

	CreateFileName();//���ɵ�һ���ļ���
}

//---------------------------------------------------------------------------
CFileData::~CFileData()
{
	CloseFile();
}
//-------------------�Զ������ļ���------------------------------------------
CString CFileData::CreateFileName()
{
	CString str=_T("");
	m_sFileName=m_sFileType;//�ļ�����
	str.Format("%03d",m_nFileSeries);
	m_nFileSeries++;//���к��Զ��ۼ�
	m_sFileName+=str;//�ļ����к�
	str=_T(".dat");
	m_sFileName+=str;//�ļ���׺��

#ifdef _DEBUG
	if(m_sFileType=="")
		afxDump<<"û�г�ʼ���ļ�\n";
#endif

	return m_sFileName;

}
//�Զ��������ģʽ���ļ�
BOOL CFileData::InitFile()
{
	if(m_sFileName=="")
		return FALSE;
	m_fFile=fopen(m_Path+m_sFileName,"ab");
	if(m_fFile==NULL)
	{
#ifdef _DEBUG
		afxDump<<"�ļ����ܴ�\n";
#endif
		return FALSE;
	}
	return TRUE;
}
void CFileData::SetPath(CString path)
{
	m_Path=path;
}
//------------------------����д���ļ�-----------------------------------------------------
//fwrite���������ݳ��ȳ���65536ʱ�������쳣��ÿ�δ洢�ĳ�����4096������������ͷ�ᶪʧ
//�������ÿ��д��ĳ��ȿ�����32768���ڣ��Խ����������
BOOL CFileData::WriteFile(const char *scr,DWORD Len)
{
	int i,n;
	if(m_fFile==NULL)
	{
		return FALSE;
	}
	for(i=0;i< Len/32768; i++)
	{
		fwrite(scr+i*32768,sizeof(char),32768,m_fFile);
	}
	n=Len - i*32768;
	if(n>0)
		fwrite(scr+i*32768,sizeof(char),n,m_fFile);
	return TRUE;
};

//------------------------���ļ�-----------------------------------------------------
//�洢��Ϻ�ر��ļ����Է�ֹ�������ʱ��Ϣȫ����ʧ��
BOOL CFileData::SaveFile(const char *scr,DWORD Len)
{
	if( m_dLpOffset+Len >= m_dWriteLen ) //���������е����ݼ������������ݹ����ȣ���д�����ļ�
	{			

		if (m_dLpOffset>m_dWriteLen)//just for safe
		{
			m_dLpOffset=0;
			m_dWriteLen= WRITESIZE;
		}
		
		if( InitFile() ==FALSE)	//�Զ��������ģʽ���ļ�
			return FALSE;
		
		if( m_dLpOffset >0 )  //��������������
		{
			WriteFile(buf,m_dLpOffset);//���Ȱѻ������е�����д���ļ�
			m_dLpOffset=0;             //��ջ�����
		}

		WriteFile(scr,Len);//�ٰѵ�ǰ���������д���ļ�

		//�ļ�����������һ�����ļ�
		if(ftell(m_fFile)>m_dFileSize)
		{
			CreateFileName();
		}
		
		fclose(m_fFile);//�ر��ļ�
	}
	else//������ݽ��٣������ڻ��������ݴ棬�ܹ�һ����������̣����ٴ��̵�Ƶ��
	{   //m_dWriteLen ����Ȼ���������С����������
		memcpy(buf+m_dLpOffset,scr,Len*sizeof(char));
		m_dLpOffset+=Len;
	}
	return TRUE;
}


BOOL CFileData::CloseFile()
{
	
	if(m_dLpOffset>0)	//�ݴ滺�����������ݴ�����
	{
		if(InitFile()==FALSE)//�Զ��������ģʽ���ļ�
			return FALSE;
		
		WriteFile(buf,m_dLpOffset);//���������е�����д������ļ�
		m_dLpOffset=0;	//��ջ�����

		fclose(m_fFile);//�ر��ļ�
	}
	m_fFile = NULL;
	m_nFileSeries=1;
	return TRUE;
}
