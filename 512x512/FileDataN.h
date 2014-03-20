// FileData.h: interface for the CFileData class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEDATA_H__3A0EDFF6_F88B_412F_B3BA_807D77AC08DB__INCLUDED_)
#define AFX_FILEDATA_H__3A0EDFF6_F88B_412F_B3BA_807D77AC08DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "data_define.h"
class CFileData  
{
public:
	void Init(CString fileType,DWORD fileSize,DWORD MAXLen,DWORD WriteLen);
	CFileData();
	CFileData(CString fileType,DWORD fileSize,DWORD MAXLen,DWORD WriteLen);
	virtual ~CFileData();

	BOOL WriteFile(const char *scr,DWORD Len);
	BOOL SaveFile(const char *scr,DWORD Len);
	BOOL CloseFile();
    void SetPath(CString path);
	CString m_sFileType;//文件类型
	CString m_Path;  //文件路径，以'\'结束
	CString m_sFileName;//文件名：文件类型(GPS)＋序列号(01)＋日期(_20030625)＋时间(_010634)
	//（GPS01_20030625_010634）,为格林威治时间（hhmmss)

private:
	BOOL InitFile();//文件初始化，对各种指针赋初值
	CString CreateFileName();//自动生成文件名


private:
	LONG m_dFileSize;//文件大小
	LONG m_dMaxLen;//一次写入数据的最大长度
	LONG m_dWriteLen;//一次写入硬盘的最大长度

	
	
	int m_nFileSeries;//文件序列号
	LONG m_dLpOffset;//写位置与文件头位置的偏移
	char buf[100*WRITESIZE];//临时缓冲区

	FILE * m_fFile;//磁盘文件

};

#endif // !defined(AFX_FILEDATA_H__3A0EDFF6_F88B_412F_B3BA_807D77AC08DB__INCLUDED_)
