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
#include "lpt_lib.h"//���ڲ�������ͷ�ļ�
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
extern CCriticalSection SendNetpacketSync;//�������������ٽ����
extern CCriticalSection CCycleMemSync;//ѭ�������ٽ����
extern CCriticalSection WaveMemSync;//ѭ�������ٽ����

extern UINT SendNetpacketProc(LPVOID pParam);
extern HANDLE IsNetpacketEvent;//�Ƿ����������ݷ���
extern HANDLE RecvNetpacketEvent;//�Ƿ��յ���������
extern HANDLE SendNetpacketEvent;//������������ͬ���¼�
extern HICON m_hIcon_Wait;//ͼ����ʾ
extern HICON m_hIcon_Work;//ͼ����ʾ

extern HICON m_recvWork;
extern HICON m_ledon;

extern void  CreateFileName(char* filename,char* filetype,char * fullfilename);//�Զ������ļ���
extern CFileData XMTVoiceFile;//���淢�͵������ļ�
extern CFileData NorVoiceFile;//�����һ���������ļ�
extern CFileData XMTFSKFile;//���淢�͵�FSK�ļ�
extern CFileData XMTPSKFile;//���淢�͵�PSK�ļ�
extern CFileData XMTFSFile;//���淢�͵�FS�ļ�
extern CFileData RecordFile;//����������м�¼
extern CFileData RECVCommDataFile;//����ͨ�Ų�����¼�ļ�
extern CFileData TextFile;//��������ͨ�ż�¼
extern CFileData USBLFile;//��������ͨ�ż�¼
extern CFileData RECVVoiceFile;//�������е����������ļ�
extern CFileData RECVFSKFile;//������յ���fsk�����ļ�
extern CFileData RECVPSKFile;//������յ���psk�����ļ�
extern CFileData RECVEOUTFile;//������յ���EOUT�����ļ�
extern CFileData RECVFSFile;//������յ���fs�����ļ�
extern CFileData ADFile;//������յ���AD����
extern CFileData Trans2SailFile;//����ת�������п���ϵͳ����Ϣ�ļ�
extern CFileData MarineDataFile;//���պ��п���ϵͳ����Ϣ�ļ�
extern int channum;//��Чͨ����
extern BOOL m_bADWaveEnable; //�Ƿ��з�������
extern CCycleMem<char,MAXBUFFSIZE,1> * OutVoiceCycleMem;
extern CCycleMem<char,MAXBUFFSIZE,1> * InVoiceCycleMem;
extern CCycleMem<char,163841,1> * WaveCycleMem;
extern short* m_pRawData;//AD��������
extern double* dWaveData;//������ʾ����
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
	void DisplayData(int nSource);//0:λ����Ϣ��1;Ǳ����Ϣ��2��bp��Ϣ

	void OnSend(char* sendbuf,int sendlenth);
	LRESULT OnNetSailSocket(WPARAM wParam,LPARAM lParam);
	LRESULT OnNetUSBLSocket(WPARAM wParam,LPARAM lParam);
	void DisableButton(BOOL bDisabled);//bDisable =false��ֹ��bDisable = ture ʹ��
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
	BOOL ViewSize;//��С�����־ false С true ��
	BOOL SEND_FLAG;//�����򺽿ط������ݱ�־λ
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
	BYTE CompressValue[COLORIMAGESIZE];//���ѹ����ͼ������
	BYTE *RecDataBuf;//���յ���֡����
	int  RecFrameNo; //�ѽ��յ���֡��
	BYTE *mybuffernew;//��ȡ��ǰ��ʾͼ�����ݻ�����ָ��
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
	//����Socket����
	//0�����ն�λ�������ݵ�UDP�ˣ�port 2000
	//1�����͸�����ϵͳ���ݵ�UDP�� port 3001��
	//2�����պ���ϵͳ��UDP�ˣ�port 4000
	CNetSocket sSocket[3];
	Host recvhost;
	Host sendhost;
	CBitmapButton m_LED;
	
	SYSTEMSENSORDATA SystemSensorData; //����ADIO���������¶ȡ�ѹ������ѹ����Ϣ
	TCM2_T   tcmdata;//������������̬����������
	CWinThread* m_pEncodeThrd;//�������������߳̾��
	CWinThread* m_pDecodeThrd;//�������������߳̾��
	CMorse MyMorse;//morse���������
	COMMUNICATIONPARAM CommunicationParam;//����ADIO������ͨ�Ų�����Ϣ
	//����USBL�Ķ�λ��Ϣ��־λ��3����Ϊ1Ϊ��������
	int RecMoveData;		//���λ��	
	int RecSubPostData;		//
	int RecShipPostData;	//
	int RecShipRefData;		//
	LPT_HANDLE hyLPT ; //���ڲ���
	BOOL RECVMPSK;//�Ƿ����ڽ���psk����
	int		m_nLightCount;		//¼��ָʾ����˸����
	BOOL	m_bRecordWork;	//�Ƿ�����¼������
	BOOL	m_bRecordLightWork;   //���Ƿ���˸
	BOOL    m_bInit;	//�Ƿ��ʼ��
	ADIOSTATUS  ADIOStatus;    //ADIO�Ĺ���״̬
	int   RecordState;//��ӡ�ڿ��ƼĴ���״̬
	int   RecordCount;//ȥë�̼�ʱ
	int		m_nRecTime;		//¼��ʱ��
	int	  nHaveStart;		//�Ѿ����������߳�
    CString xmtchannel;
	//////////////////////////////////////////////////////////////////////////
	SHIPPOST shipposition;//���͸����ص�ĸ����λ��Ϣ
	subPOST  subpost;//�洢�����ε�Ǳ����λ����
	int subpostindex;//Ǳ����λ�����±�
 	BPDATA		bpdata;//��������
	BSSSDATA	bsssdata;//BSSS����
	ADLDATA		adldata;
	CTDDATA     ctddata;//CTD��Ϣ
	SUBPOSITION subposition;//Ǳˮ��λ����Ϣ
	SYSPOSITION newPosition;
	SYSPOSITION	sysposition;
	ADCPDATA	adcpdata;	
	ABNORMITY   abnormity;//��ѧ�豸�쳣��Ϣ
	LIFESUPPLY  lifesupply;//����֧��ϵͳ
	ENERGYSYS   energysys;//��Դϵͳ��Ϣ
	ALERTDATA   alertdata;//������Ϣ
	SWITCHDATA  switchdata;//��ѧ�豸������Ϣ
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
	LRESULT ExplainAnsNetpacket(NET_PACKET *pNetpacket);//������PC104�ϴ���Ӧ�����ݰ�
	int ExplainNetpacket(NET_PACKET * pNetpacket);//������PC104�ϴ��Ŀ��ƺ���������
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
	int Save_len;//�յ���AD����
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
	afx_msg LRESULT OnNetCableSocket1(WPARAM wParam,LPARAM lParam);//���������ͨ����Ϣ1
	afx_msg LRESULT OnNetCableSocket2(WPARAM wParam,LPARAM lParam);//���������ͨ����Ϣ2
	afx_msg LRESULT OnNetCableSocket3(WPARAM wParam,LPARAM lParam);//��watchdogͨ����Ϣ3
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
