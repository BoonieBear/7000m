// MyProgress.cpp : implementation file
//

#include "stdafx.h"

#include "MyProgress.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyProgress

MyProgress::MyProgress()
{
	//��ʼ��λͼ��Դ
	bmpresource=0;
	//��ս���������
	barTitle.Empty();
}

MyProgress::~MyProgress()
{


}


BEGIN_MESSAGE_MAP(MyProgress, CProgressCtrl)
	//{{AFX_MSG_MAP(MyProgress)
	ON_WM_PAINT()
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// MyProgress message handlers

void MyProgress::OnPaint() 
{
	//�������������Ļ������
	CPaintDC dc(this);
	int pos=GetPos();
	int low,hight;
	low=hight=0;
	GetRange(low,hight);
	int range=hight-low;
	//�õ���ǰ����(%)
	float percent=float(pos)/(float)range;
	CRect rect;
	GetClientRect(&rect);
	rect.right=rect.left+percent*rect.Width();
	//���ݽ���������
	dc.FillSolidRect(&rect,RGB(0,0,255));
	
	//�����Ҫ�ڽ������ϻ��ƶ���
	if(bmpresource)
	{
		CBitmap bmp,bmpold;
		BITMAP bmpinfo;
		
		bmp.LoadBitmap(bmpresource);
		bmp.GetBitmap(&bmpinfo);
		CDC mem;
		mem.CreateCompatibleDC(&dc);
		mem.SelectObject(&bmp);
		//����ȷλ�û���ͼƬ
		CRect rectbmp;
		GetClientRect(&rectbmp);
		rectbmp.right=rectbmp.left+percent*rectbmp.Width();
		dc.BitBlt(rectbmp.right-bmpinfo.bmWidth,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&mem,0,0,SRCCOPY);
		//��ԭDC����
		mem.SelectObject(&bmpold);
	}
	
	//�����Ҫ�ڽ�����������ı�
	if(!barTitle.IsEmpty())
	{
		CRect rt;
		GetClientRect(&rt);
		rt.left-=10;
		rt.right+=10;
		//�ı������ʽΪ͸��
		dc.SetBkMode(TRANSPARENT);
		//�ı�Ĭ��ɫΪ��ɫ
		dc.SetTextColor(RGB(0,0,0));
		CSize ext;
		//GetTextExtent�������ı��ߴ�
		ext=dc.GetTextExtent(barTitle);
		int test=(rt.Width()-ext.cx)/2;
		if((percent*rt.Width())<test)
			//��������������ı���ߣ�ʹ����ɫ�ı�
			dc.SetTextColor(RGB(0,255,0));
		//������������ı�����
		dc.DrawText(barTitle, rt, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
	}
	
}

int MyProgress::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CProgressCtrl::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	return 0;
}

void MyProgress::SetBarCaption(CString title)
{
	barTitle=title;
	//��ʼ�ػ�
	Invalidate();
}

void MyProgress::SetBmp(DWORD bmp)
{
	bmpresource=bmp;
	//��ʼ�ػ�
	Invalidate();
}
