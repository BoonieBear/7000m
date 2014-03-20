// PlayMMSound.cpp : implementation file
//

#include "stdafx.h"
#include "ACSDlg.h"
#include "PlaySound.h"
#include "PlayMMSound.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlayMMSound
 UINT  PlaySound( LPVOID pParam );

IMPLEMENT_DYNCREATE(CPlayMMSound, CWinThread)

CPlayMMSound::CPlayMMSound()
{
	m_pPlaySound = NULL;
//	pSoundBuffer =NULL;
	strcpy(m_FileName,"");
	ZeroMemory(&m_MMCkInfoParent,sizeof(MMCKINFO));
	ZeroMemory(&m_MMCkInfoChild,sizeof(MMCKINFO));
	m_SoundBuffer = NULL;
	m_pSoundThread = NULL;
	m_hmmio = NULL;
	m_pStopEvent = new CEvent(FALSE,TRUE);
}

CPlayMMSound::~CPlayMMSound()
{
	if(m_SoundBuffer)
		delete m_SoundBuffer;
	if (m_pStopEvent)
	{
		delete m_pStopEvent;
	}
}

BOOL CPlayMMSound::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CPlayMMSound::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPlayMMSound, CWinThread)
	//{{AFX_MSG_MAP(CPlayMMSound)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_THREAD_MESSAGE(WM_PLAYMMSOUND_PLAYFILE,PlaySoundFile)
	ON_THREAD_MESSAGE(WM_PLAYMMSOUND_CLOSEFILE,CloseSoundFile)
	ON_THREAD_MESSAGE(WM_PLAYMMSOUND_PLAYSOUNDPTR,OnPlaySoundPtr)
	ON_THREAD_MESSAGE(WM_PLAYMMSOUND_ENDTHREAD,OnEndThread)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlayMMSound message handlers

LRESULT  CPlayMMSound::PlaySoundFile(WPARAM wParam,LPARAM lParam)
{
	char *pFileName = (char*) lParam;
	strcpy(m_FileName,pFileName);
	if(!OpenSoundFile(m_FileName))
		return FALSE;
	return TRUE;
}
BOOL CPlayMMSound::OpenSoundFile(CString csFileName)
{
	// code taken from Visual C++ Multimedia -- Aitken and Jarol p 122
	
    CloseSoundFile(0,0);
	m_hmmio = mmioOpen((LPSTR)(LPCTSTR)csFileName,NULL,MMIO_READ);
	if(!m_hmmio)
	{
		AfxMessageBox("unable to open Sound MM File");
		return FALSE;
	}
	m_MMCkInfoParent.fccType = mmioFOURCC('W','A','V','E');
	int errorCode = mmioDescend(m_hmmio, &m_MMCkInfoParent,NULL,MMIO_FINDRIFF);
	if(errorCode)
	{
		AfxMessageBox("Error descending into file");
		mmioClose(m_hmmio,0);
		m_hmmio = NULL;
		return FALSE;
	}
	m_MMCkInfoChild.ckid = mmioFOURCC('f','m','t',' ');
	errorCode = mmioDescend(m_hmmio,&m_MMCkInfoChild,&m_MMCkInfoParent,MMIO_FINDCHUNK);
	if(errorCode)
	{
		AfxMessageBox("Error descending in file");
		mmioClose(m_hmmio,0);
		m_hmmio = NULL;
		return FALSE;
	}
	DWORD bytesRead = mmioRead(m_hmmio,(LPSTR)&m_PCMWaveFmtRecord,m_MMCkInfoChild.cksize);
	if(bytesRead < 0)
	{
		AfxMessageBox("Error reading PCM wave format record");
		mmioClose(m_hmmio,0);
		return FALSE;
	}
	
	// open output sound file
	errorCode = mmioAscend(m_hmmio,&m_MMCkInfoChild,0);
	if(errorCode)
	{
		AfxMessageBox("Error ascending in File");
		mmioClose(m_hmmio,0);
		m_hmmio = NULL;
		return FALSE;
	}
	m_MMCkInfoChild.ckid = mmioFOURCC('d','a','t','a');
	errorCode = mmioDescend(m_hmmio,&m_MMCkInfoChild,
		&m_MMCkInfoParent,MMIO_FINDCHUNK);
	if(errorCode)
	{
		AfxMessageBox("error reading data chunk");
		mmioClose(m_hmmio,0);
		m_hmmio = NULL;
		return FALSE;
	}
	m_BytesToRead = m_PCMWaveFmtRecord.nChannels*
		(m_PCMWaveFmtRecord.wBitsPerSample/sizeof(BYTE))
		*m_PCMWaveFmtRecord.nBlockAlign*500;
	if(m_BytesToRead >   
		 m_MMCkInfoChild.cksize)
		 m_BytesToRead = m_MMCkInfoChild.cksize;

	m_bContinuePlaying = TRUE;
	m_pStopEvent->ResetEvent();
	m_pSoundThread = AfxBeginThread(PlaySound,this);

	return TRUE;

}
BYTE* CPlayMMSound::ReadSoundFile(int*dwBytesRead)
{
	if(m_BytesToRead <= 0)
		return NULL;
	if(!m_hmmio)
		return NULL;
	CString str;
//	TRACE("Before New pSoundBuffer\n");
	m_SoundBuffer = new BYTE[m_BytesToRead];
//	str.Format("pSoundBuffer = %x\n",pSoundBuffer);
//	TRACE(str);
//	TRACE("After New pSoundBuffer\n");
	
	if(!m_SoundBuffer)
		return NULL;
	ZeroMemory(m_SoundBuffer,m_BytesToRead*sizeof(BYTE));
//	DWORD dwRetc = mmioRead(m_hmmio,(LPSTR)pSoundBuffer, m_BytesToRead);
	DWORD dwRetc = MAXBUFFSIZE;
	while (dwRetc==MAXBUFFSIZE)
	{	
		WaitForSingleObject(RecvNetpacketEvent,INFINITE);
		
		CCycleMemSync.Lock();
		dwRetc = InVoiceCycleMem->GetDataLen();
		CCycleMemSync.Unlock();	
		Sleep(100);
		continue;
	}
//	TRACE("After GetDataLen();\n");
	if(dwRetc == -1)
	{
		AfxMessageBox("Error reading InVoiceCycleMem\n");
		if(m_SoundBuffer)
			delete[] m_SoundBuffer;
		return NULL;
	}
	
	if (dwRetc>m_BytesToRead)//cycmem数据大于分配内存
	{
		dwRetc = m_BytesToRead;
	}
	
	CCycleMemSync.Lock();
	InVoiceCycleMem->ReadData((LPSTR)m_SoundBuffer,dwRetc);
	CCycleMemSync.Unlock();//
	ResetEvent(RecvNetpacketEvent);
//	TRACE("After read InVoiceCycleMem\n");
	if(dwBytesRead)
		*dwBytesRead = dwRetc;
// 	char debugBuffer[MAX_PATH];
// 	sprintf(debugBuffer,"read %d bytes\n",dwRetc);
// 	TRACE(debugBuffer);
	return m_SoundBuffer;
}
LRESULT  CPlayMMSound::CloseSoundFile(WPARAM wParam,LPARAM lParam)
{
	if(m_pStopEvent)
		m_pStopEvent->SetEvent();
	TRACE("STOP EVENT SET\n");
	m_bContinuePlaying = FALSE;
	if(m_hmmio)
	{
		mmioClose(m_hmmio,0);
		m_hmmio = NULL;
	}
	return TRUE;
}
LRESULT  CPlayMMSound::OnPlaySoundPtr(WPARAM wParam,LPARAM lParam)
{
	CPlaySound*pPlaySound = (CPlaySound*)lParam;
	m_pPlaySound = pPlaySound;
	return TRUE;
}
LRESULT CPlayMMSound::OnEndThread(WPARAM wParam, LPARAM lParam)
{
	CloseSoundFile(0,0);
	::PostQuitMessage(0);
	return TRUE;
}

UINT CPlayMMSound::PlaySound( LPVOID pParam )
{
	CPlayMMSound* pPlayMMSound = (CPlayMMSound*) pParam;
	if(pPlayMMSound &&
			pPlayMMSound->m_pPlaySound)
	{
		pPlayMMSound->m_pPlaySound->PostThreadMessage(WM_PLAYSOUND_STARTPLAYING,GetCurrentThreadId(),(LPARAM)0);
	}

	if(!pPlayMMSound)
		return FALSE;
	if(pPlayMMSound && !pPlayMMSound->m_pPlaySound)
		return FALSE;
	HANDLE hHandle[2];
	hHandle[1] = (HANDLE) pPlayMMSound->m_pPlaySound->m_pSemaphore->m_hObject;
	hHandle[0] = (HANDLE) pPlayMMSound->m_pStopEvent->m_hObject;
	int dwBytesRead = 0;
	BYTE* pSoundBuffer = pPlayMMSound->ReadSoundFile(&dwBytesRead);
	while(pPlayMMSound->m_bContinuePlaying)
	{
		DWORD dwRetc = WaitForMultipleObjects(2,hHandle,FALSE,INFINITE);
		if(dwRetc == WAIT_FAILED)
		{
			DWORD dwRetc = ::GetLastError();
			char errorBuffer[MAX_PATH];
			sprintf(errorBuffer,"WaitForMultipleObjects failed: %d\n",dwRetc);
			TRACE(errorBuffer);

		}
		dwRetc -= WAIT_OBJECT_0;
		if(dwRetc == 0) // stop event;
		{
			TRACE("STOP Event seen\n");
			break;
		}
		if(!pPlayMMSound->m_bContinuePlaying)
			break;
		
		
		WAVEHDR* pWaveHdr = new WAVEHDR;
		ZeroMemory(pWaveHdr,sizeof(WAVEHDR));
//		TRACE("After  new WAVEHDR\n");
		pWaveHdr->lpData = (char*)pSoundBuffer;
		pWaveHdr->dwBufferLength = dwBytesRead;
		if(pPlayMMSound &&
			pPlayMMSound->m_pPlaySound)
		{
			pPlayMMSound->m_pPlaySound->PostThreadMessage(WM_PLAYSOUND_PLAYBLOCK,GetCurrentThreadId(),(LPARAM)pWaveHdr);
//			TRACE("After  call playblock\n");
		}
//		TRACE("After  second ReadSoundFile\n");
		pSoundBuffer = pPlayMMSound->ReadSoundFile(&dwBytesRead);

	}
	if(pPlayMMSound &&
		pPlayMMSound->m_pPlaySound)
	{

	//	pPlayMMSound->m_pPlaySound->PostThreadMessage(WM_PLAYSOUND_STOPPLAYING,GetCurrentThreadId(),(LPARAM)0);
	}


	return TRUE;
}