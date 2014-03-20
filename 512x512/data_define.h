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
#define WRITESIZE 1024//1024 一次性写文件的大小
#define MAXEDITLEN 1024*10   //程序运行记录显示文本的最大长度，必须大于1024
#define MAXWRITENUM 100 //最大允许的WRITESIZE个数，缓冲区长度为(MAXWRITENUM+1)*WRITESIZE
#define MAXBUFFSIZE 163841//160K
#define NORECORDWORK   1     //打印口控制寄存器BIT4高电平，表示不录音
#define WAVEINTERVAL 125
#define WMSG_SENDPHONEDATA WM_USER+100
#define	CABLE_NET_WMSG1	WM_USER+500//与吊舱网络通信的消息号1
#define	CABLE_NET_WMSG2	WM_USER+501//与吊舱网络通信的消息号2
#define	CABLE_NET_WMSG3	WM_USER+502//与watchdog通信的消息号3
#define DiSTANCE_WMSG   WM_USER+503//显示距离消息号
#define TIMEOUT_WMSG	WM_USER+504//数据命令超时消息号
#define	POSITION_NET_WMSG	WM_USER+510//接收定位声纳数据的消息号
#define	SAIL_NET_WMSG		WM_USER+520//接收航行控制系统数据的消息号
#define WMSG_SOUNDWAVE	WM_USER+800//录音文件关闭消息
#define	POSITION_NET_PORT	2000//接收定位声纳数据的端口
#define	SAIL_NET_PORT1		3001//发送航行控制系统数据的端口
#define	SAIL_NET_PORT2		4000//接收航行控制系统数据的端口
#define INADDR_BROADCAST1 "255.255.255.255"
//用于传递tab上窗体与主对话框之间命令的消息
#define WMSG_POSTDRAW WM_USER+600
#define WMSG_LOG WM_USER+601
#define WMSG_TABLOG WM_USER+602
//////////////////////////////////////////////////////////////////////////
#define RECORDWORK     0     //反之录音
#define VOICERECORDREADTIMER 1  //准备录音定时器
#define WAVESHOWTIMER	2
#define LPTREADCONTROLTIMER 3//读打印口状态寄存器定时器，为启动录音准备
#define ADPLAYTIMER 4//ad回放定时器
#define SYS_INFO_DISP_TIMER 5//系统信息显示+通信参数显示
#define BUTTONTIMER 6//按钮使能定时器
#define SENDSOUNDTIMER 7//发送声音数据包定时器
#define NETLINKTIMER 8 //网络状态定时器
#define LBLTIMER 9//长基线使能定时器
#define VOICEENABLE 10//与录音标志定时器共用
#define USBLENABLE 11//超短基线使能
#define USBLTIME 12//禁止超短基线时间8秒
#define USBLTIME2 13//母船接收与发送数据之间使能超短基线定时器
#define USBLTIME3 14//母船发送数据时使能超短基线定时器
#define END_RECORD_FLAG 0x0000000070000000// 记录结束标志
#define PI 3.1415926
#define FREQ  1000//1K
#define SAMPLE_RATE 8000
#define DOT 2000	//1滴嗒长度
//定义与AD采样波形显示相关的常量
#define SAMPLINGNUBER 40000		//每通道的显示点数
#define POS_CHANL_BASE 0x1000	//显示全部通道
extern HWND hWnd;//窗口句柄，用于接收线程发送的消息

//定义与发射数据有关的变量
//调制方式
#define MFSKMOD			0 
#define MPSKMOD			2
#define OPSKMOD			3
#define FHMOD			4
#define SOUNDMOD		6
#define SHIPMFSKSIZE	112
#define UWAMFSKSIZE		131
#define WORDSIZE		40
#define CIRCLENUM 10

#define HIGHBPPSIZE 8416   //对256×256图像进行1bpp压缩后总的字节数
#define LOWBPPSIZE 6528		//对256×256图像进行0.8bpp压缩后总的字节数
#define COLORIMAGESIZE 6560  //彩色图压缩后总字节数
#define GRAYIMAGESIZE  7040  //灰度图压缩后总字节数
#define IMAGESIZE512X512 16560

//work command

#define UWACCMD_ANS			0x7000ffff		//各种命令的应答
#define UWACCMD_BIT			0x70000201		//自检命令
#define UWACPARA_SYSINT		0x70000202		//系统初始化命令
#define UWACCMD_SETTIME		0x70001001		//对钟命令
#define UWACCMD_LOADDSP		0x70001002		//DSP重新加载命令
#define UWACCMD_TCMINIT		0x70001003		//TCM2初始化
#define UWACCMD_TCMSTART	0x70001004		//TCM2启动工作
#define UWACCMD_TCMSTOP		0x70001005		//TCM2停止工作
#define UWACCMD_STARTDSP	0x70001006		//dsp开始工作
#define UWACCMD_PC014HALT	0x70001008      //PC104系统关闭
#define UWACCMD_SYSTEMRESET	0x70001009      //PC104系统复位，ADIO复位

#define UWACCMD_LOADADIO	0x70002001		//ADIO重新加载命令
#define UWACCMD_STARTTALK   0x70002002		//ADIO启动水声通信流程
#define UWACCMD_PAUSETALK   0x70002003		//ADIO暂停水声通信流程
#define UWACCMD_ADIOSTOP    0x70002004		//ADIO停止工作，返回到初始化前状态
#define UWACCMD_ADIOREQUEST	0x70002005	//ADIO请求发射数据
#define UWACPARA_SETGAIN	0x70002006		//AGC参数，人工增益调整
#define UWACCMD_RESETADIO	0x70002007		//PC104写端口复位ADIO板
#define UWACCMD_CHANGE_TRANS	0x70002009	 //更换换能器
#define UWACCMD_FORCE_TRANSMIT  0x7000200A	//主动发射数据命令
#define UWACCMD_SOUND_END	0x7000200b		//水声数据发射结束
#define UWACCMD_DEMODULATION_MOD	0x7000200c//解调数据类型
#define UWACCMD_READMEM   0x70003001		// 	读内存命令
#define UWACCMD_WRITEMEM   0x70003002		// 	写内存命令
#define UWACCMD_FILLMEM   0x70003003		// 	填充内存命令

#define UWACCMD_START_SAMPLE_AD   0x70004001		// 	AD采集命令
#define UWACCMD_STOP_SAMPLE_AD    0x70004002
//return command 
#define	RESULT_RIGHT    0xffff0001			//正确
#define	RESULT_WRONG	0xffff0002			//错误
#define	RESULT_WAIT		0xffff0003			//缓冲区满，请等待
//定义网络协议包中目的地的ID
#define SONARCONTROLID	0x00000001			//显控的ID号
#define PC104ID			0x00000002			//PC104的ID号
#define ADIOID			0x00000008			//ADIO的ID号
#define DSP01ID			0x00000010			//DSP01的ID号
#define DSP02ID			0x00000020			//DSP02的ID号
#define DSP11ID			0x00000040			//DSP11的ID号
#define DSP12ID			0x00000080			//DSP12的ID号

#define UWACDATA_BIT			0x70006000	//自检结果
#define UWACDATA_DFEOUT			0x70006001	//回传均衡器判决后的比特流输出紧压缩格式
#define UWACDATA_TCM2DATA		0x70006002	//TCM2采集数据
#define UWACDATA_SENSORDATA		0x70006003	//ADIO温度压力电压数据结果
#define UWACDATA_DECRESULT		0x70006004	//解码比特流数据结果(紧压缩格式)
#define UWACDATA_ADIOSTATE		0x70006005		//ADIO收到同步信号时的工作状态（发射、接收、空闲）
#define UWACDATA_PROCESS_PARA	0x70006006	//ADIO回传同步处理参数
#define UWACDATA_DEMODULATION_PHONEDATA 0x70006007 //水声电话解调数据回传
#define UWACDATA_MODULATION_PHONEDATA 0x70006008//下传水声电话数据
#define UWACDATA_FH_DATA		0x70006009//扩频数据
#define UWACDATA_MIXDATA		0x70006100		//回传混合数据
#define UWACDATA_SAMDATA		0x70006101		//回传原始AD采样数据
#define UWACDATA_D1OUT			0x70006102		//回传均衡器判决前输出数据
#define UWACDATA_W				0x70006103      //回传均衡器权系数调整因子
#define UWACDATA_GARMA			0x70006104      //回传均衡器相位调整因子
#define UWACDATA_DOPPDELTA		0x70006105		//回传多普勒频移因子
#define UWACDATA_D2OUT			0x70006106		//回传均衡器判决后输出码

//自检结果
#define SELFCHECK_FALSE	0xffffffff			//
#define SELFCHECK_RIGHT	0x00000000			//

//PC104是否保存处理中间数据
#define UWACCMD_PC104_SAVE_NO_DATA 0      //正常工作模式，不保存中间数据
#define UWACCMD_PC104_SAVE_ADIO_TO_PRE 1  //保存ADIO通过LINK口传输给预处理程序的数据
#define UWACCMD_PC104_SAVE_PRE_TO_NORMA 2 //保存预处理程序处理结果，该数据传给均衡程序
#define UWACCMD_PC104_SAVE_NORMA 3        //保存均衡程序处理后输出的数据


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
	DWORD   FrmID;			//包的ID号，具体含义查看"Define.h"
	DWORD	FrmLen;			//包的总长
	DWORD	DestID;			//目的地ID号，具体含义查看"Define.h"
	DWORD	HeadParam[5];	//不同类型的包，在这5个字中的定义不一样
	char *	pData;			// 数据指针
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
	int SyncCount; //收到同步脉冲的次数
	int SyncTime;  //收到同步脉冲的时刻，暂时没有用到
	int States;    //ADIO工作状态，0－空闲，1－接收状态，2－发射状态
};
//吊舱送来的传感器数据
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
    int error_code;//若为0则数据有效，非0数据无效
};
struct SYSTEMSENSORDATA
{
    float WaterTemperature; //水温数据，℃
    float Pressure;			//压力数据，MPa
    float VoltageP5;		//+5V电源电压数据，V
    float VoltageN5;		//-5V电源电压数据，V
    float VoltageP12;		//+12V电源电压数据，V
    float VoltageN12;		//-12V电源电压数据，V
    float Recv1Temperature; //接收机板1温度数据，℃
    float Recv2Temperature; //接收机板2温度数据，℃
    float XMTTemperature;   //发射机板温度数据，℃
    float TRSwitchTemperature; //收发转换板温度数据，℃
    float Power5VTemperature; //5V电源板温度数据，℃
    float Power12VTemperature; //12V电源板温度数据，℃
    float Power3V3Temperature; //3.3V电源板温度数据，℃
    float Power24VTemperature; //24V电源板温度数据，℃
    float BaseTemperature;  //数字基板温度数据，℃
	int Reserved[8];
};


//通信系统初始化参数
struct UWACINITPARA {
	int		ID;				//	0x70000202
	int		Len;			//参数长度（以字为单位）
	int		SysWorkMode;	//通信系统的工作方式：
	//0：正常工作－禁止回传调试消息
	//1：调试状态
	int		ADIOWorkMode;	//发射机主机从机标志位。0表示主机，潜水器端，1表示从机，吊舱端
	int		IsSendADIOData;	//是否回传ADIO调试数据
	int		IsSendDSPData;	//是否回传DSP调试数据
	int		IsTCM2Work;		//TCM2是否工作。0：不工作 1：工作
	int		IsAGCWork;		//AGC工作方式，0：固定增益 1：自动增益调整
	int		AGCValue[8];    //8通道增益控制字，在固定增益时作为固定增益，在自动增益调整时为起始增益
	int		RecvChannelNum;	//采样通道数
	int		ValidChannel;	//有效的采样通道
	float	XMTAmpValue;	//发射信号幅度的比例系数，0～1
	int		XMTChannelNo;	//用于发射的换能器号
	float   XMTDelayToSync;	//本机在收到同步时钟脉冲后到开始发射的延迟
	int		XMTPackageNum;	//一个收发循环中发射的包数
	int		XMTPackFramNum; //一个发射包中的帧数mfsk
	int		XMTCodedFramNum;//一个收发循环中发射的编码帧数
	int		RecvPackageNum;//一个收发循环中接收的包数
	int		RecvPackFramNum;//一个接收包中的帧数
	int		RecvCodedFramNum;//一个收发循环中接收的编码帧数
	float   RecvDelayToSync;//通信对方在收到同步时钟脉冲后到开始发射的延迟
	
	int		SyncConcurrence;	//同步脉冲周期
	float   CentralFrequency;	//中心频率（10k）
	
	float	XMTSampleRate;	//发射信号采样频率
	int		XMTModulation;	//发射调制方式
	int		XMTWhiteProcess;//发射端的白化处理
	float	RecvSampleRate;	//接收采样频率
	int		RecvModulation;	//接收调制方式
	int		RecvWhiteProcess;//接收端的白化处理
	float	ChirpLen;		//Chirp信号的长度
	float	ChirpStartF;	//Chirp信号的起始频率
	float	ChirpStopF;		//Chirp信号的结束频
	int		DiscardLen;		//分段数据作Hilb变换去头截尾的长度
	float	MPSKPreGuardLag;//MPSK前保护间隔长度
	float	MPSKAftGuardLag;//MPSK后保护间隔长度
	int		MPSKTrainSymbolNum;//MPSK训练序列符号数
	int		MPSKDataSymbolNum;//MPSK数据符号数
	int     MPSKDataSymbolFre;//MPSK数据符号率（5k/s）
	
	int		PreFilterTap;	//均衡器前馈阶数
	int		AftFilterTap;	//均衡器反馈阶数
	float	MuMax;			//步长因子Mu的上界
	float	MuMin;			//步长因子Mu的下界
	float	AlfaPhase;		//调整相位用的常量
	float	BeltaMu;		//更新Mu用的常量
	float	GamaMax;		//相位调整因子上界
	float	GamaMin;		//相位调整因子下界
	
	float	MFSKPreGuardLag;//MFSK前保护间隔长度
	float	MFSKAftGuardLag;//MFSK后保护间隔长度
	float	MFSKInterGuardLag;//MFSK码元间的间隔长度
	int		MFSKDataSymbolNum;//MFSK数据符号数
	int     MFSKDataSymbolLen;//MFSK数据符号点数（2048）
	
	int		InterleaverLen;//交织长度
	int		SlideWinLen;//滑动窗长度
	int     IterationNum;//最大迭代次数
	
	int		TrainingSequence[32];//训练序列，紧压缩格式，低位在前
	int		VoiceCodeMode;//语音编码方式 1: 1.1melp  2: 2.4melp
	int		LoadDestID;		//加载目的地 ADIOID DSP01ID DSP02ID DSP11ID DSP10ID
	int		PC104SaveData;  //PC104保存数据，
	int		XMTMPSKPackageNum;	//一个收发循环中发射的包数
	int		XMTMPSKPackFramNum; //一个发射包中的帧数
	int		RecvMPSKPackageNum;//一个收发循环中接收的包数
	int		RecvMPSKPackFramNum;//一个接收包中的帧数
	float	MFSK_chirp_inter;
	float	MPSK_chirp_inter;
	int		Cycle_prefix;
	int		digital_tranmit_channel;
	int		Reserved[24];//预留
	
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

//控制系统与声学系统数据包定义//标准数据结构////////////////////////////////////////////////////////////
struct SYSPOSITION 
{
//	__int64 ltime;
	FILETIME ltime;	
	float shipLONG;//母船经度
	float shipLAT; //母船纬度
	short shipvel;//母船速度
	unsigned short shipheading;//母船艏向角
	short shippitch;//母船纵倾角
	short shiproll;//母船横倾角
	float   subLONG; //潜水器经度
	float   subLAT;//潜水器纬度
	unsigned short  subdepth;//潜水器深度
	short    relateX;//潜水器相对母船x轴位移
	short    relateY;//潜水器相对母船y轴位移
	unsigned short    relateZ;//潜水器相对母船z轴位移	

};//定位信息
struct BPDATA {
	FILETIME ltime;
	unsigned short		frontup;//前上避碰声呐距离
	unsigned short		front;//正前
	unsigned short		frontdown;//前下
	unsigned short		down;//正下
	unsigned short		behinddown;//后下
	unsigned short		left;//左下
	unsigned short		right;//右下	
};//避碰信息

struct BSSSDATA {
	FILETIME ltime;
	short depth;//距离海底高度
};//侧深侧扫信息



struct CTDDATA {
	FILETIME ltime;
	unsigned short watertemp;//海水温度
	unsigned short vartlevel;//
	unsigned short watercond;//海水电导率
	unsigned short soundvec;//声速
};//CTD信息

struct SUBPOSITION {
	FILETIME ltime;
	float   subLONG; //潜水器经度
	float   subLAT;//潜水器纬度
	unsigned short subheading;//潜水器艏向角
	short subpitch;//潜水器纵倾角
	short subroll;//潜水器横倾角
	short subupdownvec;//潜水器升沉速度
	short subpitchvec;//潜水器纵速度
	short subrollvec;//潜水器横速度
	unsigned short subdepth;//潜水器深度
	unsigned short subheight;//潜水器高度
};//潜水器位姿信息



struct ABNORMITY{
	FILETIME ltime;
	BYTE	equipNO;//设备号
	BYTE	abnorm;// oxff 表示正常
};//声学设备异常信息

struct LIFESUPPLY {
	FILETIME ltime;
	BYTE  oxygen;//氧气浓度
	BYTE  CO2;//二氧化碳浓度
	BYTE  pressure;//舱内压力
	BYTE  temperature;//舱内温度
	unsigned short  humidity; //舱内湿度		
};//生命支持系统

struct ENERGYSYS {
	FILETIME ltime;
	unsigned short  mainV;//主电池电压
	unsigned short  mainI;//主电池电流
	unsigned short  mainconsume;//主电池能源消耗
	unsigned short  subV;//副电池电压
	unsigned short  subI;//副电池电流
	unsigned short  subconsume;//副电池能源消耗	
};//能源系统信息

struct ALERTDATA {
	FILETIME ltime;
	BYTE  alert[4];//报警
	BYTE	aleak;//载人舱漏水
	unsigned short	pressure;//应急液压源压力
	unsigned short	head;//艏纵倾液位检测
	unsigned short	behind;//艉纵倾液位检测
	unsigned short	cable;//压载水舱液位
	BYTE    temperature;//计算机罐温度
};//报警信息

struct SWITCHDATA {
	FILETIME ltime;
	BYTE  equipNO;//设备号
	BYTE  state;//开关状态
};//开关信息

struct SHIPPOST {
//	__int64 ltime;
	FILETIME ltime;	
	float shipLONG;//母船经度
	float shipLAT; //母船纬度
	float shipheading;//母船艏向角
};//母船定位信息

struct subPOST//近5次的定位信息
{
	FILETIME ltime[5];	
	float   subLONG[5]; //潜水器经度
	float   subLAT[5];//潜水器纬度
};

//////////////////////////////////////////////////////////////////////////
///水声通信内部数据结构
 struct mfskSYSPOSITION {
	FILETIME ltime;	//起始时间
	BYTE   interval[4];//interval time from ltime
	float   subLONG[5]; //潜水器经度
	float   subLAT[5];//潜水器纬度
	unsigned short  subdepth;//潜水器深度
	short    relateX;//潜水器相对母船x轴位移
	short    relateY;//潜水器相对母船y轴位移
	unsigned short    relateZ;//潜水器相对母船z轴位移	
	float shipLONG;//母船经度
	float shipLAT; //母船纬度
};//定位信息

struct ADCPDATA{
	char	floorX[10];
	char	floorY[10];
	char	floorZ[10];
};//流速信息 ps自定义

struct ADLDATA {
	float adl1;//
	float adl2;//
};//ADL

struct mfskBPDATA {
	BYTE	frontup;//前上避碰声呐距离
	BYTE	front;//正前
	BYTE	frontdown;//前下
	BYTE	down;//正下
	BYTE	behinddown;//后下
	BYTE	left;//左下
	BYTE	right;//右下	
};//避碰信息

struct mfskBSSSDATA {
	BYTE depth;//距离海底高度
};//侧深侧扫信息



struct mfskCTDDATA {
	unsigned short watertemp;//海水温度
	unsigned short watercond;//海水电导率
	BYTE vartlevel;//可变压载水舱液位
	BYTE soundvec;//声速
};//CTD信息

struct mfskSUBPOSITION {
	float   subLONG; //潜水器经度
	float   subLAT;//潜水器纬度
	unsigned short subheading;//潜水器艏向角
	short subpitch;//潜水器纵倾角
	short subroll;//潜水器横倾角
	unsigned short subdepth;//潜水器深度
	char subupdownvec;//潜水器升沉速度
	char subpitchvec;//潜水器纵速度
	char subrollvec;//潜水器横速度
	BYTE subheight;//潜水器高度
};//潜水器位姿信息


struct mfskLIFESUPPLY {
	BYTE  oxygen;//氧气浓度
	BYTE  CO2;//二氧化碳浓度
	BYTE  pressure;//舱内压力
	BYTE  temperature;//舱内温度
	BYTE  humidity; //舱内湿度		
};//生命支持系统

struct mfskENERGYSYS {
	BYTE  mainV;//主电池电压
	BYTE  mainI;//主电池电流
	BYTE  mainconsume;//主电池能源消耗
	BYTE  subV;//副电池电压
	BYTE  subI;//副电池电流
	BYTE  subconsume;//副电池能源消耗	
};//能源系统信息

struct mfskALERTDATA {
	BYTE	alert[4];//报警
	BYTE	aleak;//载人舱漏水
	BYTE	pressure;//应急液压源压力
	BYTE	head;//艏纵倾液位检测
	BYTE	behind;//艉纵倾液位检测
	BYTE	cable;//压载水舱液位
	BYTE    temperature;//计算机罐温度
};//报警信息

struct mfskSWITCHDATA {
	BYTE  state[2];//开关状态
};//开关信息
//////////////////////////////////////////////////////////////////////////
extern CList <NET_PACKET*,NET_PACKET *> m_WzdNetpacketList;//网络发送数据包链表定义
extern CList <DIGITALBUFF *,DIGITALBUFF *> m_WzdtextList;	//需要网络发送的文字数据链表
extern CList <DATABUFF *,DATABUFF *> m_WzdvoiceList;	//需要网络发送的语音数据链表
extern CList <DIGITALBUFF *,DIGITALBUFF *> m_WzdimageList;	//需要网络发送的图像数据链表
extern UWACINITPARA UWACInitParam;//系统工作参数
extern UWACOMPARAM UWAcommparam;//处理参数
extern int Trainseq[32];//训练序列
extern int Whiteseq[250];//白化序列
// 
extern BOOL bFirstRecvData;
extern bool UsblEnableCheck;//同步钟控制;false:不控制同步钟
extern int NorAmp;//全局归一化参数
extern CImageProc imageCode;//图像编码
extern CImageProc imageDecode;//图像解码
//extern BYTE ColorImageInit[COLORIMAGESIZE];
//extern BYTE GrayImageInit[GRAYIMAGESIZE];
extern BOOL m_bRecording;
extern CMPSKTurbo mpskturo;//turbo信道编码
extern CMFSKConv  mfskconv;//卷积信道编码
#endif