#if !defined(AFX_IMAGESELECT_H__165473A2_DF0F_4922_BB89_C6F41ABA17D5__INCLUDED_)
#define AFX_IMAGESELECT_H__165473A2_DF0F_4922_BB89_C6F41ABA17D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImageSelect.h : header file
//
#include "resource.h"
#include "ximage.h"
/////////////////////////////////////////////////////////////////////////////
// CImageSelect dialog

class CImageSelect : public CDialog
{
// Construction
public:
	
	void GetImageXY(CxImage *ima, long *x, long *y);
	bool SetImageRectSelection(CRect *rect);
	void GetSelectZoomFactor(DWORD Height,DWORD Width);
	void GetMaxZoomFactor(DWORD Height,DWORD Width);
	CImageSelect(CWnd* pParent = NULL);   // standard constructor
	CString SelectFileName;
	CString SendFileName;
	int pType;
	CxImage image;
	CxImage NewImage;
	float SelectZoomFactor;
	float ZoomFactor;
	CRectTracker m_tracker;
	bool showed;
// Dialog Data
	//{{AFX_DATA(CImageSelect)
	enum { IDD = IDD_DIALOG_EDITPIC };
	CButton	m_CheckOk;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImageSelect)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImageSelect)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMAGESELECT_H__165473A2_DF0F_4922_BB89_C6F41ABA17D5__INCLUDED_)
