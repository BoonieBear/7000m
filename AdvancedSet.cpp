// AdvancedSet.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "AdvancedSet.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAdvancedSet dialog


CAdvancedSet::CAdvancedSet(CWnd* pParent /*=NULL*/)
	: CDialog(CAdvancedSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAdvancedSet)
	m_AftFilterTap = 0;
	m_AlfaPhase = 0.0f;
	m_BeltaMu = 0.0f;
	m_ChirpLen = 0.0f;
	m_ChirpStartF = 0.0f;
	m_ChirpStopF = 0.0f;
	m_GamaMax = 0.0f;
	m_GamaMin = 0.0f;
	m_InterleaverLen = 0;
	m_IterationNum = 0;
	m_MFSKAftGuardLag = 0.0f;
	m_MFSKInterGuardLag = 0.0f;
	m_MFSKPreGuardLag = 0.0f;
	m_MPSKAftGuardLag = 0.0f;
	m_MPSKDataSymbolNum = 0;
	m_MFSKDataSymbolNum = 0;
	m_MPSKPreGuardLag = 0.0f;
	m_MPSKTrainSymbolNum = 0;
	m_MuMax = 0.0f;
	m_MuMin = 0.0f;
	m_PreFilterTap =0;
	m_SlideWinLen = 0;
	m_MPSK_chirp_inter = 0;
	m_MFSK_chirp_inter = 0;
	m_cycle_prefix = 0;
	//}}AFX_DATA_INIT
}


void CAdvancedSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAdvancedSet)
	DDX_Control(pDX, IDC_CHECK1, m_check);
	DDX_Text(pDX, IDC_AftFilterTap, m_AftFilterTap);
	DDX_Text(pDX, IDC_AlfaPhase, m_AlfaPhase);
	DDX_Text(pDX, IDC_BeltaMu, m_BeltaMu);
	DDX_Text(pDX, IDC_ChirpLen, m_ChirpLen);
	DDX_Text(pDX, IDC_ChirpStartF, m_ChirpStartF);
	DDX_Text(pDX, IDC_ChirpStopF, m_ChirpStopF);
	DDX_Text(pDX, IDC_GamaMax, m_GamaMax);
	DDX_Text(pDX, IDC_GamaMin, m_GamaMin);
	DDX_Text(pDX, IDC_InterLeaverLen, m_InterleaverLen);
	DDX_Text(pDX, IDC_IterationNum, m_IterationNum);
	DDX_Text(pDX, IDC_MFSKAftGuardLag, m_MFSKAftGuardLag);
	DDX_Text(pDX, IDC_MFSKInterGuardLag, m_MFSKInterGuardLag);
	DDX_Text(pDX, IDC_MFSKPreGuardLag, m_MFSKPreGuardLag);
	DDX_Text(pDX, IDC_MPSKAftGuardLag, m_MPSKAftGuardLag);
	DDX_Text(pDX, IDC_MPSKDataSymbolNum, m_MPSKDataSymbolNum);
	DDX_Text(pDX, IDC_MFSKataSymbolNum, m_MFSKDataSymbolNum);
	DDX_Text(pDX, IDC_MPSKPreGuardLag, m_MPSKPreGuardLag);
	DDX_Text(pDX, IDC_MPSKTrainSymbolNum, m_MPSKTrainSymbolNum);
	DDX_Text(pDX, IDC_MuMax, m_MuMax);
	DDX_Text(pDX, IDC_MuMin, m_MuMin);
 	DDX_Text(pDX, IDC_PreFilterTap, m_PreFilterTap);
 	DDX_Text(pDX, IDC_SlideWinLen, m_SlideWinLen);
	DDX_Text(pDX, IDC_MPSK_chirp_inter, m_MPSK_chirp_inter);
	DDX_Text(pDX, IDC_MFSK_chirp_inter, m_MFSK_chirp_inter);
	DDX_Text(pDX, IDC_cycle_prefix, m_cycle_prefix);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAdvancedSet, CDialog)
	//{{AFX_MSG_MAP(CAdvancedSet)
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_CHECK1, OnCheck1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAdvancedSet message handlers

BOOL CAdvancedSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_AftFilterTap = UWACInitParam.AftFilterTap;
	m_AlfaPhase = UWACInitParam.AlfaPhase;
	m_BeltaMu = UWACInitParam.BeltaMu;
	m_check.SetCheck(1);

	m_ChirpLen = UWACInitParam.ChirpLen;
	m_ChirpStartF = UWACInitParam.ChirpStartF;
	m_ChirpStopF = UWACInitParam.ChirpStopF;
	m_MFSK_chirp_inter = UWACInitParam.MFSK_chirp_inter;
	m_MPSK_chirp_inter = UWACInitParam.MPSK_chirp_inter;
	m_cycle_prefix = UWACInitParam.Cycle_prefix;

	m_GamaMax = UWACInitParam.GamaMax;
	m_GamaMin = UWACInitParam.GamaMin ;
	m_InterleaverLen = UWACInitParam.InterleaverLen;


	m_IterationNum = UWACInitParam.IterationNum;
	m_MFSKAftGuardLag = UWACInitParam.MFSKAftGuardLag;
	m_MFSKInterGuardLag = UWACInitParam.MFSKInterGuardLag;
	m_MFSKPreGuardLag = UWACInitParam.MFSKPreGuardLag;
	m_MPSKAftGuardLag = UWACInitParam.MPSKAftGuardLag;
	m_MPSKDataSymbolNum = UWACInitParam.MPSKDataSymbolNum ;
	m_MFSKDataSymbolNum = UWACInitParam.MFSKDataSymbolNum;
	m_MPSKPreGuardLag = UWACInitParam.MPSKPreGuardLag;
	m_MPSKTrainSymbolNum = UWACInitParam.MPSKTrainSymbolNum;
	m_MuMax = UWACInitParam.MuMax;
	m_MuMin = UWACInitParam.MuMin;
	m_PreFilterTap = UWACInitParam.PreFilterTap;
	m_SlideWinLen = UWACInitParam.SlideWinLen;
	UpdateData(FALSE);
	hyLPT = NULL;
	if (!LPT_Open(&hyLPT))  //打开打印机端口
    {
        AfxMessageBox("Error while opening LPT:\n");
        //printf ("%s", LPT_ErrorString);
        //return 0;
    }
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CAdvancedSet::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CAdvancedSet::OnCheck1() 
{
	// TODO: Add your control notification handler code here
	if (m_check.GetCheck())
	{
		UsblEnableCheck = TRUE;
	}
	else
	{
		UsblEnableCheck = FALSE;
		// 		写并口
		LPT_Writedata(hyLPT,0xB9);  //使能
		bFirstRecvData = TRUE;
		KillTimer(USBLENABLE);
		KillTimer(USBLTIME);
		KillTimer(USBLTIME2);
		KillTimer(USBLTIME3);
	}
}
