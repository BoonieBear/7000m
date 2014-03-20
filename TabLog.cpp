// TabLog.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "TabLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTabLog dialog


CTabLog::CTabLog(CWnd* pParent /*=NULL*/)
	: CDialog(CTabLog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CTabLog)
	m_log = _T("");
	//}}AFX_DATA_INIT
}


void CTabLog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CTabLog)
	DDX_Text(pDX, IDC_EDIT1, m_log);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CTabLog, CDialog)
	//{{AFX_MSG_MAP(CTabLog)
		// NOTE: the ClassWizard will add message map macros here
		ON_MESSAGE(WMSG_TABLOG,showlog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CTabLog message handlers

void CTabLog::showlog(WPARAM wParam, LPARAM lParam)
{
	UINT nlength = (UINT)wParam;
	CString log =(char*)lParam;
	char tmpstr[100];
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT1);
	UpdateData(TRUE);
	m_log+=log;
	if (m_log.GetLength()>2048)
	{
		m_log = m_log.Right(1024);//��ȥ��512�ֽ�
		UpdateData(FALSE);
		pEdit->GetLine(0,tmpstr,100);
		int nlength = strlen(tmpstr); //�õ���������ĳ���
		m_log = m_log.Right(1024-nlength);//ȥ��nlength����
	}
	UpdateData(FALSE);
	
	
	pEdit->LineScroll(pEdit->GetLineCount(),0);
	delete (char*)lParam;
	lParam =NULL;
}