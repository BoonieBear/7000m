// VideoWindow.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "VideoWindow.h"
#include "ACSDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CVideoWindow

CVideoWindow::CVideoWindow(LONG nIndex)
	: m_nIndex(nIndex)
{
}

CVideoWindow::~CVideoWindow()
{
}


BEGIN_MESSAGE_MAP(CVideoWindow, CStatic)
	//{{AFX_MSG_MAP(CVideoWindow)
	ON_WM_LBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVideoWindow message handlers
BOOL CVideoWindow::Create(CWnd *pParentWnd,LPCTSTR szText,UINT nID,DWORD dwStyle)
{
	m_WndPos.SetRect(0,0,1,1);
	
	return CStatic::Create(szText,dwStyle,m_WndPos,pParentWnd,nID);
}

void CVideoWindow::SetWndPos(CRect &rc,LONG nDeflate)
{
	m_WndPos = rc;

	m_WndPos.DeflateRect(nDeflate,nDeflate,nDeflate,nDeflate);
	
	MoveWindow(&m_WndPos);

	ShowWindow(SW_SHOW);
}

CRect CVideoWindow::GetWndPos()
{
	return m_WndPos;
}


