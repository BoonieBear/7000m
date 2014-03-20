// ACSDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ACS.h"
#include "ACSDlg.h"
#include "Check.h"
#include "ReadUSBL.h"
#include "ReadUSBLBOX.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
CString iniFileName = "systemparam.ini";
CList <NET_PACKET*,NET_PACKET *> m_WzdNetpacketList;
CList <DIGITALBUFF *,DIGITALBUFF *> m_WzdtextList;	//��Ҫ���緢�͵�������������
CList <DATABUFF *,DATABUFF *> m_WzdvoiceList;	//��Ҫ���緢�͵�������������
CList <DIGITALBUFF *,DIGITALBUFF *> m_WzdimageList;	//��Ҫ���緢�͵�������������
BOOL m_bRecording =FALSE;
int	NorAmp =25000;
BOOL bFirstRecvData;
bool UsblEnableCheck = TRUE;
CImageProc imageCode;//ͼ�����
CImageProc imageDecode;//ͼ�����
CMPSKTurbo mpskturo;//turbo�ŵ�����
CMFSKConv  mfskconv;//����ŵ�����
//BYTE ColorImageInit[COLORIMAGESIZE];
//BYTE GrayImageInit[GRAYIMAGESIZE];
int Trainseq[32] = {0xB22290FF,0x9293A655,0xABBE68DC,0xA20DF0BB,0x6BF4D86F,0xF1AB123A,0x1442D503,
0x2E837B38,0x6A2FDA77,0x18F189F1,0x4874F7A7,0xF359F371,0x45CCAD5B,0xF876AFC9,0xBC87581C,0x5C87201F,
0xCCF78A42,0x7AE51D58,0x12DF1434,0x66794656,0x98416867,0xAD5767E6,0x4C9AA8E8,0x3B3D6042,0xCCDAFF53,
0xF1AEC329,0xF628B741,0x6E0EB21B,0x12CD0384,0xBE9398DF,0xDA3A870C,0x24A715BB};//������ѵ������

int Whiteseq[250]={0x3A2C81F0,0x48442B80,0x5E414B31,0x46AEA558,0x0CC8905E,0x34DF745F,0x55967ABE,0x866B00A2,
0x57AEED58,0x3A2B8BD9,0xC6701401,0xB900140E,0xB6307CBE,0xA36A673B,0xAEDD5AAD,0xF74563F6,0x3D6EE356,0x94596974,
0x5443DAEB,0xBFF44F59,0xBA4005AB,0x82DD8308,0xE45E9CD0,0x0BF72954,0xE93C31A8,0xA8F7F776,0x243B44A6,0x157375A2,
0x7EFAE498,0x5A40D638,0x8E8AC682,0x96E6313A,0x73C6F650,0x61A92E79,0xFB0E021A,0xD7CDBEC9,0x908AA689,0xEAE07DEC,
0xED5EEA45,0x7C0D052B,0xFDE8390D,0x3383766C,0x278ED4C9,0x86A6401E,0x252E00EC,0xE2F37F09,0xE2259339,0xE2E5A64C,
0xB191014A,0x1CD8C685,0xEEE2B4F1,0x413E7253,0x050FCECD,0xEC758CA4,0x95B876BD,0x6269CBEC,0x6B689BA1,0x008F4938,
0x6AD6861D,0x84C4826B,0x0EBA6ADA,0xF798A3C1,0x328E7797,0xC4665B43,0x35A52063,0x90F7093E,0x5B44BEC1,0x358ABA8E,
0x3DA137DA,0x5DB6FE46,0x781D1ECD,0x04A91DB8,0xF4B6E201,0xE6C9FF8D,0x20D0778E,0xA7E2E601,0x9BA068B0,0x529A6DF1,
0xA63E76A6,0x00796988,0x28014DC1,0x70E0197E,0xB9452839,0x0E5BBF2E,0x6D68F683,0x0A86F3B2,0xE5C9A3A1,0xB3FDE6CD,
0x4B20CFBD,0xD8C64814,0x4947771B,0xB75F22A0,0x2B3A0A80,0xD1F055EA,0x091B3A90,0x55A7956C,0x0CCD7540,0xD1FEAA00,
0x7FFCCC2B,0x390149BA,0x7BE949FF,0x1E6BF824,0x23D631C9,0xD3C4F87E,0x460397F5,0x0BC15FFD,0xB022B733,0x4F5CE0C7,
0x11F0AFE4,0xFA2EAA1C,0xFC836C09,0xBA5E490A,0x7DB39A8A,0x5920949C,0x1A8ED7B9,0x81CA8B71,0x36B0F920,0xD14453AB,
0x0ED54892,0x5C09B59B,0x48C1ED49,0x62058247,0xB8C625FF,0xF49FDC70,0xE6C05D1C,0xB985229B,0xB41B073E,0xC7119304,
0xCDD9668E,0xBC6FF28E,0x8B75A2FD,0x63165D02,0x4408FE4E,0x30DA53CA,0x2EE38594,0x1C08CE26,0x4C24A8D5,0xB9234155,
0xF3736A1C,0x7B7099B9,0x7992D278,0xAF0BA783,0x27B80BD8,0x9CE968AE,0x73A0808A,0x10D71A26,0xA5840F5F,0x3DD39127,
0xBFA06909,0x980C9F46,0x24CBB6C3,0xD04259F3,0x73A1266B,0x0E0C6216,0xEFD0D1D5,0xDE862156,0xF5E7D7EB,0xE66CF768,
0xB554B561,0x96C0D88B,0x07163934,0xBEDF8A40,0x11F2FF24,0xD92E98E7,0x856390A8,0xFD8166D6,0xE50914F7,0x610D8DDD,
0x81011AEB,0xC0CBA2EB,0x6EFC8BBA,0xABDB3369,0x2E9343DC,0x6D9419F5,0x5C3AB3FE,0x189FEFC3,0xD8847E40,0x2E1E407F,
0x95891560,0xE4068A53,0xD85C8985,0x23A38D8C,0x86034B71,0x67F56B35,0xF496B82A,0xA38A4162,0x4F21D3CC,0x3F12ED90,
0xEE6ABA19,0xFAF6AAD0,0xE5EAFCD6,0x541D099D,0x5F8F474E,0x1B9AA7B0,0xA3606A6D,0xF9D80EA9,0x5BCC9A53,0xA1B42863,
0x2EF6CB7A,0xFFBD12A3,0x63A0DB43,0x19F97607,0xDF86DE08,0x52B32DF9,0x71ED287F,0x5A84447D,0x955A0620,0x36012C69,
0xD1ADC9FA,0xC9A7D862,0x5C9355A0,0x541F4E7A,0x3EA8FFAC,0xC54BA6D7,0x658B1BF1,0xA339D012,0x6BF14187,0xCF787713,
0xE161DF2C,0x9FFC4635,0xD0C1386D,0x2F154DFC,0x8E869B35,0x5F555728,0xD3795316,0x845E4609,0x894B4041,0x6E85E46F,
0x92A833F4,0x399D0E16,0x4EA09BBA,0x8FAA24F0,0x7E0FF4CA,0x3159D8E6,0x6C891FBE,0x8E7447F6,0x1EE090F5,0xA07AE79E,
0x197D95A7,0x6C87BE17,0x5A384B1D,0x4EE1495E,0xA4663441,0x13628882,0xA173486F,0xCE66C17E,0xCA386968,0x00503975,
0x2581CCEA,0xE26B4C79};//�׻�����
int interleaveQPSK[3872];//QPSK��֯����
CCriticalSection SendNetpacketSync;//�������������ٽ����
CCriticalSection CCycleMemSync;
CCriticalSection WaveMemSync;
HWND hWnd =NULL;
short* m_pRawData=NULL;//AD��������
DWORD m_nRawDataLen=0;
UINT SendNetpacketProc(LPVOID pParam);//�����������ݹ����̺߳���
char* lastpacket  = NULL;
HANDLE IsNetpacketEvent=CreateEvent(NULL,TRUE,FALSE,NULL);
HANDLE RecvNetpacketEvent=CreateEvent(NULL,TRUE,FALSE,NULL);

HANDLE SendNetpacketEvent=CreateEvent(NULL,TRUE,FALSE,NULL);//������������ͬ���¼�,��ʼ�����ź�
HANDLE CCycleMemHasDataEvent = CreateEvent(NULL,TRUE,FALSE,NULL);//���Ͷ�ȡ����ͬ���¼�,��ʼ�����ź�
HICON m_hIcon_Wait;//
HICON m_hIcon_Work;//
HICON m_recvWork;
HICON m_ledoff;
UWACINITPARA UWACInitParam;//ϵͳ��������
UWACOMPARAM UWAcommparam;//�������
CFileData XMTVoiceFile;//���淢�͵������ļ�
CFileData NorVoiceFile;
CFileData XMTFSKFile;//���淢�͵�fsk�ļ�
CFileData XMTPSKFile;//���淢�͵�Psk�ļ�
CFileData XMTFSFile;//���淢�͵�fs�ļ�
CFileData RecordFile;//����������м�¼
CFileData TextFile;//��������ͨ�ż�¼
CFileData RECVVoiceFile;//�������е����������ļ�
CFileData RECVFSKFile;//������յ���fsk�ļ�
CFileData RECVPSKFile;//������յ���psk�ļ�
CFileData RECVEOUTFile;//������յ���EOUT�ļ�
CFileData RECVCommDataFile;//�����յ���ͨ�Ų���
CFileData RECVFSFile;//������յ���fs�ļ�
CFileData USBLFile;//���̻�����Ϣ
CFileData Trans2SailFile;//����ת�������п���ϵͳ����Ϣ�ļ�
CFileData MarineDataFile;//���պ��п���ϵͳ����Ϣ�ļ�
CFileData ADFile;//������յ���AD����
CCycleMem<char,MAXBUFFSIZE,1> * OutVoiceCycleMem;//����ˮ������
CCycleMem<char,MAXBUFFSIZE,1> * InVoiceCycleMem;//�յ�ˮ������
CCycleMem<char,163841,1> * WaveCycleMem;//�յ�ˮ������
int channum=8 ;//��Чͨ����
BOOL m_bADWaveEnable = TRUE; //�������
double * dWaveData;//1s������ʾ����
static int iframenum=0;
void GenSinWave (short* pBuffer, int iFreq, int nlength);
void VoiceNormalize (short* pBuffer,int nlength);//������������
void OnEnableIIR(int nEnabel);
/*�жϷ��������*/
void  CreateFileName(char* filename,char* filetype,char * fullfilename);//�Զ������ļ���
void DLLCALLCONV LPT_IntAHandlerRoutine(LPT_HANDLE hLPT, LPT_IntA_RESULT *intResult);
#pragma comment(lib, "winmm.lib") 
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CACSDlg dialog

CACSDlg::CACSDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CACSDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CACSDlg)
	Save_len = 0;
	m_strXmtChannel = _T("");
	m_log = _T("");
	m_fhstring = _T("");
	m_fhlog = _T("");
	m_strdigitalchnnl = _T("1");
	logview =NULL;
	logtab =NULL;
	LinkStatus =FALSE;
	LBLStatus = TRUE;
	bFirstRecvData = TRUE;
	nHaveStart =0;
	RecDataBuf = NULL;
	RecFrameNo = 0xFF;
	DemodulationMod =MFSKMOD;
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	
}

void CACSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CACSDlg)
	DDX_Control(pDX, IDC_BUTTON_LED, m_LED);
	DDX_Control(pDX, IDC_PROGRESS9, m_soundamp);
	DDX_Control(pDX, IDC_SLIDER_DIGITALAMP, m_slider_digitalamp);
	DDX_Control(pDX, IDC_COMBO_DIGITCHNNL, m_digitalchnnl);
	DDX_Control(pDX, IDC_SLIDER_AMP, m_slider_amp);
	DDX_Control(pDX, IDC_LIST_ADCP, m_CtrlList);
	DDX_Control(pDX, IDC_TAB, m_tabctrl);
	DDX_Control(pDX, IDC_EDIT_LOG, m_LogEdit);
	DDX_Control(pDX, IDC_COMBO_XMT, m_Xmt_Channel);
	DDX_CBString(pDX, IDC_COMBO_XMT, m_strXmtChannel);
	DDX_Text(pDX, IDC_EDIT_LOG, m_log);
	DDX_Control(pDX, IDC_PROGRESS4, m_progress4);
	DDX_Control(pDX, IDC_PROGRESS3, m_progress3);
	DDX_Control(pDX, IDC_PROGRESS2, m_progress2);
	DDX_Control(pDX, IDC_PROGRESS1, m_progress1);
	DDX_Text(pDX, IDC_FHWORD, m_fhstring);
	DDX_Text(pDX, IDC_FHLOG, m_fhlog);
	DDX_CBString(pDX, IDC_COMBO_DIGITCHNNL, m_strdigitalchnnl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CACSDlg, CDialog)
	//{{AFX_MSG_MAP(CACSDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, OnExit)
 	ON_BN_CLICKED(IDC_BUTTON_START, OnButtonStart)
	ON_BN_CLICKED(IDC_EXPAND, OnExpand)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	ON_BN_CLICKED(IDC_BUTTON7, OnButtonMsgok)
	ON_BN_CLICKED(IDC_BUTTON12, OnButtonMsgdn)
	ON_BN_CLICKED(IDC_BUTTON8, OnButtonMsgup)
	ON_BN_CLICKED(IDC_BUTTON6, OnButtonMsgdb)
	ON_BN_CLICKED(IDC_BUTTON9, OnButtonMsgdu)
	ON_BN_CLICKED(IDC_BUTTON10, OnButtonMsgwk)
	ON_BN_CLICKED(IDC_BUTTON5, OnButtonMsgisok)
	ON_BN_CLICKED(IDC_BUTTON3, OnButtonMsgrep)
	ON_BN_CLICKED(IDC_BUTTON11, OnButtonNo)
	ON_BN_CLICKED(IDC_BUTTON4, OnButtonAsk)
	ON_BN_CLICKED(IDC_ADVANCED, OnAdvanced)
	ON_BN_CLICKED(IDC_OPEN_OPTION, OnOpenOption)
	ON_BN_CLICKED(IDC_LOG, OnLog)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ADCP, OnDClickListAdcp)
	ON_BN_CLICKED(IDC_ADSAMPLE, OnAdsample)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_AMP, OnReleasedcaptureSliderAmp)
	ON_CBN_SELCHANGE(IDC_COMBO_XMT, OnSelchangeComboXmt)
	ON_BN_CLICKED(IDC_FH_SEND, OnFhSend)
	ON_CBN_SELCHANGE(IDC_COMBO_DIGITCHNNL, OnSelchangeComboDigitchnnl)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_DIGITALAMP, OnReleasedcaptureSliderDigitalamp)
	ON_CBN_EDITCHANGE(IDC_COMBO_XMT, OnEditchangeComboXmt)
	ON_BN_CLICKED(IDC_RADIO_MFSK, OnRadioMfsk)
	ON_BN_CLICKED(IDC_RADIO_MPSK, OnRadioMpsk)
	ON_CBN_EDITCHANGE(IDC_COMBO_DIGITCHNNL, OnEditchangeComboDigitchnnl)
	ON_BN_CLICKED(IDC_ENFORCE_SEND, OnEnforceSend)
	ON_BN_CLICKED(IDC_BUTTON13, OnTest)
	ON_BN_CLICKED(IDC_BUTTON14, OnParse)
	ON_WM_HSCROLL()
	ON_WM_NCPAINT( )
	ON_MESSAGE(CABLE_NET_WMSG1,OnNetCableSocket1)//���������ͨ����Ϣ
	ON_MESSAGE(CABLE_NET_WMSG2,OnNetCableSocket2)//���������ͨ����Ϣ
	ON_MESSAGE(CABLE_NET_WMSG3,OnNetCableSocket3)//��watchdogͨ����Ϣ
	ON_MESSAGE(POSITION_NET_WMSG,OnNetUSBLSocket)//���ն�λ�������ݵ���Ϣ����
	ON_MESSAGE(SAIL_NET_WMSG,OnNetSailSocket)//���պ��п���ϵͳ���ݵ���Ϣ����
	ON_MESSAGE(WMSG_SOUNDWAVE, DisplaySoundWave)
	ON_MESSAGE(WMSG_SENDPHONEDATA,SendPhoneData)
	ON_MESSAGE(TIMEOUT_WMSG,TimeOutAlarm)
	ON_BN_CLICKED(IDC_CHECKPSK, OnCheckpsk)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CACSDlg message handlers

BOOL CACSDlg::OnInitDialog()//�����ʼ��
{
	CDialog::OnInitDialog();

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);
	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}
	SkinH_Attach();
	SkinH_SetAero(0);
	lastpacket = new char[8192];
	OutVoiceCycleMem = new CCycleMem<char,MAXBUFFSIZE,1>;
	InVoiceCycleMem = new CCycleMem<char,MAXBUFFSIZE,1>;
	WaveCycleMem = new CCycleMem<char,163841,1>;
	dWaveData = new double[12000];
	m_pRawData = new short[SAMPLINGNUBER*8];//���8ͨ��
	m_nRawDataLen=0;
	/////////��ʼ��ϵͳͼ��////////////////////////////////////////////////////
// 	m_expand.LoadBitmaps(IDB_expand);
// 	m_expand.SubclassDlgItem(IDC_EXPAND,this);
// 	m_expand.SizeToContent();
	//////////////////////////////////////////////////////////////////////////
//	m_status.LoadBitmaps(IDB_OFF);
//	m_status.SubclassDlgItem(IDC_STATUS,this);
//	m_status.SizeToContent();
// 
// 	SetIcon(m_hIcon, TRUE);			// Set big icon
// 	SetIcon(m_hIcon, FALSE);		// Set small icon
 	m_hIcon_Wait = AfxGetApp()->LoadIcon(IDB_OFF);
 	m_hIcon_Work = AfxGetApp()->LoadIcon(IDB_ON);
// 	m_recvWork = AfxGetApp()->LoadIcon(IDI_LEDON);
//	m_PlayMMSound->PostThreadMessage(WM_PLAYMMSOUND_PLAYFILE,0,(LPARAM)"sound.wav");//��ʼ�����߳�
	//��ָ����֡���ڵ�ָ�븳ֵ(ȫ�ֱ���)
	hWnd = GetSafeHwnd( ) ;
	if(hWnd==NULL)
		AfxMessageBox("��ȡ������ָ��ʧ��");
	

//	m_slider_gain.SetRange(100,4000);
	m_slider_amp.SetRange(5,1000);	
	m_slider_digitalamp.SetRange(5,1000);
	CString str;
	CRect rect;
	//����ѡ��ҳ//////////////////////////////////////////////////////////////////////////
	m_tabctrl.SetMinTabWidth(80);
	m_tabctrl.GetClientRect(&rect);
	
	rect.top+=23;
	rect.left+=3;

	//add  pages
	m_tabctrl.InsertItem(0, _T(" ˮ������ "));
	pWavePage.Create(IDD_DIALOG_WAVEVIEW, &m_tabctrl);
	pWavePage.MoveWindow(&rect);
	pWavePage.ShowWindow(SW_SHOW);
//	m_tabctrl.SetCurSel(0);

	m_tabctrl.InsertItem(1, _T(" ��λ��ͼ "));
	pPostPage.Create(IDD_DIALOG_POSTVIEW, &m_tabctrl);
	pPostPage.MoveWindow(&rect);
	pPostPage.ShowWindow(SW_HIDE);

	m_tabctrl.InsertItem(2, _T(" ���ֶԻ� "));
	pWordPage.Create(IDD_DIALOG_WORD, &m_tabctrl);
	pWordPage.MoveWindow(&rect);
	pWordPage.ShowWindow(SW_HIDE);
		
	m_tabctrl.InsertItem(3, _T(" ͼ��ģʽ "));
	pPicturePage.Create(IDD_PICTURE, &m_tabctrl);
	pPicturePage.MoveWindow(&rect);
	pPicturePage.ShowWindow(SW_HIDE);

	m_tabctrl.InsertItem(4, _T(" Ǳ������ "));
	pDataPage.Create(IDD_DIALOG_DATA, &m_tabctrl);
	pDataPage.MoveWindow(&rect);
	pDataPage.ShowWindow(SW_HIDE);
	
	m_tabctrl.InsertItem(5, _T(" ���м�¼ "));
	Tablog.Create(IDD_DIALOG_Tablog, &m_tabctrl);
	Tablog.MoveWindow(&rect);
	Tablog.ShowWindow(SW_HIDE);
	//////////////////////////////////////////////////////////////////////////
	pComParamPage.Create(IDD_DIALOG_COMPARAM,this);
	pComParamPage.ShowWindow(SW_HIDE);
	logpage.Create(IDD_DIALOG_LOG,this);
	logpage.ShowWindow(SW_HIDE);
	AdSamplePage.Create(IDD_DIALOG_AD,this);
	AdSamplePage.ShowWindow(SW_HIDE);
	pAdcpPage.Create(IDD_DIALOG_ADCP,this);
	pAdcpPage.ShowWindow(SW_HIDE);
	//LPt����

	hyLPT = NULL;
	if (!LPT_Open(&hyLPT))  //�򿪴�ӡ���˿�
    {
        AfxMessageBox("Error while opening LPT:\n");
        //printf ("%s", LPT_ErrorString);
        //return 0;
    }
	
	else
	{
		SetTimer(LPTREADCONTROLTIMER,100,NULL);  //�ɹ������ӡ�ڵ�״̬�Ĵ���
		
		BYTE nControl = LPT_Readcontrol(hyLPT);	//�����ƼĴ���״̬
		nControl|= 0x10;                         //�����ж���Ӧ
		LPT_Writecontrol(hyLPT, nControl);		//д���ƼĴ���
		LPT_Writedata(hyLPT,0xB9);  //B0_DQ=1 ,�ͷ�DQ��,B6_DQ=0,������������
	
		//��������δ����
        if (!LPT_IntAEnable(hyLPT, LPT_IntAHandlerRoutine))
		{
			AfxMessageBox("��ӡ�˿��жϷ���������\n");
		}
	}

	m_nLightCount = 0;		//¼��ָʾ����˸����
	m_nRecTime  = 0;		//¼��ʱ��
	m_bRecordWork=FALSE;	//�Ƿ�����¼������
//	m_bRecordLightWork=FALSE;		//�������Ƿ���˸
	RecordState = NORECORDWORK;
//	m_bRecording = FALSE;
	m_bInit = FALSE;
	RECVMPSK = FALSE;
	//��ʼ��ADCPLIST
	m_CtrlList.SetExtendedStyle(LVCF_FMT|LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_CtrlList.InsertColumn(0,_T("����"),LVCFMT_CENTER,50);	//add column title
	m_CtrlList.InsertColumn(1,_T("X��"),LVCFMT_CENTER,45);
	m_CtrlList.InsertColumn(2,_T("Y��"),LVCFMT_CENTER,45);
	m_CtrlList.InsertColumn(3,_T("Z��"),LVCFMT_CENTER,45);
	m_CtrlList.InsertItem(1,"0��");
	m_CtrlList.InsertItem(2,"1��");
	m_CtrlList.InsertItem(3,"2��");
	m_CtrlList.InsertItem(4,"3��");
	m_CtrlList.InsertItem(5,"4��");
	m_CtrlList.InsertItem(6,"5��");
	m_CtrlList.InsertItem(7,"6��");
	m_CtrlList.InsertItem(8,"7��");
	m_CtrlList.InsertItem(9,"8��");
	m_CtrlList.InsertItem(10,"9��");
	myFont.CreatePointFont(120,"Sans Serif");
	m_CtrlList.SetFont(&myFont);
	CWnd* pWnd;
	pWnd=GetDlgItem(IDC_IMAGE);
	pWnd->GetWindowRect(&rect);
	ScreenToClient(&rect);
	m_ShowImage.Create(WS_VISIBLE | WS_CHILD, rect, this, 2001);
	m_ShowImage.FileLoad("background.bmp");
	mybuffernew = m_ShowImage.m_Dib.GetBitsAddress();
	
	m_progress1.SetRange(100,3000);
	m_progress2.SetRange(100,3000);
	m_progress3.SetRange(100,3000);
	m_progress4.SetRange(100,3000);
//	m_progress5.SetRange(100,3000);
//	m_progress6.SetRange(100,3000);
// 	m_progress7.SetRange(100,3000);
// 	m_progress8.SetRange(100,3000);
	m_soundamp.SetRange(135,175);
	ViewSize =FALSE;
	SetWindowPos(&wndNoTopMost,0,0,800,600,SWP_SHOWWINDOW);
	SetTimer(SYS_INFO_DISP_TIMER,1000,NULL);  ////ϵͳ��Ϣ��ʾ��ʱ��
	InitialSystem();//���ݳ�ʼ��
	OnExpand();
	UpdateADCP(adcpdata.floorX,adcpdata.floorY,adcpdata.floorZ,10);
	pPicturePage.OnSendpic();//Ĭ����ӷ���ͼƬ�����ⷢ��MPSKʱ��ͼƬ����
// 	TestDataPackageAndParse();
	CTime nowtime;
	nowtime = CTime::GetCurrentTime();
	str.Format("%02d:%02d:%02d",nowtime.GetHour(),nowtime.GetMinute(),nowtime.GetSecond());
	SetDlgItemText(IDC_PIC_RECVTIME,str);
//	OnRadioMfsk();
	UWACInitParam.XMTModulation = MFSKMOD;
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CACSDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CACSDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CACSDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CACSDlg::OnConnect() 
{
	// TODO: Add your control notification handler code here

	if(strlen(SendSocket.m_szAddr)!=0 && strlen(RecvSocket.m_szAddr)!=0)
	{
		while ((SendSocket.m_bConnect)||(RecvSocket.m_bConnect))
		{
			SendSocket.Close();
			RecvSocket.Close();
			Sleep(50);
		}
		m_bInit = FALSE;
		if (!watchdogsock.m_bConnect)
		{
			watchdogsock.CreateClient();
			
		}

// 		if(!SendSocket.m_bConnect)
// 		{
// 			SendSocket.CreateClient();
// 	
// 		}
// 		
// 		if(!RecvSocket.m_bConnect)
// 		{
// 			RecvSocket.CreateClient();
// 	
// 		}
	}
	else
	{
		AfxMessageBox("�����úõ��յ�IP��ַ�����������磡");
	}			
	
}

void CACSDlg::InitialSystem()
{
	//���촴��logĿ¼
	CTime ct = CTime::GetCurrentTime();
	char dirpath[_MAX_PATH+1];
	CString dirfullpath;
	GetCurrentDirectory(_MAX_PATH+1,dirpath);
	dirfullpath.Format("%s",dirpath);
	//���ļ��ж��뽻֯����
	FILE  * f;
	f = fopen("IntlvTable2.rdn","rb");
	if(f==NULL){
		AfxMessageBox("IntlvTable2.rdn��֯��򲻿�������·����");
		return;
	}
	fread(interleaveQPSK,sizeof(char),15488,f);
	fclose(f);

	//���ļ��ж���ͼ���ʼѹ������
	f = fopen("ColorBlackCompress.init","rb");
	if(f==NULL){
		AfxMessageBox("ColorBlackCompress.initѹ�������ļ��򲻿�������·����");
		return;
	}
	fread(CompressValue,sizeof(char),COLORIMAGESIZE,f);
	fclose(f);
//	memcpy(CompressValue,ColorImageInit,COLORIMAGESIZE);
/*
	f = fopen("GrayBlackCompress.init","rb");
	if(f==NULL){
		AfxMessageBox("GrayBlackCompress.initѹ�������ļ��򲻿�������·����");
		return;
	}
	fread(GrayImageInit,sizeof(char),GRAYIMAGESIZE,f);
	fclose(f);
*/
	char amp[6];
	char ip[256];
	memset(&subpost,0,sizeof(subPOST));
	subpostindex=0;
	memset(m_pRawData,0,SAMPLINGNUBER*8*sizeof(short));
	memset(&CommunicationParam,0,sizeof(COMMUNICATIONPARAM));
	memset(&UWACInitParam,0,sizeof(UWACINITPARA));
	memset(&SystemSensorData,0,sizeof(SYSTEMSENSORDATA));
	memset(&bsssdata,0,sizeof(BSSSDATA));
	memset(&adldata,0,sizeof(ADLDATA));
	memset(&ctddata,0,sizeof(CTDDATA));
	memset(&subposition,0,sizeof(SUBPOSITION));
	memset(&newPosition,0,sizeof(SYSPOSITION));
	memset(&sysposition,0,sizeof(SYSPOSITION));
	memset(&adcpdata,0,sizeof(ADCPDATA));
	memset(&abnormity,0,sizeof(ABNORMITY));
	memset(&lifesupply,0,sizeof(LIFESUPPLY));
	memset(&energysys,0,sizeof(ENERGYSYS));
	memset(&alertdata,0,sizeof(ALERTDATA));
	memset(&bpdata,0,sizeof(BPDATA));
	memset(&mfskswitchdata,0,sizeof(mfskSWITCHDATA));

	bpdata.behinddown = 65535;
	bpdata.down = 65535;
	bpdata.front = 65535;
	bpdata.frontdown = 65535;
	bpdata.frontup = 65535;
	bpdata.left = 65535;
	bpdata.right = 65535;
	memset(&shipposition,0,sizeof(SHIPPOST));
	//����¼������led
	m_LED.LoadBitmaps(IDB_ON,NULL,NULL,NULL);
	m_LED.SubclassDlgItem(IDB_ON,this);
	m_LED.SizeToContent();

	//��ȡ��ʼ����Ϣ
	iniFileName = dirfullpath+"\\systemparam.ini";
//	UWAcommparam.Mode =GetPrivateProfileInt("sysparam","Mode",2,iniFileName);
	CFile SetFile;
	//�Ӳ����ļ��ж������
	if(!SetFile.Open("default.sysinit",CFile::modeRead))
	{
		AfxMessageBox("û��Ĭ�������ļ��������˳�");
		exit(1);
	}
	SetFile.Read(&UWACInitParam,sizeof(UWACINITPARA));
	SetFile.Close();
// 	if (UWACInitParam.ADIOWorkMode != UWAcommparam.Mode)
// 	{
// 		AfxMessageBox("Ĭ�������ļ�ģʽ���������޸�");
// 		exit(1);
// 	}
	UWACInitParam.XMTModulation =MFSKMOD;//��ʼΪ��Ƶģʽ
	CButton* radioWnd =  (CButton*)GetDlgItem(IDC_RADIO_MFSK);
	radioWnd->SetCheck(1);
	UWAcommparam.XmtChannel =  GetPrivateProfileInt("sysparam","XMTChannel",1,iniFileName);
	UWAcommparam.RecvChannel = GetPrivateProfileInt("sysparam","RecvChannel",1,iniFileName);
	UWAcommparam.Gain = GetPrivateProfileInt("sysparam","RecvGain",1000,iniFileName);
	UWACInitParam.XMTChannelNo = UWAcommparam.XmtChannel;//ˮ��ͨ��
	UWACInitParam.digital_tranmit_channel = UWAcommparam.XmtChannel;
	UWACInitParam.MFSKDataSymbolNum = 12;
//	UWACInitParam.LoadDestID = DSP01ID|DSP02ID|DSP11ID|DSP12ID|ADIOID;
	GetPrivateProfileString("sysparam","XMTAMP","0.3",amp,6,iniFileName);
	CString strAmp,strGain;
	strAmp.Format("%s",amp);
	UWAcommparam.XmtAmp = atof(strAmp);
	UWACInitParam.XMTAmpValue = UWAcommparam.XmtAmp;
	GetPrivateProfileString("Host","IP","192.168.2.238",ip,256,iniFileName);
	memcpy(recvhost.HostIp,ip,256);
	memcpy(sendhost.HostIp , recvhost.HostIp,256);
	recvhost.Port = GetPrivateProfileInt("Host","SendPort",5001,iniFileName);
	sendhost.Port = GetPrivateProfileInt("Host","RecvPort",5000,iniFileName);
	NorAmp = GetPrivateProfileInt("sysparam","NormAmp",20000,iniFileName);
	m_Amp = UWAcommparam.XmtAmp;

	m_strXmtChannel.Format("%d",UWAcommparam.XmtChannel);
	m_strdigitalchnnl.Format("%d",UWACInitParam.digital_tranmit_channel);
	m_Gain =  UWAcommparam.Gain;
	UWACInitParam.XMTWhiteProcess =1;//�׻�
	strAmp.Format("%0.2f",UWACInitParam.XMTAmpValue);
	//�ƶ�������
	CWnd* pWnd;
	m_slider_amp.SetPos(UWAcommparam.XmtAmp*1000);
	pWnd = GetDlgItem(IDC_STATIC_AMP);
	pWnd->SetWindowText(strAmp);
	m_slider_digitalamp.SetPos(UWACInitParam.XMTAmpValue*1000);
	pWnd = GetDlgItem(IDC_STATIC_DIGITALAMP);
	
	pWnd->SetWindowText(strAmp);
	if(UWACInitParam.ADIOWorkMode==1)// ˮ��
	{
		channum=4;
		m_Xmt_Channel.AddString(_T("1"));
		m_Xmt_Channel.AddString(_T("2"));
 		m_Xmt_Channel.AddString(_T("3"));
 		m_Xmt_Channel.AddString(_T("4"));
		m_digitalchnnl.AddString(_T("1"));
		m_digitalchnnl.AddString(_T("2"));
 		m_digitalchnnl.AddString(_T("3"));
 		m_digitalchnnl.AddString(_T("4"));
// 		m_morselist.AddString(_T("�յ� ����"));
// 		m_morselist.AddString(_T("ѯ����� ���"));
// 		m_morselist.AddString(_T("ͬ�� ���   ���"));
// 		m_morselist.AddString(_T("�����ϸ� ������"));
// 		m_morselist.AddString(_T("��ͬ�� ����  ����"));
		

	}
	else
	{
		channum=4;
		m_Xmt_Channel.AddString(_T("1"));
		m_Xmt_Channel.AddString(_T("2"));
		m_Xmt_Channel.AddString(_T("3"));
		m_Xmt_Channel.AddString(_T("4"));
		m_digitalchnnl.AddString(_T("1"));
		m_digitalchnnl.AddString(_T("2"));
		m_digitalchnnl.AddString(_T("3"));
		m_digitalchnnl.AddString(_T("4"));
// 		m_morselist.AddString(_T("һ������ ����"));
// 		m_morselist.AddString(_T("��ɽ׶ι��� ���"));
// 		m_morselist.AddString(_T("�����ϸ� ���   ���"));
// 		m_morselist.AddString(_T("����Ӧ������ ������"));
// 		m_morselist.AddString(_T("�ͷ�Ӧ������ ���  ���  ���"));
	}
//	m_morselist.SetCurSel(0);
//	ADFile�ڽ����ļ�ʱ��ˮ��ˮ�·ֱ��ʼ��
//	ADFile.Init("AD",FILESIZE,1024,4*WRITESIZE);
		//��ʼ����¼�ļ�

	RecordFile.Init("Record",10*FILESIZE,1024,1*WRITESIZE);//��ʼ���������м�¼���ļ�
	RECVCommDataFile.Init("CommRecord",10*FILESIZE,1024*2,1*WRITESIZE);//��ʼ���������м�¼���ļ�
// 	XMTVoiceFile.Init("XMTVOICE",1*FILESIZE,1024,4*WRITESIZE);
// 	XMTFSKFile.Init("XMTFSK",1*FILESIZE,1024,4*WRITESIZE);
// 	XMTPSKFile.Init("XMTPSK",1*FILESIZE,1024,4*WRITESIZE);
 	XMTFSFile.Init("XMTFS",1*FILESIZE,1024,1*WRITESIZE);
	TextFile.Init("Text",10*FILESIZE,1024,1*WRITESIZE);//��ʼ�����淢�����ּ�¼���ļ�
	USBLFile.Init("USBL",10*FILESIZE,1024,1*WRITESIZE);
	RECVVoiceFile.Init("RECVVoice",1000*FILESIZE,3*1024,32*WRITESIZE);
// 	RECVFSKFile.Init("RECVFSK",FILESIZE,1024,4*WRITESIZE);
//	RECVPSKFile.Init("RECVPSK",FILESIZE,1024,4*WRITESIZE);
 	RECVFSFile.Init("RECVFH",FILESIZE,1024,1*WRITESIZE);
	Trans2SailFile.Init("Trans2Sail",10*FILESIZE,1024,4*WRITESIZE);
	MarineDataFile.Init("MarineData",10*FILESIZE,1024,4*WRITESIZE);

	dirfullpath.Format("%s\\log",dirpath);
	CreateDirectory(dirfullpath,NULL);

	CString dayTime,strdir;
	if (UWACInitParam.ADIOWorkMode==1)
	{
		dayTime.Format("%s\\SHIP%02d_%02d",dirfullpath,ct.GetMonth(),ct.GetDay());
	}
	else
	{
		dayTime.Format("%s\\UWV%02d_%02d",dirfullpath,ct.GetMonth(),ct.GetDay());	
	}
	
	CreateDirectory(dayTime,NULL);

	strdir.Format("%s//XMTvoice//",dayTime);
	CreateDirectory(strdir,NULL);
	XMTVoiceFile.SetPath(strdir);
	NorVoiceFile.SetPath(strdir);
	strdir.Format("%s//XMTFSKFile//",dayTime);
	CreateDirectory(strdir,NULL);
	XMTFSKFile.SetPath(strdir);

	strdir.Format("%s//XMTPSKFile//",dayTime);
	CreateDirectory(strdir,NULL);
	XMTPSKFile.SetPath(strdir);

	strdir.Format("%s//XMTFSFile//",dayTime);
	CreateDirectory(strdir,NULL);
	XMTFSFile.SetPath(strdir);

	strdir.Format("%s//RecvVoice//",dayTime);
	CreateDirectory(strdir,NULL);
	RECVVoiceFile.SetPath(strdir);

	strdir.Format("%s//XMTText//",dayTime);
	CreateDirectory(strdir,NULL);
	TextFile.SetPath(strdir);

	strdir.Format("%s//USBL//",dayTime);
	CreateDirectory(strdir,NULL);
	USBLFile.SetPath(strdir);

	strdir.Format("%s//Record//",dayTime);
	CreateDirectory(strdir,NULL);
	RecordFile.SetPath(strdir);

	strdir.Format("%s//RECVFSKFile//",dayTime);
	CreateDirectory(strdir,NULL);
	RECVFSKFile.SetPath(strdir);

	strdir.Format("%s//RECVPSKFile//",dayTime);
	CreateDirectory(strdir,NULL);
	RECVPSKFile.SetPath(strdir);

	strdir.Format("%s//RECVPSKFile//",dayTime);
	CreateDirectory(strdir,NULL);
	RECVEOUTFile.SetPath(strdir);
	
	strdir.Format("%s//Record//",dayTime);
	CreateDirectory(strdir,NULL);
	RECVCommDataFile.SetPath(strdir);
	
	strdir.Format("%s//RECVFHFile//",dayTime);
	CreateDirectory(strdir,NULL);
	RECVFSFile.SetPath(strdir);
	
	strdir.Format("%s//ADFile//",dayTime);
	CreateDirectory(strdir,NULL);
	ADFile.SetPath(strdir);

	strdir.Format("%s//Trans2SailFile//",dayTime);
	CreateDirectory(strdir,NULL);
	Trans2SailFile.SetPath(strdir);

	strdir.Format("%s//MarineDataFile//",dayTime);
	CreateDirectory(strdir,NULL);
	MarineDataFile.SetPath(strdir);

	strdir.Format("BMPFile//",dayTime);
	CreateDirectory(strdir,NULL);

	UpdateData(FALSE);
	//////////////////////////////////////////////////////////////////////////

	pDataPage.BPUpdateTime("����");
	//////////////////////////////////////////////////////////////////////////

	//����TCP�Ŀͻ���1
	SendSocket.Init(sendhost.Port,CABLE_NET_WMSG1);
	SendSocket.m_strNetpacket.pData = NULL;
	strcpy(SendSocket.m_szAddr,sendhost.HostIp);
	
	//����TCP�Ŀͻ���2
	RecvSocket.Init(recvhost.Port,CABLE_NET_WMSG2);
	RecvSocket.m_strNetpacket.pData = NULL;
	strcpy(RecvSocket.m_szAddr,recvhost.HostIp);

	//watchdog�Ŀͻ���3
	watchdogsock.Init(10010,CABLE_NET_WMSG3);
	watchdogsock.m_strNetpacket.pData = NULL;
	strcpy(watchdogsock.m_szAddr,recvhost.HostIp); 
	firstpacket = TRUE;
	SEND_FLAG=FALSE;
	//����UDP�㲥����

	//���ն�λ�������ݵ�UDP��

	sSocket[0].Init(POSITION_NET_PORT,POSITION_NET_WMSG);
	sSocket[0].m_strNetpacket.pData = NULL;
	//�����ط������ݵ�UDP��
	sSocket[1].Init(SAIL_NET_PORT1,NULL);
	sSocket[1].m_strNetpacket.pData = NULL;

	//���պ��п���ϵͳ���ݵ�UDP��
	sSocket[2].Init(SAIL_NET_PORT2,SAIL_NET_WMSG);
	sSocket[2].m_strNetpacket.pData = NULL;
	if((s1 = sSocket[0].CreateUDP())==SOCKET_ERROR)
	{
		int error=WSAGetLastError();
		LPSTR lpBuffer;
		char errbuf[256];
		FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER
			| FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			error,
			LANG_NEUTRAL,
			(LPTSTR)&lpBuffer,
		0,
		NULL );
		wsprintf(errbuf, "�붨λ������ͨ�Ŵ���ʧ��\nԭ��:  %d%s", error,lpBuffer);
		SaveRecord(errbuf);
	}
	else
	{
		SaveRecord("��λ���ݽ��ն˿ڿ����ɹ���");
	}
	if((s2=sSocket[1].CreateUDP())==SOCKET_ERROR)
	{
		int error=WSAGetLastError();
		LPSTR lpBuffer;
		char errbuf[256];
		FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER
			| FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			error,
			LANG_NEUTRAL,
			(LPTSTR)&lpBuffer,
		0,
		NULL );
		wsprintf(errbuf, "���ͺ������ݵ�����ͨ�Ŵ���ʧ��\nԭ��: %d%s", error,lpBuffer);
		SaveRecord(errbuf);
		AfxMessageBox("���ݽ����˿ڱ�ռ�ã���ر�����ͨ�ų��򲢵ȴ�3�����������");
		exit(1);
	}
	else
	{
// 		pStatic= (CStatic *)GetDlgItem(IDC_ADIO_STATE_LIGHT5);//
// 		pStatic->SetIcon(m_hIcon_Work);
		SaveRecord("�������ݷ��Ͷ˿ڿ����ɹ���");
		SEND_FLAG=TRUE;
	}
	if((s3=sSocket[2].CreateUDP())==SOCKET_ERROR)
	{
		int error=WSAGetLastError();
		LPSTR lpBuffer;
		char errbuf[256];
		FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER
			| FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			error,
			LANG_NEUTRAL,
			(LPTSTR)&lpBuffer,
		0,
		NULL );
		wsprintf(errbuf, "���պ������ݵ�����ͨ�Ŵ���ʧ��\nԭ��: %d%s", error,lpBuffer);
		SaveRecord(errbuf);
	}
	else
	{
// 		pStatic= (CStatic *)GetDlgItem(IDC_ADIO_STATE_LIGHT4);//
// 		pStatic->SetIcon(m_hIcon_Work);
		SaveRecord("�������ݽ��ն˿ڿ����ɹ���");
	}

	pDataPackage.Init();
	memcpy(UWACInitParam.TrainingSequence,Trainseq,32*sizeof(int));


}

void CACSDlg::OnButtonSysini() 
{
	// TODO: Add your control notification handler code here
	if (UWACInitParam.ADIOWorkMode==1)//�ӻ�
	{
		CWnd* pWnd = GetDlgItem(IDC_RADIO_MPSK);
		pWnd->EnableWindow(FALSE);
		
		int ButtonID[5]={IDC_BUTTON5,IDC_BUTTON6,IDC_BUTTON8,IDC_BUTTON10,IDC_BUTTON12};
		for (int i=0;i<5;i++)
		{
			pWnd = (CButton*)GetDlgItem(ButtonID[i]);
			pWnd->EnableWindow(FALSE);
		}
	}
	else
	{
		CButton* pWnd;
		int ButtonID[5]={IDC_BUTTON3,IDC_BUTTON4,IDC_BUTTON7,IDC_BUTTON9,IDC_BUTTON11};
		for (int i=0;i<5;i++)
		{
			pWnd = (CButton*)GetDlgItem(ButtonID[i]);
			pWnd->EnableWindow(FALSE);
		}
		pWnd = (CButton*)GetDlgItem(IDC_ENFORCE_SEND);
		pWnd->ShowWindow(TRUE);
		
	}
	NET_PACKET *netpacket;
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	if(netpacket==NULL)
	{
		AfxMessageBox("����NET_PACKET�ռ�����쳣��");
		return;
	}
	
	netpacket->FrmID = UWACPARA_SYSINT;
	netpacket->FrmLen = 32+sizeof(UWACINITPARA);

	netpacket->DestID = PC104ID+ADIOID+DSP01ID+DSP02ID+DSP11ID+DSP12ID;

	netpacket->HeadParam[0] = UWACPARA_SYSINT;//�������������壬��Ϊ0
	netpacket->HeadParam[1] = 1;//�ܰ���
	netpacket->HeadParam[2] = 0;//��ǰ����
	netpacket->HeadParam[3] = sizeof(UWACINITPARA);//�����ݳ���
	netpacket->HeadParam[4] = 0;
	netpacket->pData = (char *) malloc(sizeof(UWACINITPARA));
	memcpy(netpacket->pData,&UWACInitParam,sizeof(UWACINITPARA));
	m_WzdNetpacketList.AddTail(netpacket);
	SetEvent(IsNetpacketEvent);

	

}
UINT SendNetpacketProc(LPVOID pParam)
{
	CString str;
	str="�������緢���̡߳�\r\n";
#ifdef _DEBUG
					afxDump<< str;
#endif 
	
	CNetSocket *pSocket=(CNetSocket*)pParam;//�������
	BOOL bSend;
	NET_PACKET *netpacket;
	DWORD SentLen=0; //�Ѿ����͵��ܳ���
	DWORD SendingLen;//��ǰ�����͵ĳ���

	POSITION pos;	
	char *sendbuf = NULL;
	while(pSocket->m_bConnect)
	{
		if (m_WzdNetpacketList.IsEmpty())
			WaitForSingleObject(IsNetpacketEvent,INFINITE);//�ȴ��������ݣ�ÿ�δ������Ҫ��IsNetpacketEvent��λ
// 		SendNetpacketSync.Lock();
// 		bSend = (pSocket->m_bConnect) && (!m_WzdNetpacketList.IsEmpty());
// 		SendNetpacketSync.Unlock();
		//�����ݷ��Ͳ���socket��Ч
		SendNetpacketSync.Lock();
		if(!m_WzdNetpacketList.IsEmpty())
		{
			ResetEvent(IsNetpacketEvent);//�������¼���λ

			
			pos = m_WzdNetpacketList.GetHeadPosition();
			if(pos==NULL)
			{
				SendNetpacketSync.Unlock();
				continue;
			}
			netpacket = m_WzdNetpacketList.GetAt(pos);
			//��������
			SentLen=0;
			if( netpacket->FrmLen > MAXBUFFSIZE)
			{
				str = "���緢���������\r\n";
			}
	
			if(netpacket->FrmLen == 32)
			{
				SendingLen = send( pSocket->m_sSocket,
								   (char *)netpacket+SentLen,
								   netpacket->FrmLen-SentLen,0);
			}
			else
			{
				if (sendbuf!=NULL) 
				{
					free(sendbuf);
					sendbuf=NULL;
				}
				sendbuf = (char *) malloc(netpacket->FrmLen);
				memcpy(sendbuf,(char *)netpacket,32);
				memcpy(sendbuf+32,(char *)netpacket->pData,netpacket->FrmLen-32);
				SendingLen = send( pSocket->m_sSocket,
								   (char *)sendbuf+SentLen,
								   netpacket->FrmLen-SentLen,0);
				free(sendbuf);sendbuf=NULL;

			}
			if(SendingLen== SOCKET_ERROR)//����δ���
			{
				int err=WSAGetLastError();
				if (err!=WSAEWOULDBLOCK)
				{
					LPSTR lpBuffer;
					char errbuf[256];
					FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER
							| FORMAT_MESSAGE_FROM_SYSTEM,
						NULL,
						err,
						LANG_NEUTRAL,
						(LPTSTR)&lpBuffer,
						0,
						NULL );
					wsprintf(errbuf, "1����socket����ʧ��\r\nԭ��: %s\r\n", lpBuffer);
					SendNetpacketSync.Unlock();
					break;
				}
				Sleep(50);
//				else
//					SendMessage(hWnd,CABLE_NET_WMSG1,pSocket->m_sSocket,FD_READ);//change postmesssage to sendmessage
			}
			else 
			{
				SentLen+=SendingLen;
				str.Format("		1��ǰ�������ݳ���:%d\r\n",SendingLen);
				afxDump<<str;
			}
			if (pSocket->m_bConnect && (SentLen >= netpacket->FrmLen) && (SentLen!=0))
			{

				if ((netpacket->FrmID==UWACDATA_MODULATION_PHONEDATA)||(netpacket->FrmID==UWACCMD_SOUND_END)
					||(netpacket->FrmID==UWACCMD_SETTIME)||(netpacket->FrmID==UWACCMD_TCMSTART))
				{
					//ɾ�������
					pos = m_WzdNetpacketList.GetHeadPosition();
					if (pos!=NULL) 
					{
						if (netpacket->pData!=NULL) 
						{
							if(_CrtIsValidHeapPointer(netpacket->pData))
								free(netpacket->pData);
							netpacket->pData = NULL;
						}
						if (!m_WzdNetpacketList.IsEmpty())
						{
							m_WzdNetpacketList.RemoveAt(pos);//ɾ���б�ͷ��¼
						}
					}	
					ResetEvent(SendNetpacketEvent);//��λ���ź�
				}
				else//��ˮ����
				{
					DWORD	retr = WaitForSingleObject(SendNetpacketEvent,10000);
					if(retr==WAIT_TIMEOUT)
					{
						str = "1�ȴ�����Ӧ��ʱ\r\n";
						pos = m_WzdNetpacketList.GetHeadPosition();
						if (pos!=NULL) 
						{
							if ((netpacket!=NULL)&&(!m_WzdNetpacketList.IsEmpty()))//ָ�����
							{
								m_WzdNetpacketList.RemoveAt(pos);
								netpacket=NULL;
							}
						}
						SendMessage(hWnd,TIMEOUT_WMSG,NULL,NULL);
						ResetEvent(SendNetpacketEvent);//��λ���ź�
					}//�ȴ�Ӧ��ʱ�˳�
					else
					{//ɾ�������б����Ѿ����ͳɹ��������¼
						if (netpacket->pData!=NULL) 
						{
							if(_CrtIsValidHeapPointer(netpacket->pData))//debug only
							{
								free(netpacket->pData);
								
							}netpacket->pData = NULL;
						}
						
						if (!m_WzdNetpacketList.IsEmpty())
						{
							free(m_WzdNetpacketList.RemoveHead());
						}
						ResetEvent(SendNetpacketEvent);//��λ���ź�
					}//���յ�Ӧ��
				}
			}
		
		}//if(bSend)
	SendNetpacketSync.Unlock();
	}//while(pSocket->m_bConnect)
//	SendMessage(hWnd,CABLE_NET_WMSG1,pSocket->m_sSocket,FD_CLOSE);
	str =  "�˳����緢���̡߳�\r\n";
	afxDump<< str;
	return -1;
}
int CACSDlg::ReadNetSocket(SOCKET s,CNetSocket *sSocket)
{
	DWORD	RecvBytes;//ʵ���յ�������
	DWORD	len;//�Ѿ��յ�������
	len=sSocket->m_nRecvLen;
	CString str;
		//��һ�ν���һ������
	if(len<32){
			//�����ĳ���
			RecvBytes=recv(s,(char *)&(sSocket->m_strNetpacket)+len,32-len,0);
	
			if(RecvBytes==SOCKET_ERROR)
			{
				int err=WSAGetLastError();
				if (err==WSAEWOULDBLOCK)  return -2;
				LPSTR lpBuffer;
				char errbuf[256];
				FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER
						| FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,
					err,
					LANG_NEUTRAL,
					(LPTSTR)&lpBuffer,
					0,
					NULL );
				wsprintf(errbuf, "����socket����ʧ��\nԭ��(%d): %s\r\n",err, lpBuffer);
				SaveRecord(errbuf);
				return -1;

			}
			sSocket->m_nRecvLen+=RecvBytes;
			
		} //if(len<32)

		len=sSocket->m_nRecvLen;
		//��ȡ���ĳ��ȣ�����̬�������ջ�����
		if(len==32)
		{
			sSocket->m_nTotalLen = sSocket->m_strNetpacket.FrmLen;//��ȡ���������ݳ���
			if (sSocket->m_nTotalLen > MAXBUFFSIZE*2+32) {
				AfxMessageBox("��������������룬�������������磡");
				
				return -1;
			}
			if(sSocket->m_strNetpacket.pData!=NULL){
				free(sSocket->m_strNetpacket.pData);
				sSocket->m_strNetpacket.pData=NULL;
			}
			//��̬���뻺����
			if(sSocket->m_nTotalLen>32){
				sSocket->m_strNetpacket.pData = (char *)malloc(sSocket->m_nTotalLen-32);
				if(sSocket->m_strNetpacket.pData==NULL){
					int ret = GetLastError();
					AfxMessageBox("����������ն�̬����������");
					return -2;
				}
			}
		}//if(len==32)
		//��������
		if(len < sSocket->m_nTotalLen && len >= 32){
			RecvBytes=recv(s,sSocket->m_strNetpacket.pData+len-32,sSocket->m_nTotalLen-len,0);
	
			if(RecvBytes==SOCKET_ERROR)
			{
				int err=WSAGetLastError();
				if (err==WSAEWOULDBLOCK)  return -2;
				LPSTR lpBuffer;
				char errbuf[256];
				FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER
						| FORMAT_MESSAGE_FROM_SYSTEM,
					NULL,
					err,
					LANG_NEUTRAL,
					(LPTSTR)&lpBuffer,
					0,
					NULL );
				wsprintf(errbuf,"����socket����ʧ��\nԭ��: %s\r\n", lpBuffer);
				SaveRecord(errbuf);
				return -1;

			}
			str.Format("	��ǰ���ճ���:%d.\r\n",RecvBytes);
			sSocket->m_nRecvLen+=RecvBytes;
		}

	return 0;

}

//***************���������ͨ�ŵ���Ϣ������***********//
LRESULT CACSDlg::OnNetCableSocket1(WPARAM wParam,LPARAM lParam)
{
	//��������Ϣ���������Ҫ�ǽ��յ���������Ӧ��

	CNetSocket * sSocket ;
	int ExplainResult;//���ݰ��������
// 	static DWORD  DestID =0 ;//�ж��Ƿ���յ����е�Ӧ��
	CString str;
	CWnd* pWnd;
	sSocket = &SendSocket;

	CWinThread *pThr;
	if(WSAGETSELECTERROR(lParam))
	{
		SendSocket.Close();
		m_WzdNetpacketList.RemoveAll();
		ResetEvent(SendNetpacketEvent);//��λ���ź�			
		SetEvent(IsNetpacketEvent);//�����緢���߳����˳�

		{
			LPSTR lpBuffer;
			char errbuf[256];
			FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER
					| FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				WSAGETSELECTERROR(lParam),
				LANG_NEUTRAL,
				(LPTSTR)&lpBuffer,
				0,
				NULL );
			wsprintf(errbuf, "����ͨ��1����\nԭ��: %s", lpBuffer);
			SaveRecord(errbuf);
			m_bInit = FALSE;
			pWnd = GetDlgItem(IDC_BUTTON_START);
			pWnd->EnableWindow(TRUE);
		}
		
		return 0;
	}

	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
		if ( ReadNetSocket(wParam,&SendSocket) ==-1)
		{//��ȡ��������

			str="ͨ��1��������ʧ��!";
			SaveRecord(str);
			SendSocket.Close();
			RecvSocket.Close();
			m_WzdNetpacketList.RemoveAll();
			ResetEvent(SendNetpacketEvent);//��λ���ź�			
			SetEvent(IsNetpacketEvent);//�����緢���߳����˳�
		}
		//�ж����������Ƿ���յ����������ݰ�������������н���
		if(sSocket->m_nRecvLen >= sSocket->m_nTotalLen && sSocket->m_nRecvLen!=0){

			ExplainResult = ExplainAnsNetpacket(&sSocket->m_strNetpacket);//�Խ��յ����ݽ��н���
			//���ݽ�����Ľ�����ж��Ƿ���յ����е�Ӧ�������յ�����Ӧ������������һ������
			if(ExplainResult==-1){

				str = "1���յ���Ӧ�����";
				SaveRecord(str);
				SetEvent(SendNetpacketEvent);//��λ���źţ������͵ڶ�����Ϣ
				
			}
			if(ExplainResult==2){
				str = "1���յ���Ӧ������������";
				SaveRecord(str);
				// // InputRunRecord(str);

				SetEvent(SendNetpacketEvent);//��λ���źţ������͵ڶ�����Ϣ

			}
			if (ExplainResult==0) { //���յ�������ЧӦ��
				str = "���յ�������ЧӦ��";	
/*				SaveRecord(str);*/
				SetEvent(SendNetpacketEvent);//��λ���źţ������͵ڶ�����Ϣ
			}	
			//�ͷŶ�̬�ڴ�
			if(sSocket->m_strNetpacket.pData!=NULL){
				free(sSocket->m_strNetpacket.pData);
				sSocket->m_strNetpacket.pData=NULL;
			}
			//��λ����
			sSocket->m_nRecvLen=0;
			sSocket->m_nTotalLen = 0;
			//������յ���Ϊϵͳ��ʼ��Ӧ��
			if(sSocket->m_strNetpacket.HeadParam[0]==UWACPARA_SYSINT)
			{
			}
			//���û�н��յ���ʼ��Ӧ���򵯳��Ի�����ʾ��������
		}
		
		break;

	case FD_CONNECT:
		
//		m_WzdNetpacketList.RemoveAll();//�ͷ��б�	

		str = "�����ϵ��շ�����1�˿�5000";
		SaveRecord(str);
		SendSocket.m_bConnect=TRUE;
		if(wParam!=SendSocket.m_sSocket){
			SendSocket.m_sSocket=wParam;

		}

		// dTime1 = GetTickCount();
		//�����������������߳�
		ResetEvent(IsNetpacketEvent);//���緢���¼���λ
		pThr = AfxBeginThread(SendNetpacketProc,(LPVOID) &SendSocket,THREAD_PRIORITY_NORMAL,0,0,NULL);//���������������߳�
		if(pThr==NULL){

			str = "�����������ݷ����̳߳���";
			SaveRecord(str);
		}


		break;
	
	case FD_CLOSE:
		str = "�����ͨ��1������رգ�";
		pWnd = GetDlgItem(IDC_BUTTON_START);
		pWnd->EnableWindow(TRUE);
		SaveRecord(str);
		SendSocket.Close();
		m_WzdNetpacketList.RemoveAll();//�ͷ��б�
		SetEvent(IsNetpacketEvent);//�����緢���߳����˳�
		ResetEvent(SendNetpacketEvent);//��λ���ź�		
		OutVoiceCycleMem->Empty();
		InVoiceCycleMem->Empty();
		WaveCycleMem->Empty();
		break;
	case FD_WRITE:
// 		str = "���Ը�ͨ�Ż��������ݣ�";
// 		SaveRecord(str);
		break;


	}
	return -1;
}

LRESULT CACSDlg::OnNetCableSocket2(WPARAM wParam,LPARAM lParam)
{
	//��ȡ����ӵ�������������

	CNetSocket * sSocket ;
	int ExplainResult;//���ݰ��������
	DWORD SentLen;
	DWORD SendingLen;
	LPSTR lpBuffer;
	char errbuf[256];
	int err;
	CString str;
	CWnd* pWnd;
	NET_PACKET sendpacket = {UWACCMD_ANS,32,ADIOID,{0,RESULT_RIGHT,0,0,0},NULL};//Ӧ����������ʼ��


	sSocket = &(RecvSocket);
//	TRACE("OnNetCableSocket2\n");
	if(WSAGETSELECTERROR(lParam))
	{
		RecvSocket.Close();
		{

			FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER
					| FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				WSAGETSELECTERROR(lParam),
				LANG_NEUTRAL,
				(LPTSTR)&lpBuffer,
				0,
				NULL );
			wsprintf(errbuf, "����ͨ��2����\nԭ��: %s", lpBuffer);
//			SaveRecord(errbuf);
			m_bInit = FALSE;
			pWnd = GetDlgItem(IDC_BUTTON_START);
			pWnd->EnableWindow(TRUE);
		}
		
		return 0;
	}

	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
		if ( ReadNetSocket(wParam,&RecvSocket) ==-1){
			str = "	������ͨ��2���ݳ���\r\n";
			SaveRecord(str);
			RecvSocket.Close();
		}
		//�ж����������Ƿ���յ����������ݰ�������������н���
		if(sSocket->m_nRecvLen >= sSocket->m_nTotalLen && sSocket->m_nRecvLen>=32)
		{
			
			
			ExplainResult = ExplainNetpacket(&sSocket->m_strNetpacket);//�Խ��յ����ݽ��н���
			memcpy(lastpacket,sSocket->m_strNetpacket.pData,sSocket->m_strNetpacket.FrmLen-32);
			//���ݽ�����Ľ����������ͬ��Ӧ��
			if (ExplainResult==UWACCMD_ADIOREQUEST) //��UWACCMD_ADIOREQUEST���������
			{
				//////////////////////////////////////////////////////////////////////////
				LBLStatus = FALSE;//��ʼͨ������
				if (hyLPT)
				{
					if (!UWACInitParam.ADIOWorkMode)
					{
						LPT_Writedata(hyLPT,0xF9);  //B0_DQ=1 ,�ͷ�DQ�ߣ�B6_DQ=1������B6
					}
					
				}
				
				
				//////////////////////////////////////////////////////////////////////////
				unsigned char *buf;
				int len=0;
				sendpacket.HeadParam[0] = sSocket->m_strNetpacket.FrmID;
				//�γɷ������ݰ�
				if (UWACInitParam.XMTModulation==MFSKMOD)//MFSKģʽ
				{
					if (!UWACInitParam.ADIOWorkMode)
					{
						SetTimer(LBLTIMER,UWACInitParam.SyncConcurrence*4*1000+2000,NULL);//��ʼͨ�����ڼ�ʱ
					}
					
					float nbits = UWACInitParam.XMTPackageNum*UWACInitParam.XMTPackFramNum
						*UWACInitParam.MFSKDataSymbolNum*30;//������
					len = ceilf(nbits/8);//�ֽ���=bit/8��1��4��������ֶ���
					len +=32;
					buf = (unsigned char *)malloc(len);
					sendpacket.FrmLen = len;
					sendpacket.HeadParam[1] = 1;
					sendpacket.HeadParam[2] = 0;
					sendpacket.HeadParam[3] = len-32;
					sendpacket.HeadParam[4] = MFSKMOD;
					memcpy(buf,(unsigned char *)&sendpacket,32);//������������ͷ��ʽ
					memset((unsigned char *)buf+32,0,len-32);//����ȫ��
					if (UWACInitParam.ADIOWorkMode)//�ӻ�������
					{
						PackageShipData((unsigned char *)buf+32,len-32);
					} 
					else//
					{
//						PackageShipData((unsigned char *)buf+32,len-32);
						PackageUWAData((unsigned char *)buf+32,len-32);
					}
					str.Format("������ѧ���ݣ�����:%d",len);
					
					SaveRecord(str);

				}//if (UWACInitParam.XMTModulation==MFSKMOD)//MFSKģʽ
				else if(UWACInitParam.XMTModulation==MPSKMOD)//MPSK
				{
					if (!UWACInitParam.ADIOWorkMode)
					{
						SetTimer(LBLTIMER,UWACInitParam.SyncConcurrence*5*1000+2000,NULL);//��ʼͨ�����ڼ�ʱ
					}
					
					len = UWACInitParam.XMTMPSKPackageNum*UWACInitParam.XMTMPSKPackFramNum
						*UWACInitParam.MPSKDataSymbolNum*2/8;//�ֽ�
					len +=32;
					buf = (unsigned char *)malloc(len);
					sendpacket.FrmLen = len;
					sendpacket.HeadParam[1] = 1;
					sendpacket.HeadParam[2] = 0;
					sendpacket.HeadParam[3] = len-32;
					sendpacket.HeadParam[4] = MPSKMOD;
					memcpy(buf,(unsigned char *)&sendpacket,32);//������������ͷ��ʽ
					memset((unsigned char *)buf+32,0,len-32);//����ȫ��
					PackagePicture((unsigned char *)buf+32,len-32);
					SaveRecord("����ͼƬ����!");
					OnRadioMfsk();

				}
				else if(UWACInitParam.XMTModulation==OPSKMOD)//8PSK
				{
					if (!UWACInitParam.ADIOWorkMode)
					{
						SetTimer(LBLTIMER,UWACInitParam.SyncConcurrence*5*1000+2000,NULL);//��ʼͨ�����ڼ�ʱ
					}
					
					len = UWACInitParam.XMTMPSKPackageNum*UWACInitParam.XMTMPSKPackFramNum
						*UWACInitParam.MPSKDataSymbolNum*1.5*2/8;//�ֽ�
					len +=32;
					buf = (unsigned char *)malloc(len);
					sendpacket.FrmLen = len;
					sendpacket.HeadParam[1] = 1;
					sendpacket.HeadParam[2] = 0;
					sendpacket.HeadParam[3] = len-32;
					sendpacket.HeadParam[4] = OPSKMOD;
					memcpy(buf,(unsigned char *)&sendpacket,32);//������������ͷ��ʽ
					memset((unsigned char *)buf+32,0,len-32);//����ȫ��
					PackagePictureIn8psk((unsigned char *)buf+32,len-32);
					SaveRecord("����ͼƬ����8PSK!");
					OnRadioMfsk();
					
				}
				else//FH
				{
					if (!UWACInitParam.ADIOWorkMode)
					{
						SetTimer(LBLTIMER,UWACInitParam.SyncConcurrence*4*1000+2000,NULL);//��ʼͨ�����ڼ�ʱ
					}
					
					len = 8;//Ĭ�ϳ���
					len +=32;
					buf = (unsigned char *)malloc(len);
					memset(buf,0,8*sizeof(unsigned char));
					sendpacket.FrmLen = len;
					sendpacket.HeadParam[1] = 1;
					sendpacket.HeadParam[2] = 0;
					sendpacket.HeadParam[3] = len-32;
					sendpacket.HeadParam[4] = FHMOD;
					memcpy(buf,(unsigned char *)&sendpacket,32);//������������ͷ��ʽ
					memset((unsigned char *)buf+32,0,len-32);//����ȫ��
					m_fhstring = m_fhstring.Left(8);  //ȡǰ8���ֽ�
					memcpy((unsigned char *)buf+32,m_fhstring,m_fhstring.GetLength());

					str.Format("������Ƶ���ݣ�����:%d",len);
					OnRadioMfsk();
					
					SaveRecord(str);
				}
				
				SendingLen = send( (SOCKET)wParam,(char *)buf,len,0);
				if(SendingLen== SOCKET_ERROR)
				{
					err=WSAGetLastError();
					if (err!=WSAEWOULDBLOCK)
					{
						FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER
								| FORMAT_MESSAGE_FROM_SYSTEM,
								NULL,
								err,
								LANG_NEUTRAL,
								(LPTSTR)&lpBuffer,
								0,
								NULL );
						wsprintf(errbuf, "����socket2����ʧ��\nԭ��: %s", lpBuffer);
						SaveRecord(errbuf);
					}
				}
				str.Format("��ʼ������ѧ���ݣ�����:%d",SendingLen);
				OnRadioMfsk();
				if (buf)
				{
					free(buf);
				}
				
			}//if (ExplainResult==UWACCMD_ADIOREQUEST)
			else//�γ����ݰ������͸�PC104��ΪӦ��
			{	
				if(ExplainResult==-1)
				{
					str.Format("2���յ�����%X���ܽ�����",sSocket->m_strNetpacket.FrmID);
					SaveRecord(str);
				}
				sendpacket.HeadParam[0] = sSocket->m_strNetpacket.FrmID;
				SentLen=0;
				//���ݲ�ͬ�����������ͬ��Ӧ��
				while(SentLen < sendpacket.FrmLen)
				{

					SendingLen = send( (SOCKET)wParam,
									   (char *)&sendpacket+SentLen,
									   sendpacket.FrmLen-SentLen,0);
// 					str.Format("����������Ӧ����sendpacket.Id = %x",sendpacket.FrmID);
// 					SaveRecord(str);
					if(SendingLen== SOCKET_ERROR)
					{
						err=WSAGetLastError();
						if (err!=WSAEWOULDBLOCK)
						{
							FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER
									| FORMAT_MESSAGE_FROM_SYSTEM,
									NULL,
									err,
									LANG_NEUTRAL,
									(LPTSTR)&lpBuffer,
									0,
									NULL );
							wsprintf(errbuf, "����socket2����ʧ��\r\nԭ��: %s\r\n", lpBuffer);
//							SaveRecord(errbuf);
						}
					}
					else
					{
						str.Format("	2��ǰ���ͳ���:%d.\r\n",SendingLen);
						SentLen+=SendingLen;
					}
				
				}//��������while(SentLen < sendpacket.FrmLen)
			}//�ж�Ϊ��ȷ���ݰ�
			if (sendpacket.pData!=NULL) 
			{
				free(sendpacket.pData);
				sendpacket.pData = NULL;
			}

			//�ͷŶ�̬�ڴ�
			if(sSocket->m_strNetpacket.pData!=NULL)
			{
				if (_CrtIsValidHeapPointer(sSocket->m_strNetpacket.pData))
				{
					free(sSocket->m_strNetpacket.pData);
				}
				sSocket->m_strNetpacket.pData=NULL;
			}
			//��λ����
			sSocket->m_nRecvLen=0;
			sSocket->m_nTotalLen = 0;			
		}//�ж��Ƿ�Ϊ�������ݰ�

		break;

	case FD_CONNECT:
		m_WzdNetpacketList.RemoveAll();
		if(wParam!=RecvSocket.m_sSocket)
		{
			RecvSocket.m_sSocket=wParam;

		}
		RecvSocket.m_bConnect=TRUE;
		str="�����ϵ��շ�����2�˿�5001";
		SaveRecord(str);
		break;
	case FD_CLOSE:
		RecvSocket.Close();
		str = "�����ͨ��2������رգ�";
		SaveRecord(str);
		m_bInit = FALSE;
		pWnd = GetDlgItem(IDC_BUTTON_START);
		pWnd->EnableWindow(TRUE);
		OutVoiceCycleMem->Empty();
		InVoiceCycleMem->Empty();
		WaveCycleMem->Empty();
		break;
	case FD_WRITE:
		str = "���Ը����շ������ݣ�";
//		SaveRecord(str);
		break;
	}
	return -1;
}
LRESULT CACSDlg::OnNetCableSocket3(WPARAM wParam,LPARAM lParam)
{


	LPSTR lpBuffer;
	char errbuf[256];
	int err;
	CString str;

	if(WSAGETSELECTERROR(lParam))
	{
		watchdogsock.Close();
		{

			FormatMessage( FORMAT_MESSAGE_ALLOCATE_BUFFER
					| FORMAT_MESSAGE_FROM_SYSTEM,
				NULL,
				WSAGETSELECTERROR(lParam),
				LANG_NEUTRAL,
				(LPTSTR)&lpBuffer,
				0,
				NULL );
			wsprintf(errbuf, "����watchdog���ɹ�\nԭ��: %s", lpBuffer);
			SaveRecord(errbuf);
			m_bInit = FALSE;
			if(!SendSocket.m_bConnect)//���ȴ���ֱ������
			{
				SendSocket.CreateClient();
		
			}
			
			if(!RecvSocket.m_bConnect)
			{
				RecvSocket.CreateClient();
		
			}
		}
		
		return 0;
	}

	switch(WSAGETSELECTEVENT(lParam))
	{
	case FD_READ:
		break;

	case FD_CONNECT:
		str="������watchdog�˿�10010";
		SaveRecord(str);
		watchdogsock.Close();
		Sleep(3000);//�ȴ�soft_reset�ɹ�������ADIO���ܻ���ز��ɹ�
		if(!SendSocket.m_bConnect)
		{
			SendSocket.CreateClient();
	
		}
		
		if(!RecvSocket.m_bConnect)
		{
			RecvSocket.CreateClient();
	
		}
		break;
	case FD_CLOSE:
		break;
	case FD_WRITE:
		break;
	}
	return -1;
}
LRESULT CACSDlg::ExplainAnsNetpacket(NET_PACKET * pNetpacket)
{
	POSITION pos;		//��ȡ�����б���ͷ�������ָ��λ��
	NET_PACKET * pHeadNet;//��ȡ��ǰӦ���Ӧ�Ŀ�������

	CString str;

	int datalen =0;;

	if(pNetpacket->FrmID != UWACCMD_ANS) 
	{
		str="��PC104���յ�Ӧ��ID�����������鿴��\r\n";
		return -1;

	}

	//�ж��Ƿ�Ϊ��ǰ�����Ӧ��
// 	pos = m_WzdNetpacketList.GetHeadPosition();		//�õ���ǰ�����ID
// 	if (pos==NULL)
// 	{//�������������
// 		str = "Ӧ����ܳ�ʱ�����������Ѿ���գ�";
// 		SaveRecord(str);
// 		return -1;			
// 	}

// 	pHeadNet = m_WzdNetpacketList.GetAt(pos);
// 	if (pNetpacket->HeadParam[0]!= pHeadNet->FrmID) 
// 	{
// 		str = "Ӧ���ǵ�ǰ���������Ӧ�������鿴��";
// 		SaveRecord(str);
// 	}

	//Ϊ��������Ӧ��
	if (pNetpacket->FrmLen==32) 
	{
		if(pNetpacket->HeadParam[0]==UWACPARA_SYSINT)
		{
			if (pNetpacket->HeadParam[1]==RESULT_RIGHT)
			{
				if (pNetpacket->DestID & ADIOID)
				{
					SaveRecord("ͨ�Ż������ɹ�!");
					SetTimer(NETLINKTIMER,6000,NULL);
					CWnd* pWnd = GetDlgItem(IDC_BUTTON_START);
					pWnd->EnableWindow(FALSE);
					SetTime();
					StartTCM2();
					Sleep(500);
					StartDsp();
					StartAdio();
					Sleep(100);
					OnDigitalXmtSet();
					Sleep(100);
					OnButtonXmtset();
					//��ʼ������������
					if (!nHaveStart)
					{
						m_PlayMMSound->PostThreadMessage( WM_PLAYMMSOUND_PLAYSOUNDPTR ,0,(LPARAM)m_PlayThread);
						m_PlayMMSound->PostThreadMessage(WM_PLAYMMSOUND_PLAYFILE,0,(LPARAM)"sound.wav");//��ʼ�����߳�
						nHaveStart = 1;//��ֻ֤����һ�β����߳�
					}
				}
				else 
				{
					
						SaveRecord("ͨ�Ż���ʼ����ʱ!����������ͨ�Ż�");
				}
				
			}
		}
	}//if (pNetpacket->FrmLen==32)
	else
	{//Ӧ��Ϊ���������
		switch(pNetpacket->HeadParam[0]) 
		{
			case UWACCMD_READMEM://	���ڴ�	
				datalen = pNetpacket->FrmLen-32;
				str.Format("��PC104���յ�AD���ݣ�����Ϊ%d��\r\n",datalen);
				break;
			case UWACCMD_BIT://	�Լ�����	
				break;
				return 0;
			default:
				return 0;
		}
	}
	return 0;
}
int CACSDlg::ExplainNetpacket(NET_PACKET *pNetpacket)
{
	DWORD DataNum;		//pc104����������ݰ��е�С���������
	DWORD DataLen;		//С������
	DWORD StartAddr=0;		//��ȡ���ݵ���ʼ��ַ
	CString    str;
	typedef	struct{//AD����ͷ
		int id;
		int adlenth;
	}ADDATAHEAD;
	ADDATAHEAD* paddatahead;
	int m_addatanum;
	DWORD endrecord;
	LinkStatus =TRUE;
	switch(pNetpacket->FrmID)
	{
	case  UWACDATA_MIXDATA://Ϊ������ݰ�
		for(DataNum = pNetpacket->HeadParam[4]; DataNum >0; DataNum--)
		{
			DataLen = *((DWORD *)((char *)(pNetpacket->pData)+StartAddr)+1);

			switch(*(DWORD *)((char *)(pNetpacket->pData)+StartAddr)) 
			{
			case UWACDATA_FH_DATA:
				ExplainRecData((BYTE *)(pNetpacket->pData)+StartAddr+8,DataLen-8,FHMOD);
				break;
			case UWACDATA_DECRESULT://�������������ݽ��
				if (((DataLen-8==52)&&(DemodulationMod==MFSKMOD))||((DataLen-8==248)&&(DemodulationMod==MPSKMOD)))
				{
					ExplainRecData((BYTE *)(pNetpacket->pData)+StartAddr+8,DataLen-8,DemodulationMod);
				}
				else if (DataLen-8==52)
				{
					ExplainRecData((BYTE *)(pNetpacket->pData)+StartAddr+8,DataLen-8,MFSKMOD);
				}
				else if (DataLen-8==248)
				{
					ExplainRecData((BYTE *)(pNetpacket->pData)+StartAddr+8,DataLen-8,MPSKMOD);
				}
				else
				{
					str.Format("�յ��ı������ݳ��Ȳ��ԣ�Ϊ%d��\r\n",DataLen-8-4);
					SaveRecord(str);
				}
				break;
			case UWACDATA_D2OUT://�������������
				if (DataLen-8==1936*2*4+4)//����δ��
				{
					SaveEoutData((BYTE *)(pNetpacket->pData)+StartAddr+8,DataLen-8);
				}
				else
				{
					str.Format("�յ��ľ��ⳤ�Ȳ��ԣ�Ϊ%d��\r\n",DataLen-8-4);
					SaveRecord(str);
				}
				break;
			case UWACDATA_SAMDATA: //��ADIO�ϴ���AD����ԭʼ����
//				m_addatanum =AdSamplePage.m_samplerate*AdSamplePage.m_sampletime*1000*channum*2;//channumͨ����16λ��2���ֽ�,�����ʵ�λΪK
				if(m_bADWaveEnable==TRUE)//����Ѿ�������ϣ����յ���������
					break;
				endrecord=END_RECORD_FLAG;//��¼������־
				paddatahead=(ADDATAHEAD*)malloc(sizeof(ADDATAHEAD));//���붯̬�ռ����ݿ�ͷ												
				if(paddatahead==NULL){
					AfxMessageBox("ADDATAHEAD�����ڴ����");
					exit(EXIT_FAILURE);
				}
				paddatahead->id=UWACDATA_SAMDATA;
				paddatahead->adlenth=DataLen-8;
			
				//�����ݴ���
				ADFile.SaveFile((char *)paddatahead, sizeof(ADDATAHEAD));//���ݿ�ͷ
				if(paddatahead!=NULL){//�ͷŶ�̬�ռ����ݿ�ͷ
					free(paddatahead);
				}
				ADFile.SaveFile((char *)(pNetpacket->pData)+StartAddr+8, DataLen-8);//���ݿ�����
				//���в�����ʾ////////////////////////////////////////////////////////////
				if(m_nRawDataLen + DataLen-8 > SAMPLINGNUBER*8*sizeof(short))//����һҳ��ʾ����
				{
					memcpy((char*)m_pRawData,(char*)m_pRawData+DataLen-8+m_nRawDataLen-SAMPLINGNUBER*8*sizeof(short),
						SAMPLINGNUBER*8*sizeof(short)-(DataLen-8));
					memcpy((char*)m_pRawData+SAMPLINGNUBER*8*sizeof(short)-(DataLen-8),
						(char *)(pNetpacket->pData)+StartAddr+8,DataLen-8);
					m_nRawDataLen = SAMPLINGNUBER*8*sizeof(short);					
				}
				else//
				{
					memcpy((char*)m_pRawData+m_nRawDataLen,
						(char *)(pNetpacket->pData)+StartAddr+8,DataLen-8);
					m_nRawDataLen += DataLen-8;
				}
				AdSamplePage.UpdateView(m_pRawData);
				//////////////////////////////////////////////////////////////////////////
				Save_len+=(DataLen-8);//���յ������ݼ���

				if(Save_len>=m_addatanum)
				{//�Ѿ�����������>=Ԥ�������� ���������
					Save_len=0;//���յ������ݼ�������
					m_nRawDataLen = 0;
					ADFile.SaveFile((char*)&endrecord, sizeof(__int64));
					ADFile.CloseFile();
					str="AD����ֹͣ\r\n";	
					AfxMessageBox(str);
					SaveRecord(str);
				}
				break;

			case UWACCMD_BIT:			
				if(*(DWORD *)((char *)(pNetpacket->pData)+StartAddr+8+12)!=0x0000 || *(DWORD *)((char *)(pNetpacket->pData)+StartAddr+8+12+4)!=0x0000)
				{
					AfxMessageBox("SDRAM�Լ����쳣���¶ȴ������Լ����쳣");
//					OnCmdResetADIO();
				}
				else
				{

					SaveRecord("ϵͳ�Լ�����!");

				}
				break;	
			case UWACDATA_ADIOSTATE: //ADIO״̬����
				if(sizeof(ADIOSTATUS)==DataLen-8)
				{
					memcpy((char *)&ADIOStatus,(char *)(pNetpacket->pData)+StartAddr+8, DataLen-8);
					SetADIOStatusIndicatior(ADIOStatus.States);
					str="UWACDATA_ADIOSTATE\r\n";
				}

				break; 
			case UWACDATA_DEMODULATION_PHONEDATA://ˮ���绰�������
				if (!m_bInit)//δ��ʼ��
				{
					m_bInit =TRUE;
					str = "��ʼ����ˮ������!";
					SaveRecord(str);

				}
				
				CCycleMemSync.Lock();
				
				InVoiceCycleMem->WriteData(((char *)(pNetpacket->pData)+StartAddr+8),(DataLen-8));
				WaveCycleMem->WriteData(((char *)(pNetpacket->pData)+StartAddr+8),(DataLen-8));
				CCycleMemSync.Unlock();
				SetEvent(RecvNetpacketEvent);
				//�����ݴ���

 				RECVVoiceFile.SaveFile((char *)(pNetpacket->pData)+StartAddr+8, DataLen-8);//���ݿ�����
				break;
			case UWACDATA_SENSORDATA://ADIO�¶�ѹ����ѹ���ݽ��
				
				if(sizeof(SYSTEMSENSORDATA)==DataLen-8)
				{
					memcpy((char *)&SystemSensorData,(char *)(pNetpacket->pData)+StartAddr+8, DataLen-8);
					SystemSensorData.Pressure *= 10.0/2048/5*2000;  //2048=10V, 5V=2000m
					SystemSensorData.VoltageP5*= 10.0/2048;  //2048=10V
					SystemSensorData.VoltageN5*= 10.0/2048;  //2048=10V
					SystemSensorData.VoltageP12*= 2.0422*10.0/2048;  //AD:2048=10V, +12V����2.0422:1��ѹ,
					SystemSensorData.VoltageN12*= 2.0327*10.0/2048;  //AD:2048=10V, -12V����2.0327:1��ѹ
					UpdateSensorData(&SystemSensorData);
				}
				else
				{
					str="�յ�UWACDATA_SENSORDATA,���ݳ��ȴ���\r\n";
					SaveRecord(str);
				}
				
				break; 
			case UWACDATA_PROCESS_PARA://ͨ�Ų���
				if(sizeof(COMMUNICATIONPARAM)==DataLen-8)
				{
					memcpy((char *)&CommunicationParam,(char*)(pNetpacket->pData)+StartAddr+8,sizeof(COMMUNICATIONPARAM));
					SaveCommData((char *)&CommunicationParam);
				}
				else
				{
					str="ͨ�Ų���,���ݳ��ȴ���";
					SaveRecord(str);
				}
				break;
			case UWACCMD_DEMODULATION_MOD://�����������
				if(*(DWORD *)((char *)(pNetpacket->pData)+StartAddr+8)==0x55)
				{

					DemodulationMod =MFSKMOD;
				}
				else if(*(DWORD *)((char *)(pNetpacket->pData)+StartAddr+8)==0xaa)
				{
					DemodulationMod =MPSKMOD;
				}
				else
				{
					DemodulationMod =MFSKMOD;
				}

				break;
			case UWACDATA_TCM2DATA://TCM2�ɼ�����
				memcpy((char *)&tcmdata,(char *)(pNetpacket->pData)+StartAddr+8, DataLen-8);

				if(tcmdata.error_code==0)
				{
					str.Format("%.2f��",tcmdata.pitch);
					pComParamPage.SetDlgItemText(IDC_BIN_PITCH,str);
					str.Format("%.2f��",tcmdata.roll);
					pComParamPage.SetDlgItemText(IDC_BIN_ROLL,str);
				}
			
				else
				{
					str.Format("E %.2f��",tcmdata.pitch);
					pComParamPage.SetDlgItemText(IDC_BIN_PITCH,str);
					str.Format("E %.2f��",tcmdata.roll);
					pComParamPage.SetDlgItemText(IDC_BIN_ROLL,str);

				}
				
				break;
			default:
				if(((*(DWORD *)((char *)(pNetpacket->pData)+StartAddr)) & 0x70000000)!=0x70000000)  //�Ƿ���ID
				{
					str.Format("��ϰ��յ��Ƿ���ID:%x",*(DWORD *)((char *)(pNetpacket->pData)+StartAddr));
					SaveRecord(str);
					str.Format("��ϰ���:%d",pNetpacket->HeadParam[4]);
					SaveRecord(str);
					str.Format("��ϰ�����:%d",pNetpacket->FrmLen);
					SaveRecord(str);
					str.Format("StartAddr����:%d",StartAddr);
					return -1;

				}

				str.Format("��ϰ��յ��޷�������ID:%x",*(DWORD *)((char *)(pNetpacket->pData)+StartAddr));
				SaveRecord(str);
				str.Format("��ϰ���:%d",pNetpacket->HeadParam[4]);
				SaveRecord(str);
				str.Format("��ϰ�����:%d",pNetpacket->FrmLen);
				SaveRecord(str);
				str.Format("StartAddr����:%d",StartAddr);
				return -1;
			}
			StartAddr += DataLen;
			
		}//for(DataNum = pNetpacket->HeadParam[4]; DataNum >0; DataNum--)
		return 0;
		break;

	case UWACCMD_ADIOREQUEST://ADIO����������
		str="ADIO��������";
		SaveRecord(str);
		return UWACCMD_ADIOREQUEST;//Ҫ������������ݵ�Ӧ���
		break;

	case UWACDATA_BIT://�����Լ�������
		str="�����Լ������\r\n";
		// InputRunRecord(str);

		if(pNetpacket->HeadParam[0]==SELFCHECK_FALSE || pNetpacket->HeadParam[2]==SELFCHECK_FALSE)
		{
			if(IDOK==AfxMessageBox("�����Լ����������ͨ�Ż�!"))
				return -1;						
		}
		else{
			str="�����Լ�����ȷ!";

		SaveRecord(str);
		if((SendSocket.m_bConnect)&&(RecvSocket.m_bConnect))
		{
			OnButtonSysini();
			SaveRecord("��ʼ��ʼ��ϵͳ!");
		}

		}
		pNetpacket->FrmID = UWACDATA_MIXDATA;
//		return UWACDATA_BIT;
		break;
	default:
		if((pNetpacket->FrmID & 0x70000000)!=0x70000000)  //�Ƿ���ID
		{
			str.Format("�յ��Ƿ�ID:%x",pNetpacket->FrmID);
			SaveRecord(str);
			return -1;
		}
			
		//�Ϸ�����ǰ�汾����ʶ���ID
		str.Format("�յ�����ʶ���ID:%x",pNetpacket->FrmID);
		SaveRecord(str);
		break;
	}//switch(pNetpacket->FrmID)
	
	return 0;
	
}
void CACSDlg::ExplainRecData(BYTE *databuf, int len, int ntype)
{
	if (UWACInitParam.ADIOWorkMode&&bFirstRecvData&&UsblEnableCheck)
	{
		SetTimer(USBLENABLE,UWACInitParam.SyncConcurrence*1000*(CIRCLENUM-1),NULL);
	}

	switch (ntype)
	{
	case MFSKMOD://FSK
		if (UWACInitParam.ADIOWorkMode&&bFirstRecvData)
		{
			//����¼������led
			m_LED.LoadBitmaps(IDB_OFF,NULL,NULL,NULL);
			m_LED.SubclassDlgItem(IDB_OFF,this);
			m_LED.SizeToContent();
			m_LED.Invalidate(TRUE);
			
			SetTimer(VOICEENABLE,8000*4,NULL);
		}
		bFirstRecvData = FALSE;

		ExplainFSKData(databuf,len);
		break;
	case MPSKMOD://PSK
		if (UWACInitParam.ADIOWorkMode&&bFirstRecvData)
		{
			//����¼������led
			m_LED.LoadBitmaps(IDB_OFF,NULL,NULL,NULL);
			m_LED.SubclassDlgItem(IDB_OFF,this);
			m_LED.SizeToContent();
			m_LED.Invalidate(TRUE);
			RECVMPSK = true;
			SetTimer(VOICEENABLE,8000*5,NULL);
		}
		bFirstRecvData = FALSE;
		ExplainPSKData(databuf,len);
 		break;
	case FHMOD://FH
// 		if (UWACInitParam.ADIOWorkMode&&bFirstRecvData)
// 		{
// 			//����¼������led
// 			m_LED.LoadBitmaps(IDB_OFF,NULL,NULL,NULL);
// 			m_LED.SubclassDlgItem(IDB_OFF,this);
// 			m_LED.SizeToContent();
// 			m_LED.Invalidate(TRUE);
// 		
// 			
// 			SetTimer(VOICEENABLE,8000*1,NULL);
// 		}
		bFirstRecvData = FALSE;
		ExplainFHData(databuf,len);
		break;
	default:
		break;
	}

}
void CACSDlg::OnCmdResetADIO() 
{
	NET_PACKET *netpacket;
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	if(netpacket==NULL){
		AfxMessageBox("����NET_PACKET�ռ�����쳣��");
	}
	
	netpacket->FrmID = UWACCMD_RESETADIO;
	netpacket->FrmLen = 32;
	netpacket->DestID = PC104ID;
	netpacket->pData = NULL;
	
	m_WzdNetpacketList.AddTail(netpacket);
	SetEvent(IsNetpacketEvent);
	
}

void CACSDlg::OnButtonSave() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	CString str;
	str.Format("%d",m_Gain);
	FILE* pf;
	if((pf=fopen(iniFileName.GetBuffer(0),"r"))==NULL)
	{
		return;
	}
	fclose(pf);

	WritePrivateProfileString("sysparam","XMTChannel",m_strXmtChannel,iniFileName);
	WritePrivateProfileString("sysparam","RecvGain",str,iniFileName);
	str.Format("%f",m_Amp);
	WritePrivateProfileString("sysparam","XMTAMP",str,iniFileName);
//	AfxMessageBox("��������ɹ���");
}

void DLLCALLCONV LPT_IntAHandlerRoutine(LPT_HANDLE hLPT, LPT_IntA_RESULT *intResult)
{

}

void CACSDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	CStatic *pStatic;
//	pStatic= (CStatic *)AfxGetApp()->m_pMainWnd->GetDlgItem(IDC_STATIC_status);//voice record indication light
	BYTE nControl;
	BYTE statebit4;
	int nRet = 0;
	switch(nIDEvent) 
	{
	case LPTREADCONTROLTIMER://����ӡ��״̬�Ĵ���״̬
		nControl = LPT_Readstatus(hyLPT);
		statebit4 =  (nControl&0x10)>>4;
		if((RecordState==statebit4))
			RecordCount = 0;
		else{//״̬��������
			RecordCount++;
			if(RecordCount>=3)
			{//״̬�ȶ�
				RecordCount = 0;
				RecordState = statebit4;
				if((RecordState==RECORDWORK))
				{
					SetTimer(VOICERECORDREADTIMER,100,NULL);//����¼��׼��
				}
				else
				{
					//ֹͣ¼��
					KillTimer(VOICERECORDREADTIMER);
					
//					OutVoiceCycleMem->Empty();
//					pStatic->SetIcon(m_hIcon_Wait);
//					m_bRecordLightWork=FALSE;		//�������Ƿ���˸
					m_RecordThread->PostThreadMessage(WM_RECORDSOUND_STOPRECORDING, 0, 0L);
					AfxGetApp()->m_pMainWnd->SetDlgItemText(IDC_BUTTON1,"��ʼ¼��");
					SaveRecord("����¼������");
					m_LED.LoadBitmaps(IDB_ON,NULL,NULL,NULL);
					m_LED.SubclassDlgItem(IDB_ON,this);
					m_LED.SizeToContent();
					m_LED.Invalidate(TRUE);
					if (LBLStatus)//LBL���ڹ���
					{
						if (!UWACInitParam.ADIOWorkMode)
						{
							LPT_Writedata(hyLPT,0xB9);  //B0_DQ=1 ,�ͷ�DQ�ߣ�B6_DQ=0,����B6
						}
						
					
					} 
					else//����ͨ��
					{
						if (!UWACInitParam.ADIOWorkMode)
						{
							LPT_Writedata(hyLPT,0xF9);  //B0_DQ=1 ,�ͷ�DQ��,B6_DQ=1
						}
						
						
					}
					m_nRecTime=0;

				}
			}
		}

		break;

	case VOICERECORDREADTIMER://����׼��¼����ʱ����
		if(m_nLightCount<2)
		{
			m_nLightCount++;
// 			m_bRecordLightWork=!m_bRecordLightWork;
// 			if(m_bRecordLightWork)
// 				pStatic->SetIcon(m_hIcon_Work);
// 			else
// 				pStatic->SetIcon(m_hIcon_Wait);

		}
		else
		{
			m_nLightCount=0;
			KillTimer(VOICERECORDREADTIMER);
			m_nRecTime=0;
			m_RecordThread->PostThreadMessage(WM_RECORDSOUND_STARTRECORDING, 0, 0L);
			AfxGetApp()->m_pMainWnd->SetDlgItemText(IDC_BUTTON1,"ֹͣ¼��");
			SaveRecord("��ʼ¼������");
			m_LED.LoadBitmaps(IDB_WORk,NULL,NULL,NULL);
			m_LED.SubclassDlgItem(IDB_WORk,this);
			m_LED.SizeToContent();
			m_LED.Invalidate(TRUE);
			m_bRecording = TRUE;
			if (SendSocket.m_bConnect==TRUE)
			{
				//������ʾ��
				DATABUFF databuf;
				databuf.len = 2*DOT;
				databuf.buf = new short[2*DOT];
				GenSinWave(databuf.buf,1000,DOT);
				GenSinWave(databuf.buf+DOT,0,1*DOT);
				m_WzdvoiceList.AddTail(&databuf);//���뷢�Ͷ���
				SendPhoneData();
			}
			SetTimer(SENDSOUNDTIMER,2000,NULL);
			if (UWACInitParam.ADIOWorkMode&&UsblEnableCheck)
			{
				//д���ڽ�ֹ���̻���
				if (hyLPT)
				{
					LPT_Writedata(hyLPT,0x99);  //B0_DQ=1 ,�ͷ�DQ�ߣ�B6_DQ=1������B6
				}
			}
//			SetTimer(VOICERECORDTIMER,1000,NULL);
		}
		break;
	case SYS_INFO_DISP_TIMER: //ϵͳ��Ϣ��ʾ+ͨ�Ų�����ʾ
		DisplayCommParam();
		break;
	case BUTTONTIMER:
		DisableButton(TRUE);
		KillTimer(BUTTONTIMER);
		break;
	case SENDSOUNDTIMER://
		
		nRet = OutVoiceCycleMem->GetDataLen();
		if (nRet == 0)//��
		{
//			TRACE("nRet == 0\n");
			if (!m_bRecording)//¼������ҷ������
			{
//				TRACE("m_bRecording == 0\n");
				m_nRecTime = 0;
				firstpacket =TRUE;
				NorVoiceFile.CloseFile();
				SendSoundEnd();
				KillTimer(SENDSOUNDTIMER);
				AfxGetApp()->m_pMainWnd->SetDlgItemText(IDC_BUTTON1,"��ʼ¼��");
				m_bRecording=FALSE;
				m_LED.LoadBitmaps(IDB_ON,NULL,NULL,NULL);
				m_LED.SubclassDlgItem(IDB_ON,this);
				m_LED.SizeToContent();
				m_LED.Invalidate(TRUE);
				if (UWACInitParam.ADIOWorkMode&&UsblEnableCheck)
				{
					if (hyLPT)
					{
						LPT_Writedata(hyLPT,0xB9);  //
					}
				}
				break;
			}
			
		}
		else
		{
			TRACE("nRet ��= 0\n");
			DATABUFF databuf ;
			databuf.len = nRet/2;
			databuf.buf = new short[nRet/2];
			OutVoiceCycleMem->ReadData((LPSTR)databuf.buf,nRet);
			if (firstpacket)//��һ��
			{
				NorVoiceFile.Init("NorVoice",40*FILESIZE,1024,4*WRITESIZE);//�Ӵ󱣴��ļ���С����Ϊ������¼��ʱ��
				firstpacket =FALSE;
//				NorAmp = calcAmp(databuf.buf,databuf.len);//�����һ��ֵ
				
			}
//			VoiceNormalize(databuf.buf,databuf.len,NorAmp);
			NorVoiceFile.SaveFile((char*)databuf.buf,databuf.len*2);
//			TRACE("SaveFile\n");
			m_WzdvoiceList.AddTail(&databuf);//���뷢�Ͷ���
			SendPhoneData();

			
		}
		//////////////////////////////////////////////////////////////////////////
		///ȡ��¼��ʱ������2011��6��1�ո�
		/*m_nRecTime+=2;
		if (m_nRecTime>25)
		{
			firstpacket =TRUE;
			m_RecordThread->PostThreadMessage(WM_RECORDSOUND_STOPRECORDING, 0, 0L);
			AfxGetApp()->m_pMainWnd->SetDlgItemText(IDC_BUTTON1,"��ʼ¼��");
			m_bRecording = FALSE;
			m_nRecTime=0;
// 			pStatic->SetIcon(m_hIcon_Wait);
// 			SetDlgItemText(IDC_RECORD_STATUS,"û��¼��");
			OutVoiceCycleMem->Empty();
			SendSoundEnd();
			KillTimer(SENDSOUNDTIMER);
			SaveRecord("20��¼��ʱ�䵽��");
			if (hyLPT)
			{
				if (LBLStatus)//LBL���ڹ���
				{
					LPT_Writedata(hyLPT,0xB9);  //B0_DQ=1 ,�ͷ�DQ�ߣ�B6_DQ=0,����B6
					
				} 
				else//����ͨ��
				{
					LPT_Writedata(hyLPT,0xF9);  //B0_DQ=1 ,�ͷ�DQ��,B6_DQ=1
				}
			}
			
		}*/
		break;
	case NETLINKTIMER:
		if (!LinkStatus)//δ��ָ��ʱ����յ�����
		{	
//			m_status.LoadBitmaps(IDB_OFF);
			if (RecvSocket.m_bConnect)
			{
				
				SaveRecord("��ʱ��δ�յ����ݣ����粻��!!!");
			}

			
		}
		else
		{
//			m_status.LoadBitmaps(IDB_ON);
			LinkStatus =FALSE;
		}
//		m_status.Invalidate(FALSE);
		break;
	case LBLTIMER:
		LBLStatus = TRUE;//ͨ�����ڽ���
		if (hyLPT)
		{
			LPT_Writedata(hyLPT,0xB9);  //B0_DQ=1 ,�ͷ�DQ�ߣ�B6_DQ=0������B6
		}
		
		KillTimer(LBLTIMER);
		break;	
	case VOICEENABLE:
		//����¼������led
		m_LED.LoadBitmaps(IDB_ON,NULL,NULL,NULL);
		m_LED.SubclassDlgItem(IDB_ON,this);
		m_LED.SizeToContent();
		m_LED.Invalidate(TRUE);
		KillTimer(VOICEENABLE);
		break;
	case USBLENABLE:
		//д���ڽ�ֹ���̻���
		if (hyLPT)
		{
			LPT_Writedata(hyLPT,0x99);  //B0_DQ=1 ,�ͷ�DQ�ߣ�B6_DQ=1������B6
		}
		KillTimer(USBLENABLE);
		bFirstRecvData =TRUE;
		SetTimer(USBLTIME3,UWACInitParam.SyncConcurrence*1000*4,NULL);
		break;
	case USBLTIME:
		if (!RECVMPSK)//���ڽ���psk��ֹͣ����
		{
			
			KillTimer(USBLTIME);
			// 		д����
			if (hyLPT)
			{
				LPT_Writedata(hyLPT,0xB9);  //ʹ��
			}
			SetTimer(USBLTIME2,UWACInitParam.SyncConcurrence*1000*1,NULL);
		}

		RECVMPSK = FALSE;//������������´���д����
		break;
	case USBLTIME2:
		//д���ڽ�ֹ���̻���
		if (hyLPT)
		{
			LPT_Writedata(hyLPT,0x99);  //B0_DQ=1 ,�ͷ�DQ�ߣ�B6_DQ=1������B6
		}
		KillTimer(USBLTIME2);
		SetTimer(USBLTIME3,UWACInitParam.SyncConcurrence*1000*2,NULL);
		break;
	case USBLTIME3:
		KillTimer(USBLTIME);
		// 		д����
		if (hyLPT)
		{
			LPT_Writedata(hyLPT,0xB9);  //ʹ��
		}
		KillTimer(USBLTIME3);
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}


void CACSDlg::OnButton1() 
{
	CStatic *pStatic;
//	pStatic= (CStatic *)GetDlgItem(IDC_STATIC_status);//voice record indication light

	// TODO: Add your control notification handler code here
	if(m_bRecording)
	{
		m_RecordThread->PostThreadMessage(WM_RECORDSOUND_STOPRECORDING, 0, 0L);
		AfxGetApp()->m_pMainWnd->SetDlgItemText(IDC_BUTTON1,"��ʼ¼��");
		SaveRecord("ֹͣ¼������");
		//����¼������led
		m_LED.LoadBitmaps(IDB_ON,NULL,NULL,NULL);
		m_LED.SubclassDlgItem(IDB_ON,this);
		m_LED.SizeToContent();
		m_LED.Invalidate(TRUE);
		if (UWACInitParam.ADIOWorkMode&&UsblEnableCheck)
		{
			//д����
			if (hyLPT)
			{
				LPT_Writedata(hyLPT,0xB9);  //
			}
			
	}
//		m_bRecording = FALSE;
// 		pStatic->SetIcon(m_hIcon_Wait);
// 		SetDlgItemText(IDC_RECORD_STATUS,"û��¼��");
//		OutVoiceCycleMem->Empty();
	}
	else
	{
		//������ʾ��
		if (SendSocket.m_bConnect==TRUE)
		{
			DATABUFF databuf;
			databuf.len = 2*DOT;
			databuf.buf = new short[2*DOT];
			GenSinWave(databuf.buf,1000,DOT);
			GenSinWave(databuf.buf+DOT,0,1*DOT);
			m_WzdvoiceList.AddTail(&databuf);//���뷢�Ͷ���
			SendPhoneData();
		}
		m_RecordThread->PostThreadMessage(WM_RECORDSOUND_STARTRECORDING, 0, 0L);
		AfxGetApp()->m_pMainWnd->SetDlgItemText(IDC_BUTTON1,"ֹͣ¼��");
		SaveRecord("��ʼ¼������");
		m_LED.LoadBitmaps(IDB_WORk,NULL,NULL,NULL);
		m_LED.SubclassDlgItem(IDB_WORk,this);
		m_LED.SizeToContent();
		m_LED.Invalidate(TRUE);			
		SetTimer(SENDSOUNDTIMER,2000,NULL);	
		if (UWACInitParam.ADIOWorkMode&&UsblEnableCheck)
		{
			//д���ڽ�ֹ���̻���
			if (hyLPT)
			{
				LPT_Writedata(hyLPT,0x99);  //B0_DQ=1 ,�ͷ�DQ�ߣ�B6_DQ=1������B6
			}
		}
	}
	
}

void CACSDlg::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
  	
	
	RECVFSKFile.CloseFile();
	RECVPSKFile.CloseFile();
	RECVEOUTFile.CloseFile();
	RECVFSFile.CloseFile();
	RECVVoiceFile.CloseFile();
	XMTFSKFile.CloseFile();
	XMTPSKFile.CloseFile();
	XMTFSFile.CloseFile();
	XMTVoiceFile.CloseFile();
	NorVoiceFile.CloseFile();
	RecordFile.CloseFile();
	RECVCommDataFile.CloseFile();
	TextFile.CloseFile();
	ADFile.CloseFile();
	USBLFile.CloseFile();
	Trans2SailFile.CloseFile();
	MarineDataFile.CloseFile();
	if (RecDataBuf)
	{
		free(RecDataBuf);
		RecDataBuf = NULL;
	}
	CDialog::OnClose();
}

void CACSDlg::OnSendAdio()//adio��������
{
	NET_PACKET *netpacket;
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	
	if(netpacket==NULL)
	{
		AfxMessageBox("����NET_PACKET�ռ�����쳣��");
	}
	
	netpacket->FrmID = UWACCMD_STARTTALK;
	netpacket->FrmLen = 32;
	netpacket->DestID = ADIOID;
	netpacket->HeadParam[0] = 0;//
	netpacket->HeadParam[1] = 1;//�ܰ���
	netpacket->HeadParam[2] = 0;//��ǰ����
	netpacket->HeadParam[3] = 0;//�����ݳ���
	netpacket->pData =NULL;	
	m_WzdNetpacketList.AddTail(netpacket);
	SetEvent(IsNetpacketEvent);
}

void CreateFileName(char* filename,char* filetype,char * fullfilename)//�Զ������ļ���
{
	char m_sFileName[256];
	strcpy(m_sFileName,filename);
	
	char str[100];
	CTime ct = CTime::GetCurrentTime();
	sprintf(str,"%d%02d%02d%02d%02d%02d",ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());
	strcat(m_sFileName,str);//�ļ�����ʱ��
	strcat(m_sFileName,filetype);
	memcpy(fullfilename,m_sFileName,256);
	
}
void GenSinWave (short* pBuffer, int iFreq, int nlength)
{
	double fAngle =0;
	int    	i ;
	for (i = 0 ; i < nlength ; i++)
	{
		pBuffer [i] = (short) (32768 * sin (fAngle)) ;
		fAngle += 2 * PI * iFreq / SAMPLE_RATE ;
		if (	fAngle > 2 * PI)
			fAngle -= 2 * PI ;
	}
}

void CACSDlg::OnButtonSet() 
{
	// TODO: Add your control notification handler code here
	CString str;
	UpdateData(TRUE);
	if ((m_Gain<100)||(m_Gain>4000))
	{
		return;
	}
	UWAcommparam.Gain = m_Gain;
	OnButtonSave();
	OnSetGain(atoi(m_strXmtChannel),m_Gain);
	str.Format("���ý��ղ�����ͨ��%d������%d",atoi(m_strXmtChannel),m_Gain);
	SaveRecord(str);
}

void CACSDlg::SetADIOStatusIndicatior(int States)
{
	CStatic *pStatic=(CStatic *)AfxGetApp()->m_pMainWnd->GetDlgItem(IDC_ADIO_STATE_LIGHT);
	
	if(States==2)  //����״̬
	{
		SetDlgItemText(IDC_SYS_STATUS,"���ڷ���ˮ���ź�...");
		pStatic->SetIcon(m_hIcon_Work);
	}
	else if (States==1)//����
	{
		SetDlgItemText(IDC_SYS_STATUS,"���ڽ���ˮ���ź�...");
		pStatic->SetIcon(m_recvWork);
	}
	else //����
		SetDlgItemText(IDC_SYS_STATUS,"ͨ�Ż�������...");
		pStatic->SetIcon(m_hIcon_Wait);
}

void CACSDlg::OnButtonMsgok() //ͬ��
{
	// TODO: Add your control notification handler code here
	CString msg = "II";
//	SendMorseMsg(msg);
	SendMorseCommand(22);

	msg = "ͬ��";
	SaveMorseMsg(msg);
	SendSoundEnd();
}

void CACSDlg::SendMorseMsg(CString msg)
{
	DATABUFF databuff;
	databuff.buf = new short[MAXBUFFSIZE];
	int index =0 ;
	int sum=0;
	int nlength = msg.GetLength();
	if ((nlength==0)||(m_bRecording))//��ϢΪ0������¼��
	{
		return;
	}
	for (int i=0;i<nlength;i++)
	{
		MyMorse.ParseWord(msg[i],databuff.buf+sum,&index);
		sum+=index;
	}
	databuff.len = sum;
	FILE* fp = fopen("1.dat","wb");
	fwrite((char*)databuff.buf,1,databuff.len*2,fp);
	fclose(fp);
//  	CCycleMemSync.Lock();
//  	InVoiceCycleMem->WriteData((char *)databuff->buf,sum*2);
//  	CCycleMemSync.Unlock();
// 	WaveMemSync.Lock();
//  	WaveCycleMem->WriteData((char *)databuff->buf,sum*2);
//  	WaveMemSync.Unlock();

	SendNetpacketSync.Lock();
	if (!m_WzdvoiceList.IsEmpty())
	{
		if (m_WzdvoiceList.GetHead()->buf)
		{
			delete m_WzdvoiceList.GetHead()->buf;
		}
		if (m_WzdvoiceList.GetHead())
		{
			delete m_WzdvoiceList.GetHead();
		}
		
		m_WzdvoiceList.RemoveAll();
	}
	if(SendSocket.m_bConnect)
	{
		m_WzdvoiceList.AddTail(&databuff);
		
	}
	else
	{
		SaveRecord("δ��������!��Ϣδ����...");
		if(databuff.buf)
		{
			delete databuff.buf;
		}
		SendNetpacketSync.Unlock();
		return;
	}
	SendNetpacketSync.Unlock();
	SendPhoneData();
	
	SendSoundEnd();//����ֹͣˮ������
	//��һ��ʱ���ڽ�ֹ������ť��¼��
	DisableButton(FALSE);
	SetTimer(BUTTONTIMER,3000,NULL);
	
}

void CACSDlg::SaveMorseMsg(CString msg)
{
	CString str;
	if (!msg.GetLength())
	{
		return;
	}
	if (UWACInitParam.ADIOWorkMode == 0)
	{
		SaveRecord("Ǳ����"+msg);
	}
	else
	{
		SaveRecord("ĸ����"+msg);
	}

	CTime ct = CTime::GetCurrentTime();
	str.Format("%d-%02d-%02d %02d-%02d-%02d: ",ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());
	msg = str + msg + "\r\n";
	TextFile.SaveFile(msg, msg.GetLength());
}

void CACSDlg::OnButtonMsgdn() //�ͷ�Ӧ������
{
	// TODO: Add your control notification handler code here
	CString msg = "III";
//	SendMorseMsg(msg);
	SendMorseCommand(222);

	msg = "�ͷ�Ӧ������";
	SaveMorseMsg(msg);
	SendSoundEnd();

}

void CACSDlg::OnButtonMsgup() //�����ϸ�
{
	// TODO: Add your control notification handler code here
	CString msg = "II";
//	SendMorseMsg(msg);
	SendMorseCommand(22);

	msg = "�����ϸ�";
	SaveMorseMsg(msg);
	SendSoundEnd();

}

void CACSDlg::OnButtonMsgdb() //��ɽ׶ι���
{
	// TODO: Add your control notification handler code here
	CString msg = "I";
//	SendMorseMsg(msg);
	SendMorseCommand(2);

	msg = "��ɽ׶ι���";
	SaveMorseMsg(msg);
	SendSoundEnd();

}

void CACSDlg::OnButtonMsgdu() //�����ϸ�
{
	// TODO: Add your control notification handler code here
	CString msg = "5";
//	SendMorseMsg(msg);
	SendMorseCommand(5);

	msg = "�����ϸ�";
	SaveMorseMsg(msg);
	SendSoundEnd();

}

void CACSDlg::OnButtonMsgwk() //����Ӧ������
{
	// TODO: Add your control notification handler code here
	CString msg = "5";
//	SendMorseMsg(msg);
	SendMorseCommand(5);

	msg = "����Ӧ������";
	SaveMorseMsg(msg);
	SendSoundEnd();

}

void CACSDlg::OnChangeChannel(int nchannel,float fAmp,int type)//�������任�����Ż����
{
	NET_PACKET *netpacket;
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	
	if(netpacket==NULL){
		AfxMessageBox("����NET_PACKET�ռ�����쳣��");
	}
	
	netpacket->FrmID = UWACCMD_CHANGE_TRANS;
	netpacket->FrmLen = 32;
	netpacket->DestID = ADIOID;
	netpacket->HeadParam[0] = nchannel;
	netpacket->HeadParam[1] = *(int*)&fAmp;//���Ⱥ�
	netpacket->HeadParam[2] = type;//ģ��or����
	netpacket->HeadParam[3] = 0;//�����ݳ���
	netpacket->HeadParam[4] = 0;
	netpacket->pData =NULL;	
	m_WzdNetpacketList.AddTail(netpacket);
	SetEvent(IsNetpacketEvent);
				
}

void CACSDlg::OnSetGain(int nchannel,int nGain)//�������ջ��������������
{

	NET_PACKET *netpacket;
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	
	if(netpacket==NULL){
		AfxMessageBox("����NET_PACKET�ռ�����쳣��");
	}
	
	netpacket->FrmID = UWACPARA_SETGAIN;
	netpacket->FrmLen = 32;
	netpacket->DestID = ADIOID;
	netpacket->HeadParam[0] = nchannel;
	netpacket->HeadParam[1] = nGain;//��������
	netpacket->HeadParam[2] = 0;//��ǰ����
	netpacket->HeadParam[3] = 0;//�����ݳ���
	netpacket->HeadParam[4] = 0;//ˮ��
	netpacket->pData =NULL;	
	m_WzdNetpacketList.AddTail(netpacket);
	SetEvent(IsNetpacketEvent);

}

void CACSDlg::SaveRecord(CString str)
{
	str.TrimRight();
	CString strtime;
	CTime ct = CTime::GetCurrentTime();
	strtime.Format("%02d:%02d:%02d ",ct.GetHour(),ct.GetMinute(),ct.GetSecond());
	str = strtime + str + "\r\n";
	RecordFile.SaveFile(str, str.GetLength());
	UpdateData(TRUE);
	char tmpstr[100];
	CEdit* pEdit = (CEdit*)AfxGetApp()->m_pMainWnd->GetDlgItem(IDC_EDIT_LOG);	
	m_log+=str;
	if (m_log.GetLength()>2048)
	{
		m_log = m_log.Right(1024);
		UpdateData(FALSE);
		pEdit->GetLine(0,tmpstr,100);
		int nlength = strlen(tmpstr); //�õ���������ĳ���
		m_log = m_log.Right(1024-nlength);//ȥ��nlength����
	}
	logview = new char[str.GetLength()+1];
	UpdateData(FALSE);
	logtab = new char[str.GetLength()+1];
	pEdit->LineScroll(pEdit->GetLineCount(),0);
	pEdit = (CEdit*)AfxGetApp()->m_pMainWnd->GetDlgItem(IDC_FHLOG);
	pEdit->LineScroll(pEdit->GetLineCount(),0);
	memcpy(logview,(LPCTSTR)str,str.GetLength());
	memcpy(logtab,(LPCTSTR)str,str.GetLength());
	logview[str.GetLength()]='\0';//�ض��ַ�����
	logtab[str.GetLength()]='\0';//�ض��ַ�����
	::PostMessage(logpage.GetSafeHwnd(),WMSG_LOG,(WPARAM)str.GetLength(),(LPARAM)logview);
	::PostMessage(Tablog.GetSafeHwnd(),WMSG_TABLOG,(WPARAM)str.GetLength(),(LPARAM)logtab);

	
}

void CACSDlg::OnButtonMsgisok() //һ������
{
	// TODO: Add your control notification handler code here
	CString msg = "s";
//	SendMorseMsg(msg);
	SendMorseCommand(3);
	msg = "������ҵ��һ������";
	SaveMorseMsg(msg);
	SendSoundEnd();

}

void CACSDlg::OnButtonMsgrep() //�յ�
{
	// TODO: Add your control notification handler code here
	CString msg = "s";
//	SendMorseMsg(msg);
	SendMorseCommand(3);
	msg = "�յ�";
	SaveMorseMsg(msg);
	SendSoundEnd();

}



void CACSDlg::OnButtonXmtset() //ˮ��ͨ�������ȵ���
{
	// TODO: Add your control notification handler code here
	if (!SendSocket.m_bConnect)
	{
		return;
	}
	CString str;
	UWACInitParam.XMTChannelNo = atoi(m_strXmtChannel);//ˮ������ͨ��
	float amp = m_slider_amp.GetPos();
	m_Amp = float(int(amp/10))/100;//Ϊ�˷�����ʾ
	if ((m_Amp<0.00499)||(m_Amp>1))
	{
		return;
	}
	OnChangeChannel(atoi(m_strXmtChannel),m_Amp,2);//1����2ģ��
	UWAcommparam.XmtChannel = atoi(m_strXmtChannel);
	UWAcommparam.XmtAmp = m_Amp;
	UpdateData(FALSE);//��֤��ֵ����
	OnButtonSave();
	str.Format("���÷��������ͨ��%d,����%.2f",atoi(m_strXmtChannel),m_Amp);
	
	SaveRecord(str);

}

void CACSDlg::OnExit() 
{
	// TODO: Add your control notification handler code here
	m_bRecording = FALSE;
	//	m_RecordThread->PostThreadMessage(WM_RECORDSOUND_STOPRECORDING, 0, 0L);
	if (IDCANCEL ==AfxMessageBox("ȷ���˳���",MB_OKCANCEL))
	{
		return;
	}
	
	SendSocket.Close();
	RecvSocket.Close();
	Sleep(500);
	OnClose();
	CDialog::OnCancel();
}

void CACSDlg::OnButtonNo() //��ͬ��
{
	// TODO: Add your control notification handler code here
	CString msg = "SS";
//	SendMorseMsg(msg);
	SendMorseCommand(33);

	msg = "��ͬ��";
	SaveMorseMsg(msg);
	SendSoundEnd();

}

void CACSDlg::OnButtonAsk() 
{
	// TODO: Add your control notification handler code here
	CString msg = "I";
//	SendMorseMsg(msg);
	SendMorseCommand(2);
	msg = "ѯ�ʲ���״��";
	SaveMorseMsg(msg);
	SendSoundEnd();

}


BOOL CACSDlg::Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CDialog::Create(IDD, pParentWnd);
}

void CACSDlg::OnButtonStart() 
{
	// TODO: Add your control notification handler code here
	SaveRecord("��ʼ����ͨ�Ż�");
	OnConnect();	
}

void CACSDlg::OnExpand() 
{
	// TODO: Add your control notification handler code here
	
	if (UWACInitParam.ADIOWorkMode)//����״̬
	{
		SetWindowPos(NULL,0,0,1140,860,SWP_SHOWWINDOW);
		ViewSize =TRUE;

	}
	else
	{
		SetWindowPos(NULL,0,0,800,600,SWP_SHOWWINDOW);
		ViewSize = FALSE;

	}
//	Invalidate();//������ʾ������ԭ�߽���ʾ�ڽ����ϡ�
}

void CACSDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int index = m_tabctrl.GetCurSel();//ѡ���ҳ��
	//hide all page first
	pWavePage.ShowWindow(SW_HIDE);
	pPostPage.ShowWindow(SW_HIDE);
	pWordPage.ShowWindow(SW_HIDE);
	pPicturePage.ShowWindow(SW_HIDE);
//	pAdcpPage.ShowWindow(SW_HIDE);
	pDataPage.ShowWindow(SW_HIDE);
	Tablog.ShowWindow(SW_HIDE);
	
	//show the selected page
	switch (index)
	{
	case 0:
		pWavePage.ShowWindow(SW_SHOW);
		break;
	case 1:
		pPostPage.ShowWindow(SW_SHOW);
		break;
	case 2:
		pWordPage.ShowWindow(SW_SHOW);
		break;
	case 3:
		pPicturePage.ShowWindow(SW_SHOW);
		break;
	case 4:
		pDataPage.ShowWindow(SW_SHOW);
		break;
	case 5:
		Tablog.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}
	*pResult = 0;
}

void CACSDlg::OnAdvanced() 
{
	// TODO: Add your control notification handler code here
	pComParamPage.ShowWindow(SW_SHOW);
}

void CACSDlg::OnOpenOption() 
{
	// TODO: Add your control notification handler code here
	pOptionView.DoModal();
}

void CACSDlg::OnLog() 
{
	// TODO: Add your control notification handler code here
	logpage.ShowWindow(SW_SHOW);

}

void CACSDlg::OnDClickListAdcp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	pAdcpPage.ShowWindow(SW_SHOW);
	pAdcpPage.UpdateView();
	*pResult = 0;
}

void CACSDlg::OnAdsample() 
{
	// TODO: Add your control notification handler code here
	AdSamplePage.ShowWindow(SW_SHOW);
}

void CACSDlg::OnReleasedcaptureSliderAmp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
// 	float amp = m_slider_amp.GetPos();
// 	CString str;
// 	str.Format("%.2f",amp/1000);
// 	CWnd* pWnd = GetDlgItem(IDC_STATIC_AMP);
// 	pWnd->SetWindowText(str);
// 	m_Amp = amp/1000;
// 	if (!SendSocket.m_bConnect)//δ����
// 	{
// 		return;
// 	}
	OnButtonXmtset();
	*pResult = 0;
}


void CACSDlg::UpdateADCP(char *x, char *y, char *z, int nlength)
{
	CString str;
	for (int i=0;i<nlength;i++)
	{
		str.Format("%d",(int)x[i]);
		m_CtrlList.SetItemText(i,1,str);
		str.Format("%d",(int)y[i]);
		m_CtrlList.SetItemText(i,2,str);
		str.Format("%d",(int)z[i]);
		m_CtrlList.SetItemText(i,3,str);

	}
	CTime ct = CTime::GetCurrentTime();
	str.Format("���ݸ���ʱ�䣺%02d:%02d:%02d",ct.GetHour(),ct.GetMinute(),ct.GetSecond());
	CWnd* pWnd = GetDlgItem(IDC_ADCP_UPDATETIME);
	pWnd->SetWindowText(str);
	
	
}


void CACSDlg::DisplayCommParam()
{
	CString strValue;
	int i;
	int MyprogressId[8]={IDC_PROGRESS1,IDC_PROGRESS2,IDC_PROGRESS3,IDC_PROGRESS4,IDC_PROGRESS5,IDC_PROGRESS6};
	int id[4]={IDC_CH1,IDC_CH2,IDC_CH3,IDC_CH4};
	for(i=0; i<4; i++)
	{
		//��ʾ���ջ����������
		strValue.Format("%d",CommunicationParam.Gain[i]);
		pComParamPage.m_list.SetItemText(i,1,strValue);
		
		//��ʾ���ջ��������
		if( CommunicationParam.AGCamp[i] >0 )
		{
			//�ѷ���ת����mV�������Ƕ�128������ƽ����ͣ�������2048��Ӧ10V��
			strValue.Format("%.0f",sqrt(CommunicationParam.AGCamp[i]/128.0)/2048*10000+0.5);
			CProgressCtrl*pwnd = (CProgressCtrl*)GetDlgItem(MyprogressId[i]);
			pwnd->SetPos(sqrt(CommunicationParam.AGCamp[i]/128.0)/2048*10000+0.5);
//			SetDlgItemText(id[i],strValue);
		}
		else
		{
			strValue.Format("��");
		}
		pComParamPage.m_list.SetItemText(i,2,strValue);
		
		//��ʾͬ��ͷ��ط�ֵ���Ƕ�4096�����غ�����ģƽ��
		if( CommunicationParam.ChirpCorrePeak[i] >0 )
		{
			strValue.Format("%.1f",10*log10(CommunicationParam.ChirpCorrePeak[i]/4096));
		}
		else
		{
			strValue.Format("��");
		}
		pComParamPage.m_list.SetItemText(i,3,strValue);
		
		//��ʾͬ��ͷ��ط�ֵ
		strValue.Format("%.3f",CommunicationParam.ChannCorreCoe[i]);
		pComParamPage.m_list.SetItemText(i,4,strValue);
		strValue.Format("%.2f",CommunicationParam.ChannCorreCoe[i]);
		SetDlgItemText(id[i],strValue);
	}
	if (CommunicationParam.reserved[0] > 0)
	{
//		strValue.Format("%.1f ��",CommunicationParam.reserved[0]*0.15);
		::PostMessage(pComParamPage.GetSafeHwnd(),DiSTANCE_WMSG,(WPARAM)CommunicationParam.reserved[0],NULL);
//		UpdateData(FALSE);
	}
}

void CACSDlg::SendPhoneData()//��ȡ����������������������Ϣ
{
	
	CString str;
	NET_PACKET *netpacket;
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	if(netpacket==NULL)
	{
		AfxMessageBox("����NET_PACKET�ռ�����쳣��");
		return;
	}
	if (!m_WzdvoiceList.IsEmpty())
	{
		SendNetpacketSync.Lock();
		int nlength = m_WzdvoiceList.GetHead()->len*2;
		netpacket->FrmID = UWACDATA_MODULATION_PHONEDATA;
		netpacket->FrmLen = 32+nlength;
		netpacket->DestID = ADIOID;
		netpacket->HeadParam[0] = UWACCMD_ADIOREQUEST;//�������������壬��Ϊ0
		netpacket->HeadParam[1] = 1;//�ܰ���
		netpacket->HeadParam[2] = 0;//��ǰ����
		netpacket->HeadParam[3] = nlength;//�����ݳ���
		netpacket->HeadParam[4] = SOUNDMOD;
		netpacket->pData = (char *) malloc(nlength);
		memcpy(netpacket->pData,(char*)m_WzdvoiceList.GetHead()->buf,nlength);
		if(m_WzdvoiceList.GetHead()->buf)
			delete m_WzdvoiceList.GetHead()->buf;
		m_WzdvoiceList.RemoveAll();

		SendNetpacketSync.Unlock();
		m_WzdNetpacketList.AddTail(netpacket);
		SetEvent(IsNetpacketEvent);	

	}
	else
	{
		if (netpacket)
		{
			free(netpacket);
		}
		
	}



}

void CACSDlg::DisableButton(BOOL bDisabled)
{
	if (UWACInitParam.ADIOWorkMode==0)//����
	{
		CWnd* pWnd;
		
		int ButtonID[6]={IDC_BUTTON1,IDC_BUTTON5,IDC_BUTTON6,IDC_BUTTON8,IDC_BUTTON10,IDC_BUTTON12};
		for (int i=0;i<6;i++)
		{
			pWnd = (CButton*)GetDlgItem(ButtonID[i]);
			pWnd->EnableWindow(bDisabled);
		}
	}
	else
	{
		CButton* pWnd;
		int ButtonID[6]={IDC_BUTTON1,IDC_BUTTON3,IDC_BUTTON4,IDC_BUTTON7,IDC_BUTTON9,IDC_BUTTON11};
		for (int i=0;i<6;i++)
		{
			pWnd = (CButton*)GetDlgItem(ButtonID[i]);
			pWnd->EnableWindow(bDisabled);
		}

		
	}
}

void CACSDlg::OnSelchangeComboXmt() 
{
	// TODO: Add your control notification handler code here
    int i =	m_Xmt_Channel.GetCurSel();
// 	if (!UWACInitParam.ADIOWorkMode)
// 	{
// 		m_strXmtChannel.Format("%d",i+1);
// 	}
// 	else
// 	{
// 		if (i==0)
// 		{
// 			m_strXmtChannel.Format("%d",1);
// 		}
// 		else
// 			m_strXmtChannel.Format("%d",6);
// 	}
	m_strXmtChannel.Format("%d",i+1);
	OnButtonXmtset();
}

LRESULT CACSDlg::OnNetUSBLSocket(WPARAM wParam, LPARAM lParam)
{
//����Winsock API�������õ������¼����� 
	int iEvent = WSAGETSELECTEVENT(lParam); 
	//����Winsock API�������õ��������¼��Ŀͻ����׽��� 
//	SOCKET CurSock= (SOCKET)wParam; 
//	int RecvFlag = 1;//�������ݸ�ʽ��־����1������1����ȷ��0��������ʽ
	switch(iEvent) 
	{ 
	case FD_READ: //�������ݰ������¼�
	{
		int fromlen=sizeof(SOCKADDR);
		sockaddr_in sockDest;
		sockDest.sin_family = AF_INET;
		sockDest.sin_port = htons(2001);
		sockDest.sin_addr.s_addr = INADDR_BROADCAST;
		char buf[1024];
//		char strBuf[1024];
		int ret = recvfrom(s1,buf,strlen(buf)+1,0,(SOCKADDR *)&sockDest,&fromlen);
		CString pchar_buffer;
		//��������
		//�õ�ϵͳʱ��
		CString strTime=_T("");
		SYSTEMTIME st;
		GetSystemTime(&st);
		strTime.Format("%d-%02d-%02d %02d:%02d:%02d:%03d ",
			st.wYear,st.wMonth,st.wDay,(st.wHour+8)%24,st.wMinute,st.wSecond,st.wMilliseconds);
		pchar_buffer.Format("\n%s %s","USBL���ݣ�",strTime);
		USBLFile.SaveFile(pchar_buffer,pchar_buffer.GetLength());
		USBLFile.SaveFile(buf,ret);
		
		//����λ����
		byte* USBLData=(byte*)buf;
		CString str,shiplong,shiplat;
		//CReadUSBL USBLReader;
		CReadUSBLBOX USBLReader;
		memcpy(USBLReader.USBLCheck.m_sFullData,buf,ret);
		USBLReader.USBLCheck.m_nDataLen =ret;
		if(!USBLReader.USBLCheck.IsCorrect())
			return 0;//У�鲻��ȷ�˳�
		else//������ȷ
		{
			str.Format("%s",USBLData);
			switch (USBLReader.CheckDataType(str))
			{
			case 1:
				USBLReader.GetTime(str,newPosition.ltime);
				if (USBLReader.IsShipData(str))
				{
					USBLReader.GetThePost(str,newPosition.shipLAT,newPosition.shipLONG);
					RecShipPostData =1;
				} 
				else
				{
					USBLReader.GetThePost(str,newPosition.subLAT,newPosition.subLONG);
					RecSubPostData =1;
					newPosition.subdepth = USBLReader.GetAUVDepth(str);

				}
				break;
			case 2:
				if (!USBLReader.IsShipData(str))
				{
					USBLReader.GetRelativeData(str,newPosition.relateX,newPosition.relateY,newPosition.relateZ);
					RecMoveData =1;
				}
				
				break;
			case 3:
				USBLReader.GetShipStance(str,newPosition.shipheading,newPosition.shippitch,newPosition.shiproll);
				RecShipRefData =1;
				break;
			default:
				break;
			}
		}
		if ((RecShipPostData)&&(RecSubPostData)&&(RecMoveData))//�յ������Ķ�λ����
		{
			memcpy(&sysposition,&newPosition,sizeof(SYSPOSITION));
			
			RecSubPostData = 0;
			RecShipPostData = 0;
//			RecGpsData = 0;
			///////////////���5�ζ�λ��Ϣ////////////////////////////////////////////
			if (subpostindex<=4)
			{
				subpost.ltime[subpostindex] = sysposition.ltime;
				subpost.subLAT[subpostindex] = sysposition.subLAT;
				subpost.subLONG[subpostindex] = sysposition.subLONG;
				subpostindex++;
			}
			else
			{
				memcpy(&subpost.ltime[0],&subpost.ltime[1],4*sizeof(FILETIME));//ǰ��
				memcpy(&subpost.subLAT[0],&subpost.subLAT[1],4*sizeof(FILETIME));
				memcpy(&subpost.subLONG[0],&subpost.subLONG[1],4*sizeof(FILETIME));
				subpost.ltime[4] = sysposition.ltime;
				subpost.subLAT[4] = sysposition.subLAT;
				subpost.subLONG[4] = sysposition.subLONG;
				subpostindex=0;
			}
			///////////////////////////udp����ĸ����λ��Ϣ������ϵͳ/////////////////
			char ShipPost[20];

			if (RecShipRefData)
			{
				shipposition.ltime = sysposition.ltime;
				shipposition.shipheading = sysposition.shipheading;
				shipposition.shipLAT = sysposition.shipLAT;
				shipposition.shipLONG = sysposition.shipLONG;
// 				if(SEND_FLAG)
// 				{
// 					*ShipPost=0x17;
// 					*(ShipPost+1)=0x20;
//  					memcpy(ShipPost+2,(BYTE*)&shipposition,18);
// 					OnSend(ShipPost,18+2);
// 				}
				RecShipRefData=0;
			}
			

			//////////////////////////////////////////////////////////////////////////
		}
		
		////��ʾ����
		DisplayData(0);
		pDataPage.UpdateTimeDisplay("USBL");
		if (RecMoveData)
		{
			pPostPage.iX=(short)((float)newPosition.relateX*15000.0/32768);
			pPostPage.iY=(short)((float)newPosition.relateY*15000.0/32768);
			pPostPage.iZ=(short)((float)newPosition.relateZ*8000.0/65536+1);
			//��λ��ͼ��ʾ
			pPostPage.Redraw();
//			RecMoveData =0 ;

		}
		
		break; 
	}
	case FD_WRITE: //�������ݰ��������¼� 
	//�˶˿�ֻ�������USBLϵͳ���ݡ�
  			 break; 

	default: break; 
	}
	return LRESULT(0);
}

LRESULT CACSDlg::OnNetSailSocket(WPARAM wParam, LPARAM lParam)
{
	//����Winsock API�������õ������¼����� 
	int iEvent = WSAGETSELECTEVENT(lParam); 
	//����Winsock API�������õ��������¼��Ŀͻ����׽��� 
//	SOCKET CurSock= (SOCKET)wParam; 
	switch(iEvent) 
	{ 
	case FD_READ: //�������ݰ������¼�
		{
			int receivenum;	
			int fromlen=sizeof(SOCKADDR);
			sockaddr_in sockDest;
			sockDest.sin_family = AF_INET;
			sockDest.sin_port = htons(3001);
			sockDest.sin_addr.s_addr = INADDR_BROADCAST;
			char bufr[1024];
			receivenum=recvfrom(s3,bufr,strlen(bufr)+1,0,(SOCKADDR *)&sockDest,&fromlen);
///////////////////////����UDP���յ��������
			ExplainUDPPackage(bufr,receivenum);
//////////////////////����UDP���յ��������
		}
	break; 

	case FD_WRITE: //�������ݰ��������¼� 
	{
		CString str;

		 		
		break; 
	}
	default: break; 
	} 
	return LRESULT(0);
}
//////////////udp�����Ӻ���

void CACSDlg::OnSend(char *sendbuf, int sendlenth)
{
//���淢���ļ�
	time_t * nowtime;//����ʱ�䶯̬�ռ䷵��ָ��
	CString pchar_buffer;
	char *p_display_time;//ctime(nowtime)����ָ��
	nowtime=(time_t *)malloc(sizeof(time_t));//����ʱ�䶯̬�ռ�
	if(nowtime==NULL){
		AfxMessageBox("����time_t�ռ�����쳣��");
		exit(EXIT_FAILURE);	
	}

	ASSERT(time(nowtime)!=-1);
	p_display_time=ctime(nowtime);
	if(nowtime!=NULL)//�ͷ�ʱ�䶯̬�ռ�
	free(nowtime);
	pchar_buffer.Format("\n���ݷ���ʱ��:%s ��������: %x \n",p_display_time,*sendbuf);
	Trans2SailFile.SaveFile(pchar_buffer,pchar_buffer.GetLength());
	Trans2SailFile.SaveFile(sendbuf,sendlenth);

	sockaddr_in sockDest;
	sockDest.sin_family = AF_INET;
	sockDest.sin_port = htons(3000);
	sockDest.sin_addr.s_addr = INADDR_BROADCAST;
	int resultlenth=sendto(s2,sendbuf,sendlenth,0,(SOCKADDR *)&sockDest,sizeof(SOCKADDR));//����
// 	while(1)
// 	{
// 		if(sendlenth==resultlenth)
// 			return;
// 		else
// 			Sleep(10);
// 	}
}


void CACSDlg::DisplayData(int nSource)
{
	CString str;
	switch (nSource)
	{
	case 0://syspostion
		{
			CString sublong,sublat,subdistance;;
			if(sysposition.subLONG>=0)
			{
				pDataPage.SetDlgItemText(IDC_STATIC_UWVLONG,"E");
				sublong.Format("%.2f",(float)(sysposition.subLONG)/60);
				while (sublong.GetLength()<6)//����6λ��ʾ
				{
					sublong = " "+sublong;
				}
			}
			else
			{

				pDataPage.SetDlgItemText(IDC_STATIC_UWVLONG,"W");
				sublong.Format("%.2f",(float)(0-sysposition.subLONG)/60);
				while (sublong.GetLength()<6)//����6λ��ʾ
				{
					sublong = " "+sublong;
				}
			}
			pDataPage.m_uwvlong.Display(sublong);//��ʾǱ������

			if(sysposition.subLAT>=0)
			{
				pDataPage.SetDlgItemText(IDC_STATIC_UWVLAT,"N");
				sublat.Format("%.2f",(float)(sysposition.subLAT)/60);
				while (sublat.GetLength()<6)//����6λ��ʾ
				{
					sublat = " "+sublat;
				}		
			}
			else
			{
				pDataPage.SetDlgItemText(IDC_STATIC_UWVLAT,"S");
				sublat.Format("%.2f",(float)(0-sysposition.subLAT)/60);
				while (sublat.GetLength()<6)//����6λ��ʾ
				{
					sublat = " "+sublat;
				}
			}
			pDataPage.m_uwvlat.Display(sublat);//��ʾǱ��γ��

			if(sysposition.relateX>=0)
			{
				subdistance.Format("%.2f",(float)(sysposition.relateX*15000.0/32768));
				while (subdistance.GetLength()<6)//����6λ��ʾ
				{
					subdistance = " "+subdistance;
				}		
			}
			else
			{
				subdistance.Format("%.2f",(float)(0-sysposition.relateX*15000.0/32768));
				while (subdistance.GetLength()<6)//����6λ��ʾ
				{
					subdistance = " "+subdistance;
				}
			}
			pDataPage.m_distancex.Display(subdistance);//

			if(sysposition.relateY>=0)
			{
				subdistance.Format("%.2f",((float)sysposition.relateY)*15000.0/32768);
				while (subdistance.GetLength()<6)//����6λ��ʾ
				{
					subdistance = " "+subdistance;
				}		
			}
			else
			{
				subdistance.Format("%.2f",((float)(0-sysposition.relateY)*15000.0/32768));
				while (subdistance.GetLength()<6)//����6λ��ʾ
				{
					subdistance = " "+subdistance;
				}
			}
			pDataPage.m_distancey.Display(subdistance);//

		break;//case 0
		}
	case 1://subposition
		
		{
			//���
			CString subdepth;
			subdepth.Format("%.2f",(float)subposition.subdepth*8000.0/65536);
			while (subdepth.GetLength()<6)//����6λ��ʾ
			{
				subdepth = " "+subdepth;
			}
			pDataPage.m_UWVDEEP.Display(subdepth);
			str.Format("%.2f",(float)subposition.subdepth*8000.0/65536);
			SetDlgItemText(IDC_MARINE_DEPTH,str);
			//�߶�
			CString subheight;
			subheight.Format("%.2f",(float)subposition.subheight*256.0/65536);
			while (subheight.GetLength()<6)//����6λ��ʾ
			{
				subheight = " "+subheight;
			}
			pDataPage.m_UWVHEIGTH.Display(subheight);
			str.Format("%.2f",(float)subposition.subheight*256.0/65536);
			SetDlgItemText(IDC_MARINE_HEIGTH,str);
			//head
			CString subhead;
			subhead.Format("%.2f",(float)subposition.subheading*360/65536);
			while (subhead.GetLength()<6)//����6λ��ʾ
			{
				subhead = " "+subhead;
			}
			pDataPage.m_head.Display(subhead);

			//pitch
			CString subpitch;
			subpitch.Format("%.2f",(float)subposition.subpitch*180/32768);
			while (subpitch.GetLength()<6)//����6λ��ʾ
			{
				subpitch = " "+subpitch;
			}
			pDataPage.m_pitch.Display(subpitch);

			//roll
			CString subroll;
			subroll.Format("%.2f",(float)subposition.subroll*180/32768);
			while (subroll.GetLength()<6)//����6λ��ʾ
			{
				subroll = " "+subroll;
			}
			pDataPage.m_roll.Display(subroll);
			//vec
			
			
		break;//case 1;
		}
	case 2://BP
		{
			CString str;
			str.Format("%.1f",(float)bpdata.front/256);
			while (str.GetLength()<6)//����6λ��ʾ
			{
				str = " "+str;
			}
			pDataPage.m_front.Display(str);

			str.Format("%.1f",(float)bpdata.frontdown/256);
			while (str.GetLength()<6)//����6λ��ʾ
			{
				str = " "+str;
			}
			pDataPage.m_frontdown.Display(str);

			str.Format("%.1f",(float)bpdata.frontup/256);
			while (str.GetLength()<6)//����6λ��ʾ
			{
				str = " "+str;
			}
			pDataPage.m_frontup.Display(str);
			
			str.Format("%.1f",(float)bpdata.behinddown/256);
			while (str.GetLength()<6)//����6λ��ʾ
			{
				str = " "+str;
			}
			pDataPage.m_backdown.Display(str);
		
			str.Format("%.1f",(float)bpdata.down/256);
			while (str.GetLength()<6)//����6λ��ʾ
			{
				str = " "+str;
			}
			pDataPage.m_down.Display(str);

			str.Format("%.1f",(float)bpdata.right/256);
			while (str.GetLength()<6)//����6λ��ʾ
			{
				str = " "+str;
			}
			pDataPage.m_right.Display(str);
			
			str.Format("%.1f",(float)bpdata.left/256);
			while (str.GetLength()<6)//����6λ��ʾ
			{
				str = " "+str;
			}
			pDataPage.m_left.Display(str);
		break;
		}
		
	default:
		break;
	}
	
}

void CACSDlg::PackageShipData(unsigned char *buf, int len)
{
	int totlevaliddatabytelen =0;
	mfskSYSPOSITION mfsksysposition;
	totlevaliddatabytelen = len/4;//�ֽ���

	memset(&mfsksysposition,0,sizeof(mfskSYSPOSITION));

	BYTE *tempbuf=  (BYTE*)malloc(totlevaliddatabytelen*4);//Ҫ���͵�������Ч����
	
	int *codedframebit = (int *)malloc(totlevaliddatabytelen*8*sizeof(int));//û���ŵ�����ı�����,Ϊ�˾��
	int *ConvCodedbit = (int *)malloc(totlevaliddatabytelen*8*4*sizeof(int));//��������ı�����
	int *FinalCodedbit = (int *)malloc(totlevaliddatabytelen*8*4*sizeof(int));//��֯��ı�����
	memset(codedframebit,0,totlevaliddatabytelen*8*sizeof(int));
	memset(ConvCodedbit,0,totlevaliddatabytelen*8*4*sizeof(int));
	memset(FinalCodedbit,0,totlevaliddatabytelen*8*4*sizeof(int));
	memset(tempbuf,0,4*totlevaliddatabytelen*sizeof(BYTE));
	BYTE acousticdata[SHIPMFSKSIZE];//ĸ����ѧ���ݻ���
	memset(&acousticdata,0,SHIPMFSKSIZE*sizeof(BYTE));

	mfsksysposition.ltime = subpost.ltime[0];//
	CTime ct = CTime(mfsksysposition.ltime);
	CTimeSpan ts;
	int i =1;
	while ((subpost.ltime[i].dwHighDateTime)&&(subpost.ltime[i].dwLowDateTime)&&(i<5))
	{
		ts = CTime(subpost.ltime[i]) - ct;
		int t = ts.GetTotalSeconds();
		if (t>255)
		{
			t=255;
		}
		mfsksysposition.interval[i-1] = t;
		i++;
	}

	//��λ����
	memcpy(mfsksysposition.subLAT,subpost.subLAT,5*sizeof(float));
	memcpy(mfsksysposition.subLONG,subpost.subLONG,5*sizeof(float));
	mfsksysposition.shipLAT = sysposition.shipLAT;
	mfsksysposition.shipLONG = sysposition.shipLONG;
	mfsksysposition.relateX = sysposition.relateX;
	mfsksysposition.relateY = sysposition.relateY;
	mfsksysposition.relateZ = sysposition.relateZ;
	mfsksysposition.subdepth = sysposition.subdepth;
	USHORT nCRC16 = pDataPackage.CRC16((BYTE*)&mfsksysposition,sizeof(mfskSYSPOSITION));
	memcpy(&acousticdata,&mfsksysposition,sizeof(mfskSYSPOSITION));
	memcpy(&acousticdata[sizeof(mfskSYSPOSITION)],(BYTE*)&nCRC16,sizeof(USHORT));

	//����
	if(!m_WzdtextList.IsEmpty())
	{

		memcpy(&acousticdata[sizeof(mfskSYSPOSITION)+sizeof(USHORT)],(unsigned char *)m_WzdtextList.GetHead()->buf,m_WzdtextList.GetHead()->len);//����
		free(m_WzdtextList.RemoveHead());
		//		m_WzdtextList.RemoveAll();
	}
	nCRC16 = pDataPackage.CRC16(&acousticdata[sizeof(mfskSYSPOSITION)+2],WORDSIZE);
	memcpy(&acousticdata[sizeof(mfskSYSPOSITION)+sizeof(USHORT)+WORDSIZE],(BYTE*)&nCRC16,sizeof(USHORT));

	//����ԭ�����ļ�
	XMTFSKFile.Init("fsk",1*FILESIZE,1024,4*WRITESIZE);
	XMTFSKFile.SaveFile((char*)&acousticdata,SHIPMFSKSIZE);
	XMTFSKFile.CloseFile();

	//�õ�������
	for(i=0;i<SHIPMFSKSIZE;i++)
	{
		for(int j=0;j<8;j++)
		{
			codedframebit[8*i+j] = (acousticdata[i]>>j)&0x01;
	
		}
	}
// 	XMTFSKFile.Init("codedframebit",1*FILESIZE,1024,4*WRITESIZE);
// 	XMTFSKFile.SaveFile((char*)codedframebit,totlevaliddatabytelen*8*sizeof(int));
// 	XMTFSKFile.CloseFile();
	pDataPackage.scrambling(codedframebit,(totlevaliddatabytelen-1)*8);//����(ǰtotlevaliddatabytelen-1�ֽ�)
// 	XMTFSKFile.Init("afterscramb",1*FILESIZE,1024,4*WRITESIZE);
// 	XMTFSKFile.SaveFile((char*)codedframebit,totlevaliddatabytelen*8*sizeof(int));
// 	XMTFSKFile.CloseFile();
	pDataPackage.One2FourConvolution(codedframebit,ConvCodedbit,totlevaliddatabytelen*8);//1-4���
// 	XMTFSKFile.Init("after14",1*FILESIZE,1024,4*WRITESIZE);
// 	XMTFSKFile.SaveFile((char*)ConvCodedbit,totlevaliddatabytelen*8*4*sizeof(int));
// 	XMTFSKFile.CloseFile();
	pDataPackage.Interleave(ConvCodedbit,FinalCodedbit);//��֯
// 	XMTFSKFile.Init("afterinter",1*FILESIZE,1024,4*WRITESIZE);
// 	XMTFSKFile.SaveFile((char*)FinalCodedbit,totlevaliddatabytelen*8*4*sizeof(int));
// 	XMTFSKFile.CloseFile();
	////�õ�ѹ��������
	for(i=0;i<totlevaliddatabytelen*4;i++)
	{
		for(int j=0;j<8;j++)
		{
			tempbuf[i] += (FinalCodedbit[8*i+j]&0x01)<<j;
		}
	} 
	memcpy(buf,tempbuf,totlevaliddatabytelen*4);
	//����ԭ�����ļ�
	XMTFSKFile.Init("XMTfsk",1*FILESIZE,1024,4*WRITESIZE);
	XMTFSKFile.SaveFile((char*)buf,totlevaliddatabytelen*4);
	XMTFSKFile.CloseFile();
	free(tempbuf);
	free(codedframebit);
	free(ConvCodedbit);
	free(FinalCodedbit);
}

void CACSDlg::PackageUWAData(unsigned char *buf, int len)
{
	int totlevaliddatabytelen =0;
	int i=0;

	totlevaliddatabytelen = UWACInitParam.XMTPackageNum*UWACInitParam.XMTPackFramNum
						*UWACInitParam.MFSKDataSymbolNum*30/8/4;//�ֽ���
	memset(&mfsksubposition,0,sizeof(mfskSUBPOSITION));
	memset(&mfskbsssdata,0,sizeof(mfskBSSSDATA));
	memset(&mfskbpdata,0,sizeof(mfskBPDATA));
	memset(&mfskctddata,0,sizeof(mfskCTDDATA));
	memset(&mfsklifesupply,0,sizeof(mfskLIFESUPPLY));
	memset(&mfskenergysys,0,sizeof(mfskENERGYSYS));
	memset(&mfskalertdata,0,sizeof(mfskALERTDATA));
	memset(&mfskswitchdata,0,sizeof(mfskSWITCHDATA));
	memset(&mfskadcpdata,0,sizeof(ADCPDATA));

	
	
	BYTE *tempbuf = (BYTE *) malloc(totlevaliddatabytelen*4);//������ʱ������,Ҫ���͵�������Ч����
	
	int *codedframebit = (int *)malloc(totlevaliddatabytelen*8*sizeof(int));//û���ŵ�����ı�����+1Ϊ�˾��
	int *ConvCodedbit = (int *)malloc(totlevaliddatabytelen*8*4*sizeof(int));//��������ı�����
	int *FinalCodedbit = (int *)malloc(totlevaliddatabytelen*8*4*sizeof(int));//��֯��ı�����
	memset(codedframebit,0,totlevaliddatabytelen*8*sizeof(int));
	memset(ConvCodedbit,0,totlevaliddatabytelen*8*4*sizeof(int));
	memset(FinalCodedbit,0,totlevaliddatabytelen*8*4*sizeof(int));
	BYTE acousticdata[UWAMFSKSIZE];//ĸ����ѧ���ݻ���
	memset(&acousticdata,0,UWAMFSKSIZE*sizeof(BYTE));
	memset(tempbuf,0,4*totlevaliddatabytelen*sizeof(BYTE));

	//bp
	mfskbpdata.behinddown = bpdata.behinddown/256;
	mfskbpdata.down = bpdata.down/256;
	mfskbpdata.front = bpdata.front/256;
	mfskbpdata.frontdown = bpdata.frontdown/256;
	mfskbpdata.frontup = bpdata.frontup/256;
	mfskbpdata.left = bpdata.left/256;
	mfskbpdata.right = bpdata.right/256;
	memcpy(&acousticdata,&mfskbpdata,sizeof(mfskBPDATA));

	//bsss
	mfskbsssdata.depth = bsssdata.depth/256;
	acousticdata[sizeof(mfskBPDATA)] = mfskbsssdata.depth;

	//��λ����
	mfsksubposition.subLONG = subposition.subLONG;
	mfsksubposition.subLAT = subposition.subLAT;
	mfsksubposition.subheading = subposition.subheading;
	mfsksubposition.subpitch = subposition.subpitch;
	mfsksubposition.subroll = subposition.subroll;
	mfsksubposition.subupdownvec = subposition.subupdownvec/256;
	mfsksubposition.subpitchvec = subposition.subpitchvec/256;
	mfsksubposition.subrollvec = subposition.subrollvec/256;
	mfsksubposition.subdepth = subposition.subdepth;
	mfsksubposition.subheight = subposition.subheight/256;
	memcpy(&acousticdata[sizeof(mfskBPDATA)+sizeof(mfskBSSSDATA)],&mfsksubposition,sizeof(mfskSUBPOSITION));


	//ctd
	mfskctddata.watertemp = ctddata.watertemp;
	mfskctddata.watercond = ctddata.watercond;
	mfskctddata.soundvec  = ctddata.soundvec/256;
	mfskctddata.vartlevel = ctddata.vartlevel/4;
	memcpy(&acousticdata[sizeof(mfskBPDATA)+sizeof(mfskBSSSDATA)+sizeof(mfskSUBPOSITION)],&mfskctddata,sizeof(mfskCTDDATA));
	//lifesupply
	mfsklifesupply.CO2 = lifesupply.CO2;
	mfsklifesupply.humidity = lifesupply.humidity/256;
	mfsklifesupply.oxygen = lifesupply.oxygen;
	mfsklifesupply.pressure = lifesupply.pressure;
	mfsklifesupply.temperature = lifesupply.temperature;
	memcpy(&acousticdata[sizeof(mfskBPDATA)+sizeof(mfskBSSSDATA)+sizeof(mfskSUBPOSITION)+sizeof(mfskCTDDATA)],
		&mfsklifesupply,sizeof(mfskLIFESUPPLY));

	//energy
	mfskenergysys.mainconsume = energysys.mainconsume/256;
	mfskenergysys.subconsume = energysys.subconsume/256;
	mfskenergysys.mainI = energysys.mainI/256;
	mfskenergysys.mainV = energysys.mainV/256;
	mfskenergysys.subI = energysys.subI/256;
	mfskenergysys.subV = energysys.subV/256;
	memcpy(&acousticdata[sizeof(mfskBPDATA)+sizeof(mfskBSSSDATA)+sizeof(mfskSUBPOSITION)+sizeof(mfskCTDDATA)+sizeof(mfskLIFESUPPLY)],
		&mfskenergysys,sizeof(mfskENERGYSYS));

	//alert
	mfskalertdata.aleak = alertdata.aleak;
	mfskalertdata.behind = alertdata.behind/256;
	mfskalertdata.cable = alertdata.cable/256;
	mfskalertdata.head = alertdata.head/256;
	mfskalertdata.pressure = alertdata.pressure/256;
	mfskalertdata.temperature = alertdata.temperature;
	memcpy(mfskalertdata.alert,alertdata.alert,4*sizeof(BYTE));
	memcpy(&acousticdata[sizeof(mfskBPDATA)+sizeof(mfskBSSSDATA)+sizeof(mfskSUBPOSITION)
		+sizeof(mfskCTDDATA)+sizeof(mfskLIFESUPPLY)+sizeof(mfskENERGYSYS)],
		&mfskalertdata,sizeof(mfskALERTDATA));

	//switch����ת��
	memcpy(&acousticdata[sizeof(mfskBPDATA)+sizeof(mfskBSSSDATA)+sizeof(mfskSUBPOSITION)
		+sizeof(mfskCTDDATA)+sizeof(mfskLIFESUPPLY)+sizeof(mfskENERGYSYS)+sizeof(mfskALERTDATA)],
		&mfskswitchdata,sizeof(mfskSWITCHDATA));
	
 	UCHAR nCRC8 = pDataPackage.CRC8_Tab((BYTE*)&acousticdata,57);
	acousticdata[57] = nCRC8;//too many sizeof,use 57
//first part done!
	memcpy(&acousticdata[58],&adcpdata,sizeof(ADCPDATA));
	nCRC8 = pDataPackage.CRC8_Tab((BYTE*)&acousticdata[58],sizeof(ADCPDATA));
 	acousticdata[88] = nCRC8;
//second part done!

//����
	if(!m_WzdtextList.IsEmpty())
	{
		memcpy(&acousticdata[89],(unsigned char *)m_WzdtextList.GetHead()->buf,m_WzdtextList.GetHead()->len);//����
		free(m_WzdtextList.RemoveHead());
//		m_WzdtextList.RemoveAll();
	}
	USHORT nCRC16 = pDataPackage.CRC16(&acousticdata[89],WORDSIZE);
	memcpy(&acousticdata[89+WORDSIZE],(BYTE*)&nCRC16,sizeof(USHORT));

//third part done!

	//����ԭ�����ļ�
	XMTFSKFile.Init("subFSK",1*FILESIZE,1024,4*WRITESIZE);
	XMTFSKFile.SaveFile((char*)&acousticdata,UWAMFSKSIZE);
	XMTFSKFile.CloseFile();

	
	//�õ�������
	for(i=0;i<UWAMFSKSIZE;i++)
	{
		for(int j=0;j<8;j++)
		{
			codedframebit[8*i+j] = (acousticdata[i]>>j)&0x01;
	
		}
	}

	pDataPackage.scrambling(codedframebit,(totlevaliddatabytelen-1)*8);//����(ǰtotlevaliddatabytelen-1�ֽ�)

	pDataPackage.One2FourConvolution(codedframebit,ConvCodedbit,totlevaliddatabytelen*8);//1-4���

	pDataPackage.Interleave(ConvCodedbit,FinalCodedbit);//��֯

	////�õ�ѹ��������
	for(i=0;i<totlevaliddatabytelen*4;i++)
	{
		for(int j=0;j<8;j++)
		{
			tempbuf[i] += (FinalCodedbit[8*i+j]&0x01)<<j;
		}
	} 
	memcpy(buf,tempbuf,totlevaliddatabytelen*4);
	//���������ļ�
	XMTFSKFile.Init("XMTsubfsk",1*FILESIZE,1024,4*WRITESIZE);
	XMTFSKFile.SaveFile((char*)buf,totlevaliddatabytelen*4);
	XMTFSKFile.CloseFile();
	free(tempbuf);
	free(codedframebit);
	free(ConvCodedbit);
	free(FinalCodedbit);
}

void CACSDlg::PackagePicture(unsigned char *buf, int len)
{
	int totlevaliddatabytelen =0;
	int i=0,j=0;

	totlevaliddatabytelen = UWACInitParam.XMTMPSKPackageNum*UWACInitParam.XMTMPSKPackFramNum
		*UWACInitParam.MPSKDataSymbolNum*2/8;//�ɷ������ֽ���
	int bytelenperframe = UWACInitParam.MPSKDataSymbolNum*2/8;//484
	unsigned char *tempbuf;//������ʱ������,Ҫ���͵�������Ч����
	tempbuf = (unsigned char *) malloc(totlevaliddatabytelen);
	memset(tempbuf,0,totlevaliddatabytelen*sizeof(BYTE));

	BYTE* acousticdata = new BYTE[totlevaliddatabytelen/2];//ĸ����ѧ���ݻ���
	BYTE* formerdata = new BYTE[COLORIMAGESIZE];//����ǰ��ѧ���ݻ���
	BYTE Turbodata[242];//Turbo����ǰ���ݻ���
	memset(acousticdata,0,(totlevaliddatabytelen/2)*sizeof(BYTE));
	memset(formerdata,0,COLORIMAGESIZE*sizeof(BYTE));
	memset(&Turbodata,0,242*sizeof(BYTE));

	int *codedframebit = (int *)malloc(totlevaliddatabytelen/2*8*sizeof(int));//û���ŵ�����ı�����
	int *framebit = (int*)malloc(1936*sizeof(int));
	int *ConvCodedbit = (int *)malloc(1936*2*sizeof(int));//���������ÿ֡������
	memset(framebit,0,1936*sizeof(int));
	memset(codedframebit,0,totlevaliddatabytelen/2*8*sizeof(int));
	memset(ConvCodedbit,0,1936*2*sizeof(int));
	if (!m_WzdimageList.IsEmpty())
	{
		memcpy(formerdata,(unsigned char *)m_WzdimageList.GetHead()->buf,m_WzdimageList.GetHead()->len);
		
	}
	//////////////////////////����ǰ4֡����///////////////////////////////////
	USHORT	nCRC16;
	for (i=0;i<UWACInitParam.XMTMPSKPackageNum*UWACInitParam.XMTMPSKPackFramNum;i++)
	{
		memcpy(acousticdata+i*242,formerdata+i*32,32*sizeof(char));
		memcpy(acousticdata+i*242+32,formerdata+896+i*208,208*sizeof(char));
		nCRC16 = pDataPackage.CRC16(acousticdata+i*242,240);
		memcpy(acousticdata+i*242+240,(BYTE*)&nCRC16,sizeof(USHORT));
	}
	
	//////////////////////////////////////////////////////////////////////////
// 	USHORT	nCRC16 = pDataPackage.CRC16(acousticdata,COLORIMAGESIZE);
// 	memcpy(acousticdata+COLORIMAGESIZE,(BYTE*)&nCRC16,sizeof(USHORT));
	for(i=0;i<(totlevaliddatabytelen/2);i++)
	{
		for(j=0;j<8;j++)
		{
			codedframebit[8*i+j] = (acousticdata[i]>>j)&0x01;
		}
	}//�õ�������
	
	int templocal = 0;
	int local1=0;
	char bytebuf[484];
	memset(bytebuf,0,bytelenperframe);
	
	int m=0;
	XMTPSKFile.Init("PSK",1*FILESIZE,1024,4*WRITESIZE);
	for(int k=0;k<UWACInitParam.XMTMPSKPackageNum*UWACInitParam.XMTMPSKPackFramNum;k++)
	{
		memcpy(framebit,codedframebit+k*1936,1936*sizeof(int));
		memset(Turbodata,0,242*sizeof(char));
		for(i=0;i<242;i++)
		{
			for(j=0;j<8;j++)
			{
				Turbodata[i] += (framebit[8*i+j]&0x01)<<j;
			}
		} //�õ�ѹ��������
		XMTPSKFile.SaveFile((char*)Turbodata,242*sizeof(char));
		for(i=0;i<242;i++)
		{
			if(UWACInitParam.XMTWhiteProcess)//�׻�����
				Turbodata[i] ^= (unsigned char) *((unsigned char *)Whiteseq + i);
			
			
	
			for(j=0;j<8;j++)
				framebit[i*8+j] = (Turbodata[i]>>j)&0x01;//�õ�������
		}
		
		mpskturo.TurboCodeQPSK(framebit,ConvCodedbit);//�ŵ�����
		
	

		memset(bytebuf,0,bytelenperframe*sizeof(char));
		for(m=0;m<bytelenperframe;m++)
		{
			for(j=0;j<8;j++){
				bytebuf[m]+=(ConvCodedbit[8*m+j]&0x01)<<j;//�Ӿ����ı������õ��ֽ���
			}
		}
		memcpy(tempbuf+local1,bytebuf,bytelenperframe);//�����õ���һ֡����
		local1+=bytelenperframe;
		//���������ļ�								
	}
	XMTPSKFile.CloseFile();
	memcpy(buf,tempbuf,local1*sizeof(char));
	XMTPSKFile.Init("XMTPSK",1*FILESIZE,1024,4*WRITESIZE);
	XMTPSKFile.SaveFile((char*)tempbuf,local1*sizeof(char));
	XMTPSKFile.CloseFile();
	delete acousticdata;
	delete formerdata;
	free(framebit);
	free(tempbuf);
	free(codedframebit);
    free(ConvCodedbit);

}

void CACSDlg::ExplainFSKData(BYTE *databuf, int len)
{
	DWORD totlevaliddatabytelen;
	CString str;
	short checksum16 = 0;
	int   frameno;
	totlevaliddatabytelen = 135; 
	int framelength = totlevaliddatabytelen*4/(UWACInitParam.RecvPackFramNum*UWACInitParam.RecvPackageNum);

	if(RecDataBuf==NULL)
	{//Ϊ���ջ����������ڴ�
		RecDataBuf = (BYTE *) malloc(totlevaliddatabytelen*4);//
		memset(RecDataBuf,0,4*totlevaliddatabytelen*sizeof(BYTE));
	}
	frameno = *(DWORD *)databuf;
	if(frameno<UWACInitParam.RecvPackFramNum*UWACInitParam.RecvPackageNum-1)
	{// ��ȷ֡
		if(len!=(52))
		{//�жϳ����Ƿ���ȷ
			str.Format("�յ���MFSK�������ݳ��Ȳ��ԣ�Ϊ%d��\r\n      ʵ�ʳ���Ϊ48��",len-4);//ԭ����45�ֽڣ�DSP���뵽68
			SaveRecord(str);
			if (RecDataBuf)//�´��е���һ��ģʽʱ��������ڴ�����
			{
				free(RecDataBuf);
				RecDataBuf = NULL;
			}
			return;
		}
		if ((frameno!=0)&&(frameno-RecFrameNo>1))
		{
			SaveRecord("��֡�ˣ�����");
			str.Format("��һ��ϰ�����Ϊ%d",(DWORD*)lastpacket[1]);
		}
		memset(lastpacket,0,8192);
		if(frameno<=RecFrameNo)
		{//��һ�����ݽ��յĿ�ʼ,������ղ���
			str.Format("��ʼMFSK���ݽ��գ���ʼ֡��%d��",frameno);
			SaveRecord(str);
			memset(RecDataBuf,0,totlevaliddatabytelen*4);//���������
			RECVFSKFile.CloseFile();
			RECVFSKFile.Init("RECVFSK",FILESIZE,1024,4*WRITESIZE);
		}
		str.Format("�յ�����֡%d",frameno);
		SaveRecord(str);

		RECVFSKFile.SaveFile((char*)databuf+4, framelength);//�����ļ�
		RecFrameNo = frameno;
		memcpy(RecDataBuf+RecFrameNo*framelength,databuf+4,framelength);
	}
	else if (frameno == UWACInitParam.RecvPackFramNum*UWACInitParam.RecvPackageNum-1)//���һ֡
	{
		RecFrameNo = frameno;
		str.Format("�յ�����֡%d",frameno);
		SaveRecord(str);
		int *ConvCodedbit = (int *)malloc(totlevaliddatabytelen*8*4*sizeof(int));//�������ı�����
		int *FinalCodedbit = (int *)malloc(totlevaliddatabytelen*8*4*sizeof(int));//��֯�ı�����
		memset(ConvCodedbit,0,totlevaliddatabytelen*8*4*sizeof(int));
		memset(FinalCodedbit,0,totlevaliddatabytelen*8*4*sizeof(int));
		int *codedframebit = (int *)malloc(totlevaliddatabytelen*8*sizeof(int));//û���ŵ�����ı�����
		memset(codedframebit,0,totlevaliddatabytelen*8*sizeof(int));
		RECVFSKFile.SaveFile((char*)databuf+4, framelength);//�����ļ�
		RECVFSKFile.CloseFile();
		memcpy(RecDataBuf+RecFrameNo*framelength,databuf+4,framelength);
		//bit��
		for(int i=0;i<totlevaliddatabytelen*4;i++)
		{
			for(int j=0;j<8;j++)
			{
				FinalCodedbit[8*i+j] = (RecDataBuf[i]>>j)&0x01;
			}
		}

		pDataPackage.DeInterleave(FinalCodedbit,ConvCodedbit);//�⽻֯

		pDataPackage.ViterbiK7(ConvCodedbit,totlevaliddatabytelen*4*8,codedframebit);//����

		pDataPackage.scrambling(codedframebit,(totlevaliddatabytelen-1)*8);//����

		if (UWACInitParam.ADIOWorkMode==0)//����
		{	
			ParseShipData(codedframebit);
		} 
		else//ˮ��
		{	
			ParseUWAData(codedframebit);
		}
		free(codedframebit);
		free(ConvCodedbit);
		free(FinalCodedbit);
		if (RecDataBuf)
		{
			free(RecDataBuf);
			RecDataBuf = NULL;
		}
		
	}
	else//�Ƿ�֡
	{
		if (RecDataBuf)
		{
			free(RecDataBuf);
			RecDataBuf = NULL;
		}
		str.Format("�յ���MFSK��������֡�Ų���!Ϊ%d��",frameno);
		SaveRecord(str);
	}

}

void CACSDlg::ExplainPSKData(BYTE *databuf, int len)
{
	DWORD totlevaliddatabytelen;
	CString str;
	USHORT checksum16 = 0;
	int   frameno;
	int i=0;
	totlevaliddatabytelen = UWACInitParam.RecvMPSKPackageNum*UWACInitParam.RecvMPSKPackFramNum*UWACInitParam.MPSKDataSymbolNum/8; 	
	if(RecDataBuf==NULL)
	{//Ϊ���ջ����������ڴ�
		RecDataBuf = (BYTE *) malloc(totlevaliddatabytelen);//
		memset(RecDataBuf,0,totlevaliddatabytelen*sizeof(BYTE));
	}
	BYTE* formerdata = new BYTE[totlevaliddatabytelen];//����ǰ��ѧ���ݻ���
	frameno = *(DWORD *)databuf;
	if(frameno<UWACInitParam.RecvMPSKPackageNum*UWACInitParam.RecvMPSKPackFramNum-1)
	{// ��ȷ֡
		if(len!=(248))
		{//�жϳ����Ƿ���ȷ
			str.Format("�յ���PSK�������ݳ��Ȳ��ԣ�Ϊ%d��\r\n      ��ȷ����Ϊ244��",len-4);
			SaveRecord(str);
			if (RecDataBuf)//�´��е���һ��ģʽʱ��������ڴ�����
			{
				free(RecDataBuf);
				RecDataBuf = NULL;
			}
			iframenum =0;
			return;
		}

		if(frameno==0)
		{//��һ�����ݽ��յĿ�ʼ,������ղ���
			str.Format("��ʼ����PSK�źţ���ʼ֡��%d��",frameno);
			SaveRecord(str);
			iframenum = 0;
			memset(RecDataBuf,0,totlevaliddatabytelen);//���������
			RECVPSKFile.CloseFile();
			RECVPSKFile.Init("RECVPSK",FILESIZE,1024,4*WRITESIZE);
			
		}
		
		str.Format("�յ�����֡%d",frameno);
		SaveRecord(str);
		if (frameno==1&&RecFrameNo==27)
		{
			str.Format("δ�յ���0֡����!");
			SaveRecord(str);
			RECVPSKFile.CloseFile();
			RECVPSKFile.Init("RECVPSK",FILESIZE,1024,4*WRITESIZE);
		}
		RecFrameNo = frameno;
		for(i=0;i<242;i++)
		{
			if(UWACInitParam.XMTWhiteProcess)//�׻�����
				databuf[4+i] ^= (unsigned char) *((unsigned char *)Whiteseq + i);
		
		}
		
		RECVPSKFile.SaveFile((char*)databuf+4, 242);//�����ļ�
		
		
		memcpy(RecDataBuf+iframenum*UWACInitParam.MPSKDataSymbolNum/8,databuf+4,UWACInitParam.MPSKDataSymbolNum/8);
		memcpy((BYTE*)&checksum16,(BYTE*)&RecDataBuf[(iframenum+1)*UWACInitParam.MPSKDataSymbolNum/8-2],sizeof(USHORT));//crc16
		USHORT CRC16 = pDataPackage.CRC16(RecDataBuf+iframenum*UWACInitParam.MPSKDataSymbolNum/8,240);
		if (checksum16==CRC16)
		{
			str.Format("����֡%dУ����ȷ",frameno);
			SaveRecord(str);
		}
		else
		{
			str.Format("����֡%dУ�����",frameno);
			SaveRecord(str);
			memset(RecDataBuf+iframenum*UWACInitParam.MPSKDataSymbolNum/8,0,UWACInitParam.MPSKDataSymbolNum/8);
		}
		iframenum++;
	}
	else if (frameno == UWACInitParam.RecvMPSKPackageNum*UWACInitParam.RecvMPSKPackFramNum-1)//���һ֡
	{
		RecFrameNo = frameno;
		str.Format("�յ�����֡%d",frameno);
		SaveRecord(str);
		
		for(i=0;i<242;i++)
		{
			if(UWACInitParam.XMTWhiteProcess)//�׻�����
				databuf[4+i] ^= (unsigned char) *((unsigned char *)Whiteseq + i);
		
		}
		RECVPSKFile.SaveFile((char*)databuf+4, 242);//�����ļ�
		RECVPSKFile.CloseFile();
		memcpy(RecDataBuf+iframenum*UWACInitParam.MPSKDataSymbolNum/8,databuf+4,UWACInitParam.MPSKDataSymbolNum/8);
		memcpy((BYTE*)&checksum16,(BYTE*)&RecDataBuf[(iframenum+1)*UWACInitParam.MPSKDataSymbolNum/8-2],sizeof(USHORT));//crc16
		USHORT CRC16 = pDataPackage.CRC16(RecDataBuf+iframenum*UWACInitParam.MPSKDataSymbolNum/8,240);
		if (checksum16==CRC16)
		{
			str.Format("����֡%dУ����ȷ",frameno);
			SaveRecord(str);
			
		}
		else
		{
			str.Format("����֡%dУ�����",frameno);
			SaveRecord(str);
			memset(RecDataBuf+iframenum*UWACInitParam.MPSKDataSymbolNum/8,0,UWACInitParam.MPSKDataSymbolNum/8);
		}
		iframenum =0;
		memcpy(formerdata,RecDataBuf,sizeof(char)*(totlevaliddatabytelen));
		for (i=0;i<28;i++)
		{
			memcpy(RecDataBuf+i*32,formerdata+i*242,32*sizeof(char));
			memcpy(RecDataBuf+896+i*208,formerdata+i*242+32,208*sizeof(char));
		}

		if (UWACInitParam.ADIOWorkMode)//�ӻ�
		{
			str.Format("��ǰͨ�ž��룺%.1f",CommunicationParam.reserved[0]*1.5);
			SaveRecord(str);
			bFirstRecvData = TRUE;
		}
		
			
		memcpy(CompressValue,RecDataBuf,COLORIMAGESIZE);
		imageDecode.ColorDecode(mybuffernew,CompressValue,256);
		CRect rect;
		CWnd* pWnd= GetDlgItem(IDC_IMAGE);
		pWnd->GetClientRect(&rect);
		m_ShowImage.InvalidateRect(&rect);
		char filename[256];
		sprintf(filename,"%s",RECVPSKFile.m_Path+"RECV_IMAGE");
		CreateFileName(filename,".bmp",filename);
		m_ShowImage.m_Dib.Save(filename);
		if (RecDataBuf)
		{
			free(RecDataBuf);
			RecDataBuf = NULL;
		}
		CTime nowtime;
		nowtime = CTime::GetCurrentTime();
		str.Format("%02d:%02d:%02d",nowtime.GetHour(),nowtime.GetMinute(),nowtime.GetSecond());
		SetDlgItemText(IDC_PIC_RECVTIME,str);
	}
	else//�Ƿ�֡
	{
		if (RecDataBuf)
		{
			free(RecDataBuf);
			RecDataBuf = NULL;
		}
		iframenum = 0;
		str.Format("�յ���PSK��������֡�Ų��ԣ�Ϊ%d��",frameno);
		SaveRecord(str);
	}
	delete formerdata;

}
/*
void CACSDlg::ExplainPSKData(BYTE *databuf, int len)
{
	DWORD totlevaliddatabytelen;
	CString str;
	short checksum16 = 0;
	int   frameno;
	int i=0;
	totlevaliddatabytelen = UWACInitParam.RecvMPSKPackageNum*UWACInitParam.RecvMPSKPackFramNum*UWACInitParam.MPSKDataSymbolNum/8; 	
	if(RecDataBuf==NULL)
	{//Ϊ���ջ����������ڴ�
		RecDataBuf = (BYTE *) malloc(totlevaliddatabytelen);//
		memset(RecDataBuf,0,totlevaliddatabytelen*sizeof(BYTE));
	}
	frameno = *(DWORD *)databuf;
	if(frameno<UWACInitParam.RecvMPSKPackageNum*UWACInitParam.RecvMPSKPackFramNum-1)
	{// ��ȷ֡
		if(len!=(248))
		{//�жϳ����Ƿ���ȷ
			str.Format("�յ���QPSK�������ݳ��Ȳ��ԣ�Ϊ%d��\r\n      ʵ�ʳ���Ϊ244��",len-4);
			SaveRecord(str);
			if (RecDataBuf)//�´��е���һ��ģʽʱ��������ڴ�����
			{
				free(RecDataBuf);
				RecDataBuf = NULL;
			}
			iframenum =0;
			return;
		}

		if(frameno==0)
		{//��һ�����ݽ��յĿ�ʼ,������ղ���
			str.Format("��ʼ��һ�����ݽ��գ���ʼ֡��%d��",frameno);
			SaveRecord(str);
			iframenum = 0;
			memset(RecDataBuf,0,totlevaliddatabytelen);//���������
			RECVPSKFile.CloseFile();
			RECVPSKFile.Init("RECVPSK",FILESIZE,1024,4*WRITESIZE);
		}
		str.Format("�յ�����֡%d",frameno);
		SaveRecord(str);
	
		for(i=0;i<242;i++)
		{
			if(UWACInitParam.XMTWhiteProcess)//�׻�����
				databuf[4+i] ^= (unsigned char) *((unsigned char *)Whiteseq + i);
		
		}
		RECVPSKFile.SaveFile((char*)databuf+4, 242);//�����ļ�
		RecFrameNo = frameno;
		memcpy(RecDataBuf+iframenum*UWACInitParam.MPSKDataSymbolNum/8,databuf+4,UWACInitParam.MPSKDataSymbolNum/8);
		iframenum++;
	}
	else if (frameno == UWACInitParam.RecvMPSKPackageNum*UWACInitParam.RecvMPSKPackFramNum-1)//���һ֡
	{
		RecFrameNo = frameno;
		str.Format("�յ�����֡%d",frameno);
		SaveRecord(str);
		RECVPSKFile.SaveFile((char*)databuf+4, 242);//�����ļ�
		RECVPSKFile.CloseFile();
		for(i=0;i<242;i++)
		{
			if(UWACInitParam.XMTWhiteProcess)//�׻�����
				databuf[4+i] ^= (unsigned char) *((unsigned char *)Whiteseq + i);
		
		}
		memcpy(RecDataBuf+iframenum*UWACInitParam.MPSKDataSymbolNum/8,databuf+4,UWACInitParam.MPSKDataSymbolNum/8);
		iframenum =0;
		USHORT chechsum16;
		memcpy((BYTE*)&chechsum16,(BYTE*)&RecDataBuf[COLORIMAGESIZE],sizeof(USHORT));//crc16
		USHORT CRC16 = pDataPackage.CRC16(RecDataBuf,COLORIMAGESIZE);
		if (CRC16==chechsum16)
		{
			SaveRecord("ͼƬУ����ȷ��");
		}
		else
		{
			SaveRecord("ͼƬУ�鲻��ȷ��");
		}
		str.Format("��ǰͨ�ž��룺%.1f",CommunicationParam.reserved[0]*1.5);
		SaveRecord(str);	
		memcpy(CompressValue,RecDataBuf,COLORIMAGESIZE);
		imageDecode.ColorDecode(mybuffernew,CompressValue,256);
		CRect rect;
		CWnd* pWnd= GetDlgItem(IDC_IMAGE);
		pWnd->GetClientRect(&rect);
		m_ShowImage.InvalidateRect(&rect);
		char filename[256];
		sprintf(filename,"%s",RECVPSKFile.m_Path+"RECV_IMAGE");
		CreateFileName(filename,".bmp",filename);
		m_ShowImage.m_Dib.Save(filename);
		if (RecDataBuf)
		{
			free(RecDataBuf);
			RecDataBuf = NULL;
		}
		CTime nowtime;
		nowtime = CTime::GetCurrentTime();
		str.Format("%02d:%02d:%02d",nowtime.GetHour(),nowtime.GetMinute(),nowtime.GetSecond());
		SetDlgItemText(IDC_PIC_RECVTIME,str);
	}
	else//�Ƿ�֡
	{
		if (RecDataBuf)
		{
			free(RecDataBuf);
			RecDataBuf = NULL;
		}
		iframenum = 0;
		str.Format("�յ���QPSK��������֡�Ų��ԣ�Ϊ%d��",frameno);
		SaveRecord(str);
	}

}
*/
void CACSDlg::ExplainFHData(BYTE *databuf, int len)//�յ���Ƶ��Ϣ
{
	CString str,strlog;
	if (len<32)
	{
		strlog.Format("�յ����ݳ��Ȳ��ԣ�len=%d",len);
		SaveRecord(strlog);
	}
	for (int i=0;i<8;i++)
	{
		if (databuf[i*4] == 0)
		{
			break;
		}
		
		str += databuf[i*4];
	}
	strlog = "�յ���Ƶ��Ϣ:" + str;
// 	CString strtime;
// 	CTime ct = CTime::GetCurrentTime();
// 	strtime.Format("%02d:%02d:%02d ",ct.GetHour(),ct.GetMinute(),ct.GetSecond());
// 	strtime = strtime + strlog + "\r\n";
// 	XMTFSFile.SaveFile(strtime, strtime.GetLength());
	SaveRecord(strlog);
	InputFhLog(strlog);
}

void CACSDlg::OnFhSend() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_fhstring.GetLength()==0)
	{
		return;
	}
	if(m_fhstring.GetLength()>8)//ֻ�����͸��ֽ�
	{
		m_fhstring = m_fhstring.Left(8);  //ȡǰ8���ֽ�
		UpdateData(FALSE);  //������Ļ�ϵ�����
	}
	CString strlog;
	strlog = "������Ƶ��Ϣ:" + m_fhstring;


	SaveRecord(strlog);
	InputFhLog(strlog);
	if (UWACInitParam.ADIOWorkMode==1)
	{
	
 		NET_PACKET *netpacket;
		netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
		if(netpacket==NULL)
		{
			AfxMessageBox("����NET_PACKET�ռ�����쳣��");
			return;
		}
		
		netpacket->FrmID = UWACCMD_FORCE_TRANSMIT;
		netpacket->FrmLen = 32;
		netpacket->DestID = ADIOID;
		netpacket->HeadParam[0] = FHMOD;//
		netpacket->HeadParam[1] = 1;//�ܰ���
		netpacket->HeadParam[2] = 0;//��ǰ����
		netpacket->HeadParam[3] = 0;//�����ݳ���]
		netpacket->HeadParam[4] = FHMOD;//�����ݳ���
		netpacket->pData = NULL;
		SendNetpacketSync.Lock();
		m_WzdNetpacketList.AddTail(netpacket);
		SendNetpacketSync.Unlock();
		SetEvent(IsNetpacketEvent);	
	}
	UWACInitParam.XMTModulation =FHMOD;
	if (UWACInitParam.ADIOWorkMode&&UsblEnableCheck)
	{
		//д���ڽ�ֹ���̻���
		if (hyLPT)
		{
			LPT_Writedata(hyLPT,0x99);  //B0_DQ=1 ,�ͷ�DQ�ߣ�B6_DQ=1������B6
		}
		SetTimer(USBLTIME3,8000,NULL);
	}
}

void CACSDlg::InputFhLog(CString strlog)
{
	CString str,strtime;
	CTime ct = CTime::GetCurrentTime();
	strtime.Format("%02d:%02d:%02d ",ct.GetHour(),ct.GetMinute(),ct.GetSecond());
	str = strtime + strlog + "\r\n";
	RECVFSFile.SaveFile(str,str.GetLength());
	m_fhlog+=str;
	if (m_fhlog.GetLength()>1024)
	{
		m_fhlog = m_fhlog.Right(512);
	}
	UpdateData(FALSE);
	CEdit* pEdit = (CEdit*)GetDlgItem(IDC_FHLOG);
	pEdit->LineScroll(pEdit->GetLineCount(),0);
	pEdit = (CEdit*)GetDlgItem(IDC_EDIT_LOG);
	pEdit->LineScroll(pEdit->GetLineCount(),0);
	
}

void CACSDlg::ExplainUDPPackage(char *bufr, int receivenum)
{
//���淢���ļ�
	time_t * nowtime;//����ʱ�䶯̬�ռ䷵��ָ��
	CString pchar_buffer;
	char *p_display_time;//ctime(nowtime)����ָ��
	nowtime=(time_t *)malloc(sizeof(time_t));//����ʱ�䶯̬�ռ�
	if(nowtime==NULL){
		AfxMessageBox("����time_t�ռ�����쳣��");
		exit(EXIT_FAILURE);	
	}
	CString str;
	ASSERT(time(nowtime)!=-1);
	p_display_time=ctime(nowtime);
	if(nowtime!=NULL)//�ͷ�ʱ�䶯̬�ռ�
	free(nowtime);

	if(*(bufr)==0x01 && *(bufr+1)==0x10)
	{
		pchar_buffer.Format("\r\n����ʱ��:%s ����: %x \n",p_display_time,*bufr);
		MarineDataFile.SaveFile(pchar_buffer,pchar_buffer.GetLength());
		MarineDataFile.SaveFile(bufr,sizeof(SUBPOSITION));
		memcpy(&subposition,bufr+2,sizeof(SUBPOSITION));	
		DisplayData(1);
		pDataPage.UpdateTimeDisplay("�㲥");

	}//end if
	else if(*(bufr)==0x02 && *(bufr+1)==0x10)
	{
		pchar_buffer.Format("\r\n����ʱ��:%s ����: %x \n",p_display_time,*bufr);
		MarineDataFile.SaveFile(pchar_buffer,pchar_buffer.GetLength());
		MarineDataFile.SaveFile(bufr,sizeof(CTDDATA));
		memcpy(&ctddata,bufr+2,sizeof(CTDDATA));


		double fValue;
		fValue=(float)(ctddata.watertemp)*50.0/65536;
		str.Format("%.2f ��",fValue);
		SetDlgItemText(IDC_MARINE_TEMP,str);//TEMPERATURE
		
// 		double temp,press,cond,r,c,b,a,rt,salt;
// 		temp=(float)ctddata.watertemp*50/65536;
// 		press=(float)(subposition.subdepth)*8000.0/65536;
// 		cond=(float)ctddata.watercond/65536*5000/1000;
// 		r=((((1.0031E-9)*temp-6.9698E-7)*temp+1.104259E-4)*temp+2.00564E-2)*temp+0.6766097;
// 		c=(((3.989E-15)*press-6.370E-10)*press+2.070E-5)*press;
// 		b=((4.464E-4)*temp+3.426E-2)*temp+1;
// 		a=-(3.107E-3)*temp+0.4215;
// 		rt=sqrt((cond/42.914)/(r*(1+c/(a*r+b))));
// 		salt=((((2.7081*rt-7.0261)*rt+14.0941)*rt+25.3851)*rt-0.1692)*rt+0.0080+((temp-15)/(1+0.0162*(temp-15)))*(((((0.0636-0.0144*rt)*rt-0.0375)*rt-0.0066)*rt-0.0056)*rt+0.0005);
// 		str.Format("%.2f",salt);			
// 		SetDlgItemText(IDC_MARINE_SALT,str);
			
	}
	else if(*(bufr)==0x03 && *(bufr+1)==0x10)
	{
		pchar_buffer.Format("\r\n����ʱ��:%s ��������: %x \n",p_display_time,*bufr);
		MarineDataFile.SaveFile(pchar_buffer,pchar_buffer.GetLength());
		MarineDataFile.SaveFile(bufr,14);
		memcpy(&lifesupply,bufr+2,14);
		
		str.Format("%.2f",(float)lifesupply.CO2*10/256);
		SetDlgItemText(IDC_CO2,str);
		str.Format("%.2f",(float)lifesupply.pressure);
		SetDlgItemText(IDC_MARINE_PRESSURE,str);
		str.Format("%.2f",(float)lifesupply.oxygen*50/256);
		SetDlgItemText(IDC_MARINE_O2,str);
		str.Format("%.2f",(float)lifesupply.temperature*50/256);
		SetDlgItemText(IDC_MARINE_TEMPINSIDE,str);
		str.Format("%.2f",(float)lifesupply.humidity*100/65536);
		SetDlgItemText(IDC_MARINE_HUMID,str);

	}
	else if(*(bufr)==0x04 && *(bufr+1)==0x10)
	{
		pchar_buffer.Format("\r\n����ʱ��:%s ��������: %x \n",p_display_time,*bufr);
		MarineDataFile.SaveFile(pchar_buffer,pchar_buffer.GetLength());
		MarineDataFile.SaveFile(bufr,20);
		memcpy(&energysys,bufr+2,20);
		str.Format("%.2f",(float)energysys.mainI*500/65535);
		SetDlgItemText(IDC_MAIN_I,str);
		str.Format("%.2f",(float)energysys.mainV*200/65535);
		SetDlgItemText(IDC_MAIN_V,str);
	}
	else if(*(bufr)==0x05 && *(bufr+1)==0x10)
	{
		pchar_buffer.Format("\r\n����ʱ��:%s ��������: %x \n",p_display_time,*bufr);
		MarineDataFile.SaveFile(pchar_buffer,pchar_buffer.GetLength());
		MarineDataFile.SaveFile(bufr,22);
		memcpy((BYTE*)&alertdata,(BYTE*)bufr+2,22);
	}
	else if(*(bufr)==0x06 && *(bufr+1)==0x10)
	{
		pchar_buffer.Format("\r\n����ʱ��:%s ��������: %x \n",p_display_time,*bufr);
		MarineDataFile.SaveFile(pchar_buffer,pchar_buffer.GetLength());
		MarineDataFile.SaveFile(bufr,10);
		memcpy(&switchdata,bufr+2,10);
		//ת����ʽ
		int i= int(switchdata.equipNO);
		UCHAR mask= 0x01;
		if (int(switchdata.state)==1)
		{
			
			if (i<=7)
			{
				mask=mask<<i;
				mfskswitchdata.state[0]|=mask;
			}
			else
			{
				mask=mask<<(i-8);
				mfskswitchdata.state[1]|=mask;
			}
		}
		else
		{
			if (i<=7)
			{
				mask=~(mask<<i);
				mfskswitchdata.state[0]&=mask;
			}
			else
			{
				mask=~(mask<<(i-8));
				mfskswitchdata.state[1]&=mask;
			}
		}
	}
	else if(*(bufr)==0x07 && *(bufr+1)==0x10)
	{
		pchar_buffer.Format("\r\n����ʱ��:%s ��������: %x \n",p_display_time,*bufr);
// 		MarineDataFile.SaveFile(pchar_buffer,pchar_buffer.GetLength());
// 		MarineDataFile.SaveFile(bufr,24);
		memcpy((BYTE*)&bpdata,(BYTE*)bufr+2,22);
		DisplayData(2);
		pDataPage.BPUpdateTime("�㲥");
	}
	else if(*(bufr)==0x08 && *(bufr+1)==0x10)
	{
// 		pchar_buffer.Format("\r\n����ʱ��:%s ��������: %x \n",p_display_time,*bufr);
// 		MarineDataFile.SaveFile(pchar_buffer,pchar_buffer.GetLength());
// 		MarineDataFile.SaveFile(bufr,32);
		memcpy((BYTE*)&adcpdata,(BYTE*)bufr+2,30);
		UpdateADCP(adcpdata.floorX,adcpdata.floorY,adcpdata.floorZ,10);
//		SaveRecord("�յ�ADCP����...");
	}


}

void CACSDlg::ParseShipData(int *codedframebit)
{
	BYTE acousticdata[SHIPMFSKSIZE];//ĸ����ѧ���ݻ���
	memset(&acousticdata,0,SHIPMFSKSIZE*sizeof(BYTE));

	for(int m=0;m<SHIPMFSKSIZE;m++)
	{
		for(int j=0;j<8;j++){
			acousticdata[m]+=(codedframebit[8*m+j]&0x01)<<j;//�ӽ�֯��ı������õ��ֽ���
		}
	}

	RECVFSKFile.Init("FSK",FILESIZE,1024,4*WRITESIZE);
	RECVFSKFile.SaveFile((char*)acousticdata,SHIPMFSKSIZE);
	RECVFSKFile.CloseFile();
	//////////////////////////////////////////////////////////////////////////
	//����ĸ����ѧ����
	mfskSYSPOSITION mfskposition;
	memcpy(&mfskposition,acousticdata,sizeof(mfskSYSPOSITION));
	USHORT n16 = pDataPackage.CRC16((UCHAR*)&mfskposition,sizeof(mfskSYSPOSITION));
	USHORT nCRC16 = *(USHORT*)&acousticdata[sizeof(mfskSYSPOSITION)];
	if (n16==nCRC16)//У�����
	{
		SaveRecord("��λ��ϢУ����ȷ��");
		sysposition.ltime = mfskposition.ltime;
		sysposition.relateX = mfskposition.relateX;
		sysposition.relateY = mfskposition.relateY;
		sysposition.relateZ = mfskposition.relateZ;
		sysposition.shipLAT = mfskposition.shipLAT;
		sysposition.shipLONG = mfskposition.shipLONG;
		sysposition.subdepth = mfskposition.subdepth;
		sysposition.subLAT = mfskposition.subLAT[0];
		sysposition.subLONG = mfskposition.subLONG[0];
		char bufsysposition[sizeof(SYSPOSITION)+2];
		*bufsysposition=0x01;
		*(bufsysposition+1)=0x20;
		memcpy(bufsysposition+2,(char*)&sysposition,sizeof(SYSPOSITION));
		if(SEND_FLAG)//��һ��
			OnSend(bufsysposition,sizeof(SYSPOSITION)+2);

		int nSecond = mfskposition.interval[0];
		if (nSecond!=0)
		{
		
			sysposition.ltime.dwLowDateTime+=Int32x32To64(nSecond,10000000);//FILETIME�ӷ�
			sysposition.subLAT = mfskposition.subLAT[1];
			sysposition.subLONG = mfskposition.subLONG[1];
			memcpy(bufsysposition+2,(char*)&sysposition,sizeof(SYSPOSITION));
			if(SEND_FLAG)//�ڶ���
				OnSend(bufsysposition,sizeof(SYSPOSITION)+2);
		}
		nSecond = mfskposition.interval[1];
		if (nSecond!=0)
		{
			sysposition.ltime.dwLowDateTime+=Int32x32To64(nSecond,10000000);//FILETIME�ӷ�
			sysposition.subLAT = mfskposition.subLAT[2];
			sysposition.subLONG = mfskposition.subLONG[2];
			memcpy(bufsysposition+2,(char*)&sysposition,sizeof(SYSPOSITION));
			if(SEND_FLAG)//������
				OnSend(bufsysposition,sizeof(SYSPOSITION)+2);
		}
		nSecond = mfskposition.interval[2];
		if (nSecond!=0)
		{
			sysposition.ltime.dwLowDateTime+=Int32x32To64(nSecond,10000000);//FILETIME�ӷ�
			sysposition.subLAT = mfskposition.subLAT[3];
			sysposition.subLONG = mfskposition.subLONG[3];
			memcpy(bufsysposition+2,(char*)&sysposition,sizeof(SYSPOSITION));
			if(SEND_FLAG)//���İ�
				OnSend(bufsysposition,sizeof(SYSPOSITION)+2);
		}
		nSecond = mfskposition.interval[3];
		if (nSecond!=0)
		{
		sysposition.ltime.dwLowDateTime+=Int32x32To64(nSecond,10000000);//FILETIME�ӷ�
		sysposition.subLAT = mfskposition.subLAT[4];
		sysposition.subLONG = mfskposition.subLONG[4];
		memcpy(bufsysposition+2,(char*)&sysposition,sizeof(SYSPOSITION));
		if(SEND_FLAG)//�����
			OnSend(bufsysposition,sizeof(SYSPOSITION)+2);
		}
		DisplayData(0);//��ʾ��λ����
		pDataPage.UpdateTimeDisplay("USBL");
		pPostPage.iX=((float)sysposition.relateX*15000.0/32768);
		pPostPage.iY=((float)sysposition.relateY*15000.0/32768);
		pPostPage.iZ=((float)sysposition.relateZ*8000.0/65536+1);
		pPostPage.Redraw();
	}
	else
	{
		SaveRecord("��λ��ϢУ�����");
	}
	char chat[41];
	memset(chat,0,41*sizeof(char));
	memcpy(chat,(CHAR*)&acousticdata[sizeof(mfskSYSPOSITION)+2],40*sizeof(char));
	CString str = chat;
	CString strtime;
	n16 = pDataPackage.CRC16((BYTE*)chat,WORDSIZE);
	nCRC16 = *(USHORT*)&acousticdata[sizeof(mfskSYSPOSITION)+2+WORDSIZE];
	if (n16!=nCRC16)
	{
		SaveRecord("����У�����!");
	}
	else
	{
		SaveRecord("����У����ȷ!");
		CTime ct = CTime::GetCurrentTime();
		strtime.Format("%02d:%02d:%02d ",ct.GetHour(),ct.GetMinute(),ct.GetSecond());
// 		if (str.GetLength()==0)
// 		{
// 			str = "��������Ϣ";
// 			pWordPage.InputText(str);
// 			strtime = strtime + str + "\r\n";
// 			TextFile.SaveFile(strtime,strtime.GetLength());
// 		}
// 		else
// 		{
		if (str.GetLength()>0)
 		{
			strtime = strtime + "ĸ��:"  + str + "\r\n";
			TextFile.SaveFile(strtime,strtime.GetLength());
			pWavePage.ShowWindow(SW_HIDE);
			pPostPage.ShowWindow(SW_HIDE);
			pWordPage.ShowWindow(SW_SHOW);
			pPicturePage.ShowWindow(SW_HIDE);
			pDataPage.ShowWindow(SW_HIDE);
			m_tabctrl.SetCurSel(2);
			pWordPage.InputWord(str);
			str = "ĸ��:" + str;
			SaveRecord(str);
		}
		
	}
//	str.Format("��ǰͨ�ž��룺%.1f",CommunicationParam.reserved[0]*1.5);
//	SaveRecord(str);
	

	

}

void CACSDlg::ParseUWAData(int *codedframebit)
{
	BYTE acousticdata[UWAMFSKSIZE];//��ѧ���ݻ���
	memset(&acousticdata,0,UWAMFSKSIZE*sizeof(BYTE));
	CString str;
	for(int m=0;m<UWAMFSKSIZE;m++)
	{
		for(int j=0;j<8;j++){
			acousticdata[m]+=(codedframebit[8*m+j]&0x01)<<j;//�ӽ�֯��ı������õ��ֽ���
		}
	}

	RECVFSKFile.Init("subFSK",FILESIZE,1024,4*WRITESIZE);
	RECVFSKFile.SaveFile((char*)acousticdata,UWAMFSKSIZE);
	RECVFSKFile.CloseFile();
	//////////////////////////////////////////////////////////////////////////
	//����Ǳ��ˮ������
	UCHAR n8 = pDataPackage.CRC8_Tab((UCHAR*)&acousticdata,57);
	UCHAR nCRC8 = acousticdata[57];
	if (n8!=nCRC8)//У�����
	{
		SaveRecord("Ǳ������У�����");
	}
	else//��ȷ
	{	
		SaveRecord("Ǳ������У����ȷ��");
		SYSTEMTIME st;
		FILETIME ft;
		GetSystemTime(&st);
		SystemTimeToFileTime(&st,&ft);//��ȡ��ǰʱ��
		mfskSUBPOSITION mfsksubposition;
		mfskBSSSDATA mfskbsssdata;
		mfskBPDATA mfskbpdata;
		mfskCTDDATA mfskctddata;
		mfskLIFESUPPLY mfsklifesupply;
		mfskENERGYSYS mfskenergysys;
		mfskALERTDATA mfskalertdata;
		ADCPDATA mfskadcpdata;
		memset(&mfsksubposition,0,sizeof(mfskSUBPOSITION));
		memset(&mfskbsssdata,0,sizeof(mfskBSSSDATA));
		memset(&mfskbpdata,0,sizeof(mfskBPDATA));
		memset(&mfskctddata,0,sizeof(mfskCTDDATA));
		memset(&mfsklifesupply,0,sizeof(mfskLIFESUPPLY));
		memset(&mfskenergysys,0,sizeof(mfskENERGYSYS));
		memset(&mfskalertdata,0,sizeof(mfskALERTDATA));
		memset(&mfskswitchdata,0,sizeof(mfskSWITCHDATA));
		memset(&mfskadcpdata,0,sizeof(ADCPDATA));
		//bp
		memcpy(&mfskbpdata,acousticdata,sizeof(mfskbpdata));
		bpdata.behinddown = (unsigned short)mfskbpdata.behinddown*256;
		bpdata.down = (unsigned short)mfskbpdata.down*256;
		bpdata.front = (unsigned short)mfskbpdata.front*256;
		bpdata.frontdown = (unsigned short)mfskbpdata.frontdown*256;
		bpdata.frontup = (unsigned short)mfskbpdata.frontup*256;
		bpdata.left = (unsigned short)mfskbpdata.left*256;
		bpdata.right = (unsigned short)mfskbpdata.right*256;
		bpdata.ltime = ft;
		DisplayData(2);

		pDataPage.BPUpdateTime("����Ǳ��");
		//bsss
		memcpy(&mfskbsssdata,(BYTE*)&acousticdata[sizeof(mfskBPDATA)],sizeof(mfskBSSSDATA));
//		bsssdata.depth = (unsigned short)mfskbsssdata.depth*256;
//		bsssdata.ltime = ft;
//		str.Format("%.2f ",bsssdata.depth);
//		SetDlgItemText(IDC_BSSS,str);

		//λ��
  		memcpy(&mfsksubposition,&acousticdata[sizeof(mfskBPDATA)+sizeof(mfskBSSSDATA)],sizeof(mfskSUBPOSITION));
		subposition.ltime =ft;
		subposition.subdepth = mfsksubposition.subdepth;
		subposition.subheading = mfsksubposition.subheading;
		subposition.subheight = (unsigned short)mfsksubposition.subheight*256;
		subposition.subLAT = mfsksubposition.subLAT;
		subposition.subLONG = mfsksubposition.subLONG;
		subposition.subpitch = mfsksubposition.subpitch;
		subposition.subpitchvec = mfsksubposition.subpitchvec*256;
		subposition.subroll = mfsksubposition.subroll;
		subposition.subrollvec = mfsksubposition.subrollvec*256;
		subposition.subupdownvec = mfsksubposition.subupdownvec*256;
		DisplayData(1);
		pDataPage.UpdateTimeDisplay("����Ǳ��");

		char positionbuf[34];
		*positionbuf=0x11;
		*(positionbuf+1)=0x20;
		memcpy(positionbuf+2,(char*)&subposition,sizeof(SUBPOSITION));
		if(SEND_FLAG)
			OnSend((char*)positionbuf,sizeof(SUBPOSITION)+2);
		//ctd
		memcpy(&mfskctddata,&acousticdata[sizeof(mfskBPDATA)+sizeof(mfskBSSSDATA)+sizeof(mfskSUBPOSITION)],sizeof(mfskCTDDATA));
		ctddata.ltime =ft;
		ctddata.soundvec = (unsigned short)mfskctddata.soundvec*256;
		ctddata.vartlevel = (unsigned short)mfskctddata.vartlevel*4;
		ctddata.watercond = mfskctddata.watercond;
		ctddata.watertemp = mfskctddata.watertemp;
		//��ʾ
		double fValue;
		fValue=(float)(ctddata.watertemp)*50.0/65536;
		str.Format("%.2f ",fValue);
		SetDlgItemText(IDC_MARINE_TEMP,str);//TEMPERATURE
		
// 		double temp,press,cond,r,c,b,a,rt,salt;
// 		temp=(float)ctddata.watertemp*50/65536;
// 		press=(float)(subposition.subdepth)*8000.0/65536;
// 		cond=(float)ctddata.watercond/65536*5000/1000;
// 		r=((((1.0031E-9)*temp-6.9698E-7)*temp+1.104259E-4)*temp+2.00564E-2)*temp+0.6766097;
// 		c=(((3.989E-15)*press-6.370E-10)*press+2.070E-5)*press;
// 		b=((4.464E-4)*temp+3.426E-2)*temp+1;
// 		a=-(3.107E-3)*temp+0.4215;
// 		rt=sqrt((cond/42.914)/(r*(1+c/(a*r+b))));
// 		salt=((((2.7081*rt-7.0261)*rt+14.0941)*rt+25.3851)*rt-0.1692)*rt+0.0080+((temp-15)/(1+0.0162*(temp-15)))*(((((0.0636-0.0144*rt)*rt-0.0375)*rt-0.0066)*rt-0.0056)*rt+0.0005);
// 		str.Format("%.2f ",salt);			
// 		SetDlgItemText(IDC_MARINE_SALT,str);

		char ctdbuf[sizeof(CTDDATA)+2];
		*ctdbuf=0x12;
		*(ctdbuf+1)=0x20;
		memcpy(ctdbuf+2,(char*)&ctddata,sizeof(CTDDATA));
		if(SEND_FLAG)
			OnSend(ctdbuf,sizeof(CTDDATA)+2);
		//lifesupply
		memcpy(&mfsklifesupply,&acousticdata[sizeof(mfskBPDATA)+sizeof(mfskBSSSDATA)+sizeof(mfskSUBPOSITION)+sizeof(mfskCTDDATA)],sizeof(mfskLIFESUPPLY));
		lifesupply.ltime = ft;
		lifesupply.humidity = (unsigned short)mfsklifesupply.humidity*256;
		lifesupply.CO2 = mfsklifesupply.CO2;
		lifesupply.oxygen = mfsklifesupply.oxygen;
		lifesupply.pressure = mfsklifesupply.pressure;
		lifesupply.temperature = mfsklifesupply.temperature;
		str.Format("%.2f",(float)lifesupply.humidity*100/65536);
		SetDlgItemText(IDC_MARINE_HUMID,str);
		str.Format("%.2f",(float)lifesupply.oxygen*50/256);
		SetDlgItemText(IDC_MARINE_O2,str);
		str.Format("%.2f",(float)lifesupply.CO2*10/256);
		SetDlgItemText(IDC_CO2,str);
		str.Format("%.2f",(float)lifesupply.temperature*50/256);
		SetDlgItemText(IDC_MARINE_TEMPINSIDE,str);
		str.Format("%.2f",(float)lifesupply.pressure);
		SetDlgItemText(IDC_MARINE_PRESSURE,str);
		char lifebuf[sizeof(LIFESUPPLY)+2];
		*lifebuf=0x13;
		*(lifebuf+1)=0x20;
		memcpy(lifebuf+2,(char*)&lifesupply,sizeof(LIFESUPPLY));
		if(SEND_FLAG)
			OnSend(lifebuf,sizeof(LIFESUPPLY)+2);
		//energy
		memcpy(&mfskenergysys,&acousticdata[sizeof(mfskBPDATA)+sizeof(mfskBSSSDATA)+sizeof(mfskSUBPOSITION)+sizeof(mfskCTDDATA)
			+sizeof(mfskLIFESUPPLY)],sizeof(mfskENERGYSYS));
		energysys.ltime =ft;
		energysys.mainconsume = (unsigned short)mfskenergysys.mainconsume*256;
		energysys.mainI = (unsigned short)mfskenergysys.mainI*256;

		energysys.mainV = (unsigned short)mfskenergysys.mainV*256;
		str.Format("%.2f",(float)energysys.mainI*500/65536);
		SetDlgItemText(IDC_MAIN_I,str);
		str.Format("%.2f",(float)energysys.mainV*200/65536);
		SetDlgItemText(IDC_MAIN_V,str);
		energysys.subconsume = (unsigned short)mfskenergysys.subconsume*256;
		energysys.subI = (unsigned short)mfskenergysys.subI*256;
		energysys.subV = (unsigned short)mfskenergysys.subV*256;
		char bufenergysys[22];
		if(SEND_FLAG)
		{
			*bufenergysys=0x14;
			*(bufenergysys+1)=0x20;
			memcpy(bufenergysys+2,(BYTE*)&energysys,20);
			OnSend(bufenergysys,20+2);
		}
		//alarm
		memcpy(&mfskalertdata,&acousticdata[sizeof(mfskBPDATA)+sizeof(mfskBSSSDATA)+sizeof(mfskSUBPOSITION)+sizeof(mfskCTDDATA)
			+sizeof(mfskLIFESUPPLY)+sizeof(mfskENERGYSYS)],sizeof(mfskALERTDATA));
		alertdata.ltime = ft;
		memcpy(&alertdata.alert,&mfskalertdata.alert,4*sizeof(BYTE));
		alertdata.aleak = mfskalertdata.aleak;
		alertdata.behind = (unsigned short)mfskalertdata.behind*256;
		alertdata.cable = (unsigned short)mfskalertdata.cable*256;
		alertdata.head  = (unsigned short)mfskalertdata.head*256;
		alertdata.pressure = (unsigned short)mfskalertdata.pressure*256;
		alertdata.temperature = mfskalertdata.temperature;
		char bufalertdata[24];
		if(SEND_FLAG)
		{
			*bufalertdata=0x15;
			*(bufalertdata+1)=0x20;
			memcpy((BYTE*)bufalertdata+2,(BYTE*)&alertdata,22);
			OnSend(bufalertdata,22+2);
		}
		//switch
		memcpy(&mfskswitchdata,&acousticdata[sizeof(mfskBPDATA)+sizeof(mfskBSSSDATA)+sizeof(mfskSUBPOSITION)+sizeof(mfskCTDDATA)
			+sizeof(mfskLIFESUPPLY)+sizeof(mfskENERGYSYS)+sizeof(mfskALERTDATA)],sizeof(mfskSWITCHDATA));
		memset(&switchdata,0,sizeof(SWITCHDATA));
		switchdata.ltime =ft;
		for(int i=0;i<2;i++)
		{
			for(int j=0;j<8;j++)
			{
				 if(mfskswitchdata.state[i]>>j&0x01)
				 {
					 switchdata.equipNO = i*8+j;
				 }
			}
		} 
		char bufswitchdata[12];
		if(SEND_FLAG)
		{
			*bufswitchdata=0x16;
			*(bufswitchdata+1)=0x20;
			memcpy(bufswitchdata+2,(BYTE*)&switchdata,10);
			OnSend(bufswitchdata,10+2);
		}
		//first part ended

	}//��ȷ
	
	//adcp
	n8 = pDataPackage.CRC8_Tab((UCHAR*)&acousticdata[58],30);
	nCRC8 = acousticdata[88];
	if (n8!=nCRC8)//У�����
	{
		SaveRecord("ADCP����У�����");
	}
	else//��ȷ
	{
		SaveRecord("ADCP����У����ȷ��");
		memcpy(&adcpdata,&acousticdata[58],30*sizeof(BYTE));
		UpdateADCP(adcpdata.floorX,adcpdata.floorY,adcpdata.floorZ,10);
	}
	//word
	char chat[42];
	CString strtime;
	memset(chat,0,42*sizeof(char));
	memcpy(chat,(CHAR*)&acousticdata[89],WORDSIZE*sizeof(char));

	str.Format("%s",chat);
	/*
	n8 = pDataPackage.CRC8_Tab((BYTE*)chat,WORDSIZE);
	nCRC8 = acousticdata[129];
	if (n8!=nCRC8)
	{
		SaveRecord("����У�����!");
	}
	*/
	USHORT n16 = pDataPackage.CRC16((BYTE*)chat,WORDSIZE);
	USHORT nCRC16 = *(USHORT*)&acousticdata[129];
	if (n16!=nCRC16)
	{
	SaveRecord("����У�����!");
	}
	else
	{
		SaveRecord("����У����ȷ!");
		CTime ct = CTime::GetCurrentTime();
		strtime.Format("%02d:%02d:%02d ",ct.GetHour(),ct.GetMinute(),ct.GetSecond());
// 		if (str.GetLength()==0)
// 		{
// 			str = "��������Ϣ";
// 			strtime = strtime + str + "\r\n";
// 			TextFile.SaveFile(strtime,strtime.GetLength());
// 		}
 		if (str.GetLength()>0)
 		{
			
			strtime = strtime + "Ǳ����" + str + "\r\n";
			TextFile.SaveFile(strtime,strtime.GetLength());
			
			pWavePage.ShowWindow(SW_HIDE);
			pPostPage.ShowWindow(SW_HIDE);
			pWordPage.ShowWindow(SW_SHOW);
			pPicturePage.ShowWindow(SW_HIDE);
			pDataPage.ShowWindow(SW_HIDE);
			m_tabctrl.SetCurSel(2);
			pWordPage.InputWord(str);
			str = "Ǳ��:" + str;
			SaveRecord(str);
		}
		
	}
	str.Format("��ǰͨ�ž��룺%.1f",CommunicationParam.reserved[0]*1.5);
	SaveRecord(str);
	bFirstRecvData = TRUE;
	
	
	

}

void CACSDlg::UpdateSensorData(SYSTEMSENSORDATA *SystemSensorData)
{
	//+5V��Դ��ѹ���ݣ�V
	CString tempstr;
	if(SystemSensorData->VoltageP5>10 || SystemSensorData->VoltageP5<-0)
		tempstr="---";
	else
		tempstr.Format("%.2fV",SystemSensorData->VoltageP5);
	SetDlgItemText(IDC_STATIC_p5,tempstr);
	//-5V��Դ��ѹ���ݣ�V
	if(SystemSensorData->VoltageN5>0 || SystemSensorData->VoltageN5<-10)
		tempstr="---";
	else
		tempstr.Format("%.2fV",SystemSensorData->VoltageN5);
	SetDlgItemText(IDC_STATIC_n5,tempstr);
	//+12V��Դ��ѹ���ݣ�V
	if(SystemSensorData->VoltageP12>20 || SystemSensorData->VoltageP12<0)
		tempstr="---";
	else
		tempstr.Format("%.2fV",SystemSensorData->VoltageP12);
	SetDlgItemText(IDC_STATIC_p12,tempstr);
	//-12V��Դ��ѹ���ݣ�V
	if(SystemSensorData->VoltageN12>0 || SystemSensorData->VoltageN12<-20)
		tempstr="---";
	else
		tempstr.Format("%.2fV",SystemSensorData->VoltageN12);
	SetDlgItemText(IDC_STATIC_n12,tempstr);
	//��������¶����ݣ���
	if(SystemSensorData->XMTTemperature>125 || SystemSensorData->XMTTemperature<-55 || SystemSensorData->XMTTemperature==85)
		tempstr="---";
	else
		tempstr.Format("%.1f��",SystemSensorData->XMTTemperature);
	SetDlgItemText(IDC_STATIC_send,tempstr);
	//5V��Դ���¶����ݣ���
	if(SystemSensorData->Power5VTemperature>80 || SystemSensorData->Power5VTemperature<-55)
		tempstr="---";
	else
		tempstr.Format("%.1f��",SystemSensorData->Power5VTemperature);
	SetDlgItemText(IDC_STATIC_5t,tempstr);
	//12V��Դ���¶����ݣ���
	if(SystemSensorData->BaseTemperature>80 || SystemSensorData->BaseTemperature<-55)
		tempstr="---";
	else
		tempstr.Format("%.1f��",SystemSensorData->BaseTemperature);
	SetDlgItemText(IDC_STATIC_BASE,tempstr);
	//3.3V��Դ���¶����ݣ���
	if(SystemSensorData->Power3V3Temperature>80 || SystemSensorData->Power3V3Temperature<-55)
		tempstr="---";
	else
		tempstr.Format("%.1f��",SystemSensorData->Power3V3Temperature);
	SetDlgItemText(IDC_STATIC_33t,tempstr);
	//24V��Դ���¶����ݣ���
	if(SystemSensorData->Power24VTemperature>125 || SystemSensorData->Power24VTemperature<-55 || SystemSensorData->Power24VTemperature==85)
		tempstr="---";
	else
		tempstr.Format("%.1f��",SystemSensorData->Power24VTemperature);
	SetDlgItemText(IDC_STATIC_24t,tempstr);

	if(SystemSensorData->Recv1Temperature>80 || SystemSensorData->Recv1Temperature<-55)
		tempstr="---";
	else
		tempstr.Format("%.1f��",SystemSensorData->Recv1Temperature);
	SetDlgItemText(IDC_STATIC_r1,tempstr);
	if(SystemSensorData->Recv2Temperature>80 || SystemSensorData->Recv2Temperature<-55)
		tempstr="---";
	else
		tempstr.Format("%.1f��",SystemSensorData->Recv2Temperature);
	SetDlgItemText(IDC_STATIC_r2,tempstr);
	//�շ�ת�����¶����ݣ���
	if(SystemSensorData->TRSwitchTemperature>80 || SystemSensorData->TRSwitchTemperature<-55)
		tempstr="---";
	else
		tempstr.Format("%.1f��",SystemSensorData->TRSwitchTemperature);
	SetDlgItemText(IDC_STATIC_sw,tempstr);
}

void CACSDlg::TestDataPackageAndParse()
{
// 
// 	float nbits = UWACInitParam.XMTPackageNum*UWACInitParam.XMTPackFramNum
// 						*UWACInitParam.MFSKDataSymbolNum*30;//������
// 	int len = ceilf(nbits/8);//�ֽ���=bit/8��1��4��������ֶ���
// 	BYTE* buf = (unsigned char *)malloc(len);
//  	BYTE data[52];
// 	int i=0;
	int len = 13552;
	BYTE* buf = (unsigned char *)malloc(len);
	memset((unsigned char *)buf,0,len);//����ȫ��
	BYTE data[246];
// 	PackageShipData((unsigned char *)buf,len);
// 	UWACInitParam.ADIOWorkMode = 0;
// 	
// 	 
// 	for (i =0;i<12;i++)
// 	{
// 		*(DWORD*)data = i;
// 		memcpy(&data[4],&buf[i*45],45);
// 		ExplainFSKData(data,49);
// 	}
	FILE *fp;
// 
// 	PackageUWAData((unsigned char *)buf,len);
// 	FILE *fp = fopen("UWAfsk.dat","wb");
// 	fwrite(buf,1,len,fp);
// 	fclose(fp);
// 	PackagePicture(buf,13552);
// 	fp = fopen("psk1.dat","wb");
// 	fwrite(buf,1,len,fp);
// 	fclose(fp);
// 	UWACInitParam.ADIOWorkMode = 1;
// 	for (i =0;i<12;i++)
// 	{
// 		*(DWORD*)data = i;
// 		memcpy(&data[4],&buf[i*45],45);
// 		ExplainFSKData(data,52);
// 	}
	fp = fopen("psk.dat","rb");
// 	int ret = fread(buf,1,COLORIMAGESIZE,fp);
// 	memcpy(CompressValue,buf,COLORIMAGESIZE);
// 	imageDecode.ColorDecode(mybuffernew,CompressValue,256);
// 	CRect rect;
// 	CWnd* pWnd= GetDlgItem(IDC_IMAGE);
// 	pWnd->GetClientRect(&rect);
// 		m_ShowImage.InvalidateRect(&rect);
	for (int i =0;i<28;i++)
	{
		int ret = fread(&data[4],1,242,fp);
		*(DWORD*)data = i;
		ExplainPSKData(data,246);
	}
	fclose(fp);
	free(buf);

}



void CACSDlg::OnSelchangeComboDigitchnnl() 
{
	// TODO: Add your control notification handler code here

	int i =	m_digitalchnnl.GetCurSel();
// 	if (!UWACInitParam.ADIOWorkMode)
// 	{
// 		
// 	}
// 	else
// 	{
// 		if (i==0)
// 		{
// 			m_strdigitalchnnl.Format("%d",1);
// 		}
// 		else
// 			m_strdigitalchnnl.Format("%d",6);
// 	}
	m_strdigitalchnnl.Format("%d",i+1);
	OnDigitalXmtSet();
}

void CACSDlg::OnReleasedcaptureSliderDigitalamp(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
//	float amp = m_slider_digitalamp.GetPos();
// 	CString str;
// 	str.Format("%.2f",amp/1000);
// 	CWnd* pWnd = GetDlgItem(IDC_STATIC_DIGITALAMP);
// 	pWnd->SetWindowText(str);
// 	m_Amp = amp/1000;
// 	if (!SendSocket.m_bConnect)//δ����
// 	{
// 		return;
// 	}
	OnDigitalXmtSet();
	*pResult = 0;
}

void CACSDlg::OnDigitalXmtSet()
{
	if (!SendSocket.m_bConnect)
	{
		return;
	}
	CString str;
	float amp = m_slider_digitalamp.GetPos();
	m_Amp = float(int(amp/10))/100;;
	if ((m_Amp<0.00499)||(m_Amp>1))
	{
		return;
	}
	OnChangeChannel(atoi(m_strdigitalchnnl),m_Amp,1);
	UpdateData(FALSE);//ȷ����ֵ�ɹ�
	UWACInitParam.XMTAmpValue = m_Amp;//���ַ���
	UWACInitParam.digital_tranmit_channel = atoi(m_strdigitalchnnl);
	str.Format("���÷��������ͨ��%d,����%.2f",atoi(m_strdigitalchnnl),m_Amp);
	SaveRecord(str);
}


void CACSDlg::OnEditchangeComboXmt() 
{
	// TODO: Add your control notification handler code here
	OnButtonXmtset();
}

void CACSDlg::OnRadioMfsk() 
{
	// TODO: Add your control notification handler code here
	CButton* radioWnd =  (CButton*)GetDlgItem(IDC_RADIO_MPSK);
	radioWnd->SetCheck(0);
	radioWnd =  (CButton*)GetDlgItem(IDC_RADIO_MFSK);
	radioWnd->SetCheck(1);
	radioWnd =  (CButton*)GetDlgItem(IDC_CHECKPSK);
	radioWnd->EnableWindow(FALSE);
	radioWnd->SetCheck(0);
	UWACInitParam.XMTModulation = MFSKMOD;
//	CButton* pWnd = (CButton*)GetDlgItem(IDC_FH_SEND);
//	pWnd->EnableWindow(FALSE);
// 	pWavePage.ShowWindow(SW_HIDE);
// 	pPostPage.ShowWindow(SW_HIDE);
// 	pWordPage.ShowWindow(SW_SHOW);
// 	pPicturePage.ShowWindow(SW_HIDE);
// 	pDataPage.ShowWindow(SW_HIDE);
// 	m_tabctrl.SetCurSel(2);
}

void CACSDlg::OnRadioMpsk() 
{
	// TODO: Add your control notification handler code here
	UWACInitParam.XMTModulation = MPSKMOD;
	CButton* radioWnd =  (CButton*)GetDlgItem(IDC_CHECKPSK);
	radioWnd->EnableWindow(true);
	if (radioWnd->GetCheck())
	{
		UWACInitParam.XMTModulation = OPSKMOD;
	}
//	CButton* pWnd = (CButton*)GetDlgItem(IDC_FH_SEND);
//	pWnd->EnableWindow(FALSE);
// 	pWavePage.ShowWindow(SW_HIDE);
// 	pPostPage.ShowWindow(SW_HIDE);
// 	pWordPage.ShowWindow(SW_HIDE);
// 	pPicturePage.ShowWindow(SW_SHOW);
// 	pDataPage.ShowWindow(SW_HIDE);
// 	m_tabctrl.SetCurSel(3);
}
/*
void CACSDlg::OnRadioFh() 
{
	// TODO: Add your control notification handler code here
	UWACInitParam.XMTModulation = FHMOD;
	CButton* pWnd = (CButton*)GetDlgItem(IDC_FH_SEND);
	pWnd->EnableWindow(TRUE);
}
*/
void CACSDlg::SendSoundEnd()//����ˮ��ֹͣ����
{
	NET_PACKET *netpacket;
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	
	if(netpacket==NULL)
	{
		AfxMessageBox("����NET_PACKET�ռ�����쳣��");
	}
	
	netpacket->FrmID = UWACCMD_SOUND_END;
	netpacket->FrmLen = 32;
	netpacket->DestID = ADIOID;
	netpacket->HeadParam[0] = UWACCMD_SOUND_END;
	netpacket->HeadParam[1] = 1;
	netpacket->HeadParam[2] = 0;//��ǰ����
	netpacket->HeadParam[3] = 0;//�����ݳ���
	netpacket->HeadParam[4] = 0;
	netpacket->pData =NULL;	
	m_WzdNetpacketList.AddTail(netpacket);
	SetEvent(IsNetpacketEvent);
	DisableButton(FALSE);
	SetTimer(BUTTONTIMER,3000,NULL);
}

void CACSDlg::StartDsp()
{
	if (!UWACInitParam.ADIOWorkMode)//����
	{
		NET_PACKET *netpacket;//����DSP01
		netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
		if(netpacket==NULL){
			AfxMessageBox("����NET_PACKET�ռ�����쳣��");
		}
		
		netpacket->FrmID = UWACCMD_STARTDSP;
		netpacket->FrmLen = 32;
		netpacket->DestID = DSP01ID;
		netpacket->pData = NULL;	
		m_WzdNetpacketList.AddTail(netpacket);
		SetEvent(IsNetpacketEvent);
	}
	else
	{
		NET_PACKET *netpacket;//����DSP01
		netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
		if(netpacket==NULL){
			AfxMessageBox("����NET_PACKET�ռ�����쳣��");
		}
		
		netpacket->FrmID = UWACCMD_STARTDSP;
		netpacket->FrmLen = 32;
		netpacket->DestID = DSP11ID;
		netpacket->pData = NULL;	
		m_WzdNetpacketList.AddTail(netpacket);
		SetEvent(IsNetpacketEvent);
	}
	
	
// 	NET_PACKET *netpacket1;//����DSP02
// 	netpacket1 = (NET_PACKET *)malloc(sizeof(NET_PACKET));
// 	if(netpacket1==NULL){
// 		AfxMessageBox("����NET_PACKET�ռ�����쳣��");
// 	}
// 	netpacket1->FrmID = UWACCMD_STARTDSP;
// 	netpacket1->FrmLen = 32;
// 	netpacket1->DestID = DSP02ID;
// 	netpacket1->pData = NULL;	
// 	m_WzdNetpacketList.AddTail(netpacket1);
// 	SetEvent(IsNetpacketEvent);
}

void CACSDlg::StartAdio()
{
	NET_PACKET *netpacket;
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	if(netpacket==NULL){
		AfxMessageBox("����NET_PACKET�ռ�����쳣��");
	}
	
	netpacket->FrmID = UWACCMD_STARTTALK;
	netpacket->FrmLen = 32;
	netpacket->DestID = ADIOID;
	netpacket->pData = NULL;
	
	m_WzdNetpacketList.AddTail(netpacket);
	SetEvent(IsNetpacketEvent);
}


void CACSDlg::OnEditchangeComboDigitchnnl() 
{
	// TODO: Add your control notification handler code here
	OnDigitalXmtSet();
}


void CACSDlg::SetTime()
{
	time_t ltime;
	CTime ct;
	ct = CTime::GetCurrentTime();
	ltime = ct.GetTime();

	NET_PACKET *netpacket;//����DSP01
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	if(netpacket==NULL){
		AfxMessageBox("����NET_PACKET�ռ�����쳣��");
	}

	netpacket->FrmID = UWACCMD_SETTIME;
	netpacket->FrmLen = 32;
	netpacket->DestID = PC104ID;
	netpacket->HeadParam[0] = (DWORD)ltime;
	netpacket->pData = NULL;	
	m_WzdNetpacketList.AddTail(netpacket);
	SetEvent(IsNetpacketEvent);
}



int CACSDlg::calcAmp(short *pBuffer, int nlength)
{
	int AmpArray[128];
	NorAmp=32767;
	memset(AmpArray,0,128*sizeof(int));
	//ֱ��ͼͳ��
	for (int i=0;i<nlength;i++)
	{
		AmpArray[abs(pBuffer[i])>>8]++;
	}
	//����95%���ʷֲ�ʱ�ķ���ֵ
	int nSum =0;
	for (i=0;i<128;i++)
	{
		nSum += AmpArray[i];
		if ((float)nSum/nlength >0.95)
		{
			NorAmp = (i+1)*256;
			break;
		}
	}
	return NorAmp;

}



void CACSDlg::OnEnforceSend() 
{
	// TODO: Add your control notification handler code here
	NET_PACKET *netpacket;
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	if(netpacket==NULL)
	{
		AfxMessageBox("����NET_PACKET�ռ�����쳣��");
		return;
	}
	
	netpacket->FrmID = UWACCMD_FORCE_TRANSMIT;
	netpacket->FrmLen = 32;
	netpacket->DestID = ADIOID;
	netpacket->HeadParam[0] = MFSKMOD;//
	netpacket->HeadParam[1] = 1;//�ܰ���
	netpacket->HeadParam[2] = 0;//��ǰ����
	netpacket->HeadParam[3] = 0;//�����ݳ���]
	netpacket->HeadParam[4] = MFSKMOD;//�����ݳ���
	netpacket->pData = NULL;
	SendNetpacketSync.Lock();
	m_WzdNetpacketList.AddTail(netpacket);
	SendNetpacketSync.Unlock();
	SetEvent(IsNetpacketEvent);	
	UWACInitParam.XMTModulation = MFSKMOD;
	if (UWACInitParam.ADIOWorkMode&&UsblEnableCheck)
	{
		//д���ڽ�ֹ���̻���
		if (hyLPT)
		{
			LPT_Writedata(hyLPT,0x99);  //B0_DQ=1 ,�ͷ�DQ�ߣ�B6_DQ=1������B6
		}
		SetTimer(USBLTIME3,8000,NULL);
	}
}

void CACSDlg::DisplaySoundWave(WPARAM wParam, LPARAM lParam)
{
	int amp = (int)wParam;
	m_soundamp.SetPos(amp);
}


void CACSDlg::TimeOutAlarm(WPARAM wParam, LPARAM lParam)//when timeout, disp the alarm or some action
{
	CString str;
	str.Format("%s","�·����ʱ!�����Զ�����!������ͨ�Ż�");
	SaveRecord(str);
//	OnConnect();
}

void CACSDlg::StartTCM2()
{
	NET_PACKET *netpacket;
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	if(netpacket==NULL){
		AfxMessageBox("����NET_PACKET�ռ�����쳣��");
	}

	netpacket->FrmID = UWACCMD_TCMSTART;
	netpacket->FrmLen = 32;
	netpacket->DestID = PC104ID;
	netpacket->pData = NULL;
		
	m_WzdNetpacketList.AddTail(netpacket);
	SetEvent(IsNetpacketEvent);

}

void CACSDlg::OnTest() 
{
	// TODO: Add your control notification handler code here
	float nbits = UWACInitParam.XMTPackageNum*UWACInitParam.XMTPackFramNum
						*UWACInitParam.MFSKDataSymbolNum*30;//������
	int len = ceilf(nbits/8);//�ֽ���=bit/8��1��4��������ֶ���
	BYTE* buf = (unsigned char *)malloc(len);
 	BYTE data[52];
	int i=0;
	memset((unsigned char *)buf,0,len);//����ȫ��
	if (UWACInitParam.ADIOWorkMode==0)
	{
		PackageUWAData((unsigned char *)buf,len);
		FILE *fp = fopen("uwafsk.dat","wb");
		fwrite(buf,1,len,fp);
		fclose(fp);
	}
	else
	{	
		PackageShipData((unsigned char *)buf,len);
		FILE *fp = fopen("shipfsk.dat","wb");
		fwrite(buf,1,len,fp);
		fclose(fp);
	}

	
}

void CACSDlg::OnParse() 
{
	// TODO: Add your control notification handler code here
		float nbits = UWACInitParam.XMTPackageNum*UWACInitParam.XMTPackFramNum
						*UWACInitParam.MFSKDataSymbolNum*30;//������
	int len = ceilf(nbits/8);//�ֽ���=bit/8��1��4��������ֶ���
	BYTE* buf = (unsigned char *)malloc(len);
 	BYTE data[52];
	FILE *fp;
	memset((unsigned char *)buf,0,len);//����ȫ��
	if (UWACInitParam.ADIOWorkMode==0)
	{
		fp= fopen("shipfsk.dat","rb");
	
	}
	else
	{	
		fp= fopen("uwafsk.dat","rb");
	}
	for (int i =0;i<12;i++)
	{

		int ret = fread(&data[4],1,45,fp);
		*(DWORD*)data = i;
		ExplainFSKData(data,52);
	}
	fclose(fp);
}

void CACSDlg::SendMorseCommand(int CommId)
{
	if (!SendSocket.m_bConnect)
	{
		SaveRecord("δ�������磬��Ϣδ����!");
		return;
	}
	
	NET_PACKET *netpacket;
	netpacket = (NET_PACKET *)malloc(sizeof(NET_PACKET));
	if(netpacket==NULL)
	{
		AfxMessageBox("����NET_PACKET�ռ�����쳣��");
		return;
	}

	netpacket->FrmID = UWACDATA_MODULATION_PHONEDATA;
	netpacket->FrmLen = 32;
	netpacket->DestID = ADIOID;
	netpacket->HeadParam[0] = UWACCMD_ADIOREQUEST;//�������������壬��Ϊ0
	netpacket->HeadParam[1] = 1;//�ܰ���
	netpacket->HeadParam[2] = 0;//��ǰ����
	netpacket->HeadParam[3] = 0;//�����ݳ���
	netpacket->HeadParam[4] = CommId;//��pc104����ʱ���˴���ΪSOUNDMOD;
	netpacket->pData = NULL;
	m_WzdNetpacketList.AddTail(netpacket);
	SetEvent(IsNetpacketEvent);	
	if (UWACInitParam.ADIOWorkMode&&UsblEnableCheck)
	{
		//д���ڽ�ֹ���̻���
		if (hyLPT)
		{
			LPT_Writedata(hyLPT,0x99);  //B0_DQ=1 ,�ͷ�DQ�ߣ�B6_DQ=1������B6
		}
		SetTimer(USBLTIME3,8000,NULL);
	}
}

void CACSDlg::SaveEoutData(BYTE *databuf, int len)
{
	DWORD totlevaliddatabytelen;
	CString str;
	short checksum16 = 0;
	int   frameno;
	int i=0;
	totlevaliddatabytelen = len-4; 	

	frameno = *(DWORD *)databuf;
	if(frameno<UWACInitParam.RecvMPSKPackageNum*UWACInitParam.RecvMPSKPackFramNum-1)
	{// ��ȷ֡

		if(frameno==0)
		{//��һ�����ݽ��յĿ�ʼ,������ղ���
			str.Format("�յ��¾������ݣ�֡��%d��",frameno);
			SaveRecord(str);
			RECVEOUTFile.CloseFile();
			RECVEOUTFile.Init("EoutPSK",10*FILESIZE,4*WRITESIZE,32*WRITESIZE);
		}
		str.Format("�յ���������֡%d",frameno);
		SaveRecord(str);
	
		RECVEOUTFile.SaveFile((char*)databuf+4, totlevaliddatabytelen);//�����ļ�
		RecFrameNo = frameno;
//		iframenum++;
	}
	else if (frameno == UWACInitParam.RecvMPSKPackageNum*UWACInitParam.RecvMPSKPackFramNum-1)//���һ֡
	{
		RecFrameNo = frameno;
		str.Format("�յ���������֡%d",frameno);
		SaveRecord(str);
		RECVEOUTFile.SaveFile((char*)databuf+4, totlevaliddatabytelen);//�����ļ�
		RECVEOUTFile.CloseFile();
	
	}
	else//�Ƿ�֡
	{
		str.Format("�յ��ľ�������֡�Ų��ԣ�Ϊ%d��",frameno);
		SaveRecord(str);
	}
}


void CACSDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	// TODO: Add your message handler code here and/or call default
	CSliderCtrl* pSlider;
	if ((nSBCode<=SB_THUMBTRACK)&&(nSBCode>=2))
	{
		pSlider = (CSliderCtrl*)pScrollBar;
		int n = pSlider->GetDlgCtrlID();
		if (n==IDC_SLIDER_AMP)//ˮ������
		{
			float amp = m_slider_amp.GetPos();
			CString str;
			amp = float(int((amp+1)/10))/100;
			str.Format("%.2f",amp);
			CWnd* pWnd = GetDlgItem(IDC_STATIC_AMP);
			pWnd->SetWindowText(str);
		}
		if(n==IDC_SLIDER_DIGITALAMP)
		{
			float amp = m_slider_digitalamp.GetPos();
			CString str;
			amp = float(int((amp+1)/10))/100;
			str.Format("%.2f",amp);
			CWnd* pWnd = GetDlgItem(IDC_STATIC_DIGITALAMP);
			pWnd->SetWindowText(str);
		}
	}
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}



void CACSDlg::OnCheckpsk() 
{
	// TODO: Add your control notification handler code here
	CButton* radioWnd =  (CButton*)GetDlgItem(IDC_CHECKPSK);
	if (radioWnd->GetCheck())
	{
		UWACInitParam.XMTModulation = OPSKMOD;
	}
	else
	{
		UWACInitParam.XMTModulation = MPSKMOD;
	}
	
}

void CACSDlg::PackagePictureIn8psk(unsigned char *buf, int len)
{
	int totlevaliddatabytelen =0;
	int i=0,j=0;

	totlevaliddatabytelen = UWACInitParam.XMTMPSKPackageNum*UWACInitParam.XMTMPSKPackFramNum
		*UWACInitParam.MPSKDataSymbolNum*2*1.5/8;//�ɷ������ֽ���
	int bytelenperframe = UWACInitParam.MPSKDataSymbolNum*2*1.5/8;//726
	unsigned char *tempbuf;//������ʱ������,Ҫ���͵�������Ч����
	tempbuf = (unsigned char *) malloc(totlevaliddatabytelen);
	memset(tempbuf,0,totlevaliddatabytelen*sizeof(BYTE));

	BYTE* acousticdata = new BYTE[totlevaliddatabytelen/1.5];//ĸ����ѧ���ݻ���
	BYTE* formerdata = new BYTE[COLORIMAGESIZE];//����ǰ��ѧ���ݻ���
	BYTE Turbodata[484];//Turbo����ǰ���ݻ���
	memset(acousticdata,0,(totlevaliddatabytelen/1.5)*sizeof(BYTE));
	memset(formerdata,0,COLORIMAGESIZE*sizeof(BYTE));
	memset(&Turbodata,0,484*sizeof(BYTE));

	int *codedframebit = (int *)malloc(totlevaliddatabytelen/1.5*8*sizeof(int));//û���ŵ�����ı�����
	int *framebit = (int*)malloc(1936*2*sizeof(int));
	int *ConvCodedbit = (int *)malloc(1936*3*sizeof(int));//���������ÿ֡������
	memset(framebit,0,1936*2*sizeof(int));
	memset(codedframebit,0,totlevaliddatabytelen/1.5*8*sizeof(int));
	memset(ConvCodedbit,0,1936*3*sizeof(int));
	if (!m_WzdimageList.IsEmpty())
	{
		memcpy(formerdata,(unsigned char *)m_WzdimageList.GetHead()->buf,m_WzdimageList.GetHead()->len);
		
	}
	//////////////////////////����ǰ4֡����///////////////////////////////////
	USHORT	nCRC16;
	for (i=0;i<UWACInitParam.XMTMPSKPackageNum*UWACInitParam.XMTMPSKPackFramNum;i++)
	{
		memcpy(acousticdata+i*242,formerdata+i*32,32*sizeof(char));
		memcpy(acousticdata+i*242+32,formerdata+896+i*208,208*sizeof(char));
		nCRC16 = pDataPackage.CRC16(acousticdata+i*242,240);
		memcpy(acousticdata+i*242+240,(BYTE*)&nCRC16,sizeof(USHORT));
	}
	
	//////////////////////////////////////////////////////////////////////////
// 	USHORT	nCRC16 = pDataPackage.CRC16(acousticdata,COLORIMAGESIZE);
// 	memcpy(acousticdata+COLORIMAGESIZE,(BYTE*)&nCRC16,sizeof(USHORT));
	for(i=0;i<(totlevaliddatabytelen/1.5);i++)
	{
		for(j=0;j<8;j++)
		{
			codedframebit[8*i+j] = (acousticdata[i]>>j)&0x01;
		}
	}//�õ�������
	
	int templocal = 0;
	int local1=0;
	char interleavebuf1[1936*2];
	char interleavebuf2[1936*2];
	char bytebuf[726];
	memset(bytebuf,0,bytelenperframe);
	
	int m=0;
	XMTPSKFile.Init("PSK",1*FILESIZE,1024,4*WRITESIZE);
	for(int k=0;k<UWACInitParam.XMTMPSKPackageNum*UWACInitParam.XMTMPSKPackFramNum;k++)
	{
		memcpy(framebit,codedframebit+k*1936*2,1936*2*sizeof(int));
		memset(Turbodata,0,484*sizeof(char));
		for(i=0;i<484;i++)
		{
			for(j=0;j<8;j++)
			{
				Turbodata[i] += (framebit[8*i+j]&0x01)<<j;
			}
		} //�õ�ѹ��������
		XMTPSKFile.SaveFile((char*)Turbodata,242*sizeof(char));
		for(i=0;i<484;i++)
		{
			if(UWACInitParam.XMTWhiteProcess)//�׻�����
			{
				if (i<242)
				{
					Turbodata[i] ^= (unsigned char) *((unsigned char *)Whiteseq + i);
				} 
				else
				{
					Turbodata[i] ^= (unsigned char) *((unsigned char *)Whiteseq + i - 242);
				}
				
			}
			
			
	
			for(j=0;j<8;j++)
				framebit[i*8+j] = (Turbodata[i]>>j)&0x01;//�õ�������
		}
		
		mpskturo.TurboCode8PSK(framebit,ConvCodedbit);//�ŵ�����
		
	

		memset(bytebuf,0,bytelenperframe*sizeof(char));
		for(m=0;m<bytelenperframe;m++)
		{
			for(j=0;j<8;j++){
				bytebuf[m]+=(ConvCodedbit[8*m+j]&0x01)<<j;//�ӽ�֯��ı������õ��ֽ���
			}
		}
		memcpy(tempbuf+local1,bytebuf,bytelenperframe);//�����õ���һ֡����
		local1+=bytelenperframe;
		//���������ļ�								
	}
	XMTPSKFile.CloseFile();
	memcpy(buf,tempbuf,local1*sizeof(char));
	XMTPSKFile.Init("XMT8PSK",1*FILESIZE,1024,4*WRITESIZE);
	XMTPSKFile.SaveFile((char*)tempbuf,local1*sizeof(char));
	XMTPSKFile.CloseFile();
	delete acousticdata;
	delete formerdata;
	free(framebit);
	free(tempbuf);
	free(codedframebit);
    free(ConvCodedbit);
}

void CACSDlg::SaveCommData(char *CommBuffer)
{
	COMMUNICATIONPARAM comm;
	memcpy(&comm, CommBuffer,sizeof(COMMUNICATIONPARAM));
	CTime ct = CTime::GetCurrentTime();
	CString str;
	str.Format("%04d.%02d.%02d %02d:%02d:%02d\r\n",ct.GetYear(),ct.GetMonth(),ct.GetDay(),ct.GetHour(),ct.GetMinute(),ct.GetSecond());
	RECVCommDataFile.SaveFile(str,str.GetLength());
	for(int i=0; i<4; i++)
	{
		//��ʾ���ջ����������
		str.Format("%d ",comm.Gain[i]);
		RECVCommDataFile.SaveFile(str,str.GetLength());
		
		//��ʾ���ջ��������
		if( comm.AGCamp[i] >0 )
		{
			//�ѷ���ת����mV�������Ƕ�128������ƽ����ͣ�������2048��Ӧ10V��
			str.Format("%.0f ",sqrt(comm.AGCamp[i]/128.0)/2048*10000+0.5);
			
		}
		else
		{
			str.Format("�� ");
		}
		RECVCommDataFile.SaveFile(str,str.GetLength());
		
		//��ʾͬ��ͷ��ط�ֵ���Ƕ�4096�����غ�����ģƽ��
		if( CommunicationParam.ChirpCorrePeak[i] >0 )
		{
			str.Format("%.1f ",10*log10(comm.ChirpCorrePeak[i]/4096));
		}
		else
		{
			str.Format("�� ");
		}
		RECVCommDataFile.SaveFile(str,str.GetLength());
		
		//��ʾͬ��ͷ��ط�ֵ
		str.Format("%.3f ",comm.ChannCorreCoe[i]);
		RECVCommDataFile.SaveFile(str,str.GetLength());
		str = "\r\n";
		RECVCommDataFile.SaveFile(str,str.GetLength());
	}
	//��¼��̬��Ϣ

	if(tcmdata.error_code==0)
	{
		str.Format("%.2f��",tcmdata.pitch);
		RECVCommDataFile.SaveFile(str,str.GetLength());
		
		str.Format("%.2f��",tcmdata.roll);
		RECVCommDataFile.SaveFile(str,str.GetLength());
		str = "\r\n";
		RECVCommDataFile.SaveFile(str,str.GetLength());
	}

	else
	{
		str.Format("E %.2f��",tcmdata.pitch);
		RECVCommDataFile.SaveFile(str,str.GetLength());
		str.Format("E %.2f��",tcmdata.roll);
		RECVCommDataFile.SaveFile(str,str.GetLength());
		str = "\r\n";
		RECVCommDataFile.SaveFile(str,str.GetLength());
		
	}
	//////////////////////////////////////////////////////////////////////////
	if (comm.reserved[0] > 0)
	{
		str.Format("%.2f",comm.reserved[0] * 1.5);
	}
	else
	{
		str.Format("%.2f",0);
	}
	RECVCommDataFile.SaveFile(str,str.GetLength());
	str = "\r\n";
	RECVCommDataFile.SaveFile(str,str.GetLength());

}
