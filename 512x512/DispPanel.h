#if !defined(AFX_DISPPANEL_H__16D4FBC3_C693_462E_8872_6DF2FD08FB85__INCLUDED_)
#define AFX_DISPPANEL_H__16D4FBC3_C693_462E_8872_6DF2FD08FB85__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DispPanel.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CDispPanel window
//#define MY_BACKCOLOR RGB( 205,205,175 )

class CDispPanel : public CButton
{
// Construction
public:
	CDispPanel();
private:
	static int Comparedouble(const void *pval1, const void *pval2);
	int leftMarginX,topMarginY,rightMarginX,bottomMarginY;
	double *PSDreal,*PSDimag;
	bool bShowPSD;
// Attributes
public:
	bool Zoomed,showFrame;
	double MedianA(double *pIn,int length);
	double MaxA(double *pIn,int length);
	double MinA(double *pIn,int length);
	void ClearPSDMalloc();
	double scaleY;
	
	CRect CurFrameRect,lastFrameRect,m_GraphRect;
	int TotalLength,CurLength,DividedUnits;//坐标值划分区域数
	void InitScaleY();
	double *m_pTotalYdata,*m_pCurYdata,*m_pPSDYdata;
	double m_globalMaxY,m_globalMinY,m_globalMaxX,m_globalMinX,m_globalMaxf,m_globalMinf,m_globalMaxPSD,m_defaultMaxY,m_defaultMinY;
	double m_currentMaxX,m_currentMinX,m_currentMaxY,m_currentMinY,m_currentMaxf,m_currentMinf,m_defaultMaxf;

	void Plotf(CDC *pDC,CRect* pRect);
	void DrawAxis(CDC* pDC,CRect* pRect);
	
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDispPanel)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	void CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);
	PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp);
	void SaveAs(LPCTSTR szFilename);
	void ClearUnits(CDC* pDC);
	void DrawUnits(CDC *pDC, CRect *pRect);
	void GetPSD();
	void ClearData();
	virtual ~CDispPanel();

	// Generated message map functions
protected:
	//{{AFX_MSG(CDispPanel)
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DISPPANEL_H__16D4FBC3_C693_462E_8872_6DF2FD08FB85__INCLUDED_)
