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
	m_list.InsertColumn(0,_T("ͨ��"),LVCFMT_CENTER,80);	//add column title
	m_list.InsertColumn(1,_T("����"),LVCFMT_CENTER,60);	//add column title
	m_list.InsertColumn(2,_T("AGC����"),LVCFMT_CENTER,100);
	m_list.InsertColumn(3,_T("Chirp��ط�ֵ"),LVCFMT_CENTER,160);
	m_list.InsertColumn(4,_T("ͨ�����ϵ��"),LVCFMT_CENTER,150);
	m_list.InsertItem(1,"ͨ��1");
	m_list.InsertItem(2,"ͨ��2");
	m_list.InsertItem(3,"ͨ��3");
	m_list.InsertItem(4,"ͨ��4");
//	m_list.InsertItem(5,"ͨ��5");
//	m_list.InsertItem(6,"ͨ��6");
//	m_list.InsertItem(7,"ͨ��7");
//	m_list.InsertItem(8,"ͨ��8");
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
	str.Format("��������ֵ�� %d",m_gain);
	dlg->SaveRecord(str);
}

LRESULT CComParam::OnDistanceDisp(WPARAM wParam, LPARAM lParam)
{
	
	int distance = (int)wParam;
	CString strValue;
	CACSDlg* dlg= (CACSDlg*)AfxGetApp()->m_pMainWnd;
	if (UWACInitParam.ADIOWorkMode)
	{
		strValue.Format("%.1f ��",distance*1.5);
		SetDlgItemText(IDC_STATIC_DISTANCE,strValue);
	}
	
// 	strValue = "��ǰͨ�ž���: "+strValue;
// 	dlg->SaveRecord(strValue);
	return 0;
}
