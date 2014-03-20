// ADSamplePage.cpp : implementation file
//
#include "stdafx.h"
#include "ACS.h"
#include "ADSamplePage.h"
#include "ACSDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
double addata[8][SAMPLINGNUBER];

/////////////////////////////////////////////////////////////////////////////
// CADSamplePage dialog


CADSamplePage::CADSamplePage(CWnd* pParent /*=NULL*/)
	: CDialog(CADSamplePage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CADSamplePage)
	m_gain = UWACInitParam.AGCValue[0];
	if (UWACInitParam.IsAGCWork)
	{
		m_gain = 0;
	}

	
	m_samplerate = 80;
	bMode =FALSE;
	//}}AFX_DATA_INIT
}


void CADSamplePage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CADSamplePage)
	DDX_Control(pDX, IDC_adview1, m_adview1);
	DDX_Control(pDX, IDC_adview2, m_adview2);
	DDX_Control(pDX, IDC_adview3, m_adview3);
	DDX_Control(pDX, IDC_adview4, m_adview4);
	DDX_Text(pDX, IDC_GAIN, m_gain);
	DDX_Text(pDX, IDC_SAMPLE_RATE, m_samplerate);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CADSamplePage, CDialog)
	//{{AFX_MSG_MAP(CADSamplePage)
	ON_BN_CLICKED(IDC_ADSTART, OnAdstart)
	ON_BN_CLICKED(IDC_ADREPLAY, OnAdreplay)
	ON_WM_TIMER()
	ON_BN_DOUBLECLICKED(IDC_adview1, OnDoubleclickedadview1)
	ON_BN_DOUBLECLICKED(IDC_adview2, OnDoubleclickedadview2)
	ON_BN_DOUBLECLICKED(IDC_adview3, OnDoubleclickedadview3)
	ON_BN_DOUBLECLICKED(IDC_adview4, OnDoubleclickedadview4)
// 	ON_BN_DOUBLECLICKED(IDC_adview5, OnDoubleclickedadview5)
// 	ON_BN_DOUBLECLICKED(IDC_adview6, OnDoubleclickedadview6)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CADSamplePage message handlers

void CADSamplePage::OnAdstart() 
{
	// TODO: Add your control notification handler code here
	char *pchar_buffer;	//�����ļ�ͷ��̬�ռ䷵��ָ��
	time_t * nowtime;//����ʱ�䶯̬�ռ䷵��ָ��
	char *p_display_time;//ctime(nowtime)����ָ��
	int	lentemp;//�任������ʱ����
	NET_PACKET *netpacket;
	if(m_bADWaveEnable==TRUE)//���AD�ɼ��Ѿ�ֹͣ
	{
		UpdateData(TRUE);
/*		if (UWAcommparam.Mode==1)//ˮ��
		{	
			ADFile.Init("Ship_ADData",1000*FILESIZE,30000,100*WRITESIZE);

		}
		else
		{
			ADFile.Init("Sub_ADData",1000*FILESIZE,30000,100*WRITESIZE);
		}*/
		CButton* pWnd = (CButton*)GetDlgItem(IDC_ADSTART);
		pWnd->SetWindowText("ֹͣ�ɼ�");
		m_bADWaveEnable=false;
/*
		pchar_buffer=(char *)calloc(4096,sizeof(char));//�����ļ�ͷ��̬�ռ�
		if(pchar_buffer==NULL){
			AfxMessageBox("����4096�ռ�����쳣��");
			exit(EXIT_FAILURE);		
		}

		nowtime=(time_t *)malloc(sizeof(time_t));//����ʱ�䶯̬�ռ�
		if(nowtime==NULL){
			AfxMessageBox("����time_t�ռ�����쳣��");
			exit(EXIT_FAILURE);	
		}
		ASSERT(time(nowtime)!=-1);
		p_display_time=ctime(nowtime);
		if(nowtime!=NULL)//�ͷ�ʱ�䶯̬�ռ�
			free(nowtime);
		sprintf(pchar_buffer,"7000������Ǳˮ����ѧϵͳ\nAD�ɼ�����\n"
			"����ʱ��:%ds\n"
			"��������:%d\n"
			"������:%dK\n"
			"����ʱ��:%s"//p_display_time���β�Ѿ�����'\n'
			"�ļ�����:%s\n\x1A",
			m_sampletime,m_gain,m_samplerate,p_display_time,m_describ);
		ADFile.SaveFile(pchar_buffer,4096);// д�ļ�ͷ

		if(pchar_buffer!=NULL)//�ͷ�ʱ�䶯̬�ռ�
			free(pchar_buffer);
		
		lentemp=UWACInitParam.Len;
		UWACInitParam.Len=sizeof(UWACINITPARA)-sizeof(UWACInitParam.ID)-sizeof(UWACInitParam.Len);//���ݳ��Ȳ���������ͷ
		ADFile.SaveFile((char*)&UWACInitParam,sizeof(UWACINITPARA));//д���ݿ�
		UWACInitParam.Len=lentemp;
*/
		netpacket= (NET_PACKET *)malloc(sizeof(NET_PACKET));//����NET_PACKET�ṹ��̬�ռ�
		if(netpacket==NULL){
			AfxMessageBox("����NET_PACKET�ռ�����쳣��");
		}

		netpacket->FrmID = UWACCMD_START_SAMPLE_AD;
		netpacket->FrmLen = 32;
		netpacket->DestID = ADIOID;
		netpacket->HeadParam[0]=0;
		netpacket->HeadParam[1]=m_gain;
		netpacket->HeadParam[2]=(m_samplerate*1000);
		netpacket->HeadParam[3]=UWAcommparam.Mode;
		netpacket->HeadParam[4]=NULL;
		netpacket->pData = NULL;

//		lentemp=netpacket->FrmLen;
//		netpacket->FrmLen=sizeof(NET_PACKET)-sizeof(netpacket->FrmID)-sizeof(netpacket->FrmLen);//����������ͷ����
//		ADFile.SaveFile((char*)netpacket,sizeof(NET_PACKET));//д���ݿ�
//		netpacket->FrmLen=lentemp;

		m_WzdNetpacketList.AddTail(netpacket);//�������緢���������
		SetEvent(IsNetpacketEvent);//�����ͱ�־
		
	}//if(m_bADWaveEnable==true){//���AD�ɼ��Ѿ�ֹͣ
	else//AD�ɼ����ڽ���
	{
		m_nRawDataLen = 0;//������λ
		CButton* pWnd = (CButton*)GetDlgItem(IDC_ADSTART);
		pWnd->SetWindowText("��ʼ�ɼ�");
		m_bADWaveEnable=TRUE;
		netpacket= (NET_PACKET *)malloc(sizeof(NET_PACKET));//����NET_PACKET�ṹ��̬�ռ�
		if(netpacket==NULL){
			AfxMessageBox("����NET_PACKET�ռ�����쳣��");
		}

		netpacket->FrmID = UWACCMD_STOP_SAMPLE_AD;
		netpacket->FrmLen = 32;
		netpacket->DestID = ADIOID;
		netpacket->HeadParam[0]=0;
		netpacket->HeadParam[1]=0;
		netpacket->HeadParam[2]=0;
		netpacket->HeadParam[3]=0;
		netpacket->HeadParam[4]=NULL;
		netpacket->pData = NULL;
		m_WzdNetpacketList.AddTail(netpacket);//�������緢���������
		SetEvent(IsNetpacketEvent);//�����ͱ�־
//		AfxMessageBox("ֹͣ��ǰ����");
//		ADFile.CloseFile();
	}
}

void CADSamplePage::OnAdreplay() 
{
	// TODO: Add your control notification handler code here
	static char BASED_CODE szFilter[]={"AD�ļ�(*.dat)|*.dat|"}; 
  	CDialog* pAppFrame = (CDialog*) AfxGetApp()->m_pMainWnd;
	CFileDialog theDataFile( TRUE,  _T("*.dat") , NULL , OFN_HIDEREADONLY, 
			szFilter , pAppFrame  );
	CString m_sFilename;
	if( theDataFile.DoModal()!=IDOK )
		return;
	m_sFilename =  theDataFile.GetPathName( );	
	//�Ӳ����ļ��ж�������
	if(!ADPlayFile.Open(m_sFilename,CFile::modeRead)){
			TRACE0("�ļ��򲻿�");
			return;
		}
	pDataLen=ADPlayFile.GetLength();
	SetTimer(ADPLAYTIMER,10,0);
}

void CADSamplePage::UpdateView(short* srcData)
{
	ASSERT(srcData!=NULL);
	for (int i=0;i<SAMPLINGNUBER;i++)
	{
		for (int j=0;j<channum;j++)
		{
			addata[j][i]=srcData[i*channum+j];
		}
	}
	m_adview1.m_pCurYdata = NULL;
	m_adview1.m_pPSDYdata = NULL;
	m_adview1.Invalidate(FALSE);		
	m_adview2.m_pCurYdata = NULL;
	m_adview2.m_pPSDYdata = NULL;
	m_adview2.Invalidate(FALSE);
	m_adview3.m_pCurYdata = NULL;
	m_adview3.m_pPSDYdata = NULL;
	m_adview3.Invalidate(FALSE);
	m_adview4.m_pCurYdata = NULL;
	m_adview4.m_pPSDYdata = NULL;
	m_adview4.Invalidate(FALSE);
// 	m_adview5.m_pCurYdata = NULL;
// 	m_adview5.m_pPSDYdata = NULL;
// 	m_adview5.Invalidate(FALSE);
// 	m_adview6.m_pCurYdata = NULL;
// 	m_adview6.m_pPSDYdata = NULL;
// 	m_adview6.Invalidate(FALSE);


}

void CADSamplePage::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
		case ADPLAYTIMER:
			char pData[1024*32];		
//			ADPlayFile.Seek(ADPlayFile.GetLength()-pDataLen,CFile::begin );
//			pDataLen-=4096;
			ADPlayFile.Read(pData,4);//��ȡ������
			pDataLen-=4;
			while (*(DWORD*)pData!=UWACDATA_SAMDATA)
			{
				ADPlayFile.Read(pData,4);//��ȡ������
				pDataLen-=4;
				if (pDataLen<=0)
				{
					KillTimer(ADPLAYTIMER);
					ADPlayFile.Close();	
					return;
				}
				continue;
			}
			ADPlayFile.Read(pData,4);//�����ֺ����ݳ���
			pDataLen-=4;
			DWORD nlength = (*(DWORD*)pData-8) *4;
			ADPlayFile.Read(pData,24);
			pDataLen-=24;
			ADPlayFile.Read(pData,nlength);
			pDataLen-=nlength;
			//���в�����ʾ
			if(m_nRawDataLen + nlength > SAMPLINGNUBER*8*sizeof(short))//����һҳ��ʾ����
			{
				memcpy((char*)m_pRawData,(char*)m_pRawData+nlength+m_nRawDataLen-SAMPLINGNUBER*8*sizeof(short),
					SAMPLINGNUBER*8*sizeof(short)-(nlength));
				memcpy((char*)m_pRawData+SAMPLINGNUBER*8*sizeof(short)-(nlength),(char*)pData,nlength);
				m_nRawDataLen = SAMPLINGNUBER*8*sizeof(short);					
			}
			else
			{
				memcpy((char*)m_pRawData+m_nRawDataLen,pData,nlength);
				m_nRawDataLen += nlength;
			}
			UpdateView(m_pRawData);
			break;
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CADSamplePage::OnInitDialog() 
{
	CDialog::OnInitDialog();

	GetClientRect(&windowrect);//���洰�ڴ�С
	windowrect.top+=45;
	m_adview1.GetWindowRect(&ad1Rect);
	ScreenToClient(&ad1Rect);
	m_adview2.GetWindowRect(&ad2Rect);
	ScreenToClient(&ad2Rect);
	m_adview3.GetWindowRect(&ad3Rect);
	ScreenToClient(&ad3Rect);
	m_adview4.GetWindowRect(&ad4Rect);
	ScreenToClient(&ad4Rect);
// 	m_adview5.GetWindowRect(&ad5Rect);
// 	ScreenToClient(&ad5Rect);
// 	m_adview6.GetWindowRect(&ad6Rect);
// 	ScreenToClient(&ad6Rect);
	m_ADParamLen=sizeof(NET_PACKET)+sizeof(NET_PACKET)+sizeof(UWACINITPARA);
	memset(addata,0,SAMPLINGNUBER*8*sizeof(double));
	m_adview1.m_pTotalYdata = addata[0];
	m_adview1.m_defaultMaxY = 2048;
	m_adview1.m_defaultMinY = -2048;
	m_adview1.m_defaultMaxf = 15000;
	m_adview1.TotalLength = SAMPLINGNUBER;
	m_adview2.m_pTotalYdata = addata[1];
	m_adview2.m_defaultMaxY = 2048;
	m_adview2.m_defaultMinY = -2048;
	m_adview2.m_defaultMaxf = 15000;
	m_adview2.TotalLength = SAMPLINGNUBER;
	m_adview3.m_pTotalYdata = addata[2];
	m_adview3.m_defaultMaxY = 2048;
	m_adview3.m_defaultMinY = -2048;
	m_adview3.m_defaultMaxf = 15000;
	m_adview3.TotalLength = SAMPLINGNUBER;
	m_adview4.m_pTotalYdata = addata[3];
	m_adview4.m_defaultMaxY = 2048;
	m_adview4.m_defaultMinY = -2048;
	m_adview4.m_defaultMaxf = 15000;
	m_adview4.TotalLength = SAMPLINGNUBER;
// 	m_adview5.m_pTotalYdata = addata[4];
// 	m_adview5.m_defaultMaxY = 2048;
// 	m_adview5.m_defaultMinY = -2048;
// 	m_adview5.m_defaultMaxf = 150000;
// 	m_adview5.TotalLength = SAMPLINGNUBER;
// 	m_adview6.m_pTotalYdata = addata[5];
// 	m_adview6.m_defaultMaxY = 2048;
// 	m_adview6.m_defaultMinY = -2048;
// 	m_adview6.m_defaultMaxf = 100000;
// 	m_adview6.TotalLength = SAMPLINGNUBER;

	// TODO: Add extra initialization here
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CADSamplePage::OnDoubleclickedadview1() 
{
	// TODO: Add your control notification handler code here
	if (!bMode)
	{
		m_adview1.MoveWindow(&windowrect);
		m_adview2.EnableWindow(FALSE);
		m_adview3.EnableWindow(FALSE);
		m_adview4.EnableWindow(FALSE);
//		m_adview5.EnableWindow(FALSE);
//		m_adview6.EnableWindow(FALSE);
		m_adview2.ShowWindow(SW_HIDE);
		m_adview3.ShowWindow(SW_HIDE);
		m_adview4.ShowWindow(SW_HIDE);
//		m_adview5.ShowWindow(SW_HIDE);
//		m_adview6.ShowWindow(SW_HIDE);
	
	} 
	else
	{
		m_adview1.MoveWindow(&ad1Rect);
		m_adview2.EnableWindow(TRUE);
		m_adview3.EnableWindow(TRUE);
		m_adview4.EnableWindow(TRUE);
//		m_adview5.EnableWindow(TRUE);
//		m_adview6.EnableWindow(TRUE);
		m_adview2.ShowWindow(SW_SHOW);
		m_adview3.ShowWindow(SW_SHOW);
		m_adview4.ShowWindow(SW_SHOW);
//		m_adview5.ShowWindow(SW_SHOW);
//		m_adview6.ShowWindow(SW_SHOW);
		ReleaseCapture();
	}
	bMode=!bMode;
	
}

void CADSamplePage::OnDoubleclickedadview2() 
{
	// TODO: Add your control notification handler code here
	if (!bMode)
	{
		m_adview2.MoveWindow(&windowrect);
		m_adview1.EnableWindow(FALSE);
		m_adview3.EnableWindow(FALSE);
		m_adview4.EnableWindow(FALSE);
//		m_adview5.EnableWindow(FALSE);
//		m_adview6.EnableWindow(FALSE);
		m_adview1.ShowWindow(SW_HIDE);
		m_adview3.ShowWindow(SW_HIDE);
		m_adview4.ShowWindow(SW_HIDE);
//		m_adview5.ShowWindow(SW_HIDE);
//		m_adview6.ShowWindow(SW_HIDE);
	
	} 
	else
	{
		m_adview2.MoveWindow(&ad2Rect);
		m_adview1.EnableWindow(TRUE);
		m_adview3.EnableWindow(TRUE);
		m_adview4.EnableWindow(TRUE);
//		m_adview5.EnableWindow(TRUE);
//		m_adview6.EnableWindow(TRUE);
		m_adview1.ShowWindow(SW_SHOW);
		m_adview3.ShowWindow(SW_SHOW);
		m_adview4.ShowWindow(SW_SHOW);
//		m_adview5.ShowWindow(SW_SHOW);
//		m_adview6.ShowWindow(SW_SHOW);
		ReleaseCapture();
	}
	bMode=!bMode;
	
}

void CADSamplePage::OnDoubleclickedadview3() 
{
	// TODO: Add your control notification handler code here
	if (!bMode)
	{
		m_adview3.MoveWindow(&windowrect);
		m_adview1.EnableWindow(FALSE);
		m_adview2.EnableWindow(FALSE);
		m_adview4.EnableWindow(FALSE);
//		m_adview5.EnableWindow(FALSE);
//		m_adview6.EnableWindow(FALSE);
		m_adview2.ShowWindow(SW_HIDE);
		m_adview1.ShowWindow(SW_HIDE);
		m_adview4.ShowWindow(SW_HIDE);
//		m_adview5.ShowWindow(SW_HIDE);
//		m_adview6.ShowWindow(SW_HIDE);
	
	} 
	else
	{
		m_adview3.MoveWindow(&ad3Rect);
		m_adview1.EnableWindow(TRUE);
		m_adview2.EnableWindow(TRUE);
		m_adview4.EnableWindow(TRUE);
//		m_adview5.EnableWindow(TRUE);
//		m_adview6.EnableWindow(TRUE);
		m_adview2.ShowWindow(SW_SHOW);
		m_adview1.ShowWindow(SW_SHOW);
		m_adview4.ShowWindow(SW_SHOW);
//		m_adview5.ShowWindow(SW_SHOW);
//		m_adview6.ShowWindow(SW_SHOW);
		ReleaseCapture();
	}
	bMode=!bMode;	
	
}

void CADSamplePage::OnDoubleclickedadview4() 
{
	// TODO: Add your control notification handler code here
	if (!bMode)
	{
		m_adview4.MoveWindow(&windowrect);
		m_adview1.EnableWindow(FALSE);
		m_adview3.EnableWindow(FALSE);
		m_adview2.EnableWindow(FALSE);
//		m_adview5.EnableWindow(FALSE);
//		m_adview6.EnableWindow(FALSE);
		m_adview1.ShowWindow(SW_HIDE);
		m_adview2.ShowWindow(SW_HIDE);
		m_adview3.ShowWindow(SW_HIDE);
//		m_adview5.ShowWindow(SW_HIDE);
//		m_adview6.ShowWindow(SW_HIDE);
	
	} 
	else
	{
		m_adview4.MoveWindow(&ad4Rect);
		m_adview1.EnableWindow(TRUE);
		m_adview3.EnableWindow(TRUE);
		m_adview2.EnableWindow(TRUE);
//		m_adview5.EnableWindow(TRUE);
//		m_adview6.EnableWindow(TRUE);
		m_adview1.ShowWindow(SW_SHOW);
		m_adview2.ShowWindow(SW_SHOW);
		m_adview3.ShowWindow(SW_SHOW);
//		m_adview5.ShowWindow(SW_SHOW);
//		m_adview6.ShowWindow(SW_SHOW);
		ReleaseCapture();
	}
	bMode=!bMode;
	
}
/*
void CADSamplePage::OnDoubleclickedadview5() 
{
	// TODO: Add your control notification handler code here
	if (!bMode)
	{
		m_adview5.MoveWindow(&windowrect);
		m_adview1.EnableWindow(FALSE);
		m_adview3.EnableWindow(FALSE);
		m_adview4.EnableWindow(FALSE);
		m_adview2.EnableWindow(FALSE);
		m_adview6.EnableWindow(FALSE);
		m_adview1.ShowWindow(SW_HIDE);
		m_adview2.ShowWindow(SW_HIDE);
		m_adview3.ShowWindow(SW_HIDE);
		m_adview4.ShowWindow(SW_HIDE);
		m_adview6.ShowWindow(SW_HIDE);
	
	} 
	else
	{
		m_adview5.MoveWindow(&ad5Rect);
		m_adview1.EnableWindow(TRUE);
		m_adview3.EnableWindow(TRUE);
		m_adview4.EnableWindow(TRUE);
		m_adview2.EnableWindow(TRUE);
		m_adview6.EnableWindow(TRUE);
		m_adview1.ShowWindow(SW_SHOW);
		m_adview2.ShowWindow(SW_SHOW);
		m_adview3.ShowWindow(SW_SHOW);
		m_adview4.ShowWindow(SW_SHOW);
		m_adview6.ShowWindow(SW_SHOW);
		ReleaseCapture();
	}
	bMode=!bMode;	
	
}

void CADSamplePage::OnDoubleclickedadview6() 
{
	// TODO: Add your control notification handler code here
	if (!bMode)
	{
		m_adview6.MoveWindow(&windowrect);
		m_adview1.EnableWindow(FALSE);
		m_adview3.EnableWindow(FALSE);
		m_adview4.EnableWindow(FALSE);
		m_adview5.EnableWindow(FALSE);
		m_adview2.EnableWindow(FALSE);
		m_adview2.ShowWindow(SW_HIDE);
		m_adview3.ShowWindow(SW_HIDE);
		m_adview4.ShowWindow(SW_HIDE);
		m_adview5.ShowWindow(SW_HIDE);
		m_adview1.ShowWindow(SW_HIDE);
	
	} 
	else
	{
		m_adview6.MoveWindow(&ad6Rect);
		m_adview1.EnableWindow(TRUE);
		m_adview3.EnableWindow(TRUE);
		m_adview4.EnableWindow(TRUE);
		m_adview5.EnableWindow(TRUE);
		m_adview2.EnableWindow(TRUE);
		m_adview2.ShowWindow(SW_SHOW);
		m_adview3.ShowWindow(SW_SHOW);
		m_adview4.ShowWindow(SW_SHOW);
		m_adview5.ShowWindow(SW_SHOW);
		m_adview1.ShowWindow(SW_SHOW);
		ReleaseCapture();
	}
	bMode=!bMode;	
	
}
*/
