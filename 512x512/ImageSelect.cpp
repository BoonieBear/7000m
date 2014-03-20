// ImageSelect.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "ImageSelect.h"
#define WIDTH 512
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageSelect dialog


CImageSelect::CImageSelect(CWnd* pParent /*=NULL*/)
	: CDialog(CImageSelect::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImageSelect)
		// NOTE: the ClassWizard will add member initialization here
	SelectFileName = "backgroud.bmp";
	pType =1;
	//}}AFX_DATA_INIT

}


void CImageSelect::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImageSelect)
	DDX_Control(pDX, IDOK, m_CheckOk);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImageSelect, CDialog)
	//{{AFX_MSG_MAP(CImageSelect)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_CLOSE()
	ON_WM_CAPTURECHANGED()
	ON_WM_SETCURSOR()
	ON_WM_KILLFOCUS()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImageSelect message handlers

BOOL CImageSelect::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_CheckOk.EnableWindow(FALSE);
	CxImage img(SelectFileName, pType);
	image = img;
	m_tracker.m_rect = CRect(0,0,0,0);
	m_tracker.m_nStyle = CRectTracker::hatchInside|CRectTracker::solidLine;
	if (!image.IsValid())
	{
		CString s = image.GetLastError();
		AfxMessageBox(s);
		return FALSE;
	}
	showed = false;
	GetMaxZoomFactor(image.GetHeight(),image.GetWidth());
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImageSelect::OnOK() 
{
	// TODO: Add extra validation here
	NewImage.Resample(WIDTH,WIDTH,2,NULL);
	SendFileName = ".\\crop.bmp";
	NewImage.Save(SendFileName,CXIMAGE_FORMAT_BMP);
	CDialog::OnOK();
}

void CImageSelect::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CDC *pdc=GetDC();
// 	if (!showed)
// 	{
	
		float zoom	= ZoomFactor;
		image.Draw(pdc->GetSafeHdc(),(512-(int)(image.GetWidth()*zoom))/2,(512-(int)(image.GetHeight()*zoom))/2,
			(int)(image.GetWidth()*zoom),(int)(image.GetHeight()*zoom),0,TRUE);
		if ( m_tracker.m_rect.Width()>0 && m_tracker.m_rect.Height()>0 )
		{
			m_tracker.Draw(pdc);
			
		}
		NewImage.Draw(pdc->GetSafeHdc(),535,10,WIDTH/2,WIDTH/2,0,TRUE);
// 	}
// 	showed = true;
	// Do not call CDialog::OnPaint() for painting messages
}

void CImageSelect::GetMaxZoomFactor(DWORD Height, DWORD Width)
{
	ASSERT(Height > 0);
	ASSERT(Width > 0);
	if ((Height<=WIDTH)&&(Width<=WIDTH))//WIDTH*WIDTH
	{
		ZoomFactor = 1;
	}
	else
	{
		CRect rect;
		GetClientRect(&rect);
		ZoomFactor = min((float)rect.Height()/Height,(float)rect.Width()*0.65/Width);
	}
	
}

void CImageSelect::GetSelectZoomFactor(DWORD Height, DWORD Width)
{
	ASSERT(Height > 0);
	ASSERT(Width > 0);
	if ((Height<=WIDTH)&&(Width<=WIDTH))//图片小于256*256大小不变
	{
		SelectZoomFactor = 1;
	}
	else
	{
		SelectZoomFactor = min(WIDTH/Height,WIDTH/Width);
	}
	
}

void CImageSelect::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CDC *pdc=GetDC();
	if (m_tracker.HitTest(point) < 0)
	{
		CRectTracker track;
		CRect rImage((512-(int)(image.GetWidth()*ZoomFactor))/2,(512-(int)(image.GetHeight()*ZoomFactor))/2,
			(512-(int)(image.GetWidth()*ZoomFactor))/2+(int)(image.GetWidth()*ZoomFactor),
			(512-(int)(image.GetHeight()*ZoomFactor))/2+(int)(image.GetHeight()*ZoomFactor));
		if (track.TrackRubberBand(this, point, true)) 
		{
			track.m_rect.NormalizeRect();
			m_tracker.m_rect = track.m_rect;
			//确保发送图片为正方形
			int nlength = max(track.m_rect.Height(),track.m_rect.Width());
			m_tracker.m_rect.bottom = m_tracker.m_rect.top + nlength;
			m_tracker.m_rect.right = m_tracker.m_rect.left + nlength;
			//确保选取框在图片上
			if (m_tracker.m_rect.left<rImage.left)
			{
				m_tracker.m_rect.right += rImage.left-m_tracker.m_rect.left;
				m_tracker.m_rect.left = rImage.left;
			}
			if (m_tracker.m_rect.top<rImage.top)
			{
				m_tracker.m_rect.bottom += rImage.top-m_tracker.m_rect.top;
				m_tracker.m_rect.top = rImage.top;
			}
			if (m_tracker.m_rect.right>rImage.right)
			{
				m_tracker.m_rect.right = rImage.right;
			} 
			if (m_tracker.m_rect.bottom>rImage.bottom)
			{
				m_tracker.m_rect.bottom = rImage.bottom;
			}
			nlength = min(m_tracker.m_rect.Height(),m_tracker.m_rect.Width());
			m_tracker.m_rect.bottom = m_tracker.m_rect.top + nlength;
			m_tracker.m_rect.right = m_tracker.m_rect.left + nlength;
			SetImageRectSelection(&(m_tracker.m_rect));
			m_CheckOk.EnableWindow(TRUE);
		} 
		else
		{
			m_tracker.m_rect = CRect(0,0,0,0);
		}
	} 
	CRect rect;
	GetClientRect(&rect);
	InvalidateRect(&rect,TRUE);
	showed = false;
	CDialog::OnLButtonDown(nFlags, point);
}

bool CImageSelect::SetImageRectSelection(CRect *rect)
{
	CxImage* ima = &image;

	if (ima==0)
		return false;

	long x,y;
	RECT rect_img;
	x = rect_img.left = rect->left-(512-(int)(image.GetWidth()*ZoomFactor))/2;
	y = rect_img.top = rect->top-(512-(int)(image.GetHeight()*ZoomFactor))/2;
	GetImageXY(ima, &x,&y);
	rect_img.top =  y;
	rect_img.left = x;

	x = rect_img.right = rect->right-(512-(int)(image.GetWidth()*ZoomFactor))/2;
	y = rect_img.bottom = rect->bottom-(512-(int)(image.GetHeight()*ZoomFactor))/2;
	GetImageXY(ima, &x,&y);
	rect_img.bottom = y;
	rect_img.right = x;

	ima->SelectionClear();
	ima->SelectionAddRect(rect_img);
	ima->Crop(rect_img,&NewImage);
	return true;
}

void CImageSelect::GetImageXY(CxImage *ima, long *x, long *y)
{
	if (!ima) return;
	float fx =(float)(*x);
	float fy =(float)(*y);

	fx/=ZoomFactor;
	fy/=ZoomFactor;

	*x = (long)fx;
	*y = (long)fy;
}

void CImageSelect::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnClose();
}

void CImageSelect::OnCaptureChanged(CWnd *pWnd) 
{
	// TODO: Add your message handler code here
//	showed = false;
	CDialog::OnCaptureChanged(pWnd);
}

BOOL CImageSelect::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
//	showed = false;
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

void CImageSelect::OnKillFocus(CWnd* pNewWnd) 
{
	CDialog::OnKillFocus(pNewWnd);
//	showed = false;
	// TODO: Add your message handler code here
	
}
