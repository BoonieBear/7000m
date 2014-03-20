// FsPage.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "FsPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFsPage dialog


CFsPage::CFsPage(CWnd* pParent /*=NULL*/)
	: CDialog(CFsPage::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFsPage)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CFsPage::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFsPage)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFsPage, CDialog)
	//{{AFX_MSG_MAP(CFsPage)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFsPage message handlers
