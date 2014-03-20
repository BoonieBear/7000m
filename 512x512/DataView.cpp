// DataView.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "DataView.h"
#define DATABKCOLOUR RGB(160,160,160)
#define DATACOLOUR RGB(40,40,40)
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDataView dialog


CDataView::CDataView(CWnd* pParent /*=NULL*/)
	: CDialog(CDataView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDataView)
	//}}AFX_DATA_INIT
}


void CDataView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDataView)
	DDX_Control(pDX, IDC_BACKDOWN, m_backdown);
	DDX_Control(pDX, IDC_RIGHT, m_right);
	DDX_Control(pDX, IDC_LEFT, m_left);
	DDX_Control(pDX, IDC_FRONTUP, m_frontup);
	DDX_Control(pDX, IDC_FRONTDOWN, m_frontdown);
	DDX_Control(pDX, IDC_FRONT, m_front);
	DDX_Control(pDX, IDC_DOWN, m_down);
	DDX_Control(pDX, IDC_UWVHEIGTH, m_UWVHEIGTH);
	DDX_Control(pDX, IDC_UWVDEEP, m_UWVDEEP);
	DDX_Control(pDX, IDC_UWVLONG, m_uwvlong);
	DDX_Control(pDX, IDC_UWVLAT, m_uwvlat);
	DDX_Control(pDX, IDC_ROLL, m_roll);
	DDX_Control(pDX, IDC_PITCH, m_pitch);
	DDX_Control(pDX, IDC_HEAD, m_head);
	DDX_Control(pDX, IDC_DISTANCEY, m_distancey);
	DDX_Control(pDX, IDC_DISTANCEX, m_distancex);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDataView, CDialog)
	//{{AFX_MSG_MAP(CDataView)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDataView message handlers

BOOL CDataView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	//加入数据显示控件///////////////////////////////////////////////////////////////////////
	CString str;
	m_head.SetColourBackGround(DATABKCOLOUR);
	m_head.SetColourForeGround(DATACOLOUR);
	m_head.SetColourFaded(DATABKCOLOUR);
	str="     0";
	m_head.Display(str);

	m_pitch.SetColourBackGround(DATABKCOLOUR);
	m_pitch.SetColourForeGround(DATACOLOUR);
	m_pitch.SetColourFaded(DATABKCOLOUR);
	str="     0";
	m_pitch.Display(str);

	m_roll.SetColourBackGround(DATABKCOLOUR);
	m_roll.SetColourForeGround(DATACOLOUR);
	m_roll.SetColourFaded(DATABKCOLOUR);
	str="     0";
	m_roll.Display(str);

	m_uwvlat.SetColourBackGround(DATABKCOLOUR);
	m_uwvlat.SetColourForeGround(DATACOLOUR);
	m_uwvlat.SetColourFaded(DATABKCOLOUR);
	str="     0";
	m_uwvlat.Display(str);

	m_uwvlong.SetColourBackGround(DATABKCOLOUR);
	m_uwvlong.SetColourForeGround(DATACOLOUR);
	m_uwvlong.SetColourFaded(DATABKCOLOUR);
	str="     0";
	m_uwvlong.Display(str);

// 	m_shiplat.SetColourBackGround(RGB(0,0,0));
// 	m_shiplat.SetColourForeGround(DATACOLOUR);
// 	m_shiplat.SetColourFaded(DATABKCOLOUR);
// 	str="     0";
// 	m_shiplat.Display(str);
// 
// 	m_shiplong.SetColourBackGround(RGB(0,0,0));
// 	m_shiplong.SetColourForeGround(DATACOLOUR);
// 	m_shiplong.SetColourFaded(DATABKCOLOUR);
// 	str="     0";
// 	m_shiplong.Display(str);

	m_distancex.SetColourBackGround(DATABKCOLOUR);
	m_distancex.SetColourForeGround(DATACOLOUR);
	m_distancex.SetColourFaded(DATABKCOLOUR);
	str="     0";
	m_distancex.Display(str);

	m_distancey.SetColourBackGround(DATABKCOLOUR);
	m_distancey.SetColourForeGround(DATACOLOUR);
	m_distancey.SetColourFaded(DATABKCOLOUR);
	str="     0";
	m_distancey.Display(str);

	m_UWVHEIGTH.SetColourBackGround(DATABKCOLOUR);
	m_UWVHEIGTH.SetColourForeGround(DATACOLOUR);
	m_UWVHEIGTH.SetColourFaded(DATABKCOLOUR);
	str="     0";
	m_UWVHEIGTH.Display(str);

	m_UWVDEEP.SetColourBackGround(DATABKCOLOUR);
	m_UWVDEEP.SetColourForeGround(DATACOLOUR);
	m_UWVDEEP.SetColourFaded(DATABKCOLOUR);
	str="     0";
	m_UWVDEEP.Display(str);
//bp display
	m_front.SetColourBackGround(DATABKCOLOUR);
	m_front.SetColourForeGround(DATACOLOUR);
	m_front.SetColourFaded(DATABKCOLOUR);
	str="   255";
	m_front.Display(str);

	m_frontdown.SetColourBackGround(DATABKCOLOUR);
	m_frontdown.SetColourForeGround(DATACOLOUR);
	m_frontdown.SetColourFaded(DATABKCOLOUR);
	str="   255";
	m_frontdown.Display(str);

	m_frontup.SetColourBackGround(DATABKCOLOUR);
	m_frontup.SetColourForeGround(DATACOLOUR);
	m_frontup.SetColourFaded(DATABKCOLOUR);
	str="   255";
	m_frontup.Display(str);

	m_right.SetColourBackGround(DATABKCOLOUR);
	m_right.SetColourForeGround(DATACOLOUR);
	m_right.SetColourFaded(DATABKCOLOUR);
	str="   255";
	m_right.Display(str);

	m_left.SetColourBackGround(DATABKCOLOUR);
	m_left.SetColourForeGround(DATACOLOUR);
	m_left.SetColourFaded(DATABKCOLOUR);
	str="   255";
	m_left.Display(str);

	m_backdown.SetColourBackGround(DATABKCOLOUR);
	m_backdown.SetColourForeGround(DATACOLOUR);
	m_backdown.SetColourFaded(DATABKCOLOUR);
	str="   255";
	m_backdown.Display(str);

	m_down.SetColourBackGround(DATABKCOLOUR);
	m_down.SetColourForeGround(DATACOLOUR);
	m_down.SetColourFaded(DATABKCOLOUR);
	str="   255";
	m_down.Display(str);

	UpdateTimeDisplay("启动");//系统动作更新时间
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDataView::UpdateTimeDisplay(CString infoSource)
{
	CString str;
	CTime ct = CTime::GetCurrentTime();
	str.Format("%02d:%02d:%02d(%s)",ct.GetHour(),ct.GetMinute(),ct.GetSecond(),infoSource);
	CWnd* pWnd = GetDlgItem(IDC_UpdateTime);
	pWnd->SetWindowText(str);
}


void CDataView::BPUpdateTime(CString infoSource)
{
	CString str;
	CTime ct = CTime::GetCurrentTime();
	str.Format("%02d:%02d:%02d(%s)",ct.GetHour(),ct.GetMinute(),ct.GetSecond(),infoSource);
	CWnd* pWnd = GetDlgItem(IDC_BPUpdateTime);
	pWnd->SetWindowText(str);
}
