#if !defined(AFX_VIDEOSELECT_H__D4DEC09D_DF1A_4C79_B04D_CC7903A4D4CD__INCLUDED_)
#define AFX_VIDEOSELECT_H__D4DEC09D_DF1A_4C79_B04D_CC7903A4D4CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VideoSelect.h : header file
//
#include "ImageSelect.h"
#include "MediaChannel.h"
#include "VideoContainer.h"
/////////////////////////////////////////////////////////////////////////////
// CVideoSelect dialog

class CVideoSelect : public CDialog
{
// Construction
public:
	BOOL Snap(CString szResult);
	void SetSnapParam(LONG nDeviceIndex,BOOL bHoriMirror,BOOL bVertMirror,BOOL bSaveFile,long nSnapCounts,long nSnapInterval);
	CMediaChannel * GetMediaChannel(LONG nDevIdx);
	void OnChangeChannel(LONG nWndIndex);
	BOOL CreateVideoContainer();
	LONG m_nDeviceCount;
	CMediaChannel* m_pMediaChannel;
	BOOL InitializeDevice(CString &szResult);
	CVideoSelect(CWnd* pParent = NULL);   // standard constructor
	CString szSaveFileName;
// Dialog Data
	//{{AFX_DATA(CVideoSelect)
	enum { IDD = IDD_DIALOG_VIDEO };
	CVideoContainer	m_VideoContainer;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVideoSelect)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL	m_bHoriMirror;
	BOOL	m_bVertMirror;
	BOOL	m_bSaveFile;
	LONG	m_nSnapCounts;
	LONG	m_nSnapInterval;
	LONG	m_nDeviceIndex;
	BYTE *	m_pYuvData;
	// Generated message map functions
	//{{AFX_MSG(CVideoSelect)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIDEOSELECT_H__D4DEC09D_DF1A_4C79_B04D_CC7903A4D4CD__INCLUDED_)
