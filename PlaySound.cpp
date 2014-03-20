// PlaySound.cpp : implementation file
//

#ifndef __COMPLEX__
#define __COMPLEX__
typedef struct 
{
    float real; 
	float imag;
} 
COMPLEXNUMBER;
#endif

#include "stdafx.h"
#include "winbase.h"
#include <mmsystem.h>
#include <math.h>



#include "ACSDlg.h"
#include "PlaySound.h"





#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPlaySound

IMPLEMENT_DYNCREATE(CPlaySound, CWinThread)

#define BLOCKSAHEAD 3

CPlaySound::CPlaySound(int iHertz)
{
	m_nOutputBuffers = 0;
	m_nMaxOutputBuffers = 0;
	memset(&m_WaveFormatEx,0x00,sizeof(m_WaveFormatEx));
	m_WaveFormatEx.wFormatTag = WAVE_FORMAT_PCM;
	m_WaveFormatEx.nChannels = 1;
	m_WaveFormatEx.wBitsPerSample = 16;
	m_WaveFormatEx.cbSize = 0;
	m_WaveFormatEx.nSamplesPerSec = iHertz; // 20050;
	m_WaveFormatEx.nAvgBytesPerSec = m_WaveFormatEx.nSamplesPerSec
		*(m_WaveFormatEx.wBitsPerSample/8);
	m_WaveFormatEx.nBlockAlign = 
		(m_WaveFormatEx.wBitsPerSample/8)*
		m_WaveFormatEx.nChannels;
	m_pSemaphore = new CSemaphore(BLOCKSAHEAD,BLOCKSAHEAD);

	m_bPlay = FALSE;
	
}

CPlaySound::~CPlaySound()
{
	if (m_pSemaphore)
	{
		delete m_pSemaphore;
	}
}

BOOL CPlaySound::InitInstance()
{
	// TODO:  perform and per-thread initialization here
	return TRUE;
}

int CPlaySound::ExitInstance()
{
	// TODO:  perform any per-thread cleanup here
	return CWinThread::ExitInstance();
}

BEGIN_MESSAGE_MAP(CPlaySound, CWinThread)
	//{{AFX_MSG_MAP(CPlaySound)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
	ON_THREAD_MESSAGE(WM_PLAYSOUND_STARTPLAYING, OnStartPlaying)
	ON_THREAD_MESSAGE(WM_PLAYSOUND_STOPPLAYING, OnStopPlaying)
	ON_THREAD_MESSAGE(WM_PLAYSOUND_PLAYBLOCK, OnWriteSoundData)
	ON_THREAD_MESSAGE(MM_WOM_DONE, OnEndPlaySoundData)
	ON_THREAD_MESSAGE(WM_PLAYSOUND_ENDTHREAD,OnEndThread)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPlaySound message handlers
LRESULT CPlaySound::OnStartPlaying(WPARAM wParam, LPARAM lParam)
{
	DWORD mmReturn = 0;

	if(m_bPlay)
		return FALSE;

	if(!m_bPlay)
	{
		// open wavein device
		MMRESULT mmReturn = ::waveOutOpen( &m_hPlay, WAVE_MAPPER,
			&m_WaveFormatEx, ::GetCurrentThreadId(), 0, CALLBACK_THREAD);
		if(mmReturn )
		{
			char errorbuffer[MAX_PATH];
			char errorbuffer1[MAX_PATH];
			waveOutGetErrorText( mmReturn, 
								errorbuffer,
								MAX_PATH);
			sprintf(errorbuffer1,"WAVEOUT:%x:%s",mmReturn,errorbuffer);
			AfxMessageBox(errorbuffer1);  

		}

		if(!mmReturn)
		{
			m_bPlay = TRUE;
		}

	}
	return TRUE;
}
LRESULT CPlaySound::OnStopPlaying(WPARAM wParam, LPARAM lParam)
{
	MMRESULT mmReturn = 0;
	if(!m_bPlay)
		return FALSE;

	if(m_bPlay)
	{
		mmReturn = ::waveOutReset(m_hPlay);
		
		if(!mmReturn)
			m_bPlay = FALSE;
		Sleep(500);
		if(!mmReturn)
			mmReturn = ::waveOutClose(m_hPlay);
		return mmReturn;
	}
	return TRUE;
}
LRESULT CPlaySound::OnEndPlaySoundData(WPARAM wParam, LPARAM lParam)
{

	LPWAVEHDR lpHdr = (LPWAVEHDR) lParam;
	if(lpHdr)
	{
		if(_CrtIsValidHeapPointer(lpHdr->lpData))
		{
		
			if (::waveOutUnprepareHeader(m_hPlay, lpHdr, sizeof(WAVEHDR))==MMSYSERR_NOERROR)
			{		
				if(lpHdr->lpData)
				{
				
					delete[] ((BYTE*) lpHdr->lpData);
					lpHdr->lpData =NULL;
				
				}
				if (lpHdr)
				{
					delete lpHdr;
					lpHdr = NULL;
				}
				
			}

		}
		else
		{
			TRACE("_CrtIsValidHeapPointer return False!\n");
			lpHdr->lpData =NULL;
			lpHdr = NULL;
		}


		m_pSemaphore->Unlock();
	}
	return ERROR_SUCCESS;
}
LRESULT CPlaySound::OnWriteSoundData(WPARAM wParam, LPARAM lParam)
{
	LPWAVEHDR lpHdr = (LPWAVEHDR) lParam;
	MMRESULT mmResult = 0;


	if(lpHdr)
	{
// 		char debugbuffer[256];
// 		sprintf(debugbuffer, "SOUND BUFFER written: %d, %d\n",lpHdr->dwBufferLength,m_nOutputBuffers);
// 		TRACE(debugbuffer);
		if(m_bPlay)
		{
//			short int* lpInt = (short int*) lpHdr->lpData;
			DWORD dwSamples = lpHdr->dwBufferLength/sizeof(short int);

//			ProcessSoundData(lpInt, dwSamples);
//			ProcessSoundData(lpInt,lpHdr->dwBufferLength/2);
			mmResult = ::waveOutPrepareHeader(m_hPlay, lpHdr, sizeof(WAVEHDR));
			if(mmResult)
				TRACE("error from waveoutprepareheader\n");

			mmResult = ::waveOutWrite(m_hPlay, lpHdr, sizeof(WAVEHDR));


			if(mmResult)
				TRACE("error from waveoutwrite\n");
			m_nOutputBuffers++;
			
		}
// 		lpHdr->lpData =NULL;
// 		lpHdr =NULL;
	}

	return ERROR_SUCCESS;
}

LPWAVEHDR CPlaySound::CreateWaveHeader()
{
	LPWAVEHDR lpHdr = new WAVEHDR;
	ZeroMemory(lpHdr, sizeof(WAVEHDR));
	BYTE* lpByte = new BYTE[(m_WaveFormatEx.nBlockAlign*SOUNDSAMPLES)];

	lpHdr->lpData = (char *) lpByte;
	lpHdr->dwBufferLength = (m_WaveFormatEx.nBlockAlign*SOUNDSAMPLES);
	return lpHdr;

}

void CPlaySound::ProcessSoundData(short int *sound, DWORD dwSamples)
{
	

}
LRESULT CPlaySound::OnEndThread(WPARAM wParam, LPARAM lParam)
{
	if(m_bPlay)
		OnStopPlaying(0,0);
	::PostQuitMessage(0);
	return TRUE;
}