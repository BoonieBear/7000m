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
	//初始化位图资源
	bmpresource=0;
	//清空进度条标题
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
	//进度条的上下文环境句柄
	CPaintDC dc(this);
	int pos=GetPos();
	int low,hight;
	low=hight=0;
	GetRange(low,hight);
	int range=hight-low;
	//得到当前进度(%)
	float percent=float(pos)/(float)range;
	CRect rect;
	GetClientRect(&rect);
	rect.right=rect.left+percent*rect.Width();
	//根据进度填充矩形
	dc.FillSolidRect(&rect,RGB(0,0,255));
	
	//如果需要在进度条上绘制动画
	if(bmpresource)
	{
		CBitmap bmp,bmpold;
		BITMAP bmpinfo;
		
		bmp.LoadBitmap(bmpresource);
		bmp.GetBitmap(&bmpinfo);
		CDC mem;
		mem.CreateCompatibleDC(&dc);
		mem.SelectObject(&bmp);
		//在正确位置绘制图片
		CRect rectbmp;
		GetClientRect(&rectbmp);
		rectbmp.right=rectbmp.left+percent*rectbmp.Width();
		dc.BitBlt(rectbmp.right-bmpinfo.bmWidth,0,bmpinfo.bmWidth,bmpinfo.bmHeight,&mem,0,0,SRCCOPY);
		//还原DC设置
		mem.SelectObject(&bmpold);
	}
	
	//如果需要在进度条上输出文本
	if(!barTitle.IsEmpty())
	{
		CRect rt;
		GetClientRect(&rt);
		rt.left-=10;
		rt.right+=10;
		//文本输出方式为透明
		dc.SetBkMode(TRANSPARENT);
		//文本默认色为白色
		dc.SetTextColor(RGB(0,0,0));
		CSize ext;
		//GetTextExtent：测试文本尺寸
		ext=dc.GetTextExtent(barTitle);
		int test=(rt.Width()-ext.cx)/2;
		if((percent*rt.Width())<test)
			//如果进度条还在文本左边，使用蓝色文本
			dc.SetTextColor(RGB(0,255,0));
		//输出进度条的文本标题
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
	//开始重绘
	Invalidate();
}

void MyProgress::SetBmp(DWORD bmp)
{
	bmpresource=bmp;
	//开始重绘
	Invalidate();
}
