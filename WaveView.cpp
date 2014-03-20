// WaveView.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "ACSDlg.h"
#include "WaveView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
BOOL bMode =TRUE;
/////////////////////////////////////////////////////////////////////////////
// CWaveView dialog


CWaveView::CWaveView(CWnd* pParent /*=NULL*/)
	: CDialog(CWaveView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWaveView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
}

CWaveView::~CWaveView()
{
	if (sWaveData)
	{
		delete sWaveData;
	}
}

void CWaveView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWaveView)
	DDX_Control(pDX, IDC_BUTTON1, m_waveview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWaveView, CDialog)
	//{{AFX_MSG_MAP(CWaveView)
	ON_BN_CLICKED(IDC_SavPic, OnSavPic)
	ON_BN_CLICKED(IDC_PAUSE, OnPause)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_WAVEZOOMOUT, OnWavezoomout)
	ON_BN_CLICKED(IDC_WAVEZOOMIN, OnWavezoomin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWaveView message handlers

BOOL CWaveView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	sWaveData=new short[WAVEINTERVAL*8];
	memset(sWaveData,0,WAVEINTERVAL*8*sizeof(short));

	PlayButton.LoadBitmaps(IDB_PLAY,NULL,NULL,NULL);
	PlayButton.SubclassDlgItem(IDC_PAUSE,this);
	PlayButton.SizeToContent();
	
	ZOOMINButton.LoadBitmaps(IDB_ZOOMIN,NULL,NULL,NULL);
	ZOOMINButton.SubclassDlgItem(IDC_WAVEZOOMIN,this);
	ZOOMINButton.SizeToContent();

	ZOOMOUTButton.LoadBitmaps(IDB_ZOOMOUT,NULL,NULL,NULL);
	ZOOMOUTButton.SubclassDlgItem(IDC_WAVEZOOMOUT,this);
	ZOOMOUTButton.SizeToContent();

	// TODO: Add extra initialization here
	memset(dWaveData,0,12000*sizeof(double));
	m_waveview.m_pTotalYdata=dWaveData;
	m_waveview.TotalLength=12000;
	SetTimer(WAVESHOWTIMER,WAVEINTERVAL,NULL);
	OnPause();//开始play
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
	
}

void CWaveView::OnSavPic() 
{
	// TODO: Add your control notification handler code here
	CString m_sFilename;
	CTime nowtime;
	nowtime = CTime::GetCurrentTime();
	m_sFilename.Format("%04d%02d%02d%02d%02d%02d.bmp",nowtime.GetYear(),nowtime.GetMonth(),nowtime.GetDay(),
		nowtime.GetHour(),nowtime.GetMinute(),nowtime.GetSecond());
	// 保存设置
	//输入文件名
// 	static char BASED_CODE szFilter[] = {"波形视图(*.bmp)|*.bmp|"}; 
// 	CDialog* pAppFrame = (CDialog*)AfxGetApp()->m_pMainWnd;
// 	CFileDialog theDataFile(FALSE,  _T("*.bmp"), NULL, OFN_HIDEREADONLY, szFilter, pAppFrame);
// 	
// 	if( theDataFile.DoModal()!=IDOK )
// 		return;
// 	else
// 	{
// 		m_sFilename =  theDataFile.GetPathName( );
// 	}
	m_waveview.SaveAs(m_sFilename);
}

void CWaveView::OnPause() 
{
	// TODO: Add your control notification handler code here
	if (bMode==FALSE)//暂停
	{
		WaveCycleMem->Empty();
		PlayButton.LoadBitmaps(IDB_PLAY,NULL,NULL,NULL);
		bMode=TRUE;
	} 
	else
	{
		bMode=FALSE;
		PlayButton.LoadBitmaps(IDB_pause,NULL,NULL,NULL);
		
	}
}


BOOL CWaveView::DestroyWindow()
{
	// TODO: Add your specialized code here and/or call the base class
	KillTimer(WAVESHOWTIMER);
	return CDialog::DestroyWindow();
}

void CWaveView::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

	}
	else
	{
		CDialog::OnPaint();
	}
}

void CWaveView::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	switch (nIDEvent)
	{
	case WAVESHOWTIMER:
		WaveMemSync.Lock();
		if ((WaveCycleMem->GetDataLen()>=MAXBUFFSIZE)||(WaveCycleMem->GetDataLen()==0))//累计数据太多
		{
			WaveCycleMem->Empty();
			WaveMemSync.Unlock();
			return;
		}
		if (WaveCycleMem->GetDataLen()<WAVEINTERVAL*8*2)
		{
			return;
		}
		memset(sWaveData,0,WAVEINTERVAL*8*sizeof(short));
		WaveCycleMem->ReadData((char*)sWaveData,WAVEINTERVAL*8*2);

		WaveMemSync.Unlock();	
		memcpy((double*)dWaveData,(double*)&dWaveData[WAVEINTERVAL*8],(12000-WAVEINTERVAL*8)*sizeof(double));//前移
		for (int i=0;i<WAVEINTERVAL*8;i++)
		{
			dWaveData[12000-WAVEINTERVAL*8+i]=sWaveData[i];
		}	
		if (!bMode)
		{
			m_waveview.m_pCurYdata = NULL;
			m_waveview.m_pPSDYdata = NULL;
			m_waveview.Invalidate(FALSE);
		}
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CWaveView::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(WAVESHOWTIMER);
	if (sWaveData)
	{
		delete []sWaveData;
	}
	CDialog::OnClose();
}

void CWaveView::OnWavezoomout() 
{
	// TODO: Add your control notification handler code here
	if ((m_waveview.m_defaultMaxY<100)||(m_waveview.m_defaultMinY>-100))
	{
		return;
	}
	m_waveview.m_defaultMinY /= 2; 
	m_waveview.m_defaultMaxY /= 2;
	m_waveview.m_pCurYdata = NULL;
	m_waveview.m_pPSDYdata = NULL;
	m_waveview.Invalidate(FALSE);

}

void CWaveView::OnWavezoomin() 
{
	// TODO: Add your control notification handler code here
	if ((m_waveview.m_defaultMaxY>32768)||(m_waveview.m_defaultMinY<-32768))
	{
		m_waveview.m_defaultMaxY=32768;
		m_waveview.m_defaultMinY=-32768;
		return; 
	}
	m_waveview.m_defaultMinY *= 2; 
	m_waveview.m_defaultMaxY *= 2;
	m_waveview.m_pCurYdata = NULL;
	m_waveview.m_pPSDYdata = NULL;
	m_waveview.Invalidate(FALSE);
}
