#if !defined(AFX_ADCPPAGE_H__6BB0AB56_A1DB_4EFB_9590_59CEC6424AEE__INCLUDED_)
#define AFX_ADCPPAGE_H__6BB0AB56_A1DB_4EFB_9590_59CEC6424AEE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdcpPage.h : header file
//
#include "DispPanel.h"
/////////////////////////////////////////////////////////////////////////////
// CAdcpPage dialog

class CAdcpPage : public CDialog
{
// Construction
public:
	void UpdateView();
	CAdcpPage(CWnd* pParent = NULL);   // standard constructor
		//adcp data
	double xValue[10];
	double yValue[10];
	double zValue[10];
// Dialog Data
	//{{AFX_DATA(CAdcpPage)
	enum { IDD = IDD_DIALOG_ADCP };
	CDispPanel	m_zView;
	CDispPanel	m_yView;
	CDispPanel	m_xView;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdcpPage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAdcpPage)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADCPPAGE_H__6BB0AB56_A1DB_4EFB_9590_59CEC6424AEE__INCLUDED_)
