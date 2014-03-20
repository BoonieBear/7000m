//{{AFX_INCLUDES()

//}}AFX_INCLUDES
#if !defined(AFX_WAVEVIEW_H__E6BEAAE4_5460_42A4_B200_C4A860FA74B0__INCLUDED_)
#define AFX_WAVEVIEW_H__E6BEAAE4_5460_42A4_B200_C4A860FA74B0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WaveView.h : header file
//
#include "DispPanel.h"
extern BOOL bMode;
/////////////////////////////////////////////////////////////////////////////
// CWaveView dialog
class CWaveView : public CDialog
{
// Construction
public:
	CWaveView(CWnd* pParent = NULL);   // standard constructor
	~CWaveView();
	CBitmapButton PlayButton;
	CBitmapButton ZOOMOUTButton;
	CBitmapButton ZOOMINButton;
	short* sWaveData;

	

// Dialog Data
	//{{AFX_DATA(CWaveView)
	enum { IDD = IDD_DIALOG_WAVEVIEW };
	CDispPanel	m_waveview;
	//}}AFX_DATA
static	UINT OnShowWave(LPVOID pParam);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWaveView)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWaveView)
	virtual BOOL OnInitDialog();
	afx_msg void OnSavPic();
	afx_msg void OnPause();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnWavezoomout();
	afx_msg void OnWavezoomin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAVEVIEW_H__E6BEAAE4_5460_42A4_B200_C4A860FA74B0__INCLUDED_)
