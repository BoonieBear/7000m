// WordDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "WordDialog.h"
#include "ACSDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CWordDialog dialog


CWordDialog::CWordDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CWordDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWordDialog)
	m_strInput = _T("������Ϣ�20��");
	m_wordlog = _T("");
	//}}AFX_DATA_INIT
}


void CWordDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWordDialog)
	DDX_Control(pDX, IDC_EDIT_WORDLOG, m_logedit);
	DDX_Control(pDX, IDC_EDIT_INPUT, m_input);
	DDX_Text(pDX, IDC_EDIT_INPUT, m_strInput);
	DDX_Text(pDX, IDC_EDIT_WORDLOG, m_wordlog);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWordDialog, CDialog)
	//{{AFX_MSG_MAP(CWordDialog)
	ON_BN_CLICKED(ID_Send, OnSend)
	ON_BN_CLICKED(ID_AddToList, OnAddToList)

	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWordDialog message handlers

BOOL CWordDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	editfont.CreatePointFont(160,"Sans Serif");
	m_logedit.SetFont(&editfont);
	m_input.SetFont(&editfont);
	m_input.SetLimitText(20);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CWordDialog::OnSend() 
{
	// TODO: Add your control notification handler code here
/*	UpdateData(TRUE);
	if (!m_strInput.GetLength())
	{
		return;
	}
	CString strlog;
	strlog = "������Ϣ:" + m_strInput;
	CACSDlg* dlg= (CACSDlg*)AfxGetApp()->m_pMainWnd;
	dlg->SaveRecord(strlog);
	
	DIGITALBUFF* buf = (DIGITALBUFF *)malloc(sizeof(DIGITALBUFF));
	buf->len = m_strInput.GetLength();
	buf->buf = (unsigned char *)malloc(buf->len);
	memcpy(buf->buf,m_strInput,buf->len);
	m_WzdtextList.AddTail(buf);//���������б�
	InputText(strlog);
	m_strInput="";
	UpdateData(FALSE);
	
	NET_PACKET *netpacket;
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	if(netpacket==NULL)
	{
		AfxMessageBox("����NET_PACKET�ռ�����쳣��");
		return;
	}
	
	netpacket->FrmID = UWACCMD_FORCE_TRANSMIT;
	netpacket->FrmLen = 32;
	netpacket->DestID = ADIOID;
	netpacket->HeadParam[0] = MFSKMOD;//
	netpacket->HeadParam[1] = 1;//�ܰ���
	netpacket->HeadParam[2] = 0;//��ǰ����
	netpacket->HeadParam[3] = 0;//�����ݳ���
	netpacket->pData = NULL;
	SendNetpacketSync.Lock();
	m_WzdNetpacketList.AddTail(netpacket);
	SendNetpacketSync.Unlock();
	SetEvent(IsNetpacketEvent);	*/
}

void CWordDialog::OnAddToList() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	m_input.SetFocus();
	if ((!m_strInput.GetLength())||(m_strInput.GetLength()>41))
	{
		AfxMessageBox("���볤�Ȳ���!");
		return;
	}
	CString strlog;
	strlog = "���������б�:" + m_strInput;
	CACSDlg* dlg= (CACSDlg*)AfxGetApp()->m_pMainWnd;
	dlg->SaveRecord(strlog);
	
	DIGITALBUFF* buf = (DIGITALBUFF *)malloc(sizeof(DIGITALBUFF));
	buf->len = m_strInput.GetLength();
	buf->buf = (unsigned char *)malloc(buf->len);
	memcpy(buf->buf,m_strInput,buf->len);
	m_WzdtextList.AddTail(buf);//���������б�
	
	strlog = m_strInput;
	m_strInput="";
	UpdateData(FALSE);
	InputText(strlog);
	
	
}

void CWordDialog::InputText(CString strlog)
{
	UpdateData(TRUE);
	CString str,strtime;
	CTime ct = CTime::GetCurrentTime();
	strtime.Format("(%02d:%02d:%02d)",ct.GetHour(),ct.GetMinute(),ct.GetSecond());
	
	strlog = strtime + strlog + "\r\n";
	if (UWACInitParam.ADIOWorkMode==1)//ˮ��
	{
		strlog = "ĸ��:" + strlog;
	} 
	else
	{
		strlog = "Ǳ��:" + strlog;
	}
	
	
	TextFile.SaveFile(strlog, strlog.GetLength());

	m_wordlog+=strlog;
	if (m_wordlog.GetLength()>2048)
	{
		m_wordlog = m_wordlog.Right(512);
	}
	UpdateData(FALSE);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_WORDLOG);
	pEdit->LineScroll(pEdit->GetLineCount(),0);
	
}

// void CWordDialog::OnSetfocusEditInput() 
// {
// 	// TODO: Add your control notification handler code here
// 	m_strInput="";
// 	UpdateData(FALSE);
// 	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_WORDLOG);
// 	pEdit->LineScroll(pEdit->GetLineCount(),0);
// }


void CWordDialog::InputWord(CString strlog)
{
	UpdateData(TRUE);
	CString str,strtime;
	CTime ct = CTime::GetCurrentTime();
	strtime.Format("(%02d:%02d:%02d)",ct.GetHour(),ct.GetMinute(),ct.GetSecond());
	
	strlog = strtime + strlog + "\r\n";
	if (UWACInitParam.ADIOWorkMode==1)//ˮ��
	{
		strlog = "Ǳ��:" + strlog;
	} 
	else
	{
		strlog = "ĸ��:" + strlog;
	}
	
	
//	TextFile.SaveFile(strlog, strlog.GetLength());
	
	m_wordlog+=strlog;
	if (m_wordlog.GetLength()>2048)
	{
		m_wordlog = m_wordlog.Right(512);
	}
	UpdateData(FALSE);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_EDIT_WORDLOG);
	pEdit->LineScroll(pEdit->GetLineCount(),0);
}
