//{{AFX_INCLUDES()
#include "ntgraph.h"
//}}AFX_INCLUDES
#if !defined(AFX_POSTVIEW_H__568CCADA_EE4E_4B48_997A_341B91B82AB2__INCLUDED_)
#define AFX_POSTVIEW_H__568CCADA_EE4E_4B48_997A_341B91B82AB2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PostView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPostView dialog

class CPostView : public CDialog
{
// Construction
public:
	void Redraw();
	double iX;//横向距离	
	double iY;//
	double iZ;//深度
	int iMode;//视图模式0：俯视。1：平视
	int dFactor;//缩放比例因子
	CPostView(CWnd* pParent = NULL);   // standard constructor
	CBitmapButton ZoomOutButton;
	CBitmapButton ZoomInButton;
// Dialog Data
	//{{AFX_DATA(CPostView)
	enum { IDD = IDD_DIALOG_POSTVIEW };
	CNTGraph	m_postview;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPostView)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPostView)
	virtual BOOL OnInitDialog();
	afx_msg void OnSavePic();
	afx_msg void OnLookDown();
	afx_msg void OnLookFlat();
	afx_msg void OnZoomout();
	afx_msg void OnZoomin();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POSTVIEW_H__568CCADA_EE4E_4B48_997A_341B91B82AB2__INCLUDED_)
