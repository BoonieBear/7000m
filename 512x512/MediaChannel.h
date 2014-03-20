// MediaChannel.h: interface for the CMediaChannel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEDIACHANNEL_H__A077D8B7_7587_4E9B_BF10_79C66596E17A__INCLUDED_)
#define AFX_MEDIACHANNEL_H__A077D8B7_7587_4E9B_BF10_79C66596E17A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "HYUtil.h"

class CMediaChannel : public CObject 
{
public:
	CMediaChannel(LONG nDevIndex= 0);
	virtual ~CMediaChannel();

public:
	CString szSnapFile;
	BOOL	VideoPresent();
	BOOL	StartDevice(HWND hWndPStream,BOOL bStartPStream);
	void	StopDevice();

	BOOL	OpenChannel();
	BOOL	Initialize();
	void	SetBrightness(LONG nNewValue);
	void	SetContrast(LONG nNewValue);
	void	SetHue(LONG nNewValue);
	void	SetSaturation(LONG nNewValue);
	void	SetSharpness(LONG nNewValue);
	void	SetDefaultProc();
	void	SetDefaultParam();
	BOOL	SetVideoStandard(VIDEOSTD enVideoStd);
	BOOL	SetVideoSrc(VIDEOSRC enVideoSrc);
	BOOL	SetOutFormat(VIDEOFMT enVideoFmt);
	BOOL	SetVideoSize(LONG nWidth,LONG nHeight);
	void	SetFieldSeq(BOOL bTopFirst);
	void	SetProcMethod(PROCMETHOD enMethod);
	void	SetSnapMirror(BOOL bHorizon,BOOL bVertical);
	LONG	GetSnapBufSize();
	BOOL	StartSnap(LONG nCounts,LONG nInterval);
	BOOL	GetMemSnap(BYTE *pBuffer,LONG nBufSize,VIDEOFMT enFmt,LONG nDelays);
	void	PaintMemImg(BYTE *pBuffer,LONG nBufSize,HWND hPaintWnd);
	BOOL	SnapVideoImage(BYTE *pBuffer,LONG nBufSize);
	void	SetVideoOverturn(BOOL bOverturn);

	BOOL	TimeComplex(BOOL bOpen,LONG nOffx = 10,LONG nOffy = 10,BOOL bTransparent = TRUE);
	BOOL	TextComplex(BOOL bOpen,LONG nOffx = 10,LONG nOffy = 50,BOOL bTransparent = TRUE);
	BOOL	PictComplex(BOOL bOpen,LONG nOffx = 10,LONG nOffy = 100,BOOL bTransparent = TRUE);
	void	SetTimeTransparent(BOOL bTransparent = TRUE);
	void    SetTextTransparent(BOOL bTransparent = TRUE);
	void    SetPictTransparent(BOOL bTransparent = TRUE);
	BOOL	CreateEncorder(BOOL bCreateEncorder,LONG nBitRate);
	BOOL	StartRecord();
	void	StopRecord();
	BOOL	IsRecording()										{return m_bRecording;}
	CString GetRecordFileName();

	virtual void Serialize(CArchive& archive);
	void	SaveConfig();


public:
	LONG	m_nDevIndex;
	BOOL	m_bDevRunning;

protected:
	void	LoadConfig();

public:
	LONG		m_nBrightness;
	LONG		m_nContrast;
	LONG		m_nHue;
	LONG		m_nSaturation;
	LONG		m_nSharpness;

	BOOL		m_bOverTurn;
	LONG		m_nVideoWidth;
	LONG		m_nVideoHeight;
	VIDEOFMT	m_enVideoFmt;
	VIDEOSTD	m_enVideoStd;
	PROCMETHOD  m_enMethod;
	
	VIDEOEFFECT m_enPlayEffect;
	BOOL		m_bTopFieldFirst;
	BUSTYPE		m_enBusType;
	VIDEOSRC	m_enVideoSrc;

	//for osd
	HANDLE		m_hDateFileHandle;
	HANDLE		m_hTimeFileHandle;
	HANDLE		m_hTextFileHandle;
	HANDLE		m_hPictFileHandle;

	BOOL		m_bTimeTransparent;
	BOOL		m_bTextTransparent;
	BOOL		m_bPictTransparent;
	LONG		m_nTimeOffsetX;
	LONG		m_nTimeOffsetY;
	LONG		m_nTextOffsetX;
	LONG		m_nTextOffsetY;
	LONG		m_nPictOffsetX;
	LONG		m_nPictOffsetY;

	BOOL		m_bButtonSnap;

	VIDEO_ENCORE_PARAM m_VideoEncore;
	CTime		m_StartRecTime;
	CTime		m_SwitchTime;
	LONG		m_nPersistTime;

	//for snap param
	BOOL		m_bSaveAsJpg;
	CString		m_szSnapPath;
	
	//
	BOOL		m_bRecording;
	BOOL		m_bRecordMp4;
	LONG		m_nRecBitRate;
	CString		m_szRecdPath;

	CString		m_szCfgFile;
};

#endif // !defined(AFX_MEDIACHANNEL_H__A077D8B7_7587_4E9B_BF10_79C66596E17A__INCLUDED_)
