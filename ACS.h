// ACS.h : main header file for the ACS application
//

#if !defined(AFX_ACS_H__19C48A38_C14F_4033_8022_EE9B8E89E16E__INCLUDED_)
#define AFX_ACS_H__19C48A38_C14F_4033_8022_EE9B8E89E16E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "RecordSound.h"
#include "PlaySound.h"
#include "PlayMMSound.h"
#include "StaticTime.h"

#include "data_define.h"
/////////////////////////////////////////////////////////////////////////////
// CACSApp:
// See ACS.cpp for the implementation of this class
//

class CACSApp : public CWinApp
{
public:
	CACSApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CACSApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL
	virtual int ExitInstance();
// Implementation

	//{{AFX_MSG(CACSApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
	CRecordSound* m_pRecordSound;
	CPlaySound* m_pPlaySound;
	CWriteSoundFile* m_pWriteSound;
	CPlayMMSound* m_pPlayMMSound;
	BOOL InitRecording();
	BOOL InitPlaying();
	BOOL InitWriting();
	BOOL InitPlayMMSound();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACS_H__19C48A38_C14F_4033_8022_EE9B8E89E16E__INCLUDED_)
