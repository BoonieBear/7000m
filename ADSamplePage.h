#if !defined(AFX_ADSAMPLEPAGE_H__0EC306D0_5337_40D3_9F61_65CC64C52BDE__INCLUDED_)
#define AFX_ADSAMPLEPAGE_H__0EC306D0_5337_40D3_9F61_65CC64C52BDE__INCLUDED_
#include "DispPanel.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ADSamplePage.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CADSamplePage dialog

class CADSamplePage : public CDialog
{
// Construction
public:
	void UpdateView(short* srcData);
	CADSamplePage(CWnd* pParent = NULL);   // standard constructor
	bool bMode;
	CRect windowrect;
	CRect ad1Rect;
	CRect ad2Rect;
	CRect ad3Rect;
	CRect ad4Rect;
//	CRect ad5Rect;
//	CRect ad6Rect;
// Dialog Data
	//{{AFX_DATA(CADSamplePage)
	enum { IDD = IDD_DIALOG_AD };
	CDispPanel	m_adview1;
	CDispPanel	m_adview2;
	CDispPanel	m_adview3;
	CDispPanel	m_adview4;
	int		m_gain;
	int		m_samplerate;
	//}}AFX_DATA
	//AD»Ø·Å
	int ADi;
	int pDataLen;
	CFile ADPlayFile;
	int m_ADParamLen;
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CADSamplePage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CADSamplePage)
	afx_msg void OnAdstart();
	afx_msg void OnAdreplay();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnDoubleclickedadview1();
	afx_msg void OnDoubleclickedadview2();
	afx_msg void OnDoubleclickedadview3();
	afx_msg void OnDoubleclickedadview4();
//	afx_msg void OnDoubleclickedadview5();
//	afx_msg void OnDoubleclickedadview6();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADSAMPLEPAGE_H__0EC306D0_5337_40D3_9F61_65CC64C52BDE__INCLUDED_)
