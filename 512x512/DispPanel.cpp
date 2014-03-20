// DispPanel.cpp : implementation file
//

#include "stdafx.h"
#include "DispPanel.h"
#include "MyMemDC.h"
#include "FFT.h"
#include "data_define.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDispPanel

CDispPanel::CDispPanel()
{
	scaleY=0;
	m_pTotalYdata = NULL;	TotalLength = 0;
	m_pCurYdata = NULL;		CurLength = 0;
	m_pPSDYdata = NULL;
	PSDreal=NULL;	PSDimag=NULL;	
	
	CurFrameRect = CRect(0,0,0,0);
	lastFrameRect = CRect(0,0,TotalLength,0);
	Zoomed = false;
	showFrame = false;
	bShowPSD = false;
	leftMarginX		= 5;
	topMarginY		= 5;
	rightMarginX	= 10;
	bottomMarginY	= 5;
	m_globalMaxY = 0;
	m_globalMinY = 0;
	m_globalMaxX = 0;
	m_globalMinX = 0;
	m_globalMaxf = 0;
	m_globalMinf = 0;
	m_globalMaxPSD = 0;
	m_currentMaxX = 0;
	m_currentMinX = 0;
	m_currentMaxY = 0;
	m_currentMinY = 0;
	m_defaultMaxf = 4000;
	m_currentMaxf = m_defaultMaxf;
	DividedUnits=4;
	m_currentMinf =0;
	m_defaultMinY = -32768;
	m_defaultMaxY = 32768;
}

CDispPanel::~CDispPanel()
{
	ClearPSDMalloc();
}


BEGIN_MESSAGE_MAP(CDispPanel, CButton)
	//{{AFX_MSG_MAP(CDispPanel)
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONDOWN()
	ON_WM_RBUTTONDBLCLK()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDispPanel message handlers
double CDispPanel::MinA(double *pIn,int length)
{

	double result=0;
	for (int i=0;i<length;i++) 
	{
		if (result>pIn[i]) result = pIn[i];
	}
//	TRACE("min = %lf\n",result);
	return result;
}
double CDispPanel::MaxA(double *pIn,int length)
{
	double result=0;
	for (int i=0;i<length;i++) 
	{
		if (result<pIn[i]) result = pIn[i];
	}
//	TRACE("max = %lf\n",result);
	return result;
}
double CDispPanel::MedianA(double *pIn, int length)
{
	double result=0;
	double *pTemp= new double[length];
	memcpy(pTemp,pIn,sizeof(double)*length);
	qsort(pTemp,length,sizeof(double),CDispPanel::Comparedouble);
	result = pTemp[length/2];
	delete[] pTemp;
	return result;
}
int CDispPanel::Comparedouble(const void *pval1, const void *pval2)
{
	return (int)( (*(double*)pval1)-(*(double*)pval2));
}
void CDispPanel::InitScaleY()
{
	m_globalMaxY = m_defaultMaxY;	m_globalMinY = m_defaultMinY;
	if (bShowPSD)//psd
	{
		for(int i=0;i<CurLength;i++)
		{
			if (m_globalMaxY<m_pCurYdata[i]) m_globalMaxY = m_pCurYdata[i];
			if (m_globalMinY>m_pCurYdata[i]) m_globalMinY = m_pCurYdata[i];
		}
	}
	
	if (m_globalMaxY-m_globalMinY>1e-6)
	{
		double temp=max(m_globalMaxY,-m_globalMinY);
		scaleY = m_GraphRect.Height()/(temp*2);	
	}
	else
	{
		scaleY = 1;
	}
	m_currentMinY = m_globalMinY;	m_currentMaxY = m_globalMaxY;
	m_globalMinX = 0;	m_globalMaxX = TotalLength;
	m_currentMinX = m_globalMinX;	m_currentMaxX = m_globalMaxX;

}
void CDispPanel::Plotf(CDC *pDC,CRect* pRect)
{
	int x0=pRect->left,i=0;
	double nStep = 0,x=0;
	int y0=0;
	
	CPen pen1(PS_SOLID,1,RGB(255,255,255));
	CPen* pPen;
	pPen=pDC->SelectObject(&pen1);
	if(bShowPSD)
		y0=pRect->bottom;
	else
		y0=(pRect->top+pRect->bottom)/2;
	
	pDC->MoveTo(x0,y0);

	double tempMin=0,tempMax=0;;
	//对于不同数量级数据的显示，出于显示速度的问题，不采用通用方法
	if (CurLength>10*(pRect->Width()))
	{//数据量是窗口的10倍以上
		
		nStep=1.0*CurLength/(pRect->Width());
		for (x=0,i=0;i<pRect->Width();i++,x=(int)(x+nStep)) 
		{
			tempMin = MinA(&m_pCurYdata[int(x)],int(nStep));
			tempMax = MaxA(&m_pCurYdata[int(x)],int(nStep));
			if(tempMin < 0) pDC->LineTo(x0+i,(int)(y0-tempMin*scaleY)); 
			if(tempMax > 0) pDC->LineTo(x0+i,(int)(y0-tempMax*scaleY)); 
			if(tempMin == 0 && tempMax == 0) pDC->LineTo(x0+i,y0); 

		}
	}
	else 
	{//数据量是窗口的几倍或者，数据量小于窗口尺寸(波形放大)
		if (!Zoomed && CurLength>pRect->Width())//fixed bug
		{
			for (i=0;i<pRect->Width();i++) 
			{
				pDC->LineTo((int)(x0+i),(int)(y0-m_pCurYdata[i]*scaleY)); 
			}
		}
		else
		{
			if(CurLength>0)
			{
				nStep = 1.0*pRect->Width()/CurLength;
				for (i=0;i<CurLength;i++) 
				{
					pDC->LineTo((int)(x0+i*nStep),(int)(y0-m_pCurYdata[i]*scaleY)); 
				}
			}
		}

	}

	pDC->SelectObject(pPen);
}

void CDispPanel::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct) 
{
	CRect ClientRect=lpDrawItemStruct->rcItem;
	CDC* pDC=CDC::FromHandle(lpDrawItemStruct->hDC);

	ClientRect.DeflateRect(1,1,1,1);
//	pDC->DrawFocusRect(&ClientRect);
	ClearUnits(pDC);
	m_GraphRect = ClientRect;
	m_GraphRect.DeflateRect(leftMarginX,topMarginY,rightMarginX,bottomMarginY);//矩形框缩小
	
	//准备数据以及绘制坐标
	if (m_pTotalYdata!=NULL) 
	{
		if(m_pCurYdata==NULL) 
		{
			if (!bShowPSD)
			{
				m_pCurYdata = m_pTotalYdata;
				CurLength=TotalLength;
			}
			else
			{
				//add getpad
				if(!m_pPSDYdata) GetPSD();
				m_pCurYdata = m_pPSDYdata;
				CurLength=nextPow2(TotalLength)/2;
			}
		}
//		if (scaleY==0)
//		{
			InitScaleY();
//		}
	}	
	
	CMyMemDC* pMemDC=new CMyMemDC(pDC,&m_GraphRect);
	m_GraphRect = CRect(0,0,m_GraphRect.Width(),m_GraphRect.Height());
	CBrush hbr;
	hbr.CreateSolidBrush(RGB(40,40,40));//背景色
	pMemDC->FillRect(&m_GraphRect,&hbr);
	hbr.DeleteObject();
	DrawUnits(pMemDC,&m_GraphRect); //画坐标值
	DrawAxis(pMemDC,&m_GraphRect);//画坐标轴

	//画放大矩形
	if (showFrame) 	
		//pMemDC->DrawFocusRect(&CurFrameRect);
		pMemDC->FrameRect(&CurFrameRect,&CBrush(RGB(0,0,0)));
	//画数据曲线
 	Plotf(pMemDC,&m_GraphRect);
	
	delete pMemDC;

}

void CDispPanel::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(point.x<leftMarginX) return;
	if(m_pTotalYdata==NULL) return;
	if (!(nFlags&MK_CONTROL)) return;
//	if (!showFrame)
	{
		showFrame = true;
		CurFrameRect.top = point.y-topMarginY;
		CurFrameRect.bottom = CurFrameRect.top;
		CurFrameRect.left = point.x-leftMarginX;
		CurFrameRect.right = CurFrameRect.left;
		SetCapture();
	}
//	else
//	{
//		showFrame = false;
//	}
	if(!Zoomed)
	{
		if (bShowPSD)
		{
			lastFrameRect = CRect(0,0,nextPow2(TotalLength)/2,0);
		}
		else
		{
			lastFrameRect = CRect(0,0,TotalLength,0);
		}
	}
	CButton::OnLButtonDown(nFlags, point);
}

void CDispPanel::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (nFlags==MK_LBUTTON)
	{
		if(m_pTotalYdata==NULL) return;
		if (showFrame)
		{
			if (point.x-leftMarginX > CurFrameRect.left)
				CurFrameRect.right=point.x-leftMarginX;
			else
				CurFrameRect.left=point.x-leftMarginX;
			
			if (point.y-topMarginY > CurFrameRect.top)
				CurFrameRect.bottom=point.y-topMarginY;
			else
				CurFrameRect.top=point.y-topMarginY;
			Invalidate(FALSE);
		}
	}
	CButton::OnMouseMove(nFlags, point);
}

void CDispPanel::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_pTotalYdata==NULL) return;
	if(CurFrameRect.Width()<2 ||CurFrameRect.Height() < 2) return;

	if (showFrame) 
	{
		showFrame = false;
	}
	
	int OffsetBegin,OffsetEnd;

	if (Zoomed||TotalLength>=m_GraphRect.Width())
	{
		OffsetBegin= int(lastFrameRect.left+1.0*CurFrameRect.left/m_GraphRect.Width()*lastFrameRect.Width());
		OffsetEnd = int(lastFrameRect.left+1.0*CurFrameRect.right/m_GraphRect.Width()*lastFrameRect.Width());
	}
	else
	{//数据量小于窗口宽度且不放大波形
		if(CurFrameRect.left>=TotalLength) return;
		if(CurFrameRect.right>TotalLength) CurFrameRect.right=TotalLength;
		OffsetBegin= int(lastFrameRect.left+1.0*CurFrameRect.left);
		OffsetEnd = int(lastFrameRect.left+1.0*CurFrameRect.right);
	}
	//TRACE("start = %d end = %d\n",OffsetBegin,OffsetEnd);
	if(OffsetBegin<0) OffsetBegin=0;
	if(OffsetEnd>TotalLength) OffsetEnd = TotalLength;
	CurLength = OffsetEnd - OffsetBegin;

	if (bShowPSD)
	{
		m_pCurYdata	 = m_pPSDYdata+OffsetBegin;
		m_currentMinf =OffsetBegin;
		m_currentMaxf =OffsetEnd;
	}
	else
	{
		m_pCurYdata	 = m_pTotalYdata+OffsetBegin;
		m_currentMinX = m_globalMinX + OffsetBegin;
		m_currentMaxX = m_globalMinX + OffsetEnd;
	}

	if (CurFrameRect.Height()>1)
	{
		scaleY*=1.0*m_GraphRect.Height()/CurFrameRect.Height();
	}
	lastFrameRect.left = OffsetBegin;
	lastFrameRect.right = OffsetEnd;
	Zoomed = true;
	Invalidate(FALSE);

	CButton::OnLButtonUp(nFlags, point);
}

void CDispPanel::OnRButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	Zoomed = false;
	m_pCurYdata = NULL;
	ReleaseCapture();
	if (bShowPSD)
	{
		lastFrameRect = CRect(0,0,nextPow2(TotalLength)/2,0);
		m_currentMinf = 0;
		m_currentMaxf = m_defaultMaxf;
	}
	else
	{
		lastFrameRect = CRect(0,0,TotalLength,0);
		m_currentMinX = 0;
		m_currentMaxX = TotalLength;
	}
	scaleY = 0;
	Invalidate(FALSE);
	CButton::OnRButtonDown(nFlags, point);
}

void CDispPanel::ClearData()
{
	m_pTotalYdata = NULL;TotalLength = 0;
	m_pCurYdata = NULL;CurLength = 0;
	m_pPSDYdata =  NULL;
	Zoomed = false;
	showFrame = false;
	bShowPSD = false;
	m_globalMaxY=0;
	m_globalMinY=0;
	m_globalMaxX=0;
	m_globalMinX=0;
	m_defaultMinY = 0;
	m_defaultMaxY = 0;
	m_globalMaxf=0;
	m_globalMinf=0;
	m_globalMaxPSD=0;
	m_currentMaxX=0;
	m_currentMinX=0;
	m_currentMaxY=0;
	m_currentMinY=0;
	m_currentMaxf=0;//默认4000
	m_currentMinf=0;
	DividedUnits=0;
	scaleY = 0;
}

void CDispPanel::GetPSD()
{
	if(m_pTotalYdata == NULL) return;
	ClearPSDMalloc();
	m_globalMaxPSD = 0;
	PSDreal = new double[nextPow2(TotalLength)];
	PSDimag = new double[nextPow2(TotalLength)];
	
	FFT(nextPow2(TotalLength),false,m_pTotalYdata,NULL,PSDreal,PSDimag);
//	RealFFT(nextPow2(TotalLength),m_pTotalYdata,PSDreal,PSDimag);
	for (int i=0;i<nextPow2(TotalLength)/2;i++) 
	{
		PSDreal[i]=PSDreal[i]*PSDreal[i]+PSDimag[i]*PSDimag[i];
		if (m_globalMaxPSD<PSDreal[i]) m_globalMaxPSD=PSDreal[i];
	}
	if(m_globalMaxPSD>1e-6) scaleY = m_GraphRect.Height()/(m_globalMaxPSD);	
	m_pPSDYdata = PSDreal;
	m_globalMinf = 0;
	CurLength = nextPow2(TotalLength)/2;
	m_currentMinf = 0;
	m_currentMaxf = m_defaultMaxf;
}

void CDispPanel::ClearPSDMalloc()
{
	if (PSDreal!=NULL)	{delete[] PSDreal;PSDreal=NULL;}
	if (PSDimag!=NULL)	{delete[] PSDimag;PSDimag=NULL;}
}

void CDispPanel::OnRButtonDblClk(UINT nFlags, CPoint point) 
{
	if(bShowPSD)
	{
		bShowPSD = false;
	}
	else 
	{
		if(!m_pPSDYdata) GetPSD();
		bShowPSD = true;
		m_currentMinf = 0;
		m_currentMaxf = m_defaultMaxf;
	}
	OnRButtonDown(nFlags,point); 
	CButton::OnRButtonDblClk(nFlags, point);
}

void CDispPanel::DrawAxis(CDC *pDC, CRect *pRect)
{
	int x0=pRect->left+1;
	int y0=0;
	int num=10;

	CPen pen1(PS_SOLID,2,RGB(205,255,205));
	CPen* pOldPen;
	pOldPen=pDC->SelectObject(&pen1);
	
	pDC->MoveTo(pRect->left+1,pRect->top);		pDC->LineTo(pRect->left+1,pRect->bottom);//纵向左轴
	pDC->MoveTo(pRect->left+1,pRect->top+1);	pDC->LineTo(pRect->right,pRect->top+1);//水平上端轴
	pDC->MoveTo(pRect->right-1,pRect->top);		pDC->LineTo(pRect->right-1,pRect->bottom);//纵向右轴
	pDC->MoveTo(pRect->left+1,pRect->bottom-1);	pDC->LineTo(pRect->right,pRect->bottom-1);//水平下轴
	
	CPen pen2(PS_DOT,1,RGB(180,180,180));
	pDC->SelectObject(&pen2);

	double powerUnit = pow(10,floor(log10(scaleY)));
	
	y0=(pRect->top+pRect->bottom)/2;
	//画纵轴坐标线
	for(int i=0;i<2;i++)
	{
		pDC->MoveTo(pRect->left, y0-(pRect->Height()/4)*i);		
		pDC->LineTo(pRect->right,y0-(pRect->Height()/4)*i);//纵向左轴
	}

	for( i=0;i<2;i++)
	{
		pDC->MoveTo(pRect->left, y0+(pRect->Height()/4)*i);		
		pDC->LineTo(pRect->right,y0+(pRect->Height()/4)*i);//纵向左轴
	}
	

	//画横轴坐标线
	for(int j=1;j<DividedUnits;j++)
	{
		pDC->MoveTo(pRect->left+(pRect->Width()/DividedUnits)*j,pRect->top);		
		pDC->LineTo(pRect->left+(pRect->Width()/DividedUnits)*j,pRect->bottom);//横向顶轴
		pDC->MoveTo(pRect->left+(pRect->Width()/DividedUnits)*j,pRect->top);		
		pDC->LineTo(pRect->left+(pRect->Width()/DividedUnits)*j,pRect->bottom);//横向底轴
	}
	
	pDC->SelectObject(pOldPen);
	
	
}

void CDispPanel::DrawUnits(CDC *pDC, CRect *pRect)
{
	CFont font;
	int nHeight=-14;
	int x0=0;
	int y0;
	
	pDC->SetBkMode(TRANSPARENT);
	pDC->SetTextAlign(TA_RIGHT);
	COLORREF color=pDC->SetTextColor(RGB(215,215,215));
	double nScalesY,nScalesX;//changed from int to double 
	CString out,strScales;
	if (bShowPSD)
	{
		nScalesY=(int)log10(m_globalMaxY);
		nScalesY=Pow10(nScalesY);//if use int ,nScalesY may overflow
		if(nScalesY<1000) nScalesY=1;
		out.Format("%10.2f",m_globalMaxY/nScalesY);
		y0=pRect->bottom-bottomMarginY;
		pDC->TextOut(pRect->left+leftMarginX+35,pRect->top,out);
		CRect drawRT(pRect->left+leftMarginX-12,pRect->bottom-bottomMarginY,pRect->left+leftMarginX+40,pRect->bottom-bottomMarginY+15);
		int yHeight=(pRect->bottom+bottomMarginY)-(pRect->top-topMarginY);
//		pDC->TextOut(pRect->left+leftMarginX+5,y0-5,"0.0");
		//////////////////////////////////////////////////////////////////////////
		nScalesX=(int)log10(m_currentMaxf);
		nScalesX=Pow10(nScalesX);
		if(nScalesX<1000) nScalesX=1;
		pDC->SetTextAlign(TA_LEFT);
		out.Format("%10.2lf",m_currentMinf/nScalesX);
		out.TrimLeft();
		pDC->TextOut(pRect->left+leftMarginX,pRect->bottom-bottomMarginY-15,out);
		
		int xWidth=(pRect->right-rightMarginX)-(pRect->left+leftMarginX);
		for(int xx=1;xx<DividedUnits;xx++)
		{
			out.Format("%10.2lf",(m_currentMinf+xx*(m_currentMaxf-m_currentMinf)/DividedUnits)/nScalesX);
			out.TrimLeft();
			pDC->TextOut(drawRT.left+(xWidth/DividedUnits-3)*xx,drawRT.top-15,out);
		}
		pDC->SetTextAlign(TA_RIGHT);
		out.Format("%10.2lf",m_currentMaxf/nScalesX);
		pDC->TextOut(pRect->right-rightMarginX,pRect->bottom-bottomMarginY-25,out);
	}
	else
	{
		y0=pRect->bottom-bottomMarginY-pRect->Height()/2;
		//////////////////////////////////////////////////////////////////////////
		//纵轴坐标

		nScalesY=(int)log10(m_globalMaxY);
		nScalesY=Pow10(nScalesY);
		if(nScalesY<1000) nScalesY=1;
		out.Format("%10.2f",m_globalMaxY/nScalesY);
		
		pDC->TextOut(pRect->left+leftMarginX+35,pRect->top,out);//Y轴最大值
		pDC->TextOut(pRect->left+leftMarginX+35,y0+10,"0.0");
		out.Format("%10.2f",m_globalMinY/nScalesY);//Y轴最小值
 		pDC->TextOut(pRect->left+leftMarginX+35,pRect->bottom-bottomMarginY-28,out);

		
		//////////////////////////////////////////////////////////////////////////
		//横轴坐标
		nScalesX=(int)log10(m_currentMaxX);
		nScalesX=Pow10(nScalesX);
		if(nScalesX<1000) nScalesX=1;
		pDC->SetTextAlign(TA_LEFT);
		out.Format("%10.2lf",m_currentMinX/nScalesX);
		out.TrimLeft();
		pDC->TextOut(pRect->left+leftMarginX,pRect->bottom-bottomMarginY-15,out);
		
		int xWidth=(pRect->right-rightMarginX)-(pRect->left+leftMarginX);
		CRect drawRT(pRect->left+leftMarginX-12,pRect->bottom-bottomMarginY,pRect->left+leftMarginX+40,pRect->bottom-bottomMarginY+15);
		for(int xx=1;xx<DividedUnits;xx++)
		{
			out.Format("%10.2lf",(m_currentMinX+xx*(m_currentMaxX-m_currentMinX)/DividedUnits)/nScalesX);
			out.TrimLeft();
			pDC->TextOut(drawRT.left+(xWidth/DividedUnits-3)*xx,drawRT.top-15,out);
		}
		pDC->SetTextAlign(TA_RIGHT);
		out.Format("%10.2lf",m_currentMaxX/nScalesX);
		pDC->TextOut(pRect->right-rightMarginX,pRect->bottom-bottomMarginY-25,out);

	}
	if(nScalesY>1)
	{
		out.Format("x%2.0e",nScalesY*1.0);
		pDC->TextOut(pRect->left+leftMarginX+55,pRect->top+12,out);
	}
	if(nScalesX>1)
	{
		out.Format("x%2.0e",nScalesX*1.0);
		pDC->TextOut(pRect->right-rightMarginX,pRect->bottom-bottomMarginY/2-15,out);
	}

}

void CDispPanel::ClearUnits(CDC* pDC)
{
	CRect ClientRect;
	GetClientRect(&ClientRect);
	CRect temp=CRect(0,0,leftMarginX+1,ClientRect.bottom-bottomMarginY);
	pDC->FillRect(&temp,&CBrush(MY_BACKCOLOR));
//	pDC->Rectangle(&temp);
	temp=CRect(0,ClientRect.bottom-bottomMarginY-1,ClientRect.right,ClientRect.bottom);
	pDC->FillRect(&temp,&CBrush(MY_BACKCOLOR));
//	pDC->Rectangle(&temp);
}

void CDispPanel::PreSubclassWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetButtonStyle(GetButtonStyle() | BS_OWNERDRAW);
	//通过代码实现Owner Draw自绘属性
}

void CDispPanel::SaveAs(LPCTSTR szFilename)
{
	PBITMAPINFO pbi;
	CRect rect;
	CClientDC dc(this);
	GetWindowRect(&rect);
	CBitmap bitmap;
    CDC ScrDC,MemDC;
    ScrDC.CreateDC("DISPLAY", NULL, NULL, NULL);
    MemDC.CreateCompatibleDC(&ScrDC);

    bitmap.CreateCompatibleBitmap(&ScrDC,rect.Width(),rect.Height());
    MemDC.SelectObject(&bitmap);

    //开始拷贝
    MemDC.BitBlt(0, 0, rect.Width(), rect.Height(),&ScrDC,rect.left,rect.top,SRCCOPY);
	//Create the bitmap info struct
	pbi = CreateBitmapInfoStruct((HBITMAP)bitmap.GetSafeHandle());
  
	//Create the bitmap
	CreateBMPFile((char*)szFilename, pbi, (HBITMAP)bitmap.GetSafeHandle(), MemDC);  
    ScrDC.DeleteDC();
    MemDC.DeleteDC();
	
}
/*******************************/
/*Function to create the Bitmap*/
/*******************************/
void CDispPanel::CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC) 
{
  HANDLE hf;                //file handle 
  BITMAPFILEHEADER hdr;     //bitmap file-header 
  PBITMAPINFOHEADER pbih;   //bitmap info-header 
  LPBYTE lpBits;            //memory pointer 
  DWORD dwTotal;            //total count of bytes 
  DWORD cb;                 //incremental count of bytes 
  BYTE *hp;                 //byte pointer 
  DWORD dwTmp; 

  pbih = (PBITMAPINFOHEADER) pbi; 
  lpBits = (LPBYTE) GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

  if(!lpBits) 
  {
    MessageBox("Unable to allocate memory for saving bitmap", "", MB_OK|MB_ICONERROR);
    return;
  }

  //Retrieve the color table (RGBQUAD array) and the bits (array of palette indices) from the DIB. 
  if(!GetDIBits(hDC, hBMP, 0, (WORD) pbih->biHeight, lpBits, pbi, DIB_RGB_COLORS)) 
  {
    MessageBox("Unable to retrieve colour table when saving bitmap", "", MB_OK|MB_ICONERROR);
    return;
  } 
    
  //Create the .BMP file. 
  hf = CreateFile(pszFile, 
                  GENERIC_READ | GENERIC_WRITE, 
                  (DWORD) 0, 
                  NULL, 
                  CREATE_ALWAYS, 
                  FILE_ATTRIBUTE_NORMAL, 
                  (HANDLE) NULL);
  
  if(hf == INVALID_HANDLE_VALUE) 
  {
    MessageBox("Unable to open the file when saving bitmap", "", MB_OK|MB_ICONERROR);
    return;
  }
  
  hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M" 
  //Compute the size of the entire file. 
  hdr.bfSize = (DWORD) (sizeof(BITMAPFILEHEADER) + 
                pbih->biSize + pbih->biClrUsed * sizeof(RGBQUAD) + 
				pbih->biSizeImage); 

  hdr.bfReserved1 = 0; 
  hdr.bfReserved2 = 0; 

  //Compute the offset to the array of color indices. 
  hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) +
                  pbih->biSize + pbih->biClrUsed * sizeof (RGBQUAD); 

  //Copy the BITMAPFILEHEADER into the .BMP file. 
  if(!WriteFile(hf, (LPVOID) &hdr, sizeof(BITMAPFILEHEADER), (LPDWORD) &dwTmp,  NULL)) 
  {
    MessageBox("Unable to write file header when saving bitmap", "", MB_OK|MB_ICONERROR);
    return;
  }
    
  //Copy the BITMAPINFOHEADER and RGBQUAD array into the file. 
  if(!WriteFile(hf, (LPVOID) pbih, sizeof(BITMAPINFOHEADER) 
                + pbih->biClrUsed * sizeof (RGBQUAD), 
                (LPDWORD) &dwTmp, ( NULL)) )
  {
    MessageBox("Unable to write bitmap info", "", MB_OK|MB_ICONERROR);
    return;
  }
  
  //Copy the array of color indices into the .BMP file. 
  dwTotal = cb = pbih->biSizeImage; 
  hp = lpBits; 
  if(!WriteFile(hf, (LPSTR) hp, (int) cb, (LPDWORD) &dwTmp,NULL)) 
  {
    MessageBox("Unable to write colour indices when saving bitmap", "", MB_OK|MB_ICONERROR);
    return;
  } 

  // Close the .BMP file. 
  if (!CloseHandle(hf)) 
  {
    MessageBox("Unable to close file handle when saving bitmap", "", MB_OK|MB_ICONERROR);
    return;
  } 

  // Free memory. 
  GlobalFree((HGLOBAL)lpBits);
}
/*******************************************/
/*Function to create the Bitmap info struct*/
/*******************************************/
PBITMAPINFO CDispPanel::CreateBitmapInfoStruct(HBITMAP hBmp)
{ 
  BITMAP bmp; 
  PBITMAPINFO pbmi; 
  WORD cClrBits; 

  //Retrieve the bitmap colour format, width, and height. 
  if(!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp)) 
  {
    MessageBox("Unable to retrieve colour format, width and height of bitmap", "", 
							MB_OK|MB_ICONERROR);
    return NULL;
  }

  //Convert the color format to a count of bits. 
  cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel); 
  if(cClrBits == 1) 
    cClrBits = 1; 
  else if(cClrBits <= 4) 
    cClrBits = 4; 
  else if (cClrBits <= 8) 
    cClrBits = 8; 
  else if (cClrBits <= 16) 
    cClrBits = 16; 
  else if (cClrBits <= 24) 
    cClrBits = 24; 
  else cClrBits = 32; 

  //Allocate memory for the BITMAPINFO structure. (This structure 
  //contains a BITMAPINFOHEADER structure and an array of RGBQUAD 
  //data structures.) 

  if(cClrBits != 24) 
    pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER) + 
											sizeof(RGBQUAD) * (1<< cClrBits)); 
  else //There is no RGBQUAD array for the 24-bit-per-pixel format.
    pbmi = (PBITMAPINFO) LocalAlloc(LPTR, sizeof(BITMAPINFOHEADER)); 

  //Initialize the fields in the BITMAPINFO structure.
  pbmi->bmiHeader.biSize = sizeof(BITMAPINFOHEADER); 
  pbmi->bmiHeader.biWidth = bmp.bmWidth; 
  pbmi->bmiHeader.biHeight = bmp.bmHeight; 
  pbmi->bmiHeader.biPlanes = bmp.bmPlanes; 
  pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel; 
  
  if(cClrBits < 24) 
    pbmi->bmiHeader.biClrUsed = (1<<cClrBits); 

  //If the bitmap is not compressed, set the BI_RGB flag. 
  pbmi->bmiHeader.biCompression = BI_RGB; 

  //Compute the number of bytes in the array of color 
  //indices and store the result in biSizeImage. 
  //For Windows NT, the width must be DWORD aligned unless 
  //the bitmap is RLE compressed. This example shows this. 
  //For Windows 95/98/Me, the width must be WORD aligned unless the 
  //bitmap is RLE compressed.
  pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits +31) & ~31) /8
                                  * pbmi->bmiHeader.biHeight; 
  
  //Set biClrImportant to 0, indicating that all of the 
  //device colors are important. 
  pbmi->bmiHeader.biClrImportant = 0; 
  
  return pbmi; 
} 