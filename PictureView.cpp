// PictureView.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "PictureView.h"
#include "ACSDlg.h"
#include "ximage.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
struct DocType
{
public:
	int nID;
	BOOL bRead;
	BOOL bWrite;
	const TCHAR* description;
	const TCHAR* ext;
};
DocType doctypes[CMAX_IMAGE_FORMATS] =
{
	{ -1, TRUE, TRUE, _T("Supported files"), _T("*.bmp;*.gif;*.jpg;*.jpeg;*.png;*.ico;*.tif;*.tiff;*.tga;*.pcx;*.wbmp;*.wmf;*.emf;*.j2k;*.jp2;*.jbg;*.j2c;*.jpc;*.pgx;*.pnm;*.pgm;*.ppm;*.ras;*.mng;*.jng;*.ska;*.nef;*.crw;*.cr2;*.mrw;*.raf;*.erf;*.3fr;*.dcr;*.raw;*.dng;*.pef;*.x3f;*.arw;*.sr2;*.mef;*.orf") },

	{ CXIMAGE_FORMAT_BMP, TRUE, TRUE, _T("BMP files"), _T("*.bmp") },

	{ CXIMAGE_FORMAT_JPG, TRUE, TRUE, _T("JPG files"), _T("*.jpg;*.jpeg") },

};
/////////////////////////////////////////////////////////////////////////////
// CPictureView dialog


CPictureView::CPictureView(CWnd* pParent /*=NULL*/)
	: CDialog(CPictureView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPictureView)
	m_bIsDraw = FALSE;
	BMPFileName = "background.bmp";
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CPictureView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPictureView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPictureView, CDialog)
	//{{AFX_MSG_MAP(CPictureView)
	ON_BN_CLICKED(IDC_SELECTPIC, OnSelectpic)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_SELECT, OnButtonSelect)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictureView message handlers

void CPictureView::OnSelectpic() 
{
	// TODO: Add your control notification handler code here
	CFileDialog dlg(TRUE);
	
	int nDocType = -1;
	int nIndex = GetIndexFromType(nDocType, TRUE);//open file use true,save use false
	if (nIndex == -1) nIndex = 0;
	dlg.m_ofn.nFilterIndex = nIndex +1;
	// strDefExt is necessary to hold onto the memory from GetExtFromType
	CString strDefExt = GetExtFromType(nDocType).Mid(2,3);
	dlg.m_ofn.lpstrDefExt = strDefExt;
	dlg.m_ofn.Flags |= OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;
	CString title=_T("选择发送图片");	
	CString strFilter = GetFileTypes(TRUE);
	dlg.m_ofn.lpstrFilter = strFilter;
	dlg.m_ofn.lpstrTitle = title;
	char dirpath[_MAX_PATH+1];
	CString dirfullpath;
	GetCurrentDirectory(_MAX_PATH+1,dirpath);
	dirfullpath.Format("%s",dirpath);//获取当前程序目录
	dirfullpath+= "\\BMPFile";
	dlg.m_ofn.lpstrInitialDir = dirfullpath;
	dlg.m_ofn.lpstrFile = ImageSelectDlg.SelectFileName.GetBuffer(_MAX_PATH);

	BOOL bRet = (dlg.DoModal() == IDOK) ? TRUE : FALSE;
	ImageSelectDlg.SelectFileName.ReleaseBuffer();
	if (bRet)
	{
		CString ext(FindExtension(ImageSelectDlg.SelectFileName));
		ext.MakeLower();
		if (ext == _T("")) 
			return;
		ImageSelectDlg.pType = FindType(ext);

		if (ImageSelectDlg.DoModal()==IDOK)
		{
			BMPFileName = ImageSelectDlg.SendFileName;
			pDib.Load(BMPFileName);	
			m_bIsDraw=TRUE;
			CRect rect;
			GetClientRect(&rect);
			InvalidateRect(&rect);
			OnSendpic();//选择即添加图片进链表
		}
	}
	
	
}
CString CPictureView::FindExtension(const CString& name)//find ext from filename
{
	int len = name.GetLength();
	int i;
	for (i = len-1; i >= 0; i--){
		if (name[i] == '.'){
			return name.Mid(i+1);
		}
	}
	return CString(_T(""));
}
int CPictureView::FindType(const CString& ext)//find cximage id from ext
{
	return CxImage::GetTypeIdFromName(ext);
}
//////////////////////////////////////////////////////////////////////////////
int CPictureView::GetIndexFromType(int nDocType, BOOL bOpenFileDialog)
{
	int nCnt = 0;
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (bOpenFileDialog ? doctypes[i].bRead : doctypes[i].bWrite){
			if (doctypes[i].nID == nDocType) return nCnt;
			nCnt++;
		}
	}
	return -1;
}

//////////////////////////////////////////////////////////////////////////////
CString CPictureView::GetExtFromType(int nDocType)//根据文件类型找出后缀名
{
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (doctypes[i].nID == nDocType)
			return doctypes[i].ext;
	}
	return CString(_T(""));
}
//////////////////////////////////////////////////////////////////////////////
CString CPictureView::GetDescFromType(int nDocType)
{
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (doctypes[i].nID == nDocType)
			return doctypes[i].description;
	}
	return CString(_T(""));
}

//////////////////////////////////////////////////////////////////////////////
CString CPictureView::GetFileTypes(BOOL bOpenFileDialog)//设置对话框打开文件的类型
{
	CString str;
	for (int i=0;i<CMAX_IMAGE_FORMATS;i++){
		if (bOpenFileDialog && doctypes[i].bRead){
			str += doctypes[i].description;
			str += (TCHAR)NULL;
			str += doctypes[i].ext;
			str += (TCHAR)NULL;
		} else if (!bOpenFileDialog && doctypes[i].bWrite) {
			str += doctypes[i].description;
			str += (TCHAR)NULL;
			str += doctypes[i].ext;
			str += (TCHAR)NULL;
		}
	}
	return str;
}
void CPictureView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CDC *pdc=GetDC();
//	if(m_bIsDraw == TRUE)		//只有点击选择按钮，才进行重绘
	{
		m_bIsDraw = pDib.DrawBig( pdc, 110, 40, 1);
// 		CWnd* pWnd =GetDlgItem(IDC_SENDPIC);
// 		pWnd->EnableWindow(TRUE);
	}	
	//CDialog::OnPaint();
}

void CPictureView::OnSendpic() 
{
	// TODO: Add your control notification handler code here
	//图像保存到相应文件夹中
	char filename[_MAX_PATH];
	CString csfilename;
	csfilename.Format("%sImage",XMTPSKFile.m_Path);
	CreateFileName(csfilename.GetBuffer(0),".bmp",filename);
	pDib.Save(filename);
	BMPBuffer = pDib.GetBitsAddress();
	DIGITALBUFF *databuff;
	databuff = (DIGITALBUFF *)malloc(sizeof(DIGITALBUFF));
	databuff->len = COLORIMAGESIZE;
	databuff->buf = (unsigned char *)malloc(databuff->len);
	imageCode.ColorCode(BMPBuffer,(BYTE *)databuff->buf,256);
	m_WzdimageList.RemoveAll();
	m_WzdimageList.AddTail(databuff);
	

}

BOOL CPictureView::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
// 	CWnd* pWnd =GetDlgItem(IDC_SENDPIC);
// 	pWnd->EnableWindow(FALSE);
	pDib.Load(BMPFileName);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CPictureView::OnButtonSelect() //获取当前视频图像
{
	// TODO: Add your control notification handler code here
	
	if (VideoSelectDlg.DoModal()==IDOK)
	{
		ImageSelectDlg.SelectFileName = VideoSelectDlg.szSaveFileName;
		CString ext(FindExtension(ImageSelectDlg.SelectFileName));
		ext.MakeLower();

		if (ext == _T("")) 
			return;
		ImageSelectDlg.pType = FindType(ext);
	
		if (ImageSelectDlg.DoModal()==IDOK)
		{
			BMPFileName = ImageSelectDlg.SendFileName;
			pDib.Load(BMPFileName);	
			m_bIsDraw=TRUE;
			CRect rect;
			GetClientRect(&rect);
			InvalidateRect(&rect);
			OnSendpic();//选择即添加图片进链表
		}
	}
		
}
