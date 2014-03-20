#if !defined(AFX_VIDEOCONTAINER_H__A6E99B91_B165_4227_B011_1FAAF2A2055F__INCLUDED_)
#define AFX_VIDEOCONTAINER_H__A6E99B91_B165_4227_B011_1FAAF2A2055F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoContainer.h : header file
//

#include "VideoWindow.h"
/////////////////////////////////////////////////////////////////////////////
// CVideoContainer window

#define		MAX_CHANNEL_SUPPORT		4

class CUCDemoDlg;
class CMediaChannel;
class CVideoContainer : public CStatic
{
// Construction
public:
	CVideoContainer();

// Attributes
public:

// Operations
public:
	BOOL	CreateVideoWnd(LONG nDevices);
	BOOL	SetShowMode(LONG nShowMode);
	BOOL	IsValidMode(LONG nShowMode);
	void	CalcWndPos();
	BOOL	SetCurPage(LONG nActivePage);
	LONG	CalcPageNo(LONG nIndex);
	BOOL	IsValidIndex(LONG nIndex);
	void	SetActiveIndex(LONG nIndex);
	void	DrawFocusRect(CDC *pDC);
	BOOL	ShowVideoPage(LONG nPage,BOOL bShow = TRUE);
	void	StartStream(CMediaChannel *pMediaChannel,CVideoWindow *pWndShow,BOOL bStart);
	BOOL	IsFullScreen()												{return m_bFullScreen;}
	LONG	GetCurPage()												{return m_nActivePage;}
	LONG	GetActiveIndex();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoContainer)
	public:
	virtual BOOL DestroyWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CVideoContainer();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVideoContainer)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	void			DestoryVideoWnd();


public:
	CVideoWindow * m_pVideoWnd[MAX_CHANNEL_SUPPORT];
	
protected:
	CUCDemoDlg	*m_pUC1000Dlg;
	BOOL		 m_bFullScreen;
	LONG		 m_nMaxChannels;
	LONG		 m_nMaxShowMode;

	LONG		 m_nPrevMode;
	LONG		 m_nShowMode;
	LONG		 m_nActiveIndex;
	LONG		 m_nActivePage;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOCONTAINER_H__A6E99B91_B165_4227_B011_1FAAF2A2055F__INCLUDED_)
