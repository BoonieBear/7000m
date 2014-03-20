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
//fileType--文件名的开头字符
//fileSize--文件的最大长度，超过则开新文件
//MAXLen----一次写入的最大字节数
//WriteLen--多次写入累计长度超过WriteLen则写入磁盘
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
	m_sFileType+=str;//文件创建时间

	m_dLpOffset=0;    //清空暂存缓冲区
	m_nFileSeries=1;  //文件名的序列号从1开始

	CreateFileName();//生成第一个文件名
}

//---------------------------------------------------------------------------
CFileData::~CFileData()
{
	CloseFile();
}
//-------------------自动生成文件名------------------------------------------
CString CFileData::CreateFileName()
{
	CString str=_T("");
	m_sFileName=m_sFileType;//文件类型
	str.Format("%03d",m_nFileSeries);
	m_nFileSeries++;//序列号自动累加
	m_sFileName+=str;//文件序列号
	str=_T(".dat");
	m_sFileName+=str;//文件后缀名

#ifdef _DEBUG
	if(m_sFileType=="")
		afxDump<<"没有初始化文件\n";
#endif

	return m_sFileName;

}
//以二进制添加模式打开文件
BOOL CFileData::InitFile()
{
	if(m_sFileName=="")
		return FALSE;
	m_fFile=fopen(m_Path+m_sFileName,"ab");
	if(m_fFile==NULL)
	{
#ifdef _DEBUG
		afxDump<<"文件不能打开\n";
#endif
		return FALSE;
	}
	return TRUE;
}
void CFileData::SetPath(CString path)
{
	m_Path=path;
}
//------------------------数据写入文件-----------------------------------------------------
//fwrite函数在数据长度超过65536时函数会异常，每次存储的长度是4096的整数倍，零头会丢失
//本程序把每次写入的长度控制在32768以内，以解决上述问题
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

//------------------------存文件-----------------------------------------------------
//存储完毕后关闭文件，以防止程序崩溃时信息全部丢失。
BOOL CFileData::SaveFile(const char *scr,DWORD Len)
{
	if( m_dLpOffset+Len >= m_dWriteLen ) //若缓冲区中的数据加上新来的数据够长度，则写磁盘文件
	{			

		if (m_dLpOffset>m_dWriteLen)//just for safe
		{
			m_dLpOffset=0;
			m_dWriteLen= WRITESIZE;
		}
		
		if( InitFile() ==FALSE)	//以二进制添加模式打开文件
			return FALSE;
		
		if( m_dLpOffset >0 )  //缓冲区中有数据
		{
			WriteFile(buf,m_dLpOffset);//则先把缓冲区中的内容写入文件
			m_dLpOffset=0;             //清空缓冲区
		}

		WriteFile(scr,Len);//再把当前输入的内容写入文件

		//文件够大则生成一个新文件
		if(ftell(m_fFile)>m_dFileSize)
		{
			CreateFileName();
		}
		
		fclose(m_fFile);//关闭文件
	}
	else//如果数据较少，则先在缓冲区中暂存，攒够一定数量后磁盘，减少存盘的频率
	{   //m_dWriteLen 必须比缓冲区长度小，否则会溢出
		memcpy(buf+m_dLpOffset,scr,Len*sizeof(char));
		m_dLpOffset+=Len;
	}
	return TRUE;
}


BOOL CFileData::CloseFile()
{
	
	if(m_dLpOffset>0)	//暂存缓冲区中有数据待处理
	{
		if(InitFile()==FALSE)//以二进制添加模式打开文件
			return FALSE;
		
		WriteFile(buf,m_dLpOffset);//将缓冲区中的数据写入磁盘文件
		m_dLpOffset=0;	//清空缓冲区

		fclose(m_fFile);//关闭文件
	}
	m_fFile = NULL;
	m_nFileSeries=1;
	return TRUE;
}
