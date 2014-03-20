// OptionSet.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "OptionSet.h"
#include "ACSDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// COptionSet dialog


COptionSet::COptionSet(CWnd* pParent /*=NULL*/)
	: CDialog(COptionSet::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionSet)
	m_basic = TRUE;
	m_advanced = FALSE;
	//}}AFX_DATA_INIT
}


void COptionSet::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionSet)
	DDX_Check(pDX, IDC_BASIC, m_basic);
	DDX_Check(pDX, IDC_ADVANCED, m_advanced);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(COptionSet, CDialog)
	//{{AFX_MSG_MAP(COptionSet)
	ON_BN_CLICKED(IDC_SAVE, OnSave)
	ON_BN_CLICKED(IDC_LOAD, OnLoadSet)
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	ON_BN_CLICKED(IDC_BASIC, OnBasic)
	ON_BN_CLICKED(IDC_SAVEAS, OnSaveas)
	ON_BN_CLICKED(IDC_BUTTON1, OnHalt)
	ON_BN_CLICKED(IDC_SetTime, OnSetTime)
	ON_BN_CLICKED(IDC_RESETADIO, OnResetadio)
	ON_BN_CLICKED(IDC_DiSCONNECT, OnDiSCONNECT)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionSet message handlers

void COptionSet::OnSave() 
{
	// TODO: Add your control notification handler code here
	pBasicSet.UpdateData(TRUE);
	pAdvancedSet.UpdateData(TRUE);
	
	//对工作参数进行赋值
	UWACInitParam.ADIOWorkMode=pBasicSet.m_ADIOWorkMode.GetCurSel();;
/*	UWACInitParam.XMTModulation = XMTModulation;*/
	UWACInitParam.SysWorkMode = pBasicSet.m_SysWorkMode.GetCurSel();
	
// 	UWACInitParam.RecvModulation = RecvModulation;
	UWACInitParam.IsAGCWork = pBasicSet.m_IsAGCWork.GetCurSel();;

	UWACInitParam.AftFilterTap = pAdvancedSet.m_AftFilterTap;
	UWACInitParam.AlfaPhase = pAdvancedSet.m_AlfaPhase;
	UWACInitParam.BeltaMu = pAdvancedSet.m_BeltaMu;
	UWACInitParam.XMTCodedFramNum = 28;
	UWACInitParam.RecvCodedFramNum =UWACInitParam.RecvMPSKPackageNum*UWACInitParam.RecvMPSKPackFramNum;
	UWACInitParam.ValidChannel = 0;
	if(pBasicSet.m_Chann1) UWACInitParam.ValidChannel+= 0x01;  
	if(pBasicSet.m_Chann2) UWACInitParam.ValidChannel+= 0x02;  
	if(pBasicSet.m_Chann3) UWACInitParam.ValidChannel+= 0x04;  
	if(pBasicSet.m_Chann4) UWACInitParam.ValidChannel+= 0x08; 
	if(UWACInitParam.ADIOWorkMode==1)
	{
		if(pBasicSet.m_Chann5) UWACInitParam.ValidChannel+= 0x10;  
		if(pBasicSet.m_Chann6) UWACInitParam.ValidChannel+= 0x20;  
	}
	
	UWACInitParam.ChirpLen = pAdvancedSet.m_ChirpLen;
	UWACInitParam.ChirpStartF = pAdvancedSet.m_ChirpStartF;
	UWACInitParam.ChirpStopF = pAdvancedSet.m_ChirpStopF;
	UWACInitParam.DiscardLen = pBasicSet.m_DiscardLen;
	UWACInitParam.AGCValue[0] = pBasicSet.m_Gain1;
	UWACInitParam.AGCValue[1] = pBasicSet.m_Gain2;
	UWACInitParam.AGCValue[2] = pBasicSet.m_Gain3;
	UWACInitParam.AGCValue[3] = pBasicSet.m_Gain4;
	UWACInitParam.AGCValue[4] = pBasicSet.m_Gain5;
	UWACInitParam.AGCValue[5] = pBasicSet.m_Gain6;
	UWACInitParam.AGCValue[6] = 0;
	UWACInitParam.AGCValue[7] = 0;
	UWACInitParam.GamaMax = pAdvancedSet.m_GamaMax;
	UWACInitParam.GamaMin =  pAdvancedSet.m_GamaMin;
	UWACInitParam.InterleaverLen = pAdvancedSet.m_InterleaverLen;
	
	UWACInitParam.IsSendADIOData = 0;
	if(pBasicSet.m_IsSendADIOData) 
		UWACInitParam.IsSendADIOData+=0x01;
	UWACInitParam.IsSendDSPData = 0;
	if(pBasicSet.m_BeforeDecideData)	
		UWACInitParam.IsSendDSPData+=0x01;
	if(pBasicSet.m_AfterDecideData)	
		UWACInitParam.IsSendDSPData+=0x02;
	if(pBasicSet.m_AfterDecideBit)	
		UWACInitParam.IsSendDSPData+=0x04;
	if(pBasicSet.m_ParamFactor)	
		UWACInitParam.IsSendDSPData+=0x100;
	if(pBasicSet.m_PhaseFactor)	
		UWACInitParam.IsSendDSPData+=0x200;
	if(pBasicSet.m_DopplerFactor)	
		UWACInitParam.IsSendDSPData+=0x10000;

	UWACInitParam.IsTCM2Work = 0; 
	if(pBasicSet.m_IsTCM2Work) 
		UWACInitParam.IsTCM2Work = 1;

	UWACInitParam.IterationNum = pAdvancedSet.m_IterationNum;
	UWACInitParam.MFSKAftGuardLag = pAdvancedSet.m_MFSKAftGuardLag;
	UWACInitParam.MFSKInterGuardLag = pAdvancedSet.m_MFSKInterGuardLag;
	UWACInitParam.MFSKPreGuardLag = pAdvancedSet.m_MFSKPreGuardLag;
	UWACInitParam.MPSKAftGuardLag = pAdvancedSet.m_MPSKAftGuardLag;
	UWACInitParam.MPSKDataSymbolNum =  pAdvancedSet.m_MPSKDataSymbolNum;
	UWACInitParam.MFSKDataSymbolNum = pAdvancedSet.m_MFSKDataSymbolNum;
	UWACInitParam.MPSKPreGuardLag = pAdvancedSet.m_MPSKPreGuardLag;
	UWACInitParam.MPSKTrainSymbolNum = pAdvancedSet.m_MPSKTrainSymbolNum;
	UWACInitParam.MuMax = pAdvancedSet.m_MuMax;
	UWACInitParam.MuMin = pAdvancedSet.m_MuMin;
	UWACInitParam.PreFilterTap = pAdvancedSet.m_PreFilterTap;
	UWACInitParam.RecvChannelNum = pBasicSet.m_RecChannelNum;
// 	UWACInitParam.RecvCodedFramNum = m_RecvCodedFramNum;
// 	UWACInitParam.RecvPackageNum = m_RecvPackageNum;
// 	UWACInitParam.RecvPackFramNum = m_RecvPackFrameNum;
	UWACInitParam.RecvSampleRate = pBasicSet.m_RecvSampleRate;
	UWACInitParam.SlideWinLen = pAdvancedSet.m_SlideWinLen;
	UWACInitParam.SyncConcurrence = pBasicSet.m_SyncConcurrence;
	UWACInitParam.XMTAmpValue = pBasicSet.m_XMTAmpValue ;
// 	UWACInitParam.XMTChannelNo = m_XMTChannelNo;
//	UWACInitParam.XMTCodedFramNum = m_XMTCodedFramNum;
	UWACInitParam.XMTDelayToSync = pBasicSet.m_XMTDelayToSync;
// 	UWACInitParam.XMTPackageNum = m_XMTPackageNum;
// 	UWACInitParam.XMTPackFramNum = m_XMTPackFrameNum;
	UWACInitParam.XMTSampleRate = pBasicSet.m_XMTSampleRate;
	UWACInitParam.RecvDelayToSync = pBasicSet.m_RecvDelaySync; 
	UWACInitParam.LoadDestID = 0;
	UWACInitParam.PC104SaveData=UWACCMD_PC104_SAVE_NO_DATA;

	UWACInitParam.MFSK_chirp_inter = pAdvancedSet.m_MFSK_chirp_inter;
	UWACInitParam.MPSK_chirp_inter = pAdvancedSet.m_MPSK_chirp_inter;
	UWACInitParam.Cycle_prefix = pAdvancedSet.m_cycle_prefix;
	if (!UWACInitParam.ADIOWorkMode)
	{
		UWACInitParam.RecvModulation = MFSKMOD;
	}
	else
	{
		UWACInitParam.RecvModulation = MPSKMOD;
	}
	UWACInitParam.XMTMPSKPackageNum = pBasicSet.m_mpsk_packet;
	UWACInitParam.XMTMPSKPackFramNum = pBasicSet.m_mpsk_framenum;
	UWACInitParam.XMTPackageNum = pBasicSet.m_mfsk_packet;
	UWACInitParam.XMTPackFramNum = pBasicSet.m_mfsk_framenum;
	UWACInitParam.RecvMPSKPackageNum = pBasicSet.m_mpsk_recvpacket;
	UWACInitParam.RecvMPSKPackFramNum = pBasicSet.m_mpsk_recvframenum;
	UWACInitParam.RecvPackageNum = pBasicSet.m_mfsk_recvpacket;
	UWACInitParam.RecvPackFramNum = pBasicSet.m_mfsk_recvframenum;
	if(pBasicSet.m_ADIOID)	
		UWACInitParam.LoadDestID+=ADIOID;
	if(pBasicSet.m_DSP01ID)   
		UWACInitParam.LoadDestID+=DSP01ID;
	if(pBasicSet.m_DSP02ID)   
		UWACInitParam.LoadDestID+=DSP02ID;
	if(pBasicSet.m_DSP11ID)   
		UWACInitParam.LoadDestID+=DSP11ID;
	if(pBasicSet.m_DSP12ID)   
		UWACInitParam.LoadDestID+=DSP12ID;

	CString m_sFilename = "default.sysinit";
	CFile SetFile;
	//保存参数到文件中
	if(!SetFile.Open(m_sFilename,CFile::modeCreate | CFile::modeWrite))
	{
		TRACE0("文件打不开");
		return;
	}
	SetFile.Write(&UWACInitParam,sizeof(UWACINITPARA));
	SetFile.Close();
	CDialog::OnOK();
}


void COptionSet::OnLoadSet() 
{
	// TODO: Add your control notification handler code here
	//输入文件名
	static char BASED_CODE szFilter[]={"系统初始化文件(*.sysinit)|*.sysinit|"}; 
  	CDialog* pAppFrame = (CDialog*) AfxGetApp()->m_pMainWnd;
	CFileDialog theDataFile( TRUE,  _T("*.sysinit") , NULL , OFN_HIDEREADONLY, 
			szFilter , pAppFrame  );
	CString m_sFilename;

	if( theDataFile.DoModal()!=IDOK )
		return;

	m_sFilename =  theDataFile.GetPathName( );
	
	CFile SetFile;


	//从参数文件中读入参数
	if(!SetFile.Open(m_sFilename,CFile::modeRead))
	{
			TRACE0("文件打不开读");
			return;
		}
	SetFile.Read(&UWACInitParam,sizeof(UWACINITPARA));
	SetFile.Close();
	if (UWACInitParam.ADIOWorkMode != UWAcommparam.Mode)
	{
		AfxMessageBox("载入配置文件模式不符！请重新选择配置文件");
		return;
	}
	
	//设置参数
	pBasicSet.m_ADIOWorkMode.SetCurSel(UWACInitParam.ADIOWorkMode);
/*	XMTModulation = UWACInitParam.XMTModulation;*/
	pBasicSet.m_SysWorkMode.SetCurSel(UWACInitParam.SysWorkMode);
// 	RecvModulation = UWACInitParam.RecvModulation;
	pBasicSet.m_IsAGCWork.SetCurSel(UWACInitParam.IsAGCWork);

	pAdvancedSet.m_AftFilterTap = UWACInitParam.AftFilterTap;
	pAdvancedSet.m_AlfaPhase = UWACInitParam.AlfaPhase;
	pAdvancedSet.m_BeltaMu = UWACInitParam.BeltaMu;
	pBasicSet.m_Chann1 = FALSE; if(UWACInitParam.ValidChannel&0x01) pBasicSet.m_Chann1 = TRUE;  
	pBasicSet.m_Chann2 = FALSE; if(UWACInitParam.ValidChannel&0x02) pBasicSet.m_Chann2 = TRUE;  
	pBasicSet.m_Chann3 = FALSE; if(UWACInitParam.ValidChannel&0x04) pBasicSet.m_Chann3 = TRUE;  
	pBasicSet.m_Chann4 = FALSE; if(UWACInitParam.ValidChannel&0x08) pBasicSet.m_Chann4 = TRUE;
	pBasicSet.m_RecChannelNum = UWACInitParam.RecvChannelNum;
	if(pBasicSet.m_RecChannelNum==6)
	{
		pBasicSet.m_Chann5 = FALSE; if(UWACInitParam.ValidChannel&0x10) pBasicSet.m_Chann5 = TRUE;  
		pBasicSet.m_Chann6 = FALSE; if(UWACInitParam.ValidChannel&0x20) pBasicSet.m_Chann6 = TRUE;  
  
	}
	else
	{
		CButton * pButton;
		pBasicSet.m_Chann5 = FALSE;
		pBasicSet.m_Chann6 = FALSE;
		for(int i=0;i<2;i++){
			pButton= (CButton *)pBasicSet.GetDlgItem(IDC_Chann5+i);
			pButton->EnableWindow(FALSE);
		}

	}
	
	pAdvancedSet.m_ChirpLen = UWACInitParam.ChirpLen;
	pAdvancedSet.m_ChirpStartF = UWACInitParam.ChirpStartF;
	pAdvancedSet.m_ChirpStopF = UWACInitParam.ChirpStopF;
	pBasicSet.m_DiscardLen = UWACInitParam.DiscardLen;
	pBasicSet.m_Gain1 = UWACInitParam.AGCValue[0];
	pBasicSet.m_Gain2 = UWACInitParam.AGCValue[1];
	pBasicSet.m_Gain3 = UWACInitParam.AGCValue[2];
	pBasicSet.m_Gain4 = UWACInitParam.AGCValue[3];
	pBasicSet.m_Gain5 = UWACInitParam.AGCValue[4];
	pBasicSet.m_Gain6 = UWACInitParam.AGCValue[5];
	pAdvancedSet.m_GamaMax = UWACInitParam.GamaMax;
	pAdvancedSet.m_GamaMin = UWACInitParam.GamaMin ;
	pAdvancedSet.m_InterleaverLen = UWACInitParam.InterleaverLen;

	pAdvancedSet.m_cycle_prefix = UWACInitParam.Cycle_prefix;
	pAdvancedSet.m_MFSK_chirp_inter = UWACInitParam.MFSK_chirp_inter;
	pAdvancedSet.m_MPSK_chirp_inter = UWACInitParam.MPSK_chirp_inter;

	pBasicSet.m_IsSendADIOData = FALSE; 
	if (UWACInitParam.IsSendADIOData&0x01) 
		pBasicSet.m_IsSendADIOData = TRUE;

	pBasicSet.m_BeforeDecideData= FALSE;   
	if (UWACInitParam.IsSendDSPData&0x01) 
		pBasicSet.m_BeforeDecideData= TRUE; 

	pBasicSet.m_AfterDecideData = FALSE;
	if (UWACInitParam.IsSendDSPData&0x02) 
		pBasicSet.m_AfterDecideData= TRUE; 

	pBasicSet.m_AfterDecideBit= FALSE; 
	if (UWACInitParam.IsSendDSPData&0x04) 
		pBasicSet.m_AfterDecideBit= TRUE; 

	pBasicSet.m_ParamFactor= FALSE; 
	if (UWACInitParam.IsSendDSPData&0x100) 
		pBasicSet.m_ParamFactor= TRUE; 

	pBasicSet.m_PhaseFactor= FALSE; 
	if (UWACInitParam.IsSendDSPData&0x200) 
		pBasicSet.m_PhaseFactor= TRUE; 

	pBasicSet.m_DopplerFactor= FALSE; 
	if (UWACInitParam.IsSendDSPData&0x10000) 
		pBasicSet.m_DopplerFactor= TRUE; 

	pBasicSet.m_IsTCM2Work = FALSE; 
	if(UWACInitParam.IsTCM2Work) 
		pBasicSet.m_IsTCM2Work = TRUE;

	pAdvancedSet.m_IterationNum = UWACInitParam.IterationNum;
	pAdvancedSet.m_MFSKAftGuardLag = UWACInitParam.MFSKAftGuardLag;
	pAdvancedSet.m_MFSKInterGuardLag = UWACInitParam.MFSKInterGuardLag;
	pAdvancedSet.m_MFSKPreGuardLag = UWACInitParam.MFSKPreGuardLag;
	pAdvancedSet.m_MPSKAftGuardLag = UWACInitParam.MPSKAftGuardLag;
	pAdvancedSet.m_MPSKDataSymbolNum = UWACInitParam.MPSKDataSymbolNum ;
	pAdvancedSet.m_MFSKDataSymbolNum = UWACInitParam.MFSKDataSymbolNum;
	pAdvancedSet.m_MPSKPreGuardLag = UWACInitParam.MPSKPreGuardLag;
	pAdvancedSet.m_MPSKTrainSymbolNum = UWACInitParam.MPSKTrainSymbolNum;
	pAdvancedSet.m_MuMax = UWACInitParam.MuMax;
	pAdvancedSet.m_MuMin = UWACInitParam.MuMin;
	pAdvancedSet.m_PreFilterTap = UWACInitParam.PreFilterTap;
	pBasicSet.m_RecChannelNum = UWACInitParam.RecvChannelNum;
// 	m_RecvCodedFramNum = UWACInitParam.RecvCodedFramNum;
// 	m_RecvPackageNum = UWACInitParam.RecvPackageNum;
// 	m_RecvPackFrameNum = UWACInitParam.RecvPackFramNum;
	pBasicSet.m_RecvSampleRate = UWACInitParam.RecvSampleRate;
	pAdvancedSet.m_SlideWinLen = UWACInitParam.SlideWinLen;
	pBasicSet.m_SyncConcurrence = UWACInitParam.SyncConcurrence;
/*	m_XMTAmpValue  = UWACInitParam.XMTAmpValue;*/
// 	m_XMTChannelNo = UWACInitParam.XMTChannelNo;
// 	m_XMTCodedFramNum = UWACInitParam.XMTCodedFramNum;
	pBasicSet.m_XMTDelayToSync = UWACInitParam.XMTDelayToSync;
// 	m_XMTPackageNum = UWACInitParam.XMTPackageNum;
// 	m_XMTPackFrameNum = UWACInitParam.XMTPackFramNum;
	pBasicSet.m_XMTSampleRate = UWACInitParam.XMTSampleRate;
	pBasicSet.m_mpsk_packet = UWACInitParam.XMTMPSKPackageNum;
	pBasicSet.m_mpsk_framenum = UWACInitParam.XMTMPSKPackFramNum;
	pBasicSet.m_mfsk_packet = UWACInitParam.XMTPackageNum;
	pBasicSet.m_mfsk_framenum = UWACInitParam.XMTPackFramNum;
	pBasicSet.m_mpsk_recvpacket = UWACInitParam.RecvMPSKPackageNum;
	pBasicSet.m_mpsk_recvframenum = UWACInitParam.RecvMPSKPackFramNum;
	pBasicSet.m_mfsk_recvpacket = UWACInitParam.RecvPackageNum;
	pBasicSet.m_mfsk_recvframenum = UWACInitParam.RecvPackFramNum;
	
	pBasicSet.m_RecvDelaySync = UWACInitParam.RecvDelayToSync;
	 
	pBasicSet.m_ADIOID = FALSE;pBasicSet.m_DSP01ID = FALSE; pBasicSet.m_DSP02ID = FALSE;
	pBasicSet.m_DSP11ID = FALSE; pBasicSet.m_DSP12ID = FALSE;	
	if((UWACInitParam.LoadDestID&ADIOID)!=0) pBasicSet.m_ADIOID=TRUE;
	if((UWACInitParam.LoadDestID&DSP01ID)!=0) pBasicSet.m_DSP01ID=TRUE;
	if((UWACInitParam.LoadDestID&DSP02ID)!=0) pBasicSet.m_DSP02ID=TRUE;
	if((UWACInitParam.LoadDestID&DSP11ID)!=0) pBasicSet.m_DSP11ID=TRUE;
	if((UWACInitParam.LoadDestID&DSP12ID)!=0) pBasicSet.m_DSP12ID=TRUE;
		
	pBasicSet.UpdateData(FALSE);
	pAdvancedSet.UpdateData(FALSE);

}

BOOL COptionSet::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CRect rect;
	GetClientRect(&rect);
	rect.bottom-=45;
	pBasicSet.Create(IDD_BASIC,this);
	pBasicSet.MoveWindow(&rect);
	pAdvancedSet.Create(IDD_ADVANCED,this);
	pAdvancedSet.MoveWindow(&rect);
	m_basic =TRUE;
	m_advanced=FALSE;
	UpdateData(FALSE);
	pBasicSet.ShowWindow(TRUE);
	pAdvancedSet.ShowWindow(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void COptionSet::OnAdvanced() 
{
	// TODO: Add your control notification handler code here

	m_basic =FALSE;
	m_advanced=TRUE;
	UpdateData(FALSE);
	pBasicSet.ShowWindow(FALSE);
	pAdvancedSet.ShowWindow(TRUE);
}


void COptionSet::OnBasic() 
{
	// TODO: Add your control notification handler code here
	m_basic =TRUE;
	m_advanced=FALSE;
	UpdateData(FALSE);
	pBasicSet.ShowWindow(TRUE);
	pAdvancedSet.ShowWindow(FALSE);

}

BOOL COptionSet::CheckSetting()
{	
	pBasicSet.UpdateData(TRUE);
	pAdvancedSet.UpdateData(TRUE);
	if(pBasicSet.m_ADIOWorkMode.GetCurSel()==0)
	{
		if(pBasicSet.m_RecChannelNum>4)
		{
			AfxMessageBox("主机接收换能器通道不能大于4！请修改");
			return  FALSE;
		}
	}
// 	float dotlength = 1/pBasicSet.m_RecvSampleRate;
// 	float chirp_dropping_MSEC = pAdvancedSet.m_ChirpLen*dotlength;
// 	float pocket_sync_null_MSEC = pAdvancedSet.m_MFSK_chirp_inter;
// 	float chirp_raising_MSEC = chirp_dropping_MSEC;
// 	
// 	int pocket_contain_frames_NUMB = pBasicSet.m_mfsk_recvframenum;
// 	chirp_dropping_MSEC+pocket_sync_null_MSEC+pocket_contain_frames_NUMB*frame_MSEC+chirp_raising_MSEC
// 	chirp_raising_MSEC+frame_chirp_null_MSEC +frame_contain_symbols_NUMB *symbol_MSEC+frame_data_null_MSEC
	return TRUE;
}

void COptionSet::OnSaveas() 
{
	// TODO: Add your control notification handler code here
	pBasicSet.UpdateData(TRUE);
	pAdvancedSet.UpdateData(TRUE);
	
	//对工作参数进行赋值
	UWACInitParam.ADIOWorkMode=pBasicSet.m_ADIOWorkMode.GetCurSel();;
/*	UWACInitParam.XMTModulation = XMTModulation;*/
	UWACInitParam.SysWorkMode = pBasicSet.m_SysWorkMode.GetCurSel();
// 	UWACInitParam.RecvModulation = RecvModulation;
	UWACInitParam.IsAGCWork = pBasicSet.m_IsAGCWork.GetCurSel();;
	
	UWACInitParam.AftFilterTap = pAdvancedSet.m_AftFilterTap;
	UWACInitParam.AlfaPhase = pAdvancedSet.m_AlfaPhase;
	UWACInitParam.BeltaMu = pAdvancedSet.m_BeltaMu;
	
	UWACInitParam.ValidChannel = 0;
	if(pBasicSet.m_Chann1) UWACInitParam.ValidChannel+= 0x01;  
	if(pBasicSet.m_Chann2) UWACInitParam.ValidChannel+= 0x02;  
	if(pBasicSet.m_Chann3) UWACInitParam.ValidChannel+= 0x04;  
	if(pBasicSet.m_Chann4) UWACInitParam.ValidChannel+= 0x08; 
	if(UWACInitParam.ADIOWorkMode==1)
	{
		if(pBasicSet.m_Chann5) UWACInitParam.ValidChannel+= 0x10;  
		if(pBasicSet.m_Chann6) UWACInitParam.ValidChannel+= 0x20;  
	}
	UWACInitParam.XMTCodedFramNum = 28;
	UWACInitParam.RecvCodedFramNum =UWACInitParam.RecvMPSKPackageNum*UWACInitParam.RecvMPSKPackFramNum;
	UWACInitParam.ChirpLen = pAdvancedSet.m_ChirpLen;
	UWACInitParam.ChirpStartF = pAdvancedSet.m_ChirpStartF;
	UWACInitParam.ChirpStopF = pAdvancedSet.m_ChirpStopF;
	UWACInitParam.DiscardLen = pBasicSet.m_DiscardLen;
	UWACInitParam.AGCValue[0] = pBasicSet.m_Gain1;
	UWACInitParam.AGCValue[1] = pBasicSet.m_Gain2;
	UWACInitParam.AGCValue[2] = pBasicSet.m_Gain3;
	UWACInitParam.AGCValue[3] = pBasicSet.m_Gain4;
	UWACInitParam.AGCValue[4] = pBasicSet.m_Gain5;
	UWACInitParam.AGCValue[5] = pBasicSet.m_Gain6;
	UWACInitParam.AGCValue[6] = 0;
	UWACInitParam.AGCValue[7] = 0;
	UWACInitParam.GamaMax = pAdvancedSet.m_GamaMax;
	UWACInitParam.GamaMin =  pAdvancedSet.m_GamaMin;
	UWACInitParam.InterleaverLen = pAdvancedSet.m_InterleaverLen;
	
	UWACInitParam.IsSendADIOData = 0;
	if(pBasicSet.m_IsSendADIOData) 
		UWACInitParam.IsSendADIOData+=0x01;
	UWACInitParam.IsSendDSPData = 0;
	if(pBasicSet.m_BeforeDecideData)	
		UWACInitParam.IsSendDSPData+=0x01;
	if(pBasicSet.m_AfterDecideData)	
		UWACInitParam.IsSendDSPData+=0x02;
	if(pBasicSet.m_AfterDecideBit)	
		UWACInitParam.IsSendDSPData+=0x04;
	if(pBasicSet.m_ParamFactor)	
		UWACInitParam.IsSendDSPData+=0x100;
	if(pBasicSet.m_PhaseFactor)	
		UWACInitParam.IsSendDSPData+=0x200;
	if(pBasicSet.m_DopplerFactor)	
		UWACInitParam.IsSendDSPData+=0x10000;

	UWACInitParam.IsTCM2Work = 0; 
	if(pBasicSet.m_IsTCM2Work) 
		UWACInitParam.IsTCM2Work = 1;

	UWACInitParam.IterationNum = pAdvancedSet.m_IterationNum;
	UWACInitParam.MFSKAftGuardLag = pAdvancedSet.m_MFSKAftGuardLag;
	UWACInitParam.MFSKInterGuardLag = pAdvancedSet.m_MFSKInterGuardLag;
	UWACInitParam.MFSKPreGuardLag = pAdvancedSet.m_MFSKPreGuardLag;
	UWACInitParam.MPSKAftGuardLag = pAdvancedSet.m_MPSKAftGuardLag;
	UWACInitParam.MPSKDataSymbolNum =  pAdvancedSet.m_MPSKDataSymbolNum;
	UWACInitParam.MFSKDataSymbolNum = pAdvancedSet.m_MFSKDataSymbolNum;
	UWACInitParam.MPSKPreGuardLag = pAdvancedSet.m_MPSKPreGuardLag;
	UWACInitParam.MPSKTrainSymbolNum = pAdvancedSet.m_MPSKTrainSymbolNum;
	UWACInitParam.MuMax = pAdvancedSet.m_MuMax;
	UWACInitParam.MuMin = pAdvancedSet.m_MuMin;
	UWACInitParam.PreFilterTap = pAdvancedSet.m_PreFilterTap;
	UWACInitParam.RecvChannelNum = pBasicSet.m_RecChannelNum;
// 	UWACInitParam.RecvCodedFramNum = m_RecvCodedFramNum;
// 	UWACInitParam.RecvPackageNum = m_RecvPackageNum;
// 	UWACInitParam.RecvPackFramNum = m_RecvPackFrameNum;
	UWACInitParam.RecvSampleRate = pBasicSet.m_RecvSampleRate;
	UWACInitParam.SlideWinLen = pAdvancedSet.m_SlideWinLen;
	UWACInitParam.SyncConcurrence = pBasicSet.m_SyncConcurrence;
	UWACInitParam.XMTAmpValue = pBasicSet.m_XMTAmpValue ;
// 	UWACInitParam.XMTChannelNo = m_XMTChannelNo;
//	UWACInitParam.XMTCodedFramNum = m_XMTCodedFramNum;
	UWACInitParam.XMTDelayToSync = pBasicSet.m_XMTDelayToSync;
// 	UWACInitParam.XMTPackageNum = m_XMTPackageNum;
// 	UWACInitParam.XMTPackFramNum = m_XMTPackFrameNum;
	UWACInitParam.XMTSampleRate = pBasicSet.m_XMTSampleRate;
	UWACInitParam.RecvDelayToSync = pBasicSet.m_RecvDelaySync; 
	UWACInitParam.LoadDestID = 0;
	UWACInitParam.XMTMPSKPackageNum = pBasicSet.m_mpsk_packet;
	UWACInitParam.XMTMPSKPackFramNum = pBasicSet.m_mpsk_framenum;
	UWACInitParam.XMTPackageNum = pBasicSet.m_mfsk_packet;
	UWACInitParam.XMTPackFramNum = pBasicSet.m_mfsk_framenum;
	UWACInitParam.RecvMPSKPackageNum = pBasicSet.m_mpsk_recvpacket;
	UWACInitParam.RecvMPSKPackFramNum = pBasicSet.m_mpsk_recvframenum;
	UWACInitParam.RecvPackageNum = pBasicSet.m_mfsk_recvpacket;
	UWACInitParam.RecvPackFramNum = pBasicSet.m_mfsk_recvframenum;
	UWACInitParam.PC104SaveData=UWACCMD_PC104_SAVE_NO_DATA;
	UWACInitParam.MFSK_chirp_inter = pAdvancedSet.m_MFSK_chirp_inter;
	UWACInitParam.MPSK_chirp_inter = pAdvancedSet.m_MPSK_chirp_inter;
	UWACInitParam.Cycle_prefix = pAdvancedSet.m_cycle_prefix;

	if(pBasicSet.m_ADIOID)	
		UWACInitParam.LoadDestID+=ADIOID;
	if(pBasicSet.m_DSP01ID)   
		UWACInitParam.LoadDestID+=DSP01ID;
	if(pBasicSet.m_DSP02ID)   
		UWACInitParam.LoadDestID+=DSP02ID;
	if(pBasicSet.m_DSP11ID)   
		UWACInitParam.LoadDestID+=DSP11ID;
	if(pBasicSet.m_DSP12ID)   
		UWACInitParam.LoadDestID+=DSP12ID;
	if (!UWACInitParam.ADIOWorkMode)
	{
		UWACInitParam.RecvModulation = MFSKMOD;
	}
	else
	{
		UWACInitParam.RecvModulation = MPSKMOD;
	}
	//输入文件名
	static char BASED_CODE szFilter[]={"系统初始化文件(*.sysinit)|*.sysinit|"}; 
  	CDialog* pAppFrame = (CDialog*) AfxGetApp()->m_pMainWnd;
	CFileDialog theDataFile( FALSE,  _T("*.sysinit") , NULL , OFN_HIDEREADONLY, 
			szFilter , pAppFrame  );
	CString m_sFilename;

	if( theDataFile.DoModal()!=IDOK )
		return;

	if (theDataFile.GetPathName( )=="") 
	{
		return;
	}

	else 
	{
		m_sFilename =  theDataFile.GetPathName( );
	}
	
	CFile SetFile;
	//保存参数到文件中
	if(!SetFile.Open(m_sFilename,CFile::modeCreate | CFile::modeWrite))
	{
		TRACE0("文件打不开");
		return;
	}
	SetFile.Write(&UWACInitParam,sizeof(UWACINITPARA));
	SetFile.Close();
}

void COptionSet::OnHalt() 
{
	if (IDCANCEL ==AfxMessageBox("确认关闭机芯？",MB_OKCANCEL))
	{
		return;
	}
	// TODO: Add your control notification handler code here
	NET_PACKET *netpacket;
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	if(netpacket==NULL){
		AfxMessageBox("申请NET_PACKET空间出现异常！");
	}

	netpacket->FrmID = UWACCMD_PC014HALT;
	netpacket->FrmLen = 32;
	netpacket->DestID = PC104ID;
	netpacket->pData = NULL;
		
	m_WzdNetpacketList.AddTail(netpacket);
	SetEvent(IsNetpacketEvent);
}

void COptionSet::OnSetTime() 
{
	// TODO: Add your control notification handler code here
	time_t ltime;
	CTime ct;
	ct = CTime::GetCurrentTime();
	ltime = ct.GetTime();

	NET_PACKET *netpacket;//启动DSP01
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	if(netpacket==NULL){
		AfxMessageBox("申请NET_PACKET空间出现异常！");
	}

	netpacket->FrmID = UWACCMD_SETTIME;
	netpacket->FrmLen = 32;
	netpacket->DestID = PC104ID;
	netpacket->HeadParam[0] = (DWORD)ltime;
	netpacket->pData = NULL;	
	m_WzdNetpacketList.AddTail(netpacket);
	SetEvent(IsNetpacketEvent);
}

void COptionSet::OnResetadio() 
{
	// TODO: Add your control notification handler code here
	
	NET_PACKET *netpacket;
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	if(netpacket==NULL){
		AfxMessageBox("申请NET_PACKET空间出现异常！");
	}
	
	netpacket->FrmID = UWACCMD_RESETADIO;
	netpacket->FrmLen = 32;
	netpacket->DestID = PC104ID;
	netpacket->pData = NULL;
	
	m_WzdNetpacketList.AddTail(netpacket);
	SetEvent(IsNetpacketEvent);
}

void COptionSet::OnDiSCONNECT() 
{
	// TODO: Add your control notification handler code here
	CACSDlg* dlg= (CACSDlg*)AfxGetApp()->m_pMainWnd;
	dlg->SendSocket.Close();
	dlg->RecvSocket.Close();
	::PostMessage(hWnd,CABLE_NET_WMSG1,dlg->SendSocket.m_sSocket,FD_CLOSE);
	::PostMessage(hWnd,CABLE_NET_WMSG2,dlg->RecvSocket.m_sSocket,FD_CLOSE);
}
