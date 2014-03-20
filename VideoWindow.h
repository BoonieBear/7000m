#if !defined(AFX_VIDEOWINDOW_H__B2C5C8A3_0096_45A4_8FA7_F420936504CD__INCLUDED_)
#define AFX_VIDEOWINDOW_H__B2C5C8A3_0096_45A4_8FA7_F420936504CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoWindow.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CVideoWindow window

class CVideoWindow : public CStatic
{
// Construction
public:
	CVideoWindow(LONG nIndex);
 
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoWindow)
	//}}AFX_VIRTUAL

// Implementation
public:
	BOOL Create(CWnd *pParentWnd,LPCTSTR szText,UINT nID,DWORD dwStyle = (WS_CHILD | SS_NOTIFY | WS_VISIBLE));
	virtual ~CVideoWindow();

public:
	void		SetWndPos(CRect &rc,LONG nDeflate = 0);
	LONG		GetWndIndex()								{return m_nIndex;}
	CRect		GetWndPos();

	// Generated message map functions
protected:
	//{{AFX_MSG(CVideoWindow)

	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

protected:
	CRect		m_WndPos;
	LONG		m_nIndex;

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOWINDOW_H__B2C5C8A3_0096_45A4_8FA7_F420936504CD__INCLUDED_)
