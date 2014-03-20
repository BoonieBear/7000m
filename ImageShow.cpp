// ImageShow.cpp : implementation file
//

#include "stdafx.h"

#include "ImageShow.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CImageShow

CImageShow::CImageShow()
{
}

CImageShow::~CImageShow()
{
}


BEGIN_MESSAGE_MAP(CImageShow, CWnd)
	//{{AFX_MSG_MAP(CImageShow)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CImageShow message handlers

void CImageShow::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	RECT Rect;
	GetClientRect( &Rect );
	//m_Dib.SetPalette( &dc );
	m_Dib.Draw( &dc, 0, 0 );
	
	// Do not call CWnd::OnPaint() for painting messages
}

void CImageShow::FileLoad(char *filename)
{
	if( m_Dib.Load(filename ) )
		Invalidate();
}

BOOL CImageShow::Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	static CString className = AfxRegisterWndClass(CS_HREDRAW | CS_VREDRAW);

	return  CWnd::CreateEx(WS_EX_STATICEDGE|WS_EX_CLIENTEDGE   /*WS_EX_WINDOWEDGE/* |WS_EX_PALETTEWINDOW */, 
		className, NULL, dwStyle, 
		rect.left, rect.top, rect.right-rect.left, rect.bottom-rect.top,
		pParentWnd->GetSafeHwnd(), (HMENU) nID);
}

void CImageShow::FileLoad(CString filename)
{
	if( m_Dib.Load(filename ) )
		Invalidate(FALSE);

}
