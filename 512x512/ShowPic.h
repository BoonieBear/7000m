#if !defined(AFX_SHOWPIC_H__B68D3E0F_99E0_4E94_93E2_99DA5875C70C__INCLUDED_)
#define AFX_SHOWPIC_H__B68D3E0F_99E0_4E94_93E2_99DA5875C70C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ShowPic.h : header file
//
#include "CxImage/header/ximage.h"
#include "ImageShow.h"
/////////////////////////////////////////////////////////////////////////////
// CShowPic dialog

class CShowPic : public CDialog
{
// Construction
public:
	CRect rect;
	CxImage image;
	void AddToList(CString filename);
	CStringList PicFileList;
	POSITION index;
	CShowPic(CWnd* pParent = NULL);   // standard constructor
	CImageShow m_ShowImage;
// Dialog Data
	//{{AFX_DATA(CShowPic)
	enum { IDD = IDD_DIALOG_SHOWPIC };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowPic)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CShowPic)
	virtual BOOL OnInitDialog();
	afx_msg void OnNext();
	afx_msg void OnPre();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWPIC_H__B68D3E0F_99E0_4E94_93E2_99DA5875C70C__INCLUDED_)
