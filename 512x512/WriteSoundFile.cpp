// WriteSoundFile.cpp : implementation file
//

#include "stdafx.h"
#include <mmsystem.h>
#include "ACSDlg.h"
#include "WriteSoundFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWriteSoundFile

IMPLEMENT_DYNCREATE(CWriteSoundFile, CWinThread)

CWriteSoundFile::CWriteSoundFile()
{
}

CWriteSoundFile::~CWriteSoundFile()
{
}

BOOL CWriteSoundFile::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CWriteSoundFile::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CWriteSoundFile, CWinThread)
	//{{AFX_MSG_MAP(CWriteSoundFile)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_THREAD_MESSAGE(WM_WRITESOUNDFILE_FILENAME, CreateWaveFile)
	ON_THREAD_MESSAGE(WM_WRITESOUNDFILE_WRITEBLOCK, WriteToSoundFile)
	ON_THREAD_MESSAGE(WM_WRITESOUNDFILE_CLOSEFILE, CloseSoundFile)
	ON_THREAD_MESSAGE(WM_RECORDSOUND_ENDTHREAD, OnEndThread)

END_MESSAGE_MAP()

LRESULT CWriteSoundFile::CreateWaveFile(WPARAM wParam, LPARAM lParam)
{
	PWRITESOUNDFILE pWriteSoundFile = (PWRITESOUNDFILE) lParam;
	int cbWaveFormatEx = sizeof(WAVEFORMATEX) + pWriteSoundFile->waveFormatEx.cbSize;

	m_hFile = ::mmioOpen(pWriteSoundFile->lpszFileName,NULL, MMIO_CREATE|MMIO_WRITE|MMIO_DENYNONE | MMIO_ALLOCBUF);
	if(!m_hFile)
		return TRUE;

	ZeroMemory(&m_MMCKInfoParent, sizeof(MMCKINFO));
	m_MMCKInfoParent.fccType = mmioFOURCC('W','A','V','E');

	MMRESULT mmResult =  ::mmioCreateChunk( m_hFile,&m_MMCKInfoParent,
							MMIO_CREATERIFF);
	
	ZeroMemory(&m_MMCKInfoChild, sizeof(MMCKINFO));
	m_MMCKInfoChild.ckid = mmioFOURCC('f','m','t',' ');
	m_MMCKInfoChild.cksize = cbWaveFormatEx;
	mmResult = ::mmioCreateChunk(m_hFile, &m_MMCKInfoChild, 0);
	mmResult = ::mmioWrite(m_hFile, (char*)&pWriteSoundFile->waveFormatEx, cbWaveFormatEx); 
	mmResult = ::mmioAscend(m_hFile, &m_MMCKInfoChild, 0);
	m_MMCKInfoChild.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmResult = ::mmioCreateChunk(m_hFile, &m_MMCKInfoChild, 0);
	//Create other files
/*	CString filename,normfile;
	filename.Format("%s",pWriteSoundFile->lpszFileName);
	normfile = filename;
	filename.Replace("wav","8bit");
	normfile.Replace("wav","nor");
	TRY 
	{
		if (!m_h8bitFile.Open( filename, CFile::modeCreate | CFile::modeWrite ))
		{
			m_h8bitFile.m_hFile = CFile::hFileNull;
		}
		
	}
	CATCH (CFileException, e)
	{
		m_h8bitFile.m_hFile = CFile::hFileNull;
	}
	END_CATCH

	TRY 
	{
		if (!m_hNormFile.Open( normfile, CFile::modeCreate | CFile::modeWrite ))
		{
			m_hNormFile.m_hFile = CFile::hFileNull;
		}
	}
	CATCH (CFileException, e)
	{
		m_hNormFile.m_hFile = CFile::hFileNull;
	}
	END_CATCH
	*/
	return ERROR_SUCCESS;

}
LRESULT CWriteSoundFile::WriteToSoundFile(WPARAM wParam, LPARAM lParam)
{
	LPWAVEHDR lpHdr = (LPWAVEHDR) lParam;
	int cbLength = lpHdr->dwBufferLength;
	if(lpHdr)
	{
		char *soundbuffer = (char*) lpHdr->lpData;
		if(m_hFile && soundbuffer)
			::mmioWrite(m_hFile, soundbuffer, cbLength);
		if(soundbuffer)
		{
			delete[] (BYTE*) soundbuffer;
			lpHdr->lpData = NULL;
		}
		if(lpHdr)
			delete lpHdr;
		lpHdr = NULL;
	}

	return ERROR_SUCCESS;
}
LRESULT CWriteSoundFile::CloseSoundFile(WPARAM wParam, LPARAM lParam)
{

	if(m_hFile)//¹Ø±ÕÎÄ¼þ
	{
		::mmioAscend(m_hFile, &m_MMCKInfoChild, 0);
		::mmioAscend(m_hFile, &m_MMCKInfoParent, 0);
		::mmioClose(m_hFile, 0);
		m_hFile = NULL;

	}

// 	::PostMessage(hWnd,WMSG_CLOSERECFILE,NULL,NULL);
	
	return ERROR_SUCCESS;
}
LRESULT CWriteSoundFile::OnEndThread(WPARAM wParam, LPARAM lParam)
{
	CloseSoundFile(0,0);
	::PostQuitMessage(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CWriteSoundFile message handlers
