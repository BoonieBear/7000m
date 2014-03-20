#if !defined(AFX_WORDDIALOG_H__5ACC7FB6_FA30_40F1_9887_A99F808D5923__INCLUDED_)
#define AFX_WORDDIALOG_H__5ACC7FB6_FA30_40F1_9887_A99F808D5923__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// WordDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWordDialog dialog

class CWordDialog : public CDialog
{
// Construction
public:
	void InputWord(CString strlog);
	void InputText(CString strlog);
	CWordDialog(CWnd* pParent = NULL);   // standard constructor
	CFont editfont;
// Dialog Data
	//{{AFX_DATA(CWordDialog)
	enum { IDD = IDD_DIALOG_WORD };
	CEdit	m_logedit;
	CEdit	m_input;
	CString	m_strInput;
	CString	m_wordlog;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWordDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWordDialog)
	virtual BOOL OnInitDialog();
	afx_msg void OnSend();
	afx_msg void OnAddToList();

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WORDDIALOG_H__5ACC7FB6_FA30_40F1_9887_A99F808D5923__INCLUDED_)
