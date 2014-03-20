// ShowPic.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "ShowPic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CShowPic dialog


CShowPic::CShowPic(CWnd* pParent /*=NULL*/)
	: CDialog(CShowPic::IDD, pParent)
{
	//{{AFX_DATA_INIT(CShowPic)
	index = NULL;
	//}}AFX_DATA_INIT
}


void CShowPic::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CShowPic)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CShowPic, CDialog)
	//{{AFX_MSG_MAP(CShowPic)
	ON_BN_CLICKED(IDC_NEXT, OnNext)
	ON_BN_CLICKED(IDC_PRE, OnPre)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CShowPic message handlers

void CShowPic::AddToList(CString filename)
{

	image.Load(filename,CXIMAGE_SUPPORT_BMP);
	PicFileList.AddTail(filename);
	index = PicFileList.GetTailPosition();
	image.Load(filename);
	SetDlgItemText(IDC_STATIC_FILENAME,filename.GetBuffer(255));
	Invalidate(TRUE);
}

BOOL CShowPic::OnInitDialog() 
{
	CDialog::OnInitDialog();
	image.Load("background.bmp",CXIMAGE_SUPPORT_BMP);

	// TODO: Add extra initialization here
	SetDlgItemText(IDC_STATIC_FILENAME,"ȱʡ");
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CShowPic::OnNext() 
{
	// TODO: Add your control notification handler code here
	if (PicFileList.GetCount()>0)
	{
	
		POSITION  tail = PicFileList.GetTailPosition();
		if(tail != index)
		{
			CString filename = PicFileList.GetNext(index);
			
			image.Load(filename);
			SetDlgItemText(IDC_STATIC_FILENAME,filename.GetBuffer(255));
			Invalidate(TRUE);
		}
	}
}

void CShowPic::OnPre() 
{
	// TODO: Add your control notification handler code here
	if (PicFileList.GetCount()>0)
	{
		
		POSITION  head = PicFileList.GetHeadPosition();
		if(head != index)
		{
			CString filename = PicFileList.GetPrev(index);
			
			image.Load(filename);
			SetDlgItemText(IDC_STATIC_FILENAME,filename.GetBuffer(255));
			Invalidate(TRUE);
		}
	}
	
}

void CShowPic::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	CDC *pdc = GetDC();
	image.Draw(pdc->GetSafeHdc(),40,5,512,512,0,TRUE);
	
	// TODO: Add your message handler code here
	
	// Do not call CDialog::OnPaint() for painting messages
}
