#if !defined(AFX_COMPARAM_H__73637026_AC0B_4D23_8211_E940516E29E6__INCLUDED_)
#define AFX_COMPARAM_H__73637026_AC0B_4D23_8211_E940516E29E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ComParam.h : header file
//
#include "MyProgress.h"
/////////////////////////////////////////////////////////////////////////////
// CComParam dialog

class CComParam : public CDialog
{
// Construction
public:
	LRESULT OnDistanceDisp(WPARAM wParam,LPARAM lParam);
	CComParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CComParam)
	enum { IDD = IDD_DIALOG_COMPARAM };
	CListCtrl	m_list;
	UINT	m_gain;
	//}}AFX_DATA
	CFont myFont;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CComParam)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CComParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSetgain();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMPARAM_H__73637026_AC0B_4D23_8211_E940516E29E6__INCLUDED_)
