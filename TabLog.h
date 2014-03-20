#if !defined(AFX_TABLOG_H__11798478_30FE_4991_92C0_25C6051AD2F1__INCLUDED_)
#define AFX_TABLOG_H__11798478_30FE_4991_92C0_25C6051AD2F1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabLog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabLog dialog

class CTabLog : public CDialog
{
// Construction
public:
	void showlog(WPARAM wParam, LPARAM lParam);
	CTabLog(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTabLog)
	enum { IDD = IDD_DIALOG_Tablog };
	CString	m_log;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabLog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabLog)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABLOG_H__11798478_30FE_4991_92C0_25C6051AD2F1__INCLUDED_)
