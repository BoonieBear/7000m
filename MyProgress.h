#if !defined(AFX_MYPROGRESS_H__E0A58369_3736_4B06_8E6C_556ED081373E__INCLUDED_)
#define AFX_MYPROGRESS_H__E0A58369_3736_4B06_8E6C_556ED081373E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyProgress.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// MyProgress window

class MyProgress : public CProgressCtrl
{
	// Construction
public:
	CString barTitle;
	MyProgress();
	DWORD bmpresource;
	
	// Attributes
public:
	
	// Operations
public:
	
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyProgress)
	//}}AFX_VIRTUAL
	
	// Implementation
public:
	void SetBmp(DWORD bmp);
	
	void SetBarCaption(CString title);
	virtual ~MyProgress();
	
	// Generated message map functions
protected:
	//{{AFX_MSG(MyProgress)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYPROGRESS_H__E0A58369_3736_4B06_8E6C_556ED081373E__INCLUDED_)
