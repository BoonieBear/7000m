// AdcpPage.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "AdcpPage.h"
#include "ACSDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdcpPage dialog


CAdcpPage::CAdcpPage(CWnd* pParent /*=NULL*/)
	: CDialog(CAdcpPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdcpPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

}


void CAdcpPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdcpPage)
	DDX_Control(pDX, IDC_BUTTON3, m_zView);
	DDX_Control(pDX, IDC_BUTTON2, m_yView);
	DDX_Control(pDX, IDC_BUTTON1, m_xView);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdcpPage, CDialog)
	//{{AFX_MSG_MAP(CAdcpPage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdcpPage message handlers

BOOL CAdcpPage::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here

	m_xView.m_defaultMaxY = 100;
	m_xView.m_defaultMinY = -100;
	m_xView.DividedUnits =5;
	
	m_xView.TotalLength = 10;// ADCP层数-1
	m_xView.m_pTotalYdata = xValue;

	m_yView.m_defaultMaxY = 100;
	m_yView.m_defaultMinY = -100;
	m_yView.DividedUnits =5;
	
	m_yView.TotalLength = 10;// ADCP层数-1
	m_yView.m_pTotalYdata = yValue;

	m_zView.m_defaultMaxY = 100;
	m_zView.m_defaultMinY = -100;
	m_zView.DividedUnits =5;
	m_zView.TotalLength = 10;// ADCP层数-1
	m_zView.m_pTotalYdata = zValue;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAdcpPage::UpdateView()
{
	CACSDlg* pAcsDlg = (CACSDlg*)GetParent();//父窗口指针
	for (int i=0;i<10;i++)
	{
		xValue[i] = (double)pAcsDlg->adcpdata.floorX[i];
		yValue[i] = (double)pAcsDlg->adcpdata.floorY[i];
		zValue[i] = (double)pAcsDlg->adcpdata.floorZ[i];
	}
	m_xView.m_pCurYdata = NULL;
	m_xView.m_pPSDYdata = NULL;
	m_xView.Invalidate(FALSE);
	m_yView.m_pCurYdata = NULL;
	m_yView.m_pPSDYdata = NULL;
	m_yView.Invalidate(FALSE);
	m_zView.m_pCurYdata = NULL;
	m_zView.m_pPSDYdata = NULL;
	m_zView.Invalidate(FALSE);
}
