#if !defined(AFX_ADVANCEDSET_H__FC92BDB8_4203_4784_BDC0_72721E4B1701__INCLUDED_)
#define AFX_ADVANCEDSET_H__FC92BDB8_4203_4784_BDC0_72721E4B1701__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AdvancedSet.h : header file
//
#include "lpt_lib.h"//并口操作函数头文件

/////////////////////////////////////////////////////////////////////////////
// CAdvancedSet dialog

class CAdvancedSet : public CDialog
{
// Construction
public:
	CAdvancedSet(CWnd* pParent = NULL);   // standard constructor
	LPT_HANDLE hyLPT; //并口操作
// Dialog Data
	//{{AFX_DATA(CAdvancedSet)
	enum { IDD = IDD_ADVANCED };
	CButton	m_check;
	int		m_AftFilterTap;
	float	m_AlfaPhase;
	float	m_BeltaMu;
	float	m_ChirpLen;
	float	m_ChirpStartF;
	float	m_ChirpStopF;
	float	m_GamaMax;
	float	m_GamaMin;
	int		m_InterleaverLen;
	int		m_IterationNum;
	float	m_MFSKAftGuardLag;
	float	m_MFSKInterGuardLag;
	float	m_MFSKPreGuardLag;
	float	m_MPSKAftGuardLag;
	int		m_MPSKDataSymbolNum;
	int		m_MFSKDataSymbolNum;
	float	m_MPSKPreGuardLag;
	int		m_MPSKTrainSymbolNum;
	float	m_MuMax;
	float	m_MuMin;
	int		m_PreFilterTap;
	int		m_SlideWinLen;
	int		m_MPSK_chirp_inter;
	int		m_MFSK_chirp_inter;
	int		m_cycle_prefix;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAdvancedSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CAdvancedSet)
	virtual BOOL OnInitDialog();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheck1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADVANCEDSET_H__FC92BDB8_4203_4784_BDC0_72721E4B1701__INCLUDED_)
