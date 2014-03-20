#ifndef _DATA_DEFINE_H_
#define _DATA_DEFINE_H_
#include "Afxtempl.h"
#include  "MFSKConv.h"
#include  "MPSKTurbo.h"
#include "ImageProc.h"
#define TIMEOUT_EVER 0xFFFFFFFF
#define MY_BACKCOLOR RGB( 205,205,205 )
#define BUF_SIZE 10240//10k
#define FILESIZE 100000//100k
#define WRITESIZE 1024//1024 һ����д�ļ��Ĵ�С
#define MAXEDITLEN 1024*10   //�������м�¼��ʾ�ı�����󳤶ȣ��������1024
#define MAXWRITENUM 100 //��������WRITESIZE����������������Ϊ(MAXWRITENUM+1)*WRITESIZE
#define MAXBUFFSIZE 163841//160K
#define NORECORDWORK   1     //��ӡ�ڿ��ƼĴ���BIT4�ߵ�ƽ����ʾ��¼��
#define WAVEINTERVAL 125
#define WMSG_SENDPHONEDATA WM_USER+100
#define	CABLE_NET_WMSG1	WM_USER+500//���������ͨ�ŵ���Ϣ��1
#define	CABLE_NET_WMSG2	WM_USER+501//���������ͨ�ŵ���Ϣ��2
#define	CABLE_NET_WMSG3	WM_USER+502//��watchdogͨ�ŵ���Ϣ��3
#define DiSTANCE_WMSG   WM_USER+503//��ʾ������Ϣ��
#define TIMEOUT_WMSG	WM_USER+504//�������ʱ��Ϣ��
#define	POSITION_NET_WMSG	WM_USER+510//���ն�λ�������ݵ���Ϣ��
#define	SAIL_NET_WMSG		WM_USER+520//���պ��п���ϵͳ���ݵ���Ϣ��
#define WMSG_SOUNDWAVE	WM_USER+800//¼���ļ��ر���Ϣ
#define	POSITION_NET_PORT	2000//���ն�λ�������ݵĶ˿�
#define	SAIL_NET_PORT1		3001//���ͺ��п���ϵͳ���ݵĶ˿�
#define	SAIL_NET_PORT2		4000//���պ��п���ϵͳ���ݵĶ˿�
#define INADDR_BROADCAST1 "255.255.255.255"
//���ڴ���tab�ϴ��������Ի���֮���������Ϣ
#define WMSG_POSTDRAW WM_USER+600
#define WMSG_LOG WM_USER+601
#define WMSG_TABLOG WM_USER+602
//////////////////////////////////////////////////////////////////////////
#define RECORDWORK     0     //��֮¼��
#define VOICERECORDREADTIMER 1  //׼��¼����ʱ��
#define WAVESHOWTIMER	2
#define LPTREADCONTROLTIMER 3//����ӡ��״̬�Ĵ�����ʱ����Ϊ����¼��׼��
#define ADPLAYTIMER 4//ad�طŶ�ʱ��
#define SYS_INFO_DISP_TIMER 5//ϵͳ��Ϣ��ʾ+ͨ�Ų�����ʾ
#define BUTTONTIMER 6//��ťʹ�ܶ�ʱ��
#define SENDSOUNDTIMER 7//�����������ݰ���ʱ��
#define NETLINKTIMER 8 //����״̬��ʱ��
#define LBLTIMER 9//������ʹ�ܶ�ʱ��
#define VOICEENABLE 10//��¼����־��ʱ������
#define USBLENABLE 11//���̻���ʹ��
#define USBLTIME 12//��ֹ���̻���ʱ��8��
#define USBLTIME2 13//ĸ�������뷢������֮��ʹ�ܳ��̻��߶�ʱ��
#define USBLTIME3 14//ĸ����������ʱʹ�ܳ��̻��߶�ʱ��
#define END_RECORD_FLAG 0x0000000070000000// ��¼������־
#define PI 3.1415926
#define FREQ  1000//1K
#define SAMPLE_RATE 8000
#define DOT 2000	//1��ળ���
//������AD����������ʾ��صĳ���
#define SAMPLINGNUBER 40000		//ÿͨ������ʾ����
#define POS_CHANL_BASE 0x1000	//��ʾȫ��ͨ��
extern HWND hWnd;//���ھ�������ڽ����̷߳��͵���Ϣ

//�����뷢�������йصı���
//���Ʒ�ʽ
#define MFSKMOD			0 
#define MPSKMOD			2
#define OPSKMOD			3
#define FHMOD			4
#define SOUNDMOD		6
#define SHIPMFSKSIZE	112
#define UWAMFSKSIZE		131
#define WORDSIZE		40
#define CIRCLENUM 10

#define HIGHBPPSIZE 8416   //��256��256ͼ�����1bppѹ�����ܵ��ֽ���
#define LOWBPPSIZE 6528		//��256��256ͼ�����0.8bppѹ�����ܵ��ֽ���
#define COLORIMAGESIZE 6560  //��ɫͼѹ�������ֽ���
#define GRAYIMAGESIZE  7040  //�Ҷ�ͼѹ�������ֽ���
#define IMAGESIZE512X512 16560

//work command

#define UWACCMD_ANS			0x7000ffff		//���������Ӧ��
#define UWACCMD_BIT			0x70000201		//�Լ�����
#define UWACPARA_SYSINT		0x70000202		//ϵͳ��ʼ������
#define UWACCMD_SETTIME		0x70001001		//��������
#define UWACCMD_LOADDSP		0x70001002		//DSP���¼�������
#define UWACCMD_TCMINIT		0x70001003		//TCM2��ʼ��
#define UWACCMD_TCMSTART	0x70001004		//TCM2��������
#define UWACCMD_TCMSTOP		0x70001005		//TCM2ֹͣ����
#define UWACCMD_STARTDSP	0x70001006		//dsp��ʼ����
#define UWACCMD_PC014HALT	0x70001008      //PC104ϵͳ�ر�
#define UWACCMD_SYSTEMRESET	0x70001009      //PC104ϵͳ��λ��ADIO��λ

#define UWACCMD_LOADADIO	0x70002001		//ADIO���¼�������
#define UWACCMD_STARTTALK   0x70002002		//ADIO����ˮ��ͨ������
#define UWACCMD_PAUSETALK   0x70002003		//ADIO��ͣˮ��ͨ������
#define UWACCMD_ADIOSTOP    0x70002004		//ADIOֹͣ���������ص���ʼ��ǰ״̬
#define UWACCMD_ADIOREQUEST	0x70002005	//ADIO����������
#define UWACPARA_SETGAIN	0x70002006		//AGC�������˹��������
#define UWACCMD_RESETADIO	0x70002007		//PC104д�˿ڸ�λADIO��
#define UWACCMD_CHANGE_TRANS	0x70002009	 //����������
#define UWACCMD_FORCE_TRANSMIT  0x7000200A	//����������������
#define UWACCMD_SOUND_END	0x7000200b		//ˮ�����ݷ������
#define UWACCMD_DEMODULATION_MOD	0x7000200c//�����������
#define UWACCMD_READMEM   0x70003001		// 	���ڴ�����
#define UWACCMD_WRITEMEM   0x70003002		// 	д�ڴ�����
#define UWACCMD_FILLMEM   0x70003003		// 	����ڴ�����

#define UWACCMD_START_SAMPLE_AD   0x70004001		// 	AD�ɼ�����
#define UWACCMD_STOP_SAMPLE_AD    0x70004002
//return command 
#define	RESULT_RIGHT    0xffff0001			//��ȷ
#define	RESULT_WRONG	0xffff0002			//����
#define	RESULT_WAIT		0xffff0003			//������������ȴ�
//��������Э�����Ŀ�ĵص�ID
#define SONARCONTROLID	0x00000001			//�Կص�ID��
#define PC104ID			0x00000002			//PC104��ID��
#define ADIOID			0x00000008			//ADIO��ID��
#define DSP01ID			0x00000010			//DSP01��ID��
#define DSP02ID			0x00000020			//DSP02��ID��
#define DSP11ID			0x00000040			//DSP11��ID��
#define DSP12ID			0x00000080			//DSP12��ID��

#define UWACDATA_BIT			0x70006000	//�Լ���
#define UWACDATA_DFEOUT			0x70006001	//�ش��������о���ı����������ѹ����ʽ
#define UWACDATA_TCM2DATA		0x70006002	//TCM2�ɼ�����
#define UWACDATA_SENSORDATA		0x70006003	//ADIO�¶�ѹ����ѹ���ݽ��
#define UWACDATA_DECRESULT		0x70006004	//������������ݽ��(��ѹ����ʽ)
#define UWACDATA_ADIOSTATE		0x70006005		//ADIO�յ�ͬ���ź�ʱ�Ĺ���״̬�����䡢���ա����У�
#define UWACDATA_PROCESS_PARA	0x70006006	//ADIO�ش�ͬ���������
#define UWACDATA_DEMODULATION_PHONEDATA 0x70006007 //ˮ���绰������ݻش�
#define UWACDATA_MODULATION_PHONEDATA 0x70006008//�´�ˮ���绰����
#define UWACDATA_FH_DATA		0x70006009//��Ƶ����
#define UWACDATA_MIXDATA		0x70006100		//�ش��������
#define UWACDATA_SAMDATA		0x70006101		//�ش�ԭʼAD��������
#define UWACDATA_D1OUT			0x70006102		//�ش��������о�ǰ�������
#define UWACDATA_W				0x70006103      //�ش�������Ȩϵ����������
#define UWACDATA_GARMA			0x70006104      //�ش���������λ��������
#define UWACDATA_DOPPDELTA		0x70006105		//�ش�������Ƶ������
#define UWACDATA_D2OUT			0x70006106		//�ش��������о��������

//�Լ���
#define SELFCHECK_FALSE	0xffffffff			//
#define SELFCHECK_RIGHT	0x00000000			//

//PC104�Ƿ񱣴洦���м�����
#define UWACCMD_PC104_SAVE_NO_DATA 0      //��������ģʽ���������м�����
#define UWACCMD_PC104_SAVE_ADIO_TO_PRE 1  //����ADIOͨ��LINK�ڴ����Ԥ������������
#define UWACCMD_PC104_SAVE_PRE_TO_NORMA 2 //����Ԥ������������������ݴ����������
#define UWACCMD_PC104_SAVE_NORMA 3        //����������������������


typedef struct Host 
{	
	HWND hwnd;
	char HostIp[256];
	int Port;
}HostInfo;
typedef struct  message
{	
	HWND hwnd;
	char HostIp[256];
	int Port;
	CString buffer;
	UINT nOverTime;
	
}MessageInfo;
struct NET_PACKET{
	DWORD   FrmID;			//����ID�ţ����庬��鿴"Define.h"
	DWORD	FrmLen;			//�����ܳ�
	DWORD	DestID;			//Ŀ�ĵ�ID�ţ����庬��鿴"Define.h"
	DWORD	HeadParam[5];	//��ͬ���͵İ�������5�����еĶ��岻һ��
	char *	pData;			// ����ָ��
};
struct DATABUFF {
	int len;
	short *buf;
};
struct DIGITALBUFF {
	int len;
	BYTE *buf;
};
struct ADIOSTATUS {
	int SyncCount; //�յ�ͬ������Ĵ���
	int SyncTime;  //�յ�ͬ�������ʱ�̣���ʱû���õ�
	int States;    //ADIO����״̬��0�����У�1������״̬��2������״̬
};
//���������Ĵ���������
struct TCM2_T
{
    float compass;
    float pitch; 
    float roll; 
    float megx; 
    float megy;
    float megz;
    float t;   
    int sum;  
    int error_code;//��Ϊ0��������Ч����0������Ч
};
struct SYSTEMSENSORDATA
{
    float WaterTemperature; //ˮ�����ݣ���
    float Pressure;			//ѹ�����ݣ�MPa
    float VoltageP5;		//+5V��Դ��ѹ���ݣ�V
    float VoltageN5;		//-5V��Դ��ѹ���ݣ�V
    float VoltageP12;		//+12V��Դ��ѹ���ݣ�V
    float VoltageN12;		//-12V��Դ��ѹ���ݣ�V
    float Recv1Temperature; //���ջ���1�¶����ݣ���
    float Recv2Temperature; //���ջ���2�¶����ݣ���
    float XMTTemperature;   //��������¶����ݣ���
    float TRSwitchTemperature; //�շ�ת�����¶����ݣ���
    float Power5VTemperature; //5V��Դ���¶����ݣ���
    float Power12VTemperature; //12V��Դ���¶����ݣ���
    float Power3V3Temperature; //3.3V��Դ���¶����ݣ���
    float Power24VTemperature; //24V��Դ���¶����ݣ���
    float BaseTemperature;  //���ֻ����¶����ݣ���
	int Reserved[8];
};


//ͨ��ϵͳ��ʼ������
struct UWACINITPARA {
	int		ID;				//	0x70000202
	int		Len;			//�������ȣ�����Ϊ��λ��
	int		SysWorkMode;	//ͨ��ϵͳ�Ĺ�����ʽ��
	//0��������������ֹ�ش�������Ϣ
	//1������״̬
	int		ADIOWorkMode;	//����������ӻ���־λ��0��ʾ������Ǳˮ���ˣ�1��ʾ�ӻ������ն�
	int		IsSendADIOData;	//�Ƿ�ش�ADIO��������
	int		IsSendDSPData;	//�Ƿ�ش�DSP��������
	int		IsTCM2Work;		//TCM2�Ƿ�����0�������� 1������
	int		IsAGCWork;		//AGC������ʽ��0���̶����� 1���Զ��������
	int		AGCValue[8];    //8ͨ����������֣��ڹ̶�����ʱ��Ϊ�̶����棬���Զ��������ʱΪ��ʼ����
	int		RecvChannelNum;	//����ͨ����
	int		ValidChannel;	//��Ч�Ĳ���ͨ��
	float	XMTAmpValue;	//�����źŷ��ȵı���ϵ����0��1
	int		XMTChannelNo;	//���ڷ���Ļ�������
	float   XMTDelayToSync;	//�������յ�ͬ��ʱ������󵽿�ʼ������ӳ�
	int		XMTPackageNum;	//һ���շ�ѭ���з���İ���
	int		XMTPackFramNum; //һ��������е�֡��mfsk
	int		XMTCodedFramNum;//һ���շ�ѭ���з���ı���֡��
	int		RecvPackageNum;//һ���շ�ѭ���н��յİ���
	int		RecvPackFramNum;//һ�����հ��е�֡��
	int		RecvCodedFramNum;//һ���շ�ѭ���н��յı���֡��
	float   RecvDelayToSync;//ͨ�ŶԷ����յ�ͬ��ʱ������󵽿�ʼ������ӳ�
	
	int		SyncConcurrence;	//ͬ����������
	float   CentralFrequency;	//����Ƶ�ʣ�10k��
	
	float	XMTSampleRate;	//�����źŲ���Ƶ��
	int		XMTModulation;	//������Ʒ�ʽ
	int		XMTWhiteProcess;//����˵İ׻�����
	float	RecvSampleRate;	//���ղ���Ƶ��
	int		RecvModulation;	//���յ��Ʒ�ʽ
	int		RecvWhiteProcess;//���ն˵İ׻�����
	float	ChirpLen;		//Chirp�źŵĳ���
	float	ChirpStartF;	//Chirp�źŵ���ʼƵ��
	float	ChirpStopF;		//Chirp�źŵĽ���Ƶ
	int		DiscardLen;		//�ֶ�������Hilb�任ȥͷ��β�ĳ���
	float	MPSKPreGuardLag;//MPSKǰ�����������
	float	MPSKAftGuardLag;//MPSK�󱣻��������
	int		MPSKTrainSymbolNum;//MPSKѵ�����з�����
	int		MPSKDataSymbolNum;//MPSK���ݷ�����
	int     MPSKDataSymbolFre;//MPSK���ݷ����ʣ�5k/s��
	
	int		PreFilterTap;	//������ǰ������
	int		AftFilterTap;	//��������������
	float	MuMax;			//��������Mu���Ͻ�
	float	MuMin;			//��������Mu���½�
	float	AlfaPhase;		//������λ�õĳ���
	float	BeltaMu;		//����Mu�õĳ���
	float	GamaMax;		//��λ���������Ͻ�
	float	GamaMin;		//��λ���������½�
	
	float	MFSKPreGuardLag;//MFSKǰ�����������
	float	MFSKAftGuardLag;//MFSK�󱣻��������
	float	MFSKInterGuardLag;//MFSK��Ԫ��ļ������
	int		MFSKDataSymbolNum;//MFSK���ݷ�����
	int     MFSKDataSymbolLen;//MFSK���ݷ��ŵ�����2048��
	
	int		InterleaverLen;//��֯����
	int		SlideWinLen;//����������
	int     IterationNum;//����������
	
	int		TrainingSequence[32];//ѵ�����У���ѹ����ʽ����λ��ǰ
	int		VoiceCodeMode;//�������뷽ʽ 1: 1.1melp  2: 2.4melp
	int		LoadDestID;		//����Ŀ�ĵ� ADIOID DSP01ID DSP02ID DSP11ID DSP10ID
	int		PC104SaveData;  //PC104�������ݣ�
	int		XMTMPSKPackageNum;	//һ���շ�ѭ���з���İ���
	int		XMTMPSKPackFramNum; //һ��������е�֡��
	int		RecvMPSKPackageNum;//һ���շ�ѭ���н��յİ���
	int		RecvMPSKPackFramNum;//һ�����հ��е�֡��
	float	MFSK_chirp_inter;
	float	MPSK_chirp_inter;
	int		Cycle_prefix;
	int		digital_tranmit_channel;
	int		Reserved[24];//Ԥ��
	
};
struct COMMUNICATIONPARAM
{
	int Gain[8];
	int AGCamp[8];
	float ChirpCorrePeak[8];
	float ChannCorreCoe[8];
	int reserved[8];
	
};
struct UWACOMPARAM  
{
	int Mode;
	int XmtChannel;
	int RecvChannel;
	float XmtAmp;
	int Gain;

};

//����ϵͳ����ѧϵͳ���ݰ�����//��׼���ݽṹ////////////////////////////////////////////////////////////
struct SYSPOSITION 
{
//	__int64 ltime;
	FILETIME ltime;	
	float shipLONG;//ĸ������
	float shipLAT; //ĸ��γ��
	short shipvel;//ĸ���ٶ�
	unsigned short shipheading;//ĸ�������
	short shippitch;//ĸ�������
	short shiproll;//ĸ�������
	float   subLONG; //Ǳˮ������
	float   subLAT;//Ǳˮ��γ��
	unsigned short  subdepth;//Ǳˮ�����
	short    relateX;//Ǳˮ�����ĸ��x��λ��
	short    relateY;//Ǳˮ�����ĸ��y��λ��
	unsigned short    relateZ;//Ǳˮ�����ĸ��z��λ��	

};//��λ��Ϣ
struct BPDATA {
	FILETIME ltime;
	unsigned short		frontup;//ǰ�ϱ������ž���
	unsigned short		front;//��ǰ
	unsigned short		frontdown;//ǰ��
	unsigned short		down;//����
	unsigned short		behinddown;//����
	unsigned short		left;//����
	unsigned short		right;//����	
};//������Ϣ

struct BSSSDATA {
	FILETIME ltime;
	short depth;//���뺣�׸߶�
};//�����ɨ��Ϣ



struct CTDDATA {
	FILETIME ltime;
	unsigned short watertemp;//��ˮ�¶�
	unsigned short vartlevel;//
	unsigned short watercond;//��ˮ�絼��
	unsigned short soundvec;//����
};//CTD��Ϣ

struct SUBPOSITION {
	FILETIME ltime;
	float   subLONG; //Ǳˮ������
	float   subLAT;//Ǳˮ��γ��
	unsigned short subheading;//Ǳˮ�������
	short subpitch;//Ǳˮ�������
	short subroll;//Ǳˮ�������
	short subupdownvec;//Ǳˮ�������ٶ�
	short subpitchvec;//Ǳˮ�����ٶ�
	short subrollvec;//Ǳˮ�����ٶ�
	unsigned short subdepth;//Ǳˮ�����
	unsigned short subheight;//Ǳˮ���߶�
};//Ǳˮ��λ����Ϣ



struct ABNORMITY{
	FILETIME ltime;
	BYTE	equipNO;//�豸��
	BYTE	abnorm;// oxff ��ʾ����
};//��ѧ�豸�쳣��Ϣ

struct LIFESUPPLY {
	FILETIME ltime;
	BYTE  oxygen;//����Ũ��
	BYTE  CO2;//������̼Ũ��
	BYTE  pressure;//����ѹ��
	BYTE  temperature;//�����¶�
	unsigned short  humidity; //����ʪ��		
};//����֧��ϵͳ

struct ENERGYSYS {
	FILETIME ltime;
	unsigned short  mainV;//����ص�ѹ
	unsigned short  mainI;//����ص���
	unsigned short  mainconsume;//�������Դ����
	unsigned short  subV;//����ص�ѹ
	unsigned short  subI;//����ص���
	unsigned short  subconsume;//�������Դ����	
};//��Դϵͳ��Ϣ

struct ALERTDATA {
	FILETIME ltime;
	BYTE  alert[4];//����
	BYTE	aleak;//���˲�©ˮ
	unsigned short	pressure;//Ӧ��ҺѹԴѹ��
	unsigned short	head;//������Һλ���
	unsigned short	behind;//������Һλ���
	unsigned short	cable;//ѹ��ˮ��Һλ
	BYTE    temperature;//��������¶�
};//������Ϣ

struct SWITCHDATA {
	FILETIME ltime;
	BYTE  equipNO;//�豸��
	BYTE  state;//����״̬
};//������Ϣ

struct SHIPPOST {
//	__int64 ltime;
	FILETIME ltime;	
	float shipLONG;//ĸ������
	float shipLAT; //ĸ��γ��
	float shipheading;//ĸ�������
};//ĸ����λ��Ϣ

struct subPOST//��5�εĶ�λ��Ϣ
{
	FILETIME ltime[5];	
	float   subLONG[5]; //Ǳˮ������
	float   subLAT[5];//Ǳˮ��γ��
};

//////////////////////////////////////////////////////////////////////////
///ˮ��ͨ���ڲ����ݽṹ
 struct mfskSYSPOSITION {
	FILETIME ltime;	//��ʼʱ��
	BYTE   interval[4];//interval time from ltime
	float   subLONG[5]; //Ǳˮ������
	float   subLAT[5];//Ǳˮ��γ��
	unsigned short  subdepth;//Ǳˮ�����
	short    relateX;//Ǳˮ�����ĸ��x��λ��
	short    relateY;//Ǳˮ�����ĸ��y��λ��
	unsigned short    relateZ;//Ǳˮ�����ĸ��z��λ��	
	float shipLONG;//ĸ������
	float shipLAT; //ĸ��γ��
};//��λ��Ϣ

struct ADCPDATA{
	char	floorX[10];
	char	floorY[10];
	char	floorZ[10];
};//������Ϣ ps�Զ���

struct ADLDATA {
	float adl1;//
	float adl2;//
};//ADL

struct mfskBPDATA {
	BYTE	frontup;//ǰ�ϱ������ž���
	BYTE	front;//��ǰ
	BYTE	frontdown;//ǰ��
	BYTE	down;//����
	BYTE	behinddown;//����
	BYTE	left;//����
	BYTE	right;//����	
};//������Ϣ

struct mfskBSSSDATA {
	BYTE depth;//���뺣�׸߶�
};//�����ɨ��Ϣ



struct mfskCTDDATA {
	unsigned short watertemp;//��ˮ�¶�
	unsigned short watercond;//��ˮ�絼��
	BYTE vartlevel;//�ɱ�ѹ��ˮ��Һλ
	BYTE soundvec;//����
};//CTD��Ϣ

struct mfskSUBPOSITION {
	float   subLONG; //Ǳˮ������
	float   subLAT;//Ǳˮ��γ��
	unsigned short subheading;//Ǳˮ�������
	short subpitch;//Ǳˮ�������
	short subroll;//Ǳˮ�������
	unsigned short subdepth;//Ǳˮ�����
	char subupdownvec;//Ǳˮ�������ٶ�
	char subpitchvec;//Ǳˮ�����ٶ�
	char subrollvec;//Ǳˮ�����ٶ�
	BYTE subheight;//Ǳˮ���߶�
};//Ǳˮ��λ����Ϣ


struct mfskLIFESUPPLY {
	BYTE  oxygen;//����Ũ��
	BYTE  CO2;//������̼Ũ��
	BYTE  pressure;//����ѹ��
	BYTE  temperature;//�����¶�
	BYTE  humidity; //����ʪ��		
};//����֧��ϵͳ

struct mfskENERGYSYS {
	BYTE  mainV;//����ص�ѹ
	BYTE  mainI;//����ص���
	BYTE  mainconsume;//�������Դ����
	BYTE  subV;//����ص�ѹ
	BYTE  subI;//����ص���
	BYTE  subconsume;//�������Դ����	
};//��Դϵͳ��Ϣ

struct mfskALERTDATA {
	BYTE	alert[4];//����
	BYTE	aleak;//���˲�©ˮ
	BYTE	pressure;//Ӧ��ҺѹԴѹ��
	BYTE	head;//������Һλ���
	BYTE	behind;//������Һλ���
	BYTE	cable;//ѹ��ˮ��Һλ
	BYTE    temperature;//��������¶�
};//������Ϣ

struct mfskSWITCHDATA {
	BYTE  state[2];//����״̬
};//������Ϣ
//////////////////////////////////////////////////////////////////////////
extern CList <NET_PACKET*,NET_PACKET *> m_WzdNetpacketList;//���緢�����ݰ�������
extern CList <DIGITALBUFF *,DIGITALBUFF *> m_WzdtextList;	//��Ҫ���緢�͵�������������
extern CList <DATABUFF *,DATABUFF *> m_WzdvoiceList;	//��Ҫ���緢�͵�������������
extern CList <DIGITALBUFF *,DIGITALBUFF *> m_WzdimageList;	//��Ҫ���緢�͵�ͼ����������
extern UWACINITPARA UWACInitParam;//ϵͳ��������
extern UWACOMPARAM UWAcommparam;//�������
extern int Trainseq[32];//ѵ������
extern int Whiteseq[250];//�׻�����
// 
extern BOOL bFirstRecvData;
extern bool UsblEnableCheck;//ͬ���ӿ���;false:������ͬ����
extern int NorAmp;//ȫ�ֹ�һ������
extern CImageProc imageCode;//ͼ�����
extern CImageProc imageDecode;//ͼ�����
//extern BYTE ColorImageInit[COLORIMAGESIZE];
//extern BYTE GrayImageInit[GRAYIMAGESIZE];
extern BOOL m_bRecording;
extern CMPSKTurbo mpskturo;//turbo�ŵ�����
extern CMFSKConv  mfskconv;//����ŵ�����
#endif