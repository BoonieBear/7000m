#if !defined(AFX_FSPAGE_H__A6734FE4_2354_4288_ADF9_4BA5B83BEA50__INCLUDED_)
#define AFX_FSPAGE_H__A6734FE4_2354_4288_ADF9_4BA5B83BEA50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FsPage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFsPage dialog

class CFsPage : public CDialog
{
// Construction
public:
	CFsPage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFsPage)
	enum { IDD = IDD_DIALOG_FS };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFsPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFsPage)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FSPAGE_H__A6734FE4_2354_4288_ADF9_4BA5B83BEA50__INCLUDED_)
