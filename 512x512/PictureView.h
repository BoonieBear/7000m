#if !defined(AFX_PICTUREVIEW_H__F8DC6AA5_2730_4AA9_AF59_DED25C2DD101__INCLUDED_)
#define AFX_PICTUREVIEW_H__F8DC6AA5_2730_4AA9_AF59_DED25C2DD101__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PictureView.h : header file
//
#include "DIB.h"
#include "ImageShow.h"
#include "ImageSelect.h"
#include "VideoSelect.h"
/////////////////////////////////////////////////////////////////////////////
// CPictureView dialog

class CPictureView : public CDialog
{
// Construction
public:
	afx_msg void OnSendpic();
	CPictureView(CWnd* pParent = NULL);   // standard constructor
	CDIB pDib;
	BOOL    m_bIsDraw;
	CString BMPFileName;
	BYTE* BMPBuffer;
	CImageSelect ImageSelectDlg; 
	CVideoSelect VideoSelectDlg;
	int GetIndexFromType(int nDocType, BOOL bOpenFileDialog);

	CString GetExtFromType(int nDocType);
	CString GetDescFromType(int nDocType);
	CString GetFileTypes(BOOL bOpenFileDialog);

	CString FindExtension(const CString& name);
	int FindType(const CString& ext);
// Dialog Data
	//{{AFX_DATA(CPictureView)
	enum { IDD = IDD_PICTURE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPictureView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPictureView)
	afx_msg void OnSelectpic();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonSelect();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PICTUREVIEW_H__F8DC6AA5_2730_4AA9_AF59_DED25C2DD101__INCLUDED_)
