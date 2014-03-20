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
	CString m_sFileType;//�ļ�����
	CString m_Path;  //�ļ�·������'\'����
	CString m_sFileName;//�ļ������ļ�����(GPS)�����к�(01)������(_20030625)��ʱ��(_010634)
	//��GPS01_20030625_010634��,Ϊ��������ʱ�䣨hhmmss)

private:
	BOOL InitFile();//�ļ���ʼ�����Ը���ָ�븳��ֵ
	CString CreateFileName();//�Զ������ļ���


private:
	LONG m_dFileSize;//�ļ���С
	LONG m_dMaxLen;//һ��д�����ݵ���󳤶�
	LONG m_dWriteLen;//һ��д��Ӳ�̵���󳤶�

	
	
	int m_nFileSeries;//�ļ����к�
	LONG m_dLpOffset;//дλ�����ļ�ͷλ�õ�ƫ��
	char buf[100*WRITESIZE];//��ʱ������

	FILE * m_fFile;//�����ļ�

};

#endif // !defined(AFX_FILEDATA_H__3A0EDFF6_F88B_412F_B3BA_807D77AC08DB__INCLUDED_)
