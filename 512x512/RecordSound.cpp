// RecordSound.cpp : implementation file
//

#include "stdafx.h"
#include <mmsystem.h>
#include "RecordSound.h"
#include "ACSDlg.h"
#include "PlaySound.h"
#include "WriteSoundFile.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRecordSound

IMPLEMENT_DYNCREATE(CRecordSound, CWinThread)


#define MAXINPUTBUFFERS 25

CRecordSound::CRecordSound(int iHertz)
{
	
	m_nInputBuffers = 0;
	m_nMaxInputBuffers = MAXINPUTBUFFERS;
	memset(&m_WaveFormatEx,0x00,sizeof(m_WaveFormatEx));
	m_WaveFormatEx.wFormatTag = WAVE_FORMAT_PCM;
	m_WaveFormatEx.nChannels = 1;
	m_WaveFormatEx.wBitsPerSample = 16;
	m_WaveFormatEx.cbSize = 0;
	m_WaveFormatEx.nSamplesPerSec = iHertz;//20050;
	m_WaveFormatEx.nAvgBytesPerSec = m_WaveFormatEx.nSamplesPerSec
		*(m_WaveFormatEx.wBitsPerSample/8);
	m_WaveFormatEx.nBlockAlign = 
		(m_WaveFormatEx.wBitsPerSample/8)*
		m_WaveFormatEx.nChannels;
//	firsttime =TRUE;
//	m_bRecording = FALSE;
	m_Player = NULL;
	m_Writer = NULL;
}






CRecordSound::~CRecordSound()
{

}

BOOL CRecordSound::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CRecordSound::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CRecordSound, CWinThread)
	//{{AFX_MSG_MAP(CRecordSound)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_THREAD_MESSAGE(WM_RECORDSOUND_STARTRECORDING, OnStartRecording)
	ON_THREAD_MESSAGE(WM_RECORDSOUND_STOPRECORDING, OnStopRecording)
	ON_THREAD_MESSAGE(MM_WIM_DATA, OnSoundData)
	ON_THREAD_MESSAGE(WM_RECORDSOUND_SOUNDPLAYER, OnPtrSoundPlayer)
	ON_THREAD_MESSAGE(WM_RECORDSOUND_ENDTHREAD, OnEndThread)
	ON_THREAD_MESSAGE(WM_RECORDSOUND_WRITERTHREAD,OnPtrSoundWriter)
END_MESSAGE_MAP()



/////////////////////////////////////////////////////////////////////////////
// CRecordSound message handlers
LRESULT CRecordSound::OnPtrSoundPlayer(WPARAM wParam, LPARAM lParam)
{
	m_Player = (CPlaySound*) lParam;
	
	return ERROR_SUCCESS;
}
LRESULT CRecordSound::OnStartRecording(WPARAM wParam, LPARAM lParam)
{
	DWORD mmReturn = 0;

	if(m_bRecording)
		return FALSE;

	if(!m_bRecording)
	{
		// open wavein device
		MMRESULT mmReturn = ::waveInOpen( &m_hRecord, WAVE_MAPPER,
			&m_WaveFormatEx, ::GetCurrentThreadId(), 0, CALLBACK_THREAD);
		if(mmReturn)
		{
			char errorbuffer[MAX_PATH];
			char errorbuffer1[MAX_PATH];
			waveInGetErrorText( mmReturn, 
								errorbuffer,
								MAX_PATH);
			sprintf(errorbuffer1,"WAVEIN:%x:%s",mmReturn,errorbuffer);

			AfxMessageBox(errorbuffer1);  

		}
	
			
		if(!mmReturn)
		{
			for(int i=0; i < m_nMaxInputBuffers; i++)
			{
				LPWAVEHDR lpHdr = CreateWaveHeader();
				mmReturn = ::waveInPrepareHeader(m_hRecord,lpHdr, sizeof(WAVEHDR));
				mmReturn = ::waveInAddBuffer(m_hRecord, lpHdr, sizeof(WAVEHDR));
				m_nInputBuffers++;
			}
			mmReturn = ::waveInStart(m_hRecord);
			if(mmReturn )
		{
			char errorbuffer[MAX_PATH];
			char errorbuffer1[MAX_PATH];
			waveInGetErrorText( mmReturn, 
								errorbuffer,
								MAX_PATH);
			sprintf(errorbuffer1,"WAVEIN:%x:%s",mmReturn,errorbuffer);

			AfxMessageBox(errorbuffer1);  

		}
	
			if(!mmReturn)
			{
				m_bRecording = TRUE;
				if(m_Player)
					m_Player->PostThreadMessage(WM_PLAYSOUND_STARTPLAYING, 0, 0);				
					if(m_Writer)
					{
						char SendFileName[MAX_PATH];
						memset(SendFileName,0,MAX_PATH*sizeof(char));
						pwsf= (PWRITESOUNDFILE) new WRITESOUNDFILE;
						ZeroMemory(pwsf,sizeof(WRITESOUNDFILE));
						char *p = pwsf->lpszFileName;
						CString strdir,fullname;
						strdir.Format("%sXMTvoice",XMTVoiceFile.m_Path);
						CreateFileName(strdir.GetBuffer(0),".wav",SendFileName);
						strcpy(p,SendFileName);
						memcpy(&pwsf->waveFormatEx,&m_WaveFormatEx,sizeof(m_WaveFormatEx));
						m_Writer->PostThreadMessage(WM_WRITESOUNDFILE_FILENAME,0,(LPARAM)pwsf);
					}
		
				return ERROR_SUCCESS;
			}
		}
	

	}
	return TRUE;
}
LRESULT CRecordSound::OnStopRecording(WPARAM wParam, LPARAM lParam)
{
	MMRESULT mmReturn = 0;
	if(!m_bRecording)
		return FALSE;

	if(m_bRecording)
	{
		mmReturn = ::waveInStop(m_hRecord);
		if(!mmReturn)
			mmReturn = ::waveInReset(m_hRecord);
		Sleep(500);

		if(!mmReturn)
			mmReturn = ::waveInClose(m_hRecord);
		if(!mmReturn)
			m_bRecording = FALSE;
		if(m_Player)
			m_Player->PostThreadMessage(WM_PLAYSOUND_STOPPLAYING,0,0);

		if(m_Writer)
			m_Writer->PostThreadMessage(WM_WRITESOUNDFILE_CLOSEFILE,0,0);
		if (_CrtIsValidHeapPointer(pwsf))
		{
			delete pwsf;
			
		}
		pwsf = NULL;
		return mmReturn;
	}

	return TRUE;
}
LRESULT CRecordSound::OnSoundData(WPARAM wParam, LPARAM lParam)
{
	LPWAVEHDR lpHdr = (LPWAVEHDR) lParam;

	if(lpHdr)
	{
		short int * lpInt = (short int*) lpHdr->lpData;
		DWORD cbRecorded = lpHdr->dwBytesRecorded;
		::waveInUnprepareHeader(m_hRecord, lpHdr, sizeof(WAVEHDR));

		ProcessSoundData(lpInt, cbRecorded/sizeof(short int));
// 		if ((cbRecorded==0)&&(m_bRecording == FALSE))//无声音缓冲进入
// 		{
// 			TRACE("firsttime =TRUE\n");
// 			firsttime =TRUE;
// 		}
		if(m_Writer)
		{
			WAVEHDR* pWriteHdr = new WAVEHDR;
			if(!pWriteHdr)
				return FALSE;
			memcpy(pWriteHdr,lpHdr,sizeof(WAVEHDR));
			BYTE * pSound = new BYTE[lpHdr->dwBufferLength];
			if(!pSound)
			{
				if (pWriteHdr)
				{
					delete pWriteHdr;
				}
				
				return FALSE;
			}
			memcpy(pSound,lpHdr->lpData,lpHdr->dwBufferLength);
			pWriteHdr->lpData = (char*)pSound;
			m_Writer->PostThreadMessage(WM_WRITESOUNDFILE_WRITEBLOCK,GetCurrentThreadId(),(LPARAM) pWriteHdr);
		}
		

		if(m_Player)
		{
	
			m_Player->PostThreadMessage(WM_PLAYSOUND_PLAYBLOCK, GetCurrentThreadId(),(LPARAM) lpHdr);
		
		}
		else
		{
			if (lpHdr->lpData)
			{
				delete lpHdr->lpData;
				lpHdr->lpData = NULL;
			}
			if (lpHdr)
			{
				delete lpHdr;
				lpHdr = NULL;
			}
			
			
		}
		char debugbuffer[256];
		sprintf(debugbuffer, "SOUND BUFFER returned: %d\n",cbRecorded);
		TRACE(debugbuffer);
		if(m_bRecording)
		{
			
			LPWAVEHDR lpHdr = CreateWaveHeader();
			::waveInPrepareHeader(m_hRecord,lpHdr, sizeof(WAVEHDR));
			::waveInAddBuffer(m_hRecord, lpHdr, sizeof(WAVEHDR));
			m_nInputBuffers++;
		}
	}


	return ERROR_SUCCESS;
}

LPWAVEHDR CRecordSound::CreateWaveHeader()
{
	LPWAVEHDR lpHdr = new WAVEHDR;
	ZeroMemory(lpHdr, sizeof(WAVEHDR));
	BYTE* lpByte = new BYTE[(m_WaveFormatEx.nBlockAlign*SOUNDSAMPLES)];

	lpHdr->lpData = (char *) lpByte;
	lpHdr->dwBufferLength = (m_WaveFormatEx.nBlockAlign*SOUNDSAMPLES);
	return lpHdr;

}

void CRecordSound::ProcessSoundData(short int* sound, DWORD dwSamples)
{
	CACSDlg* pAcsDlg = (CACSDlg*)AfxGetApp()->m_pMainWnd;
	//
 	int i=0;
 	int sum=0;
	VoiceNormalize(sound,dwSamples,NorAmp);
	for (i=0;i<dwSamples;i++)
	{
		sum+=abs(*((short int*)sound+i));
	}
	sum = 10*log(sum);

	::PostMessage(hWnd,WMSG_SOUNDWAVE,(WPARAM)sum,NULL);
		//加入缓存
//		if(pAcsDlg->SendSocket.m_bConnect)
//		{
			OutVoiceCycleMem->WriteData((char *)sound,dwSamples*sizeof(short));
//		}
//	TRACE("加入缓存\n");
}
LRESULT CRecordSound::OnEndThread(WPARAM wParam, LPARAM lParam)
{
	if(m_bRecording)
	{
		OnStopRecording(0, 0);
	}
	::PostQuitMessage(0);
	return TRUE;
}
LRESULT CRecordSound::OnPtrSoundWriter(WPARAM wParam, LPARAM lParam)
{
	m_Writer = (CWriteSoundFile*) lParam;
	return TRUE;
}
void CRecordSound::VoiceNormalize(short *pBuffer, int nlength,int nAmp)
{
	
	//以该幅值做归一化
	float fFactor = 32767.0/nAmp;
	for (int i=0;i<nlength;i++)
	{
		if (pBuffer[i]>=nAmp)
		{
			pBuffer[i] =32767;
		}
		else if(pBuffer[i]<=-nAmp)
		{
			pBuffer[i] =-32767;
		}
		else
			pBuffer[i]*=fFactor;
	}
	
}	