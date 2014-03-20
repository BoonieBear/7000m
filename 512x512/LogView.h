#if !defined(AFX_LOGVIEW_H__76FA5E9E_31DF_4827_9B3E_1806DBA7A169__INCLUDED_)
#define AFX_LOGVIEW_H__76FA5E9E_31DF_4827_9B3E_1806DBA7A169__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LogView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLogView dialog

class CLogView : public CDialog
{
// Construction
public:
	void showlog(WPARAM wParam,LPARAM lParam);
	CLogView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CLogView)
	enum { IDD = IDD_DIALOG_LOG };
	CString	m_log;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLogView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLogView)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGVIEW_H__76FA5E9E_31DF_4827_9B3E_1806DBA7A169__INCLUDED_)
