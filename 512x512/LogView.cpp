// LogView.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "LogView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLogView dialog


CLogView::CLogView(CWnd* pParent /*=NULL*/)
	: CDialog(CLogView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLogView)
	m_log = _T("");
	//}}AFX_DATA_INIT
}


void CLogView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLogView)
	DDX_Text(pDX, IDC_EDIT1, m_log);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLogView, CDialog)
	//{{AFX_MSG_MAP(CLogView)
		// NOTE: the ClassWizard will add message map macros here
	ON_MESSAGE(WMSG_LOG,showlog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLogView message handlers

void CLogView::showlog(WPARAM wParam, LPARAM lParam)
{
	UINT nlength = (UINT)wParam;
	CString log =(char*)lParam;
	char tmpstr[100];
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	UpdateData(TRUE);
	m_log+=log;
	if (m_log.GetLength()>2048)
	{
		m_log = m_log.Right(1024);//先去掉512字节
		UpdateData(FALSE);
		pEdit->GetLine(0,tmpstr,100);
		int nlength = strlen(tmpstr); //得到可能乱码的长度
		m_log = m_log.Right(1024-nlength);//去掉nlength长度
	}
	UpdateData(FALSE);
	
	
	pEdit->LineScroll(pEdit->GetLineCount(),0);
	delete (char*)lParam;
	lParam =NULL;
}
