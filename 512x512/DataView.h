#if !defined(AFX_DATAVIEW_H__6682D6BB_C439_4BC4_9E5A_4D87602D9584__INCLUDED_)
#define AFX_DATAVIEW_H__6682D6BB_C439_4BC4_9E5A_4D87602D9584__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DataView.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDataView dialog

class CDataView : public CDialog
{
// Construction
public:
	void BPUpdateTime(CString infoSource);
	void UpdateTimeDisplay(CString infoSource);
	CDataView(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDataView)
	enum { IDD = IDD_DIALOG_DATA };
	CStaticTime	m_backdown;
	CStaticTime	m_right;
	CStaticTime	m_left;
	CStaticTime	m_frontup;
	CStaticTime	m_frontdown;
	CStaticTime	m_front;
	CStaticTime	m_down;
	CStaticTime	m_UWVHEIGTH;
	CStaticTime	m_UWVDEEP;
	CStaticTime	m_uwvlong;
	CStaticTime	m_uwvlat;
	CStaticTime	m_roll;
	CStaticTime	m_pitch;
	CStaticTime	m_head;
	CStaticTime	m_distancey;
	CStaticTime	m_distancex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDataView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDataView)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DATAVIEW_H__6682D6BB_C439_4BC4_9E5A_4D87602D9584__INCLUDED_)
