// ACS.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "ACS.h"
#include "ACSDlg.h"
#include "PlaySound.h"
#include "RecordSound.h"
#include "WriteSoundFile.h"
#include "PlayMMSound.h"
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CACSApp

BEGIN_MESSAGE_MAP(CACSApp, CWinApp)
	//{{AFX_MSG_MAP(CACSApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CACSApp construction

CACSApp::CACSApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CACSApp object

CACSApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CACSApp initialization
int CACSApp::ExitInstance()
{
	if (!m_WzdimageList.IsEmpty())
	{
		free(m_WzdimageList.GetHead()->buf);
		free(m_WzdimageList.GetHead());
	}
	m_WzdimageList.RemoveAll();
	m_WzdtextList.RemoveAll();
	m_WzdvoiceList.RemoveAll();
//	ExitSkinMagicLib();
	if(m_pPlayMMSound)
	{
		m_pPlayMMSound->PostThreadMessage(WM_PLAYMMSOUND_ENDTHREAD,0,0);
		if (m_pPlayMMSound->m_hThread)
		{
			::WaitForSingleObject(m_pPlayMMSound->m_hThread, 3000);
		}

		m_pPlayMMSound = NULL;
		
	}
	if(m_pPlaySound)
	{
		m_pPlaySound->PostThreadMessage(WM_PLAYSOUND_ENDTHREAD,0,0);
		
		if (m_pPlaySound->m_hThread)
		{
			::WaitForSingleObject(m_pPlaySound->m_hThread, 3000);
		}
		
		m_pPlaySound = NULL;
		
	}
	if(m_pRecordSound)
	{
		m_pRecordSound->PostThreadMessage(WM_RECORDSOUND_ENDTHREAD,0,0);
		if (m_pRecordSound->m_hThread)
		{
			::WaitForSingleObject(m_pRecordSound->m_hThread, 3000);
		}
		

		m_pRecordSound = NULL;
	}
	if(m_pWriteSound)
	{
		m_pWriteSound->PostThreadMessage(WM_WRITESOUNDFILE_ENDTHREAD,0,0);
		if (m_pWriteSound->m_hThread)
		{
			::WaitForSingleObject(m_pWriteSound->m_hThread, 3000);
		}
		
		delete m_pWriteSound;
		m_pWriteSound = NULL;
		
	}
	if(InVoiceCycleMem)
 		delete InVoiceCycleMem;
	if (OutVoiceCycleMem)
	{
		delete OutVoiceCycleMem;
	}
	if (dWaveData)
	{
		delete dWaveData;
	}
	if(WaveCycleMem)
 		delete WaveCycleMem;
	if (m_pRawData)
	{
		delete m_pRawData;
	}
	if (lastpacket)
	{
		delete lastpacket;
	}
	_CrtDumpMemoryLeaks();
	return 0;
}
BOOL CACSApp::InitInstance()
{
	AfxEnableControlContainer();
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.
//	_CrtSetBreakAlloc();
#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif


	
	InitRecording();
	InitPlaying();
	InitWriting();
	InitPlayMMSound();
	
	if(m_pRecordSound)
	{
// 		m_pRecordSound->PostThreadMessage(WM_RECORDSOUND_SOUNDPLAYER,(WPARAM)0, (LPARAM)
// 			m_pPlaySound);
		m_pRecordSound->PostThreadMessage(WM_RECORDSOUND_WRITERTHREAD ,(WPARAM)0, (LPARAM)
			m_pWriteSound);
		
	}
	HYInitialize();
	CACSDlg dlg;
	
	m_pMainWnd = &dlg;
//	VERIFY( 1 == InitSkinMagicLib( AfxGetInstanceHandle(), "Dialog" , 
// 					  NULL,
// 					  NULL ) );
		//¼ÓÔØSkinMagicÆ¤·ô
//	VERIFY(1 == LoadSkinFromResource(NULL, (LPSTR)Devior, "SKINMAGIC"));
//	VERIFY(1 == SetWindowSkin(m_pMainWnd->m_hWnd, "MainFrame"));
//	VERIFY(1 == SetDialogSkin("Dialog"));
	dlg.m_RecordThread = m_pRecordSound;
	dlg.m_PlayThread = m_pPlaySound;
	dlg.m_PlayMMSound = m_pPlayMMSound;
	SetDialogBkColor(MY_BACKCOLOR,RGB(0,0,0));
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}
	HYUninitialize();
	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.
	return FALSE;
}
BOOL CACSApp::InitRecording()
{
	m_pRecordSound = new CRecordSound();
	m_pRecordSound->CreateThread();
	return TRUE;
}
BOOL CACSApp::InitPlayMMSound()
{
	m_pPlayMMSound = new CPlayMMSound();
	m_pPlayMMSound->CreateThread();
	return TRUE;
}

BOOL CACSApp::InitWriting()
{
	m_pWriteSound = new CWriteSoundFile();
	m_pWriteSound->CreateThread();
	return TRUE;
}
BOOL CACSApp::InitPlaying()
{
	m_pPlaySound = new CPlaySound();
	m_pPlaySound->CreateThread();
	return TRUE;
}
