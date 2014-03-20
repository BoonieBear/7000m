// PostView.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "PostView.h"
#include <math.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPostView dialog


CPostView::CPostView(CWnd* pParent /*=NULL*/)
	: CDialog(CPostView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPostView)
	iX=0;
	iY=0;
	iZ=0;
	//}}AFX_DATA_INIT
}


void CPostView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPostView)
	DDX_Control(pDX, IDC_NTGRAPHCTRL1, m_postview);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPostView, CDialog)
	//{{AFX_MSG_MAP(CPostView)
	ON_BN_CLICKED(IDC_SavePic, OnSavePic)
	ON_BN_CLICKED(IDC_LOOK_DOWN, OnLookDown)
	ON_BN_CLICKED(IDC_LOOK_FLAT, OnLookFlat)
	ON_BN_CLICKED(IDC_ZOOMOUT, OnZoomout)
	ON_MESSAGE(WMSG_POSTDRAW,Redraw)
	ON_BN_CLICKED(IDC_ZOOMIN, OnZoomin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPostView message handlers

BOOL CPostView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
	//������ͼ����
	iMode=0;//��ʼ����ͼ
	dFactor=1;
	m_postview.SetCaption("��λ��ͼ(����)");
	m_postview.SetFrameStyle(0);
	m_postview.SetControlFrameColor(MY_BACKCOLOR);
	m_postview.SetTrackMode(1);
	m_postview.SetCursorMode(2);
	m_postview.SetXLabel("�������(Km)");
	m_postview.SetYLabel("�������(Km)");
	m_postview.SetRange(-8,8,-8,8);
	Redraw();
	ZoomOutButton.LoadBitmaps(IDB_ZOOMOUT,NULL,NULL,NULL);
	ZoomOutButton.SubclassDlgItem(IDC_ZOOMOUT,this);
	ZoomOutButton.SizeToContent();
	ZoomInButton.LoadBitmaps(IDB_ZOOMIN,NULL,NULL,NULL);
	ZoomInButton.SubclassDlgItem(IDC_ZOOMIN,this);
	ZoomInButton.SizeToContent();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPostView::OnSavePic() 
{
	// TODO: Add your control notification handler code here
	CString TempStr;
	CString m_sFilename;
	
	// ��������
	//�����ļ���
	static char BASED_CODE szFilter[] = {"��λ��ͼ(*.bmp)|*.bmp|"}; 
	CDialog* pAppFrame = (CDialog*)AfxGetApp()->m_pMainWnd;
	CFileDialog theDataFile(FALSE,  _T("*.bmp"), NULL, OFN_HIDEREADONLY, szFilter, pAppFrame);
	
	if( theDataFile.DoModal()!=IDOK )
		return;
	else
	{
		m_sFilename =  theDataFile.GetPathName( );
	}
	m_postview.SaveAs(m_sFilename);
}

void CPostView::Redraw()
{
	CString str;
	if (iMode==0)//����ͼ
	{
		m_postview.ClearGraph();
		str.Format("��λ��ͼ(����) ����%.1f��",sqrt(iX*iX+iY*iY));
		m_postview.SetCaption(str);
		m_postview.SetXLabel("�������(Km)");
		m_postview.SetYLabel("�������(Km)");
		m_postview.SetRange(-8/dFactor,8/dFactor,-8/dFactor,8/dFactor);
		m_postview.SetElementLinetype(2);
		m_postview.SetElementLineColor(RGB(40,40,40));
		m_postview.SetElementWidth(1);
		//����
		m_postview.PlotXY(0,0,0);
		m_postview.PlotXY(iX/1000,iY/1000,0);
		//ship
		m_postview.AddElement();
		m_postview.SetElementLinetype(5);//����Ϊnone
		m_postview.SetElementPointSymbol(6);//����
		m_postview.SetElementPointColor(RGB(0,255,0));//��ɫ
		m_postview.SetElementSolidPoint(TRUE);//�յ㻹��ʵ�㣬TRUEΪʵ��
		m_postview.SetElementWidth(5);//��Ĵ�С
		m_postview.PlotXY(0,0,1);
		//auv
		m_postview.AddElement();
		m_postview.SetElementLinetype(5);//����Ϊnone
		m_postview.SetElementPointSymbol(4);//����
		m_postview.SetElementPointColor(RGB(255,0,0));//��ɫ
		m_postview.SetElementSolidPoint(TRUE);//�յ㻹��ʵ�㣬TRUEΪʵ��
		m_postview.SetElementWidth(4);//��Ĵ�С
		m_postview.PlotXY(iX/1000,iY/1000,2);

	}
	else
	{
		m_postview.ClearGraph();
		str.Format("��λ��ͼ(ˮƽ) ���%.1f��",iZ);
		m_postview.SetCaption(str);
		m_postview.SetXLabel("�������(Km)");
		m_postview.SetYLabel("���(Km)");
		m_postview.SetRange(-8/dFactor,8/dFactor,-8/dFactor,0);
		m_postview.SetElementLinetype(2);
		m_postview.SetElementLineColor(RGB(40,40,40));
		m_postview.SetElementWidth(1);
		//����
		m_postview.PlotXY(0,0,0);
		m_postview.PlotXY(iX/1000,-iZ/1000,0);
		//ship
		m_postview.AddElement();
		m_postview.SetElementLinetype(5);//����Ϊnone
		m_postview.SetElementPointSymbol(6);//����
		m_postview.SetElementPointColor(RGB(0,255,0));//��ɫ
		m_postview.SetElementSolidPoint(TRUE);//�յ㻹��ʵ�㣬TRUEΪʵ��
		m_postview.SetElementWidth(5);//��Ĵ�С
		m_postview.PlotXY(0,0,1);
		//auv
		m_postview.AddElement();
		m_postview.SetElementLinetype(5);//����Ϊnone
		m_postview.SetElementPointSymbol(4);//����
		m_postview.SetElementPointColor(RGB(255,0,0));//��ɫ
		m_postview.SetElementSolidPoint(TRUE);//�յ㻹��ʵ�㣬TRUEΪʵ��
		m_postview.SetElementWidth(4);//��Ĵ�С
		m_postview.PlotXY(iX/1000,iZ/1000,2);
	}
}

void CPostView::OnLookDown() 
{
	// TODO: Add your control notification handler code here
	iMode=0;
	Redraw();
}

void CPostView::OnLookFlat() 
{
	// TODO: Add your control notification handler code here
	iMode=1;
	Redraw();
}

void CPostView::OnZoomout() 
{
	// TODO: Add your control notification handler code here
	if (dFactor==8)
	{
		return;
	}
	dFactor*=2;
	Redraw();
}

void CPostView::OnZoomin() 
{
	// TODO: Add your control notification handler code here
	if (dFactor==1)
	{
		return;
	}
	dFactor/=2;
	Redraw();
}

BOOL CPostView::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class

	
	return CDialog::DestroyWindow();
}
