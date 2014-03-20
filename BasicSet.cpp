// BasicSet.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "BasicSet.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBasicSet dialog


CBasicSet::CBasicSet(CWnd* pParent /*=NULL*/)
	: CDialog(CBasicSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(CBasicSet)
	m_Chann1 = FALSE;
	m_Chann2 = FALSE;
	m_Chann3 = FALSE;
	m_Chann4 = FALSE;
	m_Chann5 = FALSE;
	m_Chann6 = FALSE;
	m_DiscardLen = 0;
	m_Gain1 = 0;
	m_Gain2 = 0;
	m_Gain3 = 0;
	m_Gain4 = 0;
	m_Gain5 = 0;
	m_Gain6 = 0;
	m_IsTCM2Work = FALSE;
	m_RecvSampleRate = 0.0f;
	m_SyncConcurrence = 0;
	m_XMTSampleRate = 0.0f;     
	m_XMTDelayToSync = 0.0f;
	m_RecChannelNum =0;
	m_SametoGain1 = FALSE;
	m_ADIOID = FALSE;
	m_DSP01ID = FALSE;
	m_DSP02ID = FALSE;
	m_DSP11ID = FALSE;
	m_DSP12ID = FALSE;
	m_RecvDelaySync = 0.0f;
	m_IsSendADIOData = FALSE;
	m_ParamFactor = FALSE;
	m_PhaseFactor = FALSE;
	m_XMTAmpValue = 0.0f;
	m_AfterDecideBit = FALSE;
	m_AfterDecideData = FALSE;
	m_BeforeDecideData = FALSE;
	m_DopplerFactor = FALSE;
	m_mfsk_framenum = 0;
	m_mfsk_packet = 0;
	m_mfsk_recvpacket = 0;
	m_mfsk_recvframenum = 0;
	m_mpsk_framenum = 0;
	m_mpsk_packet = 0;
	m_mpsk_recvframenum = 0;
	m_mpsk_recvpacket = 0;
	//}}AFX_DATA_INIT
}


void CBasicSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CBasicSet)
	DDX_Control(pDX, IDC_SysWorkMode, m_SysWorkMode);
	DDX_Control(pDX, IDC_IsAGCWork, m_IsAGCWork);
	DDX_Control(pDX, IDC_ADIOWorkMode, m_ADIOWorkMode);
	DDX_Check(pDX, IDC_Chann1, m_Chann1);
	DDX_Check(pDX, IDC_Chann2, m_Chann2);
	DDX_Check(pDX, IDC_Chann3, m_Chann3);
	DDX_Check(pDX, IDC_Chann4, m_Chann4);
	DDX_Check(pDX, IDC_Chann5, m_Chann5);
	DDX_Check(pDX, IDC_Chann6, m_Chann6);
	DDX_Text(pDX, IDC_DiscardLen, m_DiscardLen);
	DDX_Text(pDX, IDC_Gain1, m_Gain1);
	DDX_Text(pDX, IDC_Gain2, m_Gain2);
	DDX_Text(pDX, IDC_Gain3, m_Gain3);
	DDX_Text(pDX, IDC_Gain4, m_Gain4);
	DDX_Text(pDX, IDC_Gain5, m_Gain5);
	DDX_Text(pDX, IDC_Gain6, m_Gain6);
	DDX_Check(pDX, IDC_IsTCM2Work, m_IsTCM2Work);
	DDX_Text(pDX, IDC_RecvSampleRate, m_RecvSampleRate);
	DDX_Text(pDX, IDC_SyncConcurrence, m_SyncConcurrence);
	DDX_Text(pDX, IDC_XMTSampleRate, m_XMTSampleRate);
	DDX_Text(pDX, IDC_XMTDelayToSync, m_XMTDelayToSync);
	DDX_Text(pDX, IDC_RecChannelNum, m_RecChannelNum);
	DDX_Check(pDX, IDC_SAMETOGAIN1, m_SametoGain1);
	DDX_Check(pDX, IDC_ADIOID, m_ADIOID);
	DDX_Check(pDX, IDC_DSP01ID, m_DSP01ID);
	DDX_Check(pDX, IDC_DSP02ID, m_DSP02ID);
	DDX_Check(pDX, IDC_DSP11ID, m_DSP11ID);
	DDX_Check(pDX, IDC_DSP12ID, m_DSP12ID);
	DDX_Text(pDX, IDC_RECVDELAYSYNC, m_RecvDelaySync);
	DDX_Check(pDX, IDC_IsSendADIOData, m_IsSendADIOData);
	DDX_Check(pDX, IDC_ParamFactor, m_ParamFactor);
	DDX_Check(pDX, IDC_PhaseFactor, m_PhaseFactor);
	DDX_Text(pDX, IDC_XMTAmpValue, m_XMTAmpValue);
	DDV_MinMaxFloat(pDX, m_XMTAmpValue, 5.e-003f, 1.f);
	DDX_Check(pDX, IDC_AfterDecideBit, m_AfterDecideBit);
	DDX_Check(pDX, IDC_AfterDecideData, m_AfterDecideData);
	DDX_Check(pDX, IDC_BeforeDecideData, m_BeforeDecideData);
	DDX_Check(pDX, IDC_DopplerFactor, m_DopplerFactor);
	DDX_Text(pDX, IDC_MFSK_FRAMENUM, m_mfsk_framenum);
	DDX_Text(pDX, IDC_MFSK_PACKET, m_mfsk_packet);
	DDX_Text(pDX, IDC_MFSK_RECVPACKET, m_mfsk_recvpacket);
	DDX_Text(pDX, IDC_MFSK_RECVFRAMENUM, m_mfsk_recvframenum);
	DDX_Text(pDX, IDC_MPSK_FRAMENUM, m_mpsk_framenum);
	DDX_Text(pDX, IDC_MPSK_PACKET, m_mpsk_packet);
	DDX_Text(pDX, IDC_MPSK_RECVFRAMENUM, m_mpsk_recvframenum);
	DDX_Text(pDX, IDC_MPSK_RECVPACKET, m_mpsk_recvpacket);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CBasicSet, CDialog)
	//{{AFX_MSG_MAP(CBasicSet)
	ON_BN_CLICKED(IDC_SAMETOGAIN1, OnSametogain1)
	ON_CBN_SELCHANGE(IDC_ADIOWorkMode, OnSelchangeADIOWorkMode)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBasicSet message handlers

void CBasicSet::OnSametogain1() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_SametoGain1 == TRUE)	
	{
		m_Gain2 = m_Gain1;
		m_Gain3 = m_Gain1;
		m_Gain4 = m_Gain1;
		m_Gain5 = m_Gain1;
		m_Gain6 = m_Gain1;
	}
	UpdateData(FALSE);
}

BOOL CBasicSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//设置参数
	 m_ADIOWorkMode.SetCurSel(UWACInitParam.ADIOWorkMode);
	 m_SysWorkMode.SetCurSel(UWACInitParam.SysWorkMode);
	 m_IsAGCWork.SetCurSel(UWACInitParam.IsAGCWork);

	 m_Chann1 = FALSE; if(UWACInitParam.ValidChannel&0x01)  m_Chann1 = TRUE;  
	 m_Chann2 = FALSE; if(UWACInitParam.ValidChannel&0x02)  m_Chann2 = TRUE;  
	 m_Chann3 = FALSE; if(UWACInitParam.ValidChannel&0x04)  m_Chann3 = TRUE;  
	 m_Chann4 = FALSE; if(UWACInitParam.ValidChannel&0x08)  m_Chann4 = TRUE;
	 m_RecChannelNum = UWACInitParam.RecvChannelNum;
	if( m_ADIOWorkMode.GetCurSel()==1)
	{
		 m_Chann5 = FALSE; if(UWACInitParam.ValidChannel&0x10)  m_Chann5 = TRUE;  
		 m_Chann6 = FALSE; if(UWACInitParam.ValidChannel&0x20)  m_Chann6 = TRUE;  
  
	}
	else
	{
		CButton * pButton;
		 m_Chann5 = FALSE;
		 m_Chann6 = FALSE;
		for(int i=0;i<2;i++){
			pButton= (CButton *) GetDlgItem(IDC_Chann5+i);
			pButton->EnableWindow(FALSE);
		}

	}
	
	 m_DiscardLen = UWACInitParam.DiscardLen;
	 m_Gain1 = UWACInitParam.AGCValue[0];
	 m_Gain2 = UWACInitParam.AGCValue[1];
	 m_Gain3 = UWACInitParam.AGCValue[2];
	 m_Gain4 = UWACInitParam.AGCValue[3];
	 m_Gain5 = UWACInitParam.AGCValue[4];
	 m_Gain6 = UWACInitParam.AGCValue[5];

	
	 m_IsSendADIOData = FALSE; 
	if (UWACInitParam.IsSendADIOData&0x01) 
		 m_IsSendADIOData = TRUE;

	 m_BeforeDecideData= FALSE;   
	if (UWACInitParam.IsSendDSPData&0x01) 
		 m_BeforeDecideData= TRUE; 

	 m_AfterDecideData = FALSE;
	if (UWACInitParam.IsSendDSPData&0x02) 
		 m_AfterDecideData= TRUE; 

	 m_AfterDecideBit= FALSE; 
	if (UWACInitParam.IsSendDSPData&0x04) 
		 m_AfterDecideBit= TRUE; 

	 m_ParamFactor= FALSE; 
	if (UWACInitParam.IsSendDSPData&0x100) 
		 m_ParamFactor= TRUE; 

	 m_PhaseFactor= FALSE; 
	if (UWACInitParam.IsSendDSPData&0x200) 
		 m_PhaseFactor= TRUE; 

	 m_DopplerFactor= FALSE; 
	if (UWACInitParam.IsSendDSPData&0x10000) 
		 m_DopplerFactor= TRUE; 

	 m_IsTCM2Work = FALSE; 
	if(UWACInitParam.IsTCM2Work) 
		 m_IsTCM2Work = TRUE;

	m_mpsk_packet = UWACInitParam.XMTMPSKPackageNum;
	m_mpsk_framenum = UWACInitParam.XMTMPSKPackFramNum;
	m_mfsk_packet = UWACInitParam.XMTPackageNum;
	m_mfsk_framenum = UWACInitParam.XMTPackFramNum;
	m_mpsk_recvpacket = UWACInitParam.RecvMPSKPackageNum;
	m_mpsk_recvframenum = UWACInitParam.RecvMPSKPackFramNum;
	m_mfsk_recvpacket = UWACInitParam.RecvPackageNum;
	m_mfsk_recvframenum = UWACInitParam.RecvPackFramNum;

	m_RecChannelNum = UWACInitParam.RecvChannelNum;
	m_RecvSampleRate = UWACInitParam.RecvSampleRate;
	m_SyncConcurrence = UWACInitParam.SyncConcurrence;
	m_XMTDelayToSync = UWACInitParam.XMTDelayToSync;
	m_XMTSampleRate = UWACInitParam.XMTSampleRate;
	m_XMTAmpValue = UWACInitParam.XMTAmpValue;
	m_RecvDelaySync = UWACInitParam.RecvDelayToSync; 
	


	m_ADIOID = FALSE; m_DSP01ID = FALSE;  m_DSP02ID = FALSE;
	m_DSP11ID = FALSE;  m_DSP12ID = FALSE;	
	if((UWACInitParam.LoadDestID&ADIOID)!=0)  m_ADIOID=TRUE;
	if((UWACInitParam.LoadDestID&DSP01ID)!=0)  m_DSP01ID=TRUE;
	if((UWACInitParam.LoadDestID&DSP02ID)!=0)  m_DSP02ID=TRUE;
	if((UWACInitParam.LoadDestID&DSP11ID)!=0)  m_DSP11ID=TRUE;
	if((UWACInitParam.LoadDestID&DSP12ID)!=0)  m_DSP12ID=TRUE;
	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CBasicSet::OnSelchangeADIOWorkMode() 
{
	// TODO: Add your control notification handler code here
	int i = m_ADIOWorkMode.GetCurSel();
	CButton * pButton;
	if (i==0)//主机模式
	{
		
		UWACInitParam.RecvModulation = MFSKMOD;
		m_Chann5 = FALSE;
		m_Chann6 = FALSE;
		m_DSP11ID=FALSE;
		m_DSP12ID=FALSE;
		for(int i=0;i<2;i++){
			pButton= (CButton *) GetDlgItem(IDC_Chann5+i);
			pButton->EnableWindow(FALSE);
		}
	}
	else
	{
		
		UWACInitParam.RecvModulation = MPSKMOD;
		m_Chann5 = TRUE;
		m_Chann6 = TRUE;
		m_DSP11ID=TRUE;
		m_DSP12ID=TRUE;
		for(int i=0;i<2;i++){
			pButton= (CButton *) GetDlgItem(IDC_Chann5+i);
			pButton->EnableWindow(TRUE);
		}
	}
	UpdateData(FALSE);
}
