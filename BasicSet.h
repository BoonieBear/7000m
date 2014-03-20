#if !defined(AFX_BASICSET_H__966253E1_5473_4C3D_83F0_C9FF06A019C1__INCLUDED_)
#define AFX_BASICSET_H__966253E1_5473_4C3D_83F0_C9FF06A019C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BasicSet.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CBasicSet dialog

class CBasicSet : public CDialog
{
// Construction
public:
	CBasicSet(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CBasicSet)
	enum { IDD = IDD_BASIC };
	CComboBox	m_SysWorkMode;
	CComboBox	m_IsAGCWork;
	CComboBox	m_ADIOWorkMode;
	BOOL	m_Chann1;
	BOOL	m_Chann2;
	BOOL	m_Chann3;
	BOOL	m_Chann4;
	BOOL	m_Chann5;
	BOOL	m_Chann6;
	int		m_DiscardLen;
	int		m_Gain1;
	int		m_Gain2;
	int		m_Gain3;
	int		m_Gain4;
	int		m_Gain5;
	int		m_Gain6;
	BOOL	m_IsTCM2Work;
	float	m_RecvSampleRate;
	int		m_SlideWinLen;
	int		m_SyncConcurrence;
	float	m_XMTSampleRate;
	float	m_XMTDelayToSync;
	int     m_RecChannelNum;
	BOOL	m_SametoGain1;
	BOOL	m_ADIOID;
	BOOL	m_DSP01ID;
	BOOL	m_DSP02ID;
	BOOL	m_DSP11ID;
	BOOL	m_DSP12ID;
	float	m_RecvDelaySync;
	BOOL	m_IsSendADIOData;
	BOOL	m_ParamFactor;
	BOOL	m_PhaseFactor;
	float	m_XMTAmpValue;
	BOOL	m_AfterDecideBit;
	BOOL	m_AfterDecideData;
	BOOL	m_BeforeDecideData;
	BOOL	m_DopplerFactor;
	int		m_mfsk_framenum;
	int		m_mfsk_packet;
	int		m_mfsk_recvpacket;
	int		m_mfsk_recvframenum;
	int		m_mpsk_framenum;
	int		m_mpsk_packet;
	int		m_mpsk_recvframenum;
	int		m_mpsk_recvpacket;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBasicSet)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CBasicSet)
	afx_msg void OnSametogain1();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeADIOWorkMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BASICSET_H__966253E1_5473_4C3D_83F0_C9FF06A019C1__INCLUDED_)
