#if !defined(AFX_OPTIONSET_H__357DCA76_B8F8_469C_826B_4682BC9F184D__INCLUDED_)
#define AFX_OPTIONSET_H__357DCA76_B8F8_469C_826B_4682BC9F184D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OptionSet.h : header file
//
#include "BasicSet.h"
#include "AdvancedSet.h"
/////////////////////////////////////////////////////////////////////////////
// COptionSet dialog

class COptionSet : public CDialog
{
// Construction
public:
	BOOL CheckSetting();
	COptionSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(COptionSet)
	enum { IDD = IDD_OPTIONS };
	BOOL	m_basic;
	BOOL	m_advanced;
	//}}AFX_DATA
	CBasicSet pBasicSet;
	CAdvancedSet pAdvancedSet;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(COptionSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(COptionSet)
	afx_msg void OnSave();
	afx_msg void OnLoadSet();
	virtual BOOL OnInitDialog();
	afx_msg void OnAdvanced();
	afx_msg void OnBasic();
	afx_msg void OnSaveas();
	afx_msg void OnHalt();
	afx_msg void OnSetTime();
	afx_msg void OnResetadio();
	afx_msg void OnDiSCONNECT();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPTIONSET_H__357DCA76_B8F8_469C_826B_4682BC9F184D__INCLUDED_)
