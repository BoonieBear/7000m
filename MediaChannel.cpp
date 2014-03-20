// MediaChannel.cpp: implementation of the CMediaChannel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ACS.h"
#include "MediaChannel.h"
#include <Shlwapi.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define DEFAULT_BRIGHTNESS	100
#define DEFAULT_CONTRAST	62
#define DEFAULT_HUE			128
#define DEFAULT_SATURATION	64
#define DEFAULT_SHARPNESS	8

BOOL _CreateDirectory(CString szPath,int nStartPos/*=2*/ )
{
	if(szPath[1] != ':')								//such as "c:\\sdf\\asdf\\dfbdf";
		return FALSE;
	
	if(PathIsDirectory(szPath))
		return TRUE;

	int nPos = szPath.Find('\\',nStartPos);

	if(nPos == -1)
		return PathIsDirectory(szPath);

	int nEndPos = szPath.Find('\\',nPos + 1);

	BOOL bReachEnd = FALSE;
	
	if(nEndPos == -1)
	{
		bReachEnd = TRUE;
		nEndPos = szPath.GetLength();
	}

	CString szFolder = szPath.Left(nEndPos);

	CreateDirectory(szFolder,NULL);

	if(!PathFileExists(szFolder))
		return FALSE;
 
	if(bReachEnd)
		return PathIsDirectory(szPath);

	return _CreateDirectory(szPath,nEndPos);
}				  


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMediaChannel::CMediaChannel(LONG nDevIndex)
	: m_nDevIndex(nDevIndex)
	, m_nVideoWidth(720)
	, m_nVideoHeight(576)
	, m_enVideoFmt(FMT_YUY2)
	, m_enVideoStd(STD_PAL)
	, m_enMethod(METHOD_COMPLEX)
	, m_enPlayEffect(EFT_GOOD)
	, m_bTopFieldFirst(TRUE)
	, m_enBusType(BUS_EXCLUSIVE)
	, m_enVideoSrc(SRC_AV1)
	, m_bDevRunning(FALSE)
	, m_nBrightness(DEFAULT_BRIGHTNESS)
	, m_nContrast(DEFAULT_CONTRAST)
	, m_nHue(DEFAULT_HUE)
	, m_nSaturation(DEFAULT_SATURATION)
	, m_nSharpness(DEFAULT_SHARPNESS)
	, m_bRecording(FALSE)
	, m_bRecordMp4(TRUE)
	, m_nRecBitRate(4000)
	, m_bOverTurn(FALSE)
	, m_bButtonSnap(TRUE)
	, m_bSaveAsJpg(TRUE)
{
	m_szSnapPath = _T("C:\\Mygica_Snap\\");
	m_szRecdPath = _T("C:\\Mygica_Recd\\");

	m_hDateFileHandle  = NULL;
	m_hTimeFileHandle  = NULL;
	m_hTextFileHandle  = NULL;
	m_hPictFileHandle  = NULL;
	m_bTimeTransparent = TRUE;
	m_bTextTransparent = TRUE;
	m_bPictTransparent = TRUE;
	m_nTimeOffsetX	   = 10;
	m_nTimeOffsetY	   = 10;
	m_nTextOffsetX	   = 10;
	m_nTextOffsetY	   = 50;
	m_nPictOffsetX	   = 10;
	m_nPictOffsetY	   = 100;


	ZeroMemory(&m_VideoEncore,sizeof(VIDEO_ENCORE_PARAM));
	
	m_VideoEncore.dbFrameRate		= (m_enVideoStd == STD_PAL) ? 25 : 30;
	m_VideoEncore.dwBitRate			= 4000;
	m_VideoEncore.dwKeyFrmInterval  = (DWORD)m_VideoEncore.dbFrameRate * 4;
	m_VideoEncore.dwVideoWidth		= m_nVideoWidth;
	m_VideoEncore.dwVideoHeight		= m_nVideoHeight;
	m_VideoEncore.dwMotionPrecision = 2;
	m_VideoEncore.enEncoreMode		= VIDEO_ENCORE_CBR;

	m_StartRecTime = 0;
	m_nPersistTime = 0;

	//
	TCHAR szBuf[MAX_PATH];
	TCHAR szDir[MAX_PATH];

	GetModuleFileName(NULL,szBuf,MAX_PATH);

	CString szFileName = szBuf;

	szBuf[0] = _T('\0');

	_tsplitpath(szFileName, szBuf, szDir, NULL, NULL);

	::lstrcat(szBuf, szDir);

	m_szCfgFile = szBuf;

	if(m_szCfgFile.Right(1) != _T('\\'))
		m_szCfgFile = m_szCfgFile + _T('\\');
	
	szFileName.Format("IConfig%x.ini",(m_nDevIndex + 1));

	m_szCfgFile = m_szCfgFile + szFileName;
	//

}


CMediaChannel::~CMediaChannel()
{
	SaveConfig();
}

BOOL CMediaChannel::VideoPresent()
{
	BOOL bVideoPresent = FALSE;

	if(HYVideoPresent(m_nDevIndex,bVideoPresent) != ERR_SUCCESS)
		bVideoPresent = TRUE;
	
	return bVideoPresent;
}

BOOL CMediaChannel::OpenChannel()
{
	LoadConfig();

	UINT unRet = HYOpenDev(m_nDevIndex);

	return (unRet == ERR_SUCCESS) ? Initialize() : FALSE;
}

void CMediaChannel::SetDefaultParam()
{
	m_nBrightness	 = DEFAULT_BRIGHTNESS;
	m_nContrast		 = DEFAULT_CONTRAST;
	m_nHue			 = DEFAULT_HUE - 128;
	m_nSaturation	 = DEFAULT_SATURATION;
	m_nSharpness	 = DEFAULT_SHARPNESS;
	
	m_nVideoWidth	 = 720;
	m_nVideoHeight	 = 576;
	m_bOverTurn		 = FALSE;

	m_enVideoStd	 = STD_PAL;	
	m_enVideoFmt	 = FMT_YUY2;
	m_enVideoSrc	 = SRC_AV1;

	m_bButtonSnap	 = TRUE;

	m_bSaveAsJpg	 = TRUE;

	m_szSnapPath	 = _T("C:\\Mygica_Snap\\");

	m_nRecBitRate	 = 4000;
	m_bRecordMp4	 = TRUE;
	m_szRecdPath	 = _T("C:\\Mygica_Recd\\");
}


void CMediaChannel::LoadConfig()
{
	CFile CfgFile;

	if(!CfgFile.Open(m_szCfgFile,CFile::modeReadWrite))
	{
		SetDefaultParam();
		return;
	}
	
	CArchive archive(&CfgFile,CArchive::load);
	
	try
	{
		Serialize(archive);
	}
	catch(...)
	{
		SetDefaultParam();
	}
	
	archive.Close();
	
	CfgFile.Close();
	
	return;
}


BOOL CMediaChannel::Initialize()
{
	BOOL bUsb20 = FALSE;
	
	UINT unRet = HYPortSpeed(m_nDevIndex,bUsb20);

//	unRet = (unRet != ERR_SUCCESS) ? unRet : HYSetOwnerWnd(m_nDevIndex,m_VideoContainer.GetSafeHwnd());
	unRet = (unRet != ERR_SUCCESS) ? unRet : HYSetVideoSize(m_nDevIndex,m_nVideoWidth,m_nVideoHeight);
	unRet = (unRet != ERR_SUCCESS) ? unRet : HYSetVideoFmt(m_nDevIndex,m_enVideoFmt);
	unRet = (unRet != ERR_SUCCESS) ? unRet : HYSetVideoStd(m_nDevIndex,m_enVideoStd);
//  unRet = (unRet != ERR_SUCCESS) ? unRet : HYSetScanMode(m_nDevIndex,SCAN_FRAME);
	unRet = (unRet != ERR_SUCCESS) ? unRet : HYSetProcMethod(m_nDevIndex,m_enMethod);
	unRet = (unRet != ERR_SUCCESS) ? unRet : HYSetPlayEffect(m_nDevIndex,m_enPlayEffect);
	unRet = (unRet != ERR_SUCCESS) ? unRet : HYSetFieldSeq(m_nDevIndex,m_bTopFieldFirst);
	unRet = (unRet != ERR_SUCCESS) ? unRet : HYSetBusType(m_nDevIndex,m_enBusType);
	unRet = (unRet != ERR_SUCCESS) ? unRet : HYSetVideoSrc(m_nDevIndex,m_enVideoSrc,TRUE);
	
	if(unRet != ERR_SUCCESS)
		return FALSE;
	
	SetBrightness(m_nBrightness);
	SetContrast(m_nContrast);
	SetHue(m_nHue);
	SetSaturation(m_nSaturation);
	SetSharpness(m_nSharpness);

	return TRUE;
}

BOOL CMediaChannel::StartDevice(HWND hWndPStream,BOOL bStartPStream)
{
	UINT unRet = ERR_SUCCESS;

	if(bStartPStream)
	{
		unRet = HYSetOwnerWnd(0,hWndPStream);
		unRet = (unRet == ERR_SUCCESS) ? (HYStartDevice(m_nDevIndex)) : unRet;
		
		m_bDevRunning = (unRet == ERR_SUCCESS);

		return m_bDevRunning;
	}
	
	HYStopDevice(m_nDevIndex);
	
	m_bDevRunning = FALSE;

	return TRUE;
}

void CMediaChannel::SetBrightness(LONG nNewValue)
{
	UINT unRet = HYSetVideoProp(m_nDevIndex,VIDEO_BRIGHTNESS,nNewValue);

	m_nBrightness = (unRet == ERR_SUCCESS) ? nNewValue : m_nBrightness;
}

void CMediaChannel::SetContrast(LONG nNewValue)
{
	UINT unRet = HYSetVideoProp(m_nDevIndex,VIDEO_CONTRAST,nNewValue);

	m_nContrast = (unRet == ERR_SUCCESS) ? nNewValue : m_nContrast;
}

void CMediaChannel::SetHue(LONG nNewValue)
{
	UINT unRet = HYSetVideoProp(m_nDevIndex,VIDEO_HUE,nNewValue);

	m_nHue = (unRet == ERR_SUCCESS) ? nNewValue : m_nHue;
}

void CMediaChannel::SetSaturation(LONG nNewValue)
{
	UINT unRet = HYSetVideoProp(m_nDevIndex,VIDEO_SATURATION,nNewValue);

	m_nSaturation = (unRet == ERR_SUCCESS) ? nNewValue : m_nSaturation;
}

void CMediaChannel::SetSharpness(LONG nNewValue)
{
	UINT unRet = HYSetVideoProp(m_nDevIndex,VIDEO_SHARPNESS,nNewValue);

	m_nSharpness = (unRet == ERR_SUCCESS) ? nNewValue : m_nSharpness;
}

void CMediaChannel::SetDefaultProc()
{
	m_nBrightness	 = DEFAULT_BRIGHTNESS;
	m_nContrast		 = DEFAULT_CONTRAST;
	m_nHue			 = DEFAULT_HUE - 128;
	m_nSaturation	 = DEFAULT_SATURATION;
	m_nSharpness	 = DEFAULT_SHARPNESS;
	
	SetBrightness(m_nBrightness);
	SetContrast(m_nContrast);
	SetHue(m_nHue);
	SetSaturation(m_nSaturation);
	SetSharpness(m_nSharpness);
}

void CMediaChannel::StopDevice()
{
	HYStopDevice(m_nDevIndex);
	
	m_bDevRunning = FALSE;
}

BOOL CMediaChannel::SetVideoStandard(VIDEOSTD enVideoStd)
{
	HYStopDevice(m_nDevIndex);

	UINT unRet = HYSetVideoStd(m_nDevIndex,enVideoStd);
	
	if(m_bDevRunning)
		HYStartDevice(m_nDevIndex);
	
	m_enVideoStd = enVideoStd;

	return (unRet == ERR_SUCCESS);
}

BOOL CMediaChannel::SetVideoSrc(VIDEOSRC enVideoSrc)
{
	HYStopDevice(m_nDevIndex);

	UINT unRet = HYSetVideoSrc(m_nDevIndex,enVideoSrc,FALSE);
	
	if(m_bDevRunning)
		HYStartDevice(m_nDevIndex);

	m_enVideoSrc = enVideoSrc;

	return (unRet == ERR_SUCCESS);
}

BOOL CMediaChannel::SetOutFormat(VIDEOFMT enVideoFmt)
{
	HYStopDevice(m_nDevIndex);

	UINT unRet = HYSetVideoFmt(m_nDevIndex,enVideoFmt);
	
	if(m_bDevRunning)
		HYStartDevice(m_nDevIndex);
	
	m_enVideoFmt = enVideoFmt;

	return (unRet == ERR_SUCCESS);
}

BOOL CMediaChannel::SetVideoSize(LONG nWidth,LONG nHeight)
{
	HYStopDevice(m_nDevIndex);
	
	UINT unRet = HYSetVideoSize(m_nDevIndex,nWidth,nHeight);
	
	if(m_bDevRunning)
		HYStartDevice(m_nDevIndex);

	m_nVideoWidth  = nWidth;
	m_nVideoHeight = nHeight;
	
	return (unRet == ERR_SUCCESS);
}

void CMediaChannel::SetFieldSeq(BOOL bTopFirst)
{
	HYSetFieldSeq(m_nDevIndex,bTopFirst);
	
	m_bTopFieldFirst = bTopFirst;
}

void CMediaChannel::SetProcMethod(PROCMETHOD enMethod)
{
	HYSetProcMethod(m_nDevIndex,enMethod);

	m_enMethod = enMethod;
}

void CMediaChannel::SetSnapMirror(BOOL bHorizon,BOOL bVertical)
{
	HYMirrorHorizon (m_nDevIndex,bHorizon);
	HYMirrorVertical(m_nDevIndex,!bVertical);
}

LONG CMediaChannel::GetSnapBufSize()
{
	LONG nBufSize = 0;
		
	VIDEOFMT enFmt = FMT_YUY2;

	UINT unRet = HYGetImgBufsize(m_nDevIndex,&nBufSize,enFmt);
	
	if(unRet == ERR_SUCCESS)
		return nBufSize;

	return -1;
}

BOOL CMediaChannel::StartSnap(LONG nCounts,LONG nInterval)
{
	return (HYStartSnap(m_nDevIndex,nCounts,nInterval) == ERR_SUCCESS);
}

BOOL CMediaChannel::GetMemSnap(BYTE *pBuffer,LONG nBufSize,VIDEOFMT enFmt,LONG nDelays)
{
	return (HYGetMemSnap(m_nDevIndex,pBuffer,nBufSize,enFmt,nDelays) == ERR_SUCCESS);
}

void CMediaChannel::PaintMemImg(BYTE *pBuffer,LONG nBufSize,HWND hPaintWnd)
{
	HYPaintMemImg(pBuffer,nBufSize,hPaintWnd);
}


BOOL CMediaChannel::SnapVideoImage(BYTE *pBuffer,LONG nBufSize)
{
	static LONG g_nIndex = 0;

	CTime TimeCur = CTime::GetCurrentTime();
	
	szSnapFile;

	szSnapFile.Format("Image%04d%02d%02d-%02d%02d%02d.",TimeCur.GetYear(),
															  TimeCur.GetMonth(),
															  TimeCur.GetDay(),
															  TimeCur.GetHour(),
															  TimeCur.GetMinute(),
															  TimeCur.GetSecond());

	g_nIndex++;

	g_nIndex %= 30;
	
	szSnapFile = szSnapFile + ((m_bSaveAsJpg) ? "JPG" : "BMP");
	
	szSnapFile = m_szSnapPath + szSnapFile;
	
	if(!_CreateDirectory(m_szSnapPath,2))
		return FALSE;

	UINT unRet = ERR_SUCCESS;

	if(m_bSaveAsJpg)
		unRet = HYSaveImgAsJpg(pBuffer,nBufSize,szSnapFile,100);
	else
		unRet = HYSaveImgAsBmp(pBuffer,nBufSize,szSnapFile);

	return (unRet == ERR_SUCCESS);
}


void CMediaChannel::SetTimeTransparent(BOOL bTransparent)
{
	m_bTimeTransparent = bTransparent;

	if(m_hDateFileHandle != NULL && m_hTimeFileHandle != NULL)
	{
		HYSetComplexEffect(m_nDevIndex,m_hDateFileHandle,bTransparent);
		HYSetComplexEffect(m_nDevIndex,m_hTimeFileHandle,bTransparent);
	}
	
	return;
}

void CMediaChannel::SetTextTransparent(BOOL bTransparent)
{
	m_bTextTransparent = bTransparent;

	if(m_hTextFileHandle != NULL)
	{
		HYSetComplexEffect(m_nDevIndex,m_hTextFileHandle,bTransparent);
	}
}

void CMediaChannel::SetPictTransparent(BOOL bTransparent)
{
	m_bPictTransparent = bTransparent;

	if(m_hPictFileHandle != NULL)
	{
		HYSetComplexEffect(m_nDevIndex,m_hPictFileHandle,bTransparent);
	}
}


BOOL CMediaChannel::TimeComplex(BOOL bOpen,LONG nOffx,LONG nOffy,BOOL bTransparent)
{
	HYCloseComplexFile(m_nDevIndex,m_hDateFileHandle);
	HYCloseComplexFile(m_nDevIndex,m_hTimeFileHandle);

	m_hDateFileHandle = NULL;
	m_hTimeFileHandle = NULL;

	if(bOpen == FALSE)
		return TRUE;

	CString szTimeFile = "C:\\TimeFormat.cpx";
	CString szDateFile = "C:\\DateFormat.cpx";
		
	m_hDateFileHandle = HYOpenComplexFile(m_nDevIndex,szDateFile);
	m_hTimeFileHandle = HYOpenComplexFile(m_nDevIndex,szTimeFile);
	
	if(m_hDateFileHandle == NULL || m_hTimeFileHandle == NULL)
		return FALSE;
	
	SetTimeTransparent(bTransparent);

	m_nTimeOffsetX = nOffx;
	m_nTimeOffsetY = nOffy;

	HYSetComplexPos(m_nDevIndex,m_hDateFileHandle,nOffx,nOffy);
	HYSetComplexPos(m_nDevIndex,m_hTimeFileHandle,nOffx + 130,nOffy);
	
	UINT unRet = ERR_SUCCESS;

	unRet = (unRet == ERR_SUCCESS) ? HYComplexEnable(m_nDevIndex,m_hDateFileHandle,TRUE) : unRet;
	unRet = (unRet == ERR_SUCCESS) ? HYComplexEnable(m_nDevIndex,m_hTimeFileHandle,TRUE) : unRet;
	
	if(unRet != ERR_SUCCESS)
	{
		HYCloseComplexFile(m_nDevIndex,m_hDateFileHandle);
		HYCloseComplexFile(m_nDevIndex,m_hTimeFileHandle);

		m_hDateFileHandle = NULL;
		m_hTimeFileHandle = NULL;

		return FALSE;
	}
	
	return TRUE;
}


BOOL CMediaChannel::TextComplex(BOOL bOpen,LONG nOffx,LONG nOffy,BOOL bTransparent)
{
	HYCloseComplexFile(m_nDevIndex,m_hTextFileHandle);

	m_hTextFileHandle = NULL;

	if(bOpen == FALSE)
		return TRUE;

	CString szTextFile = "C:\\TextFormat.cpx";
		
	m_hTextFileHandle = HYOpenComplexFile(m_nDevIndex,szTextFile);
	
	if(m_hTextFileHandle == NULL)
		return FALSE;
	
	SetTextTransparent(bTransparent);

	m_nTextOffsetX = nOffx;
	m_nTextOffsetY = nOffy;

	HYSetComplexPos(m_nDevIndex,m_hTextFileHandle,nOffx,nOffy);
	
	UINT unRet = HYComplexEnable(m_nDevIndex,m_hTextFileHandle,TRUE);
	
	if(unRet != ERR_SUCCESS)
	{
		HYCloseComplexFile(m_nDevIndex,m_hTextFileHandle);

		m_hTextFileHandle = NULL;

		return FALSE;
	}
	
	return TRUE;
}


BOOL CMediaChannel::PictComplex(BOOL bOpen,LONG nOffx,LONG nOffy,BOOL bTransparent)
{
	HYCloseComplexFile(m_nDevIndex,m_hPictFileHandle);

	m_hPictFileHandle = NULL;

	if(bOpen == FALSE)
		return TRUE;

	CString szPictFile = "C:\\PictFormat.cpx";
		
	m_hPictFileHandle = HYOpenComplexFile(m_nDevIndex,szPictFile);
	
	if(m_hPictFileHandle == NULL)
		return FALSE;
	
	SetPictTransparent(bTransparent);

	m_nPictOffsetX = nOffx;
	m_nPictOffsetY = nOffy;

	HYSetComplexPos(m_nDevIndex,m_hPictFileHandle,nOffx,nOffy);
	
	UINT unRet = HYComplexEnable(m_nDevIndex,m_hPictFileHandle,TRUE);
	
	if(unRet != ERR_SUCCESS)
	{
		HYCloseComplexFile(m_nDevIndex,m_hPictFileHandle);

		m_hPictFileHandle = NULL;

		return FALSE;
	}
	
	return TRUE;
}

BOOL CMediaChannel::CreateEncorder(BOOL bCreateEncorder,LONG nBitRate)
{
	UINT unRet = ERR_SUCCESS;

	if(bCreateEncorder)
	{
		m_VideoEncore.dbFrameRate		= (m_enVideoStd == STD_PAL) ? 25 : 30;
		m_VideoEncore.dwBitRate			= nBitRate;
		m_VideoEncore.dwKeyFrmInterval  = (DWORD)m_VideoEncore.dbFrameRate * 4;
		m_VideoEncore.dwVideoWidth		= m_nVideoWidth;
		m_VideoEncore.dwVideoHeight		= m_nVideoHeight;
		m_VideoEncore.dwMotionPrecision = 2;
		m_VideoEncore.enEncoreMode		= VIDEO_ENCORE_CBR;

		UINT unFlag = FLAG_REQUEST_VIDEO;
		
		UINT unRet  = HYCreateEncoder(m_nDevIndex,unFlag,&m_VideoEncore);

		return (unRet == ERR_SUCCESS);
	}
	
	unRet = HYDestoryEncoder(m_nDevIndex);

	return (unRet == ERR_SUCCESS);
}

BOOL CMediaChannel::StartRecord()
{
	if(!CreateEncorder(TRUE,m_nRecBitRate))
		return FALSE;

	CString szFile = GetRecordFileName();
	
	if(szFile.IsEmpty())
		return FALSE;

	RECTYPE enType = m_bRecordMp4 ? RECTYPE_MP4 : RECTYPE_AVI;

	if(HYCreateRecordFile(m_nDevIndex,szFile,enType) != ERR_SUCCESS)
		return FALSE;

	HYSetPlayEffect(m_nDevIndex,EFT_NORMAL);

	HYEnableEncode(m_nDevIndex,TRUE);
	
	m_bRecording  = TRUE;
	
	m_SwitchTime  = CTime::GetCurrentTime() + CTimeSpan( 0, 0, 40, 0 );

	return TRUE;
}

void CMediaChannel::StopRecord()
{
	HYEnableEncode(m_nDevIndex,FALSE);
	
	HYCloseRecordFile(m_nDevIndex);

	HYDestoryEncoder(m_nDevIndex);

	HYSetPlayEffect(m_nDevIndex,EFT_GOOD);

	m_bRecording = FALSE;
	
	return;
}

void CMediaChannel::SetVideoOverturn(BOOL bOverturn)
{
	m_bOverTurn = bOverturn;
	
	HYSetVideoOverturn(m_nDevIndex,bOverturn);
}

CString CMediaChannel::GetRecordFileName()
{
	CString szFile = _T("");

	if(!PathIsDirectory(m_szRecdPath))
	{
		if(!CreateDirectory(m_szRecdPath,NULL))
			return szFile;
	}
	
	CTime TimeNow = CTime::GetCurrentTime();

	szFile.Format("Usb%04d%02d%02d_%02d%02d%02d.avi",
				   TimeNow.GetYear(),
				   TimeNow.GetMonth(),
				   TimeNow.GetDay(),
				   TimeNow.GetHour(),
				   TimeNow.GetMinute(),
				   TimeNow.GetSecond());
	
	szFile = m_szRecdPath + szFile;

	return szFile;
}

void CMediaChannel::Serialize(CArchive& archive)
{
	CObject::Serialize(archive);

	if(archive.IsStoring())									//store param
	{
		archive << m_nBrightness; 
		archive << m_nContrast;
		archive << m_nHue;
		archive << m_nSaturation;
		archive << m_nSharpness;
		archive << m_nVideoWidth;
		archive << m_nVideoHeight;
		archive << m_bOverTurn;
		
		archive << (LONG)m_enVideoStd;
		archive << (LONG)m_enVideoFmt;
		archive << (LONG)m_enVideoSrc;

		archive << m_bButtonSnap;
		archive << m_bSaveAsJpg;

		archive.WriteString(m_szSnapPath);
		archive.WriteString("\n");

		archive << m_nRecBitRate;
		archive << m_bRecordMp4;

		archive.WriteString(m_szRecdPath);
		archive.WriteString("\n");
	}
	else
	{
		archive >> m_nBrightness; 
		archive >> m_nContrast;
		archive >> m_nHue;
		archive >> m_nSaturation;
		archive >> m_nSharpness;
		archive >> m_nVideoWidth;
		archive >> m_nVideoHeight;
		archive >> m_bOverTurn;

//
		LONG nEnumValue = 0;
		
		archive >> nEnumValue;
		m_enVideoStd = (VIDEOSTD)nEnumValue;

		archive >> nEnumValue;
		m_enVideoFmt = (VIDEOFMT)nEnumValue;

		archive >> nEnumValue;
		m_enVideoSrc = (VIDEOSRC)nEnumValue;
//

		archive >> m_bButtonSnap;
		archive >> m_bSaveAsJpg;

		archive.ReadString(m_szSnapPath);

		archive >> m_nRecBitRate;
		archive >> m_bRecordMp4;

		archive.ReadString(m_szRecdPath);
	}
}

void CMediaChannel::SaveConfig()
{
	CFile CfgFile;
	
	if(CfgFile.Open(m_szCfgFile,CFile::modeReadWrite | CFile::modeCreate))
	{
		CArchive archive(&CfgFile,CArchive::store);
		
		try
		{
			Serialize(archive);
		}
		catch(...)
		{
		}

		archive.Close();
		CfgFile.Close();
	}
}

