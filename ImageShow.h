#if !defined(AFX_IMAGESHOW_H__223BAB75_091F_4125_A163_F05456116E1B__INCLUDED_)
#define AFX_IMAGESHOW_H__223BAB75_091F_4125_A163_F05456116E1B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageShow.h : header file
//
#include "DIB.h"
/////////////////////////////////////////////////////////////////////////////
// CImageShow window

class CImageShow : public CWnd
{
// Construction
public:
	CImageShow();

// Attributes
public:
	CDIB m_Dib;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageShow)
	public:
	virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	//}}AFX_VIRTUAL

// Implementation
public:

	void FileLoad(CString filename);
	void FileLoad(char *filename);
	virtual ~CImageShow();

	// Generated message map functions
protected:
	//{{AFX_MSG(CImageShow)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGESHOW_H__223BAB75_091F_4125_A163_F05456116E1B__INCLUDED_)
