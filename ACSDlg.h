// ACSDlg.h : header file
//
//{{AFX_INCLUDES()
#include "ntgraph.h"
//}}AFX_INCLUDES

#if !defined(AFX_ACSDLG_H__03D78378_B92D_4E35_908F_6ABA992D7E9E__INCLUDED_)
#define AFX_ACSDLG_H__03D78378_B92D_4E35_908F_6ABA992D7E9E__INCLUDED_
#include "stdafx.h"
#include "windows.h"
#include "AFXMT.h"
#include "lpt_lib.h"//并口操作函数头文件
#include "NetSocket.h"
#include "data_define.h"
#include "FileDataN.h"
#include "MyProgress.h"
#include "resource.h"
#include "RecordSound.h"
#include "PlaySound.h"
#include "PlayMMSound.h"
#include "CycleMem.h"
#include "Morse.h"
#include "StaticTime.h"
#include "WordDialog.h"
#include "WaveView.h"
#include "PostView.h"
#include "AdcpPage.h"
#include "ComParam.h"
#include "DataView.h"
#include "PictureView.h"
#include "OptionSet.h"
#include "DataEncode.h"
#include "ImageShow.h"
#include "LogView.h"
#include "TabLog.h"
#include "ADSamplePage.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CACSDlg dialog
extern CCriticalSection SendNetpacketSync;//发送网络数据临界对象
extern CCriticalSection CCycleMemSync;//循环缓冲临界对象
extern CCriticalSection WaveMemSync;//循环缓冲临界对象

extern UINT SendNetpacketProc(LPVOID pParam);
extern HANDLE IsNetpacketEvent;//是否有网络数据发送
extern HANDLE RecvNetpacketEvent;//是否收到网络数据
extern HANDLE SendNetpacketEvent;//发送网络数据同步事件
extern HICON m_hIcon_Wait;//图标显示
extern HICON m_hIcon_Work;//图标显示

extern HICON m_recvWork;
extern HICON m_ledon;

extern void  CreateFileName(char* filename,char* filetype,char * fullfilename);//自动生成文件名
extern CFileData XMTVoiceFile;//保存发送的声音文件
extern CFileData NorVoiceFile;//保存归一化后声音文件
extern CFileData XMTFSKFile;//保存发送的FSK文件
extern CFileData XMTPSKFile;//保存发送的PSK文件
extern CFileData XMTFSFile;//保存发送的FS文件
extern CFileData RecordFile;//保存程序运行记录
extern CFileData RECVCommDataFile;//保存通信参数记录文件
extern CFileData TextFile;//保存文字通信记录
extern CFileData USBLFile;//保存文字通信记录
extern CFileData RECVVoiceFile;//保存所有的声音数据文件
extern CFileData RECVFSKFile;//保存接收到的fsk数据文件
extern CFileData RECVPSKFile;//保存接收到的psk数据文件
extern CFileData RECVEOUTFile;//保存接收到的EOUT数据文件
extern CFileData RECVFSFile;//保存接收到的fs数据文件
extern CFileData ADFile;//保存接收到的AD数据
extern CFileData Trans2SailFile;//保存转发给航行控制系统的信息文件
extern CFileData MarineDataFile;//接收航行控制系统的信息文件
extern int channum;//有效通道数
extern BOOL m_bADWaveEnable; //是否有否接收完毕
extern CCycleMem<char,MAXBUFFSIZE,1> * OutVoiceCycleMem;
extern CCycleMem<char,MAXBUFFSIZE,1> * InVoiceCycleMem;
extern CCycleMem<char,163841,1> * WaveCycleMem;
extern short* m_pRawData;//AD采样数组
extern double* dWaveData;//波形显示数组
extern DWORD m_nRawDataLen;
extern void GenSinWave (short* pBuffer, int iFreq, int nlength);
extern char* lastpacket;

class CACSDlg : public CDialog
{
// Construction
public:
	void SaveCommData(char* CommBuffer);
	void PackagePictureIn8psk(unsigned char *buf, int len);
	void OnButtonSet();
	void OnButtonSave();
	void OnButtonXmtset();
	void SaveEoutData(BYTE *databuf, int len);
	BOOL LinkStatus;
	BOOL LBLStatus;
	
	void SendMorseCommand(int CommId);
	void StartTCM2();
	void TimeOutAlarm(WPARAM wParam,LPARAM lParam);
	void DisplaySoundWave(WPARAM wParam, LPARAM lParam);
	int calcAmp(short *pBuffer, int nlength);
	void SetTime();
	void OnConnect();
	void StartAdio();
	void StartDsp();
	void SendSoundEnd();
	void OnDigitalXmtSet();
	void TestDataPackageAndParse();
	void UpdateSensorData(SYSTEMSENSORDATA* SystemSensorData);
	void ParseUWAData(int *codedframebit);
	void ParseShipData(int *codedframebit);
	void ExplainUDPPackage(char* bufr,int receivenum);
	void InputFhLog(CString strlog);
	void ExplainFHData(BYTE* databuf, int len);
	void ExplainPSKData(BYTE* databuf, int len);
	void ExplainFSKData(BYTE* databuf, int len);
	void PackagePicture(unsigned char *buf, int len);
	void PackageUWAData(unsigned char *buf, int len);
	void PackageShipData(unsigned char *buf, int len);
	void DisplayData(int nSource);//0:位置信息，1;潜器信息，2：bp信息

	void OnSend(char* sendbuf,int sendlenth);
	LRESULT OnNetSailSocket(WPARAM wParam,LPARAM lParam);
	LRESULT OnNetUSBLSocket(WPARAM wParam,LPARAM lParam);
	void DisableButton(BOOL bDisabled);//bDisable =false禁止；bDisable = ture 使能
	void SendPhoneData();
	void DisplayCommParam();
	void UpdateADCP(char* x,char* y,char* z,int nlength);
//	void ShowLog(CString str);
	void SaveRecord(CString str);
	void OnSetGain(int nchannel,int nGain);
	void OnChangeChannel(int nchannel,float fAmp,int type);
	void SaveMorseMsg(CString msg);
	void SendMorseMsg(CString msg);
	void SetADIOStatusIndicatior(int States);
	void OnSendAdio();
	void OnButtonSysini();
	void InitialSystem();
	int ReadNetSocket(SOCKET s,CNetSocket *sSocket);
	void ExplainRecData(BYTE *databuf, int len, int ntype);//ntype=0:MFSK 1:MPSK 2:FH
	CFont myFont;
	char *logview;
	char *logtab;
	int lastIndex;
	BOOL ViewSize;//大小界面标志 false 小 true 大
	BOOL SEND_FLAG;//可以向航控发送数据标志位
	BOOL firstpacket;
	CDataEncode pDataPackage;
	CWordDialog pWordPage;
	CComParam pComParamPage;
	CWaveView pWavePage;
	CPostView pPostPage;
	CAdcpPage pAdcpPage;
	CDataView pDataPage;
	CPictureView pPicturePage;
	COptionSet pOptionView;
	CLogView logpage;
	CTabLog Tablog;
	CADSamplePage AdSamplePage;
	BYTE CompressValue[COLORIMAGESIZE];//存放压缩的图像数据
	BYTE *RecDataBuf;//接收到的帧数据
	int  RecFrameNo; //已接收到的帧号
	BYTE *mybuffernew;//获取当前显示图像数据缓冲区指针
	int DemodulationMod;
//	CBitmapButton m_expand;
//	CBitmapButton m_status;
	CImageShow m_ShowImage;
	SOCKET s1,s2,s3;
	float	m_Amp;
	int		m_Gain;
	
	CNetSocket RecvSocket;
	CNetSocket SendSocket;
	CNetSocket watchdogsock;
	//网络Socket对象
	//0：接收定位声纳数据的UDP端，port 2000
	//1：发送给航行系统数据的UDP端 port 3001；
	//2：接收航行系统的UDP端，port 4000
	CNetSocket sSocket[3];
	Host recvhost;
	Host sendhost;
	CBitmapButton m_LED;
	
	SYSTEMSENSORDATA SystemSensorData; //吊舱ADIO板送来的温度、压力、电压等信息
	TCM2_T   tcmdata;//吊舱送来的姿态传感器数据
	CWinThread* m_pEncodeThrd;//代表语音编码线程句柄
	CWinThread* m_pDecodeThrd;//代表语音解码线程句柄
	CMorse MyMorse;//morse码操作对象
	COMMUNICATIONPARAM CommunicationParam;//吊舱ADIO送来的通信参数信息
	//接收USBL的定位信息标志位，3个都为1为完整数据
	int RecMoveData;		//相对位移	
	int RecSubPostData;		//
	int RecShipPostData;	//
	int RecShipRefData;		//
	LPT_HANDLE hyLPT ; //并口操作
	BOOL RECVMPSK;//是否正在接收psk数据
	int		m_nLightCount;		//录音指示灯闪烁计数
	BOOL	m_bRecordWork;	//是否正在录音工作
	BOOL	m_bRecordLightWork;   //灯是否闪烁
	BOOL    m_bInit;	//是否初始化
	ADIOSTATUS  ADIOStatus;    //ADIO的工作状态
	int   RecordState;//打印口控制寄存器状态
	int   RecordCount;//去毛刺计时
	int		m_nRecTime;		//录音时间
	int	  nHaveStart;		//已经启动播放线程
    CString xmtchannel;
	//////////////////////////////////////////////////////////////////////////
	SHIPPOST shipposition;//发送给航控的母船定位信息
	subPOST  subpost;//存储近几次的潜器定位数据
	int subpostindex;//潜器定位数据下标
 	BPDATA		bpdata;//避碰数据
	BSSSDATA	bsssdata;//BSSS数据
	ADLDATA		adldata;
	CTDDATA     ctddata;//CTD信息
	SUBPOSITION subposition;//潜水器位姿信息
	SYSPOSITION newPosition;
	SYSPOSITION	sysposition;
	ADCPDATA	adcpdata;	
	ABNORMITY   abnormity;//声学设备异常信息
	LIFESUPPLY  lifesupply;//生命支持系统
	ENERGYSYS   energysys;//能源系统信息
	ALERTDATA   alertdata;//报警信息
	SWITCHDATA  switchdata;//声学设备开关信息
	//////////////////////////////////////////////////////////////////////////
	mfskSWITCHDATA mfskswitchdata;
	mfskSUBPOSITION mfsksubposition;
	mfskBSSSDATA mfskbsssdata;
	mfskBPDATA mfskbpdata;
	mfskCTDDATA mfskctddata;
	mfskLIFESUPPLY mfsklifesupply;
	mfskENERGYSYS mfskenergysys;
	mfskALERTDATA mfskalertdata;
	ADCPDATA mfskadcpdata;
	//////////////////////////////////////////////////////////////////////////
	//////////////////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////////////////
	CACSDlg(CWnd* pParent = NULL);	// standard constructor
	LRESULT ExplainAnsNetpacket(NET_PACKET *pNetpacket);//解析从PC104上传的应答数据包
	int ExplainNetpacket(NET_PACKET * pNetpacket);//解析从PC104上传的控制和数据命令
	void OnCmdResetADIO();
	
	CRecordSound* m_RecordThread;
	CPlaySound* m_PlayThread;
	CPlayMMSound* m_PlayMMSound;
// Dialog Data
	//{{AFX_DATA(CACSDlg)
	enum { IDD = IDD_ACS_DIALOG };
	
	CProgressCtrl	m_soundamp;
	CSliderCtrl	m_slider_digitalamp;
	CComboBox	m_digitalchnnl;
	int Save_len;//收到的AD长度
	CSliderCtrl	m_slider_amp;
	CListCtrl	m_CtrlList;
	CStatic	m_UpdateTime;
	CTabCtrl	m_tabctrl;
	CEdit	m_LogEdit;
	CComboBox	m_Xmt_Channel;
	CButton	m_DspRun;
	CString	m_strXmtChannel;
	CString	m_log;
	CProgressCtrl	m_progress4;
	CProgressCtrl	m_progress3;
	CProgressCtrl	m_progress2;
	CProgressCtrl	m_progress1;
	CString	m_fhstring;
	CString	m_fhlog;
	CString	m_strdigitalchnnl;
	//}}AFX_DATA
	
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CACSDlg)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;
	afx_msg LRESULT OnNetCableSocket1(WPARAM wParam,LPARAM lParam);//与吊舱网络通信消息1
	afx_msg LRESULT OnNetCableSocket2(WPARAM wParam,LPARAM lParam);//与吊舱网络通信消息2
	afx_msg LRESULT OnNetCableSocket3(WPARAM wParam,LPARAM lParam);//与watchdog通信消息3
	// Generated message map functions
	//{{AFX_MSG(CACSDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnButton1();
	afx_msg void OnClose();
	afx_msg void OnExit();
	afx_msg void OnButtonStart();
	afx_msg void OnExpand();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg	void OnButtonMsgok();
	afx_msg void OnButtonMsgdn();
	afx_msg void OnButtonMsgup();
	afx_msg void OnButtonMsgdb();
	afx_msg void OnButtonMsgdu();
	afx_msg void OnButtonMsgwk();
	afx_msg void OnButtonMsgisok();
	afx_msg void OnButtonMsgrep();
	afx_msg void OnButtonNo();
	afx_msg void OnButtonAsk();
	afx_msg void OnAdvanced();
	afx_msg void OnOpenOption();
	afx_msg void OnLog();
	afx_msg void OnDClickListAdcp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnAdsample();
	afx_msg void OnReleasedcaptureSliderAmp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboXmt();
	afx_msg void OnFhSend();
	afx_msg void OnSelchangeComboDigitchnnl();
	afx_msg void OnReleasedcaptureSliderDigitalamp(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnEditchangeComboXmt();
	afx_msg void OnRadioMfsk();
	afx_msg void OnRadioMpsk();
	afx_msg void OnEditchangeComboDigitchnnl();
	afx_msg void OnEnforceSend();
	afx_msg void OnTest();
	afx_msg void OnParse();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnCheckpsk();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ACSDLG_H__03D78378_B92D_4E35_908F_6ABA992D7E9E__INCLUDED_)
