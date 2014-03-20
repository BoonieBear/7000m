// VideoContainer.cpp : implementation file
//

#include "stdafx.h"
#include "ACSDlg.h"
#include "VideoContainer.h"
#include "ACS.h"
#include <math.h>
#include "MediaChannel.h"
#include "VideoSelect.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoContainer

CVideoContainer::CVideoContainer()
{
	m_bFullScreen	= FALSE;
	m_nMaxChannels	= 0;
	m_nMaxShowMode  = 0;

	m_nPrevMode		= -1;
	m_nShowMode     = -1;
	m_nActiveIndex  = -1;
	m_nActivePage	= -1;

	for(int i = 0; i < MAX_CHANNEL_SUPPORT; i++)
		m_pVideoWnd[i] = NULL;
}

CVideoContainer::~CVideoContainer()
{
}


BEGIN_MESSAGE_MAP(CVideoContainer, CStatic)
	//{{AFX_MSG_MAP(CVideoContainer)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoContainer message handlers

BOOL CVideoContainer::CreateVideoWnd(LONG nChannels)
{
	m_pUC1000Dlg = (CUCDemoDlg *)GetParent();
	
	if(m_pUC1000Dlg == NULL)
	{
		ASSERT(FALSE);
		return FALSE;
	}

	if(nChannels <= 0 || nChannels >= MAX_CHANNEL_SUPPORT)
		return FALSE;

	double  dbMode = sqrt(nChannels);
	LONG nShowMode = (LONG)dbMode;

	if(dbMode == (double)nShowMode)
		nShowMode--;

	if(nShowMode < 0 || nShowMode > 1)
		return FALSE;

	m_nMaxChannels = nChannels;
	m_nMaxShowMode = nShowMode;

	CString szTest;
	
#define	START_STATIC_ID	0xFF00
	
	UINT nID = START_STATIC_ID;

	for(LONG i = 0; i < m_nMaxChannels; i++)
	{
		m_pVideoWnd[i] = new CVideoWindow(i);

		if(m_pVideoWnd[i] != NULL)
		{

			if(!m_pVideoWnd[i]->Create(this,szTest,nID++))
			{
				SAFE_DELETE(m_pVideoWnd[i]);
			}
		}

		if(m_pVideoWnd[i] == NULL)
		{
			DestoryVideoWnd();

			return FALSE;
		}
	}

	return TRUE;
}

void CVideoContainer::DestoryVideoWnd()
{
	for(int i = 0; i < MAX_CHANNEL_SUPPORT; i++)
	{
		SAFE_DELETE(m_pVideoWnd[i]);
	}
}

BOOL CVideoContainer::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	DestoryVideoWnd();
	m_bFullScreen	= FALSE;
	m_nMaxChannels	= 0;
	m_nMaxShowMode  = 0;
	
	m_nPrevMode		= -1;
	m_nShowMode     = -1;
	m_nActiveIndex  = -1;
	m_nActivePage	= -1;
	return CStatic::DestroyWindow();
}

BOOL CVideoContainer::IsValidMode(LONG nShowMode)
{
	return (nShowMode >= 0 && nShowMode <= m_nMaxShowMode);
}

BOOL CVideoContainer::SetShowMode(LONG nShowMode)
{
	if(!IsValidMode(nShowMode))
		return FALSE;

	if(m_nShowMode == nShowMode)
		return TRUE;

	ShowVideoPage(m_nActivePage,FALSE);

	m_nShowMode = nShowMode;

	CalcWndPos();

	LONG nActivePage = CalcPageNo(m_nActiveIndex);

	if(nActivePage == -1)
	{
		nActivePage = 0;
		
		SetActiveIndex(0);
	}
	
	BOOL bResult = SetCurPage(nActivePage);

	return bResult;
}

void CVideoContainer::CalcWndPos()
{
	if(!IsValidMode(m_nShowMode))
		return;

	CRect rc;

	GetClientRect(&rc);

	LONG nWndIndex = 0;
	LONG nIndex    = 0;
	LONG nMaxWnd   = 4;

	LONG nRowCol = (m_nShowMode + 1);
	
	double dbWidth  = ((double)(rc.Width() - 1) / nRowCol);
	double dbHeight = ((double)(rc.Height() - 1) / nRowCol);
	
	nMaxWnd = nRowCol * nRowCol;
	
	CRect rcWnd;
	
	for(LONG i = 0; i < nRowCol; i++)
	{
		for(LONG j = 0; j < nRowCol; j++)
		{
			rcWnd.left   = (LONG)(j * dbWidth);
			rcWnd.top    = (LONG)(i * dbHeight);
			rcWnd.right  = (LONG)((j + 1) * dbWidth);
			rcWnd.bottom = (LONG)((i + 1) * dbHeight); 
			
			nWndIndex = nIndex;
			
			if(m_pVideoWnd[nWndIndex] != NULL)
			{
				m_pVideoWnd[nWndIndex]->SetWndPos(rcWnd,1);
			}
			
			nIndex++;
		}
	}
}

BOOL CVideoContainer::SetCurPage(LONG nActivePage)
{
	ShowVideoPage(m_nActivePage,FALSE);
	
	if(ShowVideoPage(nActivePage,TRUE))
	{
		Invalidate();
		
		m_nActivePage = nActivePage;

		return TRUE;
	}
	else
	{
		ShowVideoPage(m_nActivePage,TRUE);
		return FALSE;
	}
}

LONG CVideoContainer::CalcPageNo(LONG nIndex)
{
	if(!IsValidMode(m_nShowMode) || !IsValidIndex(nIndex))
		return -1;
	
	LONG nMaxWnd  = (m_nShowMode + 1) * (m_nShowMode + 1);
	LONG nMaxPage = (m_nMaxChannels + (nMaxWnd - 1)) / nMaxWnd;
	
	LONG nPageNo  = nIndex / nMaxWnd;

	if(nPageNo >= 0 && nPageNo < nMaxPage)
		return nPageNo;

	return -1;
}

BOOL CVideoContainer::IsValidIndex(LONG nIndex)
{
	return (nIndex >= 0 && nIndex < m_nMaxChannels);
}

void CVideoContainer::SetActiveIndex(LONG nIndex)
{
	if(!IsValidIndex(nIndex))
		return;

	if(m_nActiveIndex != nIndex)
	{
		CDC *pDC = GetWindowDC();

		DrawFocusRect(pDC);

		m_nActiveIndex = nIndex;

		DrawFocusRect(pDC);

		ReleaseDC(pDC);

		CVideoSelect *pUC1000Dlg = (CVideoSelect *)GetParent();

		ASSERT(pUC1000Dlg != NULL);

		LONG nWndIndex = nIndex;
				
		pUC1000Dlg->OnChangeChannel(nWndIndex);
	}
}

void CVideoContainer::DrawFocusRect(CDC *pDC)
{
	if(IsValidIndex(m_nActiveIndex))
	{
		LONG nWndIndex = m_nActiveIndex;
		
		if(m_pVideoWnd[nWndIndex] != NULL)
		{
			HWND hWndActive = m_pVideoWnd[nWndIndex]->GetSafeHwnd();

			if(!::IsWindow(hWndActive) || !::IsWindowVisible(hWndActive))
				return;

			CRect rc = m_pVideoWnd[nWndIndex]->GetWndPos();
			
			rc.InflateRect(1,1,1,1);
			
			CPen PenDraw;
			
			PenDraw.CreatePen(PS_SOLID,1,RGB(255,10,10));
			
			CPen *pOldPen = pDC->SelectObject(&PenDraw);
			
			int nOldMode = pDC->GetROP2();
			
			pDC->SetROP2(R2_NOTXORPEN);
			
			pDC->MoveTo(rc.left,rc.top);
			pDC->LineTo(rc.right,rc.top);
			pDC->LineTo(rc.right,rc.bottom);
			pDC->LineTo(rc.left,rc.bottom);
			pDC->LineTo(rc.left,rc.top);
			
			pDC->SetROP2(nOldMode);
			pDC->SelectObject(pOldPen);
		}
	}
}

BOOL CVideoContainer::ShowVideoPage(LONG nPage,BOOL bShow)
{
	if(!IsValidMode(m_nShowMode))
		return FALSE;

	CVideoSelect *pUC1000Dlg = (CVideoSelect *)GetParent();

	LONG nMaxWnd  = (m_nShowMode + 1) * (m_nShowMode + 1);
	LONG nMaxPage = (m_nMaxChannels + (nMaxWnd - 1)) / nMaxWnd;

	if(nPage >= 0 && nPage < nMaxPage)
	{
		LONG i = nPage * nMaxWnd;

		while((i < m_nMaxChannels) && (nMaxWnd > 0))
		{
			LONG nWndIndex = i;

			if(m_pVideoWnd[nWndIndex] != NULL)
			{
				CMediaChannel *pMediaChannel = pUC1000Dlg->GetMediaChannel(nWndIndex);
				
				m_pVideoWnd[nWndIndex]->ShowWindow(bShow ? SW_SHOW : SW_HIDE);
				
				StartStream(pMediaChannel,m_pVideoWnd[nWndIndex],bShow);
			}

			i++;

			nMaxWnd--;
		}
	}
	
	return TRUE;
}

void CVideoContainer::StartStream(CMediaChannel *pMediaChannel,CVideoWindow *pWndShow,BOOL bStart)
{
	if(pMediaChannel != NULL && pWndShow != NULL)
	{
		pMediaChannel->StartDevice(pWndShow->GetSafeHwnd(),bStart);
	}		
}

LONG CVideoContainer::GetActiveIndex()
{
	return m_nActiveIndex;
}
