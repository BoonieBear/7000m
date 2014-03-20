// VideoSelect.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "VideoSelect.h"
#include "HYUtil.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoSelect dialog
#define VIDEO_CONTAINER_RECT CRect(9,7,620,496)
#define MAX_SHOW_MODE 1
CVideoSelect::CVideoSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CVideoSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CVideoSelect)
	m_pMediaChannel = NULL;
	m_bHoriMirror   = FALSE;
	m_bVertMirror   = FALSE;
	m_bSaveFile     = FALSE;
	m_nSnapCounts   = 1;
	m_nSnapInterval = 0;
	m_nDeviceIndex	= 0;
	m_pYuvData		= NULL;
	//}}AFX_DATA_INIT
}


void CVideoSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CVideoSelect)
	DDX_Control(pDX, IDC_STATIC_VIDEO, m_VideoContainer);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CVideoSelect, CDialog)
	//{{AFX_MSG_MAP(CVideoSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoSelect message handlers

BOOL CVideoSelect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CString szCaption = "系统提示";
	CString szResult  = _T("");
	
	if(!InitializeDevice(szResult))
	{
		MessageBox(szResult,szCaption,MB_OK|MB_ICONINFORMATION);
		
		EndDialog(0);
		
		return FALSE;
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CVideoSelect::InitializeDevice(CString &szResult)
{
	m_nDeviceCount = HYGetDevCnt();
	
	if(m_nDeviceCount <= 0)
	{
		szResult = _T("没有找到视频采集设备，请检查!");
		return FALSE;
	}
	
	LONG nRealCount = 0;
	
	
	m_pMediaChannel = new CMediaChannel(0);
	
	if(m_pMediaChannel == NULL)
		return FALSE;
	
	if(m_pMediaChannel->OpenChannel())
	{
		nRealCount++;
		HYRegNotifyWnd(0,GetSafeHwnd(),TRUE);
	}
	else
		SAFE_DELETE(m_pMediaChannel);

	if(!CreateVideoContainer())
	{
		szResult = _T("不能创建视频输出窗口,错误返回!");
		
		return FALSE;
	}
	
	return TRUE;
}

BOOL CVideoSelect::CreateVideoContainer()
{
	if(m_nDeviceCount <= 0)
		return FALSE;
	
	if(!m_VideoContainer.CreateVideoWnd(m_nDeviceCount))
	{
		MessageBox("创建视频窗口失败!","系统提示",MB_OK|MB_ICONINFORMATION);
		return FALSE;
	}
	
	m_VideoContainer.MoveWindow(VIDEO_CONTAINER_RECT);
	
	for(int i = MAX_SHOW_MODE; i >= 0; i--)
	{
		if(m_VideoContainer.IsValidMode(i))
		{
			m_VideoContainer.SetShowMode(i);
			break;
		}
	}
	
	return TRUE;
}

void CVideoSelect::OnChangeChannel(LONG nWndIndex)
{
	LONG nDevIdx = nWndIndex;
	
	CMediaChannel *pChannel = m_pMediaChannel;
	
	if(pChannel != NULL)
	{
		UpdateData(FALSE);
	}
}

CMediaChannel * CVideoSelect::GetMediaChannel(LONG nDevIdx)
{
	if(nDevIdx < 0 || nDevIdx >= MAX_DEV_SUPPORT)
		return NULL;
	
	return m_pMediaChannel;
}

BOOL CVideoSelect::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	HYStopDevice(0);
	HYCloseDev(0);
	SAFE_DELETE_ARRAY(m_pYuvData);
	SAFE_DELETE(m_pMediaChannel);
	m_VideoContainer.DestroyWindow();
	return CDialog::DestroyWindow();
}

void CVideoSelect::OnOK() 
{
	// TODO: Add extra validation here
	SetSnapParam(m_VideoContainer.GetActiveIndex(),FALSE,FALSE,TRUE,1,0);
	CString szResult = _T("");
	
	if(!Snap(szResult))
	{
		CString szCaption = "系统提示";
		
		MessageBox(szResult,szCaption,MB_OK|MB_ICONINFORMATION);
	}
	CDialog::OnOK();
}

void CVideoSelect::SetSnapParam(LONG nDeviceIndex, BOOL bHoriMirror, BOOL bVertMirror, BOOL bSaveFile, long nSnapCounts, long nSnapInterval)
{
	m_nDeviceIndex  = nDeviceIndex;
	m_bHoriMirror   = bHoriMirror;
	m_bVertMirror   = bVertMirror;
	m_bSaveFile     = bSaveFile;
	m_nSnapCounts   = nSnapCounts;
	m_nSnapInterval = nSnapInterval;
}

BOOL CVideoSelect::Snap(CString szResult)
{
	CMediaChannel *pChannel = m_pMediaChannel;
	if (pChannel==NULL)
	{
		szResult = _T("快照通道没有创建,为空!");
		return FALSE;
	}
	LONG nBufSize = pChannel->GetSnapBufSize();
	if(nBufSize <= 0)
	{
		szResult = _T("获取尺寸信息失败!");
		
		return FALSE;
	}
	
	pChannel->SetSnapMirror(m_bHoriMirror,m_bVertMirror);

	m_pYuvData = new BYTE[nBufSize];
	if(pChannel->StartSnap(1,0))
	{
	
			VIDEOFMT enFmt = FMT_YUY2;
			if(pChannel->GetMemSnap(m_pYuvData,nBufSize,enFmt,1000))
			{
				
				if(m_bSaveFile)
				{
					if (pChannel->SnapVideoImage(m_pYuvData,nBufSize))
					{
						szSaveFileName = pChannel->szSnapFile;
					}
				}
			}
			
		
		return TRUE;
	}
	SAFE_DELETE_ARRAY(m_pYuvData);
	szResult = _T("快照失败!");
	return FALSE;
}
