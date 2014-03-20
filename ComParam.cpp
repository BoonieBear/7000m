// ComParam.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "ComParam.h"
#include "ACSDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CComParam dialog


CComParam::CComParam(CWnd* pParent /*=NULL*/)
	: CDialog(CComParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(CComParam)
	m_gain = 1500;
	//}}AFX_DATA_INIT
}


void CComParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CComParam)
	DDX_Control(pDX, IDC_PARAMLIST, m_list);
	DDX_Text(pDX, IDC_GAIN, m_gain);
	DDV_MinMaxUInt(pDX, m_gain, 100, 4000);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CComParam, CDialog)
	//{{AFX_MSG_MAP(CComParam)
	ON_BN_CLICKED(IDC_BUTTON_SETGAIN, OnButtonSetgain)
	ON_MESSAGE(DiSTANCE_WMSG,OnDistanceDisp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CComParam message handlers

BOOL CComParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_list.SetExtendedStyle(LVCF_FMT|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_list.InsertColumn(0,_T("通道"),LVCFMT_CENTER,80);	//add column title
	m_list.InsertColumn(1,_T("增益"),LVCFMT_CENTER,60);	//add column title
	m_list.InsertColumn(2,_T("AGC幅度"),LVCFMT_CENTER,100);
	m_list.InsertColumn(3,_T("Chirp相关峰值"),LVCFMT_CENTER,160);
	m_list.InsertColumn(4,_T("通道相关系数"),LVCFMT_CENTER,150);
	m_list.InsertItem(1,"通道1");
	m_list.InsertItem(2,"通道2");
	m_list.InsertItem(3,"通道3");
	m_list.InsertItem(4,"通道4");
//	m_list.InsertItem(5,"通道5");
//	m_list.InsertItem(6,"通道6");
//	m_list.InsertItem(7,"通道7");
//	m_list.InsertItem(8,"通道8");
	myFont.CreatePointFont(150,"Sans Serif");
	m_list.SetFont(&myFont);

	//////////////////////////////////////////////////////////////////////////

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CComParam::OnButtonSetgain() 
{
	// TODO: Add your control notification handler code here
	CString str;
	CACSDlg* dlg= (CACSDlg*)AfxGetApp()->m_pMainWnd;
	UpdateData(TRUE);
	dlg->OnSetGain(15,m_gain);
	str.Format("设置增益值到 %d",m_gain);
	dlg->SaveRecord(str);
}

LRESULT CComParam::OnDistanceDisp(WPARAM wParam, LPARAM lParam)
{
	
	int distance = (int)wParam;
	CString strValue;
	CACSDlg* dlg= (CACSDlg*)AfxGetApp()->m_pMainWnd;
	if (UWACInitParam.ADIOWorkMode)
	{
		strValue.Format("%.1f 米",distance*1.5);
		SetDlgItemText(IDC_STATIC_DISTANCE,strValue);
	}
	
// 	strValue = "当前通信距离: "+strValue;
// 	dlg->SaveRecord(strValue);
	return 0;
}
