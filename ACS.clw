; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWaveView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ACS.h"

ClassCount=22
Class1=CACSApp
Class2=CACSDlg
Class3=CAboutDlg

ResourceCount=20
Resource1=IDR_MENU
Resource2=IDR_MAINFRAME
Class4=CShipPage
Resource3=IDD_ADVANCED
Resource4=IDD_DIALOG_Tablog
Class5=CMorsePage
Resource5=IDD_DIALOG_AD
Class6=CMorseAUVPage
Resource6=IDD_DIALOGEDITPIC
Class7=CWordDialog
Resource7=IDD_DIALOG_WORD
Class8=CFsPage
Class9=CComParam
Class10=CPostView
Resource8=IDD_BASIC
Class11=CDataView
Resource9=IDD_ABOUTBOX
Class12=CWaveView
Resource10=IDD_PICTURE
Class13=CAdcpPage
Class14=CPictureView
Resource11=IDD_DIALOG_DATA
Class15=COptionSet
Resource12=IDD_DIALOG_COMPARAM
Class16=CLogView
Resource13=IDD_OPTIONS
Class17=CADSamplePage
Resource14=IDD_DIALOG_EDITPIC
Resource15=IDD_ACS_DIALOG
Class18=CBasicSet
Class19=CAdvancedSet
Resource16=IDD_DIALOG_LOG
Class20=CTabLog
Resource17=IDD_DIALOG_POSTVIEW
Class21=CImageSelect
Resource18=IDD_DIALOG_WAVEVIEW
Resource19=IDD_DIALOG_ADCP
Class22=CVideoSelect
Resource20=IDD_DIALOG_VIDEO

[CLS:CACSApp]
Type=0
HeaderFile=ACS.h
ImplementationFile=ACS.cpp
Filter=N
LastObject=CACSApp

[CLS:CACSDlg]
Type=0
HeaderFile=ACSDlg.h
ImplementationFile=ACSDlg.cpp
Filter=D
LastObject=IDC_TAB
BaseClass=CDialog
VirtualFilter=dWC

[CLS:CAboutDlg]
Type=0
HeaderFile=ACSDlg.h
ImplementationFile=ACSDlg.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_ACS_DIALOG]
Type=1
Class=CACSDlg
ControlCount=133
Control1=IDC_BUTTON1,button,1342177280
Control2=IDC_EDIT_LOG,edit,1352728644
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO_XMT,combobox,1344340226
Control5=IDC_BUTTON_START,button,1342242817
Control6=IDC_OPEN_OPTION,button,1342242816
Control7=IDC_LIST_ADCP,SysListView32,1350639637
Control8=IDC_TAB,SysTabControl32,1342242816
Control9=IDC_ADVANCED,button,1342242816
Control10=IDC_STATIC,button,1342178055
Control11=IDC_SLIDER_AMP,msctls_trackbar32,1342242836
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC_AMP,static,1342308352
Control14=IDC_STATIC,button,1342178055
Control15=IDC_STATIC,static,1342177287
Control16=IDC_STATIC,static,1342177287
Control17=IDC_ADSAMPLE,button,1342242816
Control18=IDC_IMAGE,static,1342308352
Control19=IDC_LOG,button,1342242817
Control20=IDC_STATIC,button,1342178055
Control21=IDC_STATIC,button,1342178055
Control22=IDC_BUTTON3,button,1342242816
Control23=IDC_BUTTON4,button,1342242816
Control24=IDC_BUTTON5,button,1342242816
Control25=IDC_BUTTON6,button,1342242816
Control26=IDC_BUTTON7,button,1342242816
Control27=IDC_BUTTON8,button,1342242816
Control28=IDC_BUTTON9,button,1342242816
Control29=IDC_BUTTON10,button,1342242816
Control30=IDC_BUTTON11,button,1342242816
Control31=IDC_BUTTON12,button,1342242816
Control32=IDC_STATIC,static,1342308352
Control33=IDC_STATIC,static,1342308352
Control34=IDC_STATIC,static,1342308353
Control35=IDC_STATIC,static,1342308353
Control36=IDC_STATIC,static,1342308353
Control37=IDC_STATIC,static,1342308353
Control38=IDC_STATIC,static,1342308353
Control39=IDC_STATIC,static,1342308353
Control40=IDC_STATIC,static,1342308353
Control41=IDC_STATIC,static,1342308353
Control42=IDC_STATIC,static,1342308353
Control43=IDC_STATIC,static,1342308353
Control44=IDC_STATIC,static,1342177287
Control45=IDC_STATIC,static,1342177287
Control46=IDC_STATIC,static,1342177287
Control47=IDC_STATIC,static,1342308352
Control48=IDC_STATIC,static,1342308352
Control49=IDC_FH_SEND,button,1342242816
Control50=IDC_FHLOG,edit,1352730692
Control51=IDC_FHWORD,edit,1350631552
Control52=IDC_STATIC,static,1342308352
Control53=IDC_COMBO_DIGITCHNNL,combobox,1344340226
Control54=IDC_STATIC,static,1342308352
Control55=IDC_SLIDER_DIGITALAMP,msctls_trackbar32,1342242836
Control56=IDC_STATIC,static,1342308352
Control57=IDC_STATIC_DIGITALAMP,static,1342308352
Control58=IDC_RADIO_MFSK,button,1342177289
Control59=IDC_RADIO_MPSK,button,1342177289
Control60=IDC_STATIC,static,1342308354
Control61=IDC_STATIC,static,1342308354
Control62=IDC_STATIC,static,1342308354
Control63=IDC_STATIC,static,1342308354
Control64=IDC_STATIC,static,1342308354
Control65=IDC_STATIC,static,1342308354
Control66=IDC_STATIC,static,1342308354
Control67=IDC_STATIC,static,1342308354
Control68=IDC_STATIC,static,1342308354
Control69=IDC_STATIC,static,1342308354
Control70=IDC_STATIC,static,1342308354
Control71=IDC_STATIC,static,1342308354
Control72=IDC_STATIC_p5,static,1342308352
Control73=IDC_STATIC_p12,static,1342308352
Control74=IDC_STATIC_r1,static,1342308352
Control75=IDC_STATIC_send,static,1342308352
Control76=IDC_STATIC_5t,static,1342308352
Control77=IDC_STATIC_33t,static,1342308352
Control78=IDC_STATIC_n5,static,1342308352
Control79=IDC_STATIC_n12,static,1342308352
Control80=IDC_STATIC_r2,static,1342308352
Control81=IDC_STATIC_sw,static,1342308352
Control82=IDC_STATIC_BASE,static,1342308352
Control83=IDC_STATIC_24t,static,1342308352
Control84=IDC_PIC_RECVTIME,static,1342308352
Control85=IDC_ENFORCE_SEND,button,1342242816
Control86=IDC_PROGRESS9,msctls_progress32,1350565888
Control87=IDC_STATIC,static,1342308352
Control88=IDC_PROGRESS1,msctls_progress32,1350565893
Control89=IDC_PROGRESS2,msctls_progress32,1350565893
Control90=IDC_PROGRESS3,msctls_progress32,1350565893
Control91=IDC_PROGRESS4,msctls_progress32,1350565893
Control92=IDC_CH1,static,1342308352
Control93=IDC_CH2,static,1342308352
Control94=IDC_CH3,static,1342308352
Control95=IDC_CH4,static,1342308352
Control96=IDC_STATIC,button,1342178055
Control97=IDC_BUTTON13,button,1073807360
Control98=IDC_BUTTON14,button,1342242816
Control99=IDC_STATIC,button,1342178055
Control100=IDC_STATIC,static,1342308352
Control101=IDC_STATIC,static,1342308352
Control102=IDC_STATIC,static,1342308352
Control103=IDC_MARINE_TEMP,static,1342308352
Control104=IDC_MARINE_HUMID,static,1342308352
Control105=IDC_CO2,static,1342308352
Control106=IDC_STATIC,static,1342308352
Control107=IDC_STATIC,static,1342308352
Control108=IDC_MARINE_O2,static,1342308352
Control109=IDC_MARINE_TEMPINSIDE,static,1342308352
Control110=IDC_STATIC,static,1342308352
Control111=IDC_STATIC,static,1342308352
Control112=IDC_STATIC,static,1342308352
Control113=IDC_STATIC,static,1342308352
Control114=IDC_STATIC,static,1342308352
Control115=IDC_MARINE_PRESSURE,static,1342308352
Control116=IDC_STATIC,static,1342308352
Control117=IDC_STATIC,static,1342308352
Control118=IDC_STATIC,static,1342308352
Control119=IDC_MAIN_V,static,1342308352
Control120=IDC_MAIN_I,static,1342308352
Control121=IDC_STATIC,static,1342308352
Control122=IDC_STATIC,static,1342308352
Control123=IDC_STATIC,static,1342308352
Control124=IDC_STATIC,static,1342308352
Control125=IDC_MARINE_DEPTH,static,1342308352
Control126=IDC_MARINE_HEIGTH,static,1342308352
Control127=IDC_STATIC,static,1342308352
Control128=IDC_STATIC,static,1342308352
Control129=IDC_STATIC,static,1342308352
Control130=IDC_ADCP_UPDATETIME,static,1342308352
Control131=IDC_STATIC,button,1342178055
Control132=IDC_CHECKPSK,button,1476460547
Control133=IDC_BUTTON_LED,button,1342177291

[MNU:IDR_MENU]
Type=1
Class=?
Command1=ID_MENUSTART
Command2=ID_MENUCLOSEPC104
CommandCount=2

[CLS:CMorsePage]
Type=0
HeaderFile=MorsePage.h
ImplementationFile=MorsePage.cpp
BaseClass=CDialog
Filter=D
LastObject=CMorsePage
VirtualFilter=dWC

[CLS:CMorseAUVPage]
Type=0
HeaderFile=MorseAUVPage.h
ImplementationFile=MorseAUVPage.cpp
BaseClass=CDialog
Filter=D
LastObject=CMorseAUVPage
VirtualFilter=dWC

[CLS:CShipPage]
Type=0
HeaderFile=ShipPage.h
ImplementationFile=ShipPage.cpp
BaseClass=CPropertyPage
Filter=D

[DLG:IDD_DIALOG_WORD]
Type=1
Class=CWordDialog
ControlCount=4
Control1=ID_AddToList,button,1073807361
Control2=ID_Send,button,1207959552
Control3=IDC_EDIT_INPUT,edit,1352728644
Control4=IDC_EDIT_WORDLOG,edit,1352728900

[CLS:CWordDialog]
Type=0
HeaderFile=WordDialog.h
ImplementationFile=WordDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CWordDialog
VirtualFilter=dWC

[CLS:CFsPage]
Type=0
HeaderFile=FsPage.h
ImplementationFile=FsPage.cpp
BaseClass=CDialog
Filter=D

[DLG:IDD_DIALOG_COMPARAM]
Type=1
Class=CComParam
ControlCount=11
Control1=IDC_PARAMLIST,SysListView32,1350631425
Control2=IDC_GAIN,edit,1350631552
Control3=IDC_STATIC,static,1342308352
Control4=IDC_BUTTON_SETGAIN,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC_DISTANCE,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_BIN_ROLL,static,1342308352
Control10=IDC_STATIC,static,1342308352
Control11=IDC_BIN_PITCH,static,1342308352

[CLS:CComParam]
Type=0
HeaderFile=ComParam.h
ImplementationFile=ComParam.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_STATIC_DISTANCE
VirtualFilter=dWC

[DLG:IDD_PICTURE]
Type=1
Class=CPictureView
ControlCount=3
Control1=IDC_SELECTPIC,button,1342242816
Control2=IDC_STATIC,button,1342178055
Control3=IDC_BUTTON_SELECT,button,1342242816

[DLG:IDD_DIALOG_POSTVIEW]
Type=1
Class=CPostView
ControlCount=6
Control1=IDC_NTGRAPHCTRL1,{C9FE01C2-2746-479B-96AB-E0BE9931B018},1342242816
Control2=IDC_ZOOMOUT,button,1342242827
Control3=IDC_ZOOMIN,button,1342242827
Control4=IDC_SavePic,button,1342242816
Control5=IDC_LOOK_DOWN,button,1342242816
Control6=IDC_LOOK_FLAT,button,1342242816

[CLS:CPostView]
Type=0
HeaderFile=PostView.h
ImplementationFile=PostView.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CPostView

[DLG:IDD_DIALOG_DATA]
Type=1
Class=CDataView
ControlCount=40
Control1=IDC_STATIC,static,1342308352
Control2=IDC_HEAD,static,1342177288
Control3=IDC_STATIC,static,1342308352
Control4=IDC_UpdateTime,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_PITCH,static,1342177288
Control10=IDC_ROLL,static,1342177288
Control11=IDC_UWVLONG,static,1342177288
Control12=IDC_UWVLAT,static,1342177288
Control13=IDC_DISTANCEX,static,1342177288
Control14=IDC_DISTANCEY,static,1342177288
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC_UWVLONG,static,1342308352
Control18=IDC_STATIC_UWVLAT,static,1342308352
Control19=IDC_STATIC,button,1342178055
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_STATIC,static,1342308352
Control26=IDC_STATIC,static,1342308352
Control27=IDC_FRONT,static,1342177288
Control28=IDC_FRONTDOWN,static,1342177288
Control29=IDC_FRONTUP,static,1342177288
Control30=IDC_LEFT,static,1342177288
Control31=IDC_RIGHT,static,1342177288
Control32=IDC_DOWN,static,1342177288
Control33=IDC_BACKDOWN,static,1342177288
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,button,1342178055
Control36=IDC_BPUpdateTime,static,1342308352
Control37=IDC_STATIC,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_UWVDEEP,static,1342177288
Control40=IDC_UWVHEIGTH,static,1342177288

[CLS:CDataView]
Type=0
HeaderFile=DataView.h
ImplementationFile=DataView.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_DISTANCEX
VirtualFilter=dWC

[DLG:IDD_DIALOG_WAVEVIEW]
Type=1
Class=CWaveView
ControlCount=5
Control1=IDC_PAUSE,button,1342242827
Control2=IDC_SavPic,button,1073807360
Control3=IDC_BUTTON1,button,1342242827
Control4=IDC_WAVEZOOMIN,button,1342242827
Control5=IDC_WAVEZOOMOUT,button,1342242827

[CLS:CWaveView]
Type=0
HeaderFile=WaveView.h
ImplementationFile=WaveView.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTON1

[DLG:IDD_DIALOG_ADCP]
Type=1
Class=CAdcpPage
ControlCount=3
Control1=IDC_BUTTON1,button,1342242827
Control2=IDC_BUTTON2,button,1342242827
Control3=IDC_BUTTON3,button,1342242827

[CLS:CAdcpPage]
Type=0
HeaderFile=AdcpPage.h
ImplementationFile=AdcpPage.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BUTTON1

[CLS:CPictureView]
Type=0
HeaderFile=PictureView.h
ImplementationFile=PictureView.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BUTTON_SELECT
VirtualFilter=dWC

[DLG:IDD_OPTIONS]
Type=1
Class=COptionSet
ControlCount=9
Control1=IDC_SAVEAS,button,1342242816
Control2=IDC_LOAD,button,1342242816
Control3=IDC_ADVANCED,button,1342242819
Control4=IDC_BASIC,button,1342242819
Control5=IDC_SAVE,button,1342242817
Control6=IDC_BUTTON1,button,1342242816
Control7=IDC_SetTime,button,1342242816
Control8=IDC_RESETADIO,button,1342242816
Control9=IDC_DiSCONNECT,button,1342242816

[CLS:COptionSet]
Type=0
HeaderFile=OptionSet.h
ImplementationFile=OptionSet.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_BASIC
VirtualFilter=dWC

[DLG:IDD_DIALOG_LOG]
Type=1
Class=CLogView
ControlCount=1
Control1=IDC_EDIT1,edit,1352732740

[CLS:CLogView]
Type=0
HeaderFile=LogView.h
ImplementationFile=LogView.cpp
BaseClass=CDialog
Filter=D
LastObject=CLogView
VirtualFilter=dWC

[DLG:IDD_DIALOG_AD]
Type=1
Class=CADSamplePage
ControlCount=11
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_GAIN,edit,1350631552
Control4=IDC_SAMPLE_RATE,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_ADSTART,button,1342242816
Control7=IDC_adview3,button,1342242827
Control8=IDC_adview2,button,1342242827
Control9=IDC_adview1,button,1342242827
Control10=IDC_adview4,button,1342242827
Control11=IDC_ADREPLAY,button,1342242816

[CLS:CADSamplePage]
Type=0
HeaderFile=ADSamplePage.h
ImplementationFile=ADSamplePage.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_adview6
VirtualFilter=dWC

[DLG:IDD_BASIC]
Type=1
Class=CBasicSet
ControlCount=84
Control1=IDC_STATIC,button,1342178055
Control2=IDC_STATIC,button,1342178055
Control3=IDC_STATIC,button,1342178055
Control4=IDC_STATIC,button,1342178055
Control5=IDC_STATIC,static,1342308352
Control6=IDC_SysWorkMode,combobox,1344340226
Control7=IDC_STATIC,static,1342308352
Control8=IDC_ADIOWorkMode,combobox,1344340226
Control9=IDC_STATIC,static,1342308352
Control10=IDC_SyncConcurrence,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_IsTCM2Work,button,1342242819
Control13=IDC_STATIC,static,1342308352
Control14=IDC_DiscardLen,edit,1350631552
Control15=IDC_IsSendADIOData,button,1342242819
Control16=IDC_STATIC,button,1342178055
Control17=IDC_BeforeDecideData,button,1342242819
Control18=IDC_AfterDecideData,button,1342242819
Control19=IDC_AfterDecideBit,button,1342242819
Control20=IDC_ParamFactor,button,1342242819
Control21=IDC_PhaseFactor,button,1342242819
Control22=IDC_DopplerFactor,button,1342242819
Control23=IDC_STATIC,static,1342308352
Control24=IDC_IsAGCWork,combobox,1344340226
Control25=IDC_SAMETOGAIN1,button,1342242819
Control26=IDC_STATIC,static,1342308352
Control27=IDC_STATIC,static,1342308352
Control28=IDC_STATIC,static,1342308352
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_Gain1,edit,1350631552
Control33=IDC_Gain2,edit,1350631552
Control34=IDC_Gain3,edit,1350631552
Control35=IDC_Gain4,edit,1350631552
Control36=IDC_Gain5,edit,1350631552
Control37=IDC_Gain6,edit,1350631552
Control38=IDC_ADIOID,button,1342242819
Control39=IDC_DSP01ID,button,1342242819
Control40=IDC_DSP02ID,button,1342242819
Control41=IDC_DSP11ID,button,1342242819
Control42=IDC_DSP12ID,button,1342242819
Control43=IDC_STATIC,static,1342308352
Control44=IDC_XMTAmpValue,edit,1350631552
Control45=IDC_STATIC,static,1342308352
Control46=IDC_XMTSampleRate,edit,1350631552
Control47=IDC_STATIC,static,1342308352
Control48=IDC_XMTDelayToSync,edit,1350631552
Control49=IDC_STATIC,static,1342308352
Control50=IDC_MFSK_PACKET,edit,1350631552
Control51=IDC_STATIC,static,1342308352
Control52=IDC_MPSK_PACKET,edit,1350631552
Control53=IDC_MFSK_FRAMENUM,edit,1350631552
Control54=IDC_MPSK_FRAMENUM,edit,1350631552
Control55=IDC_STATIC,button,1342178055
Control56=IDC_STATIC,button,1342177287
Control57=IDC_STATIC,static,1342308352
Control58=IDC_RecChannelNum,edit,1350631552
Control59=IDC_STATIC,static,1342308352
Control60=IDC_RecvSampleRate,edit,1350631552
Control61=IDC_STATIC,static,1342308352
Control62=IDC_STATIC,static,1342308352
Control63=IDC_STATIC,static,1342308352
Control64=IDC_RECVDELAYSYNC,edit,1350631552
Control65=IDC_STATIC,static,1342308352
Control66=IDC_STATIC,static,1342308352
Control67=IDC_Chann1,button,1342242819
Control68=IDC_Chann2,button,1342242819
Control69=IDC_Chann3,button,1342242819
Control70=IDC_Chann4,button,1342242819
Control71=IDC_Chann5,button,1342242819
Control72=IDC_Chann6,button,1342242819
Control73=IDC_STATIC,static,1342308352
Control74=IDC_STATIC,static,1342308352
Control75=IDC_MFSK_RECVPACKET,edit,1350631552
Control76=IDC_STATIC,static,1342308352
Control77=IDC_STATIC,static,1342308352
Control78=IDC_MPSK_RECVPACKET,edit,1350631552
Control79=IDC_MFSK_RECVFRAMENUM,edit,1350631552
Control80=IDC_MPSK_RECVFRAMENUM,edit,1350631552
Control81=IDC_STATIC,button,1342177287
Control82=IDC_STATIC,button,1342177287
Control83=IDC_STATIC,static,1342308352
Control84=IDC_STATIC,static,1342308352

[DLG:IDD_ADVANCED]
Type=1
Class=CAdvancedSet
ControlCount=66
Control1=IDC_STATIC,button,1342178055
Control2=IDC_STATIC,button,1342178055
Control3=IDC_STATIC,button,1342178055
Control4=IDC_STATIC,button,1342178055
Control5=IDC_STATIC,button,1342178055
Control6=IDC_STATIC,button,1342178055
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_MPSKPreGuardLag,edit,1350631552
Control10=IDC_STATIC,static,1342308352
Control11=IDC_MPSKAftGuardLag,edit,1350631552
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_MPSKTrainSymbolNum,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_MPSKDataSymbolNum,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_MFSKPreGuardLag,edit,1350631552
Control20=IDC_STATIC,static,1342308352
Control21=IDC_MFSKAftGuardLag,edit,1350631552
Control22=IDC_STATIC,static,1342308352
Control23=IDC_STATIC,static,1342308352
Control24=IDC_MFSKInterGuardLag,edit,1350631552
Control25=IDC_STATIC,static,1342308352
Control26=IDC_MFSKataSymbolNum,edit,1350631552
Control27=IDC_ChirpLen,edit,1350631552
Control28=IDC_ChirpStartF,edit,1350631552
Control29=IDC_ChirpStopF,edit,1350631552
Control30=IDC_InterLeaverLen,edit,1350631552
Control31=IDC_BeltaMu,edit,1350631552
Control32=IDC_IterationNum,edit,1350631552
Control33=IDC_PreFilterTap,edit,1350631552
Control34=IDC_MuMin,edit,1350631552
Control35=IDC_SlideWinLen,edit,1350631552
Control36=IDC_AlfaPhase,edit,1350631552
Control37=IDC_AftFilterTap,edit,1350631552
Control38=IDC_MuMax,edit,1350631552
Control39=IDC_GamaMax,edit,1350631552
Control40=IDC_GamaMin,edit,1350631552
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,static,1342308352
Control44=IDC_STATIC,static,1342308352
Control45=IDC_STATIC,static,1342308352
Control46=IDC_STATIC,static,1342308352
Control47=IDC_STATIC,static,1342308352
Control48=IDC_STATIC,static,1342308352
Control49=IDC_STATIC,static,1342308352
Control50=IDC_STATIC,static,1342308352
Control51=IDC_STATIC,static,1342308352
Control52=IDC_STATIC,static,1342308352
Control53=IDC_STATIC,static,1342308352
Control54=IDC_STATIC,static,1342308352
Control55=IDC_STATIC,static,1342308352
Control56=IDC_STATIC,static,1342308352
Control57=IDC_STATIC,static,1342308352
Control58=IDC_STATIC,static,1342308352
Control59=IDC_MPSK_chirp_inter,edit,1350631552
Control60=IDC_STATIC,static,1342308352
Control61=IDC_MFSK_chirp_inter,edit,1350631552
Control62=IDC_STATIC,static,1342308352
Control63=IDC_STATIC,static,1342308352
Control64=IDC_STATIC,static,1342308352
Control65=IDC_cycle_prefix,edit,1350631552
Control66=IDC_CHECK1,button,1342242819

[CLS:CBasicSet]
Type=0
HeaderFile=BasicSet.h
ImplementationFile=BasicSet.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_Chann2
VirtualFilter=dWC

[CLS:CAdvancedSet]
Type=0
HeaderFile=AdvancedSet.h
ImplementationFile=AdvancedSet.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_CHECK1
VirtualFilter=dWC

[DLG:IDD_DIALOG_Tablog]
Type=1
Class=CTabLog
ControlCount=1
Control1=IDC_EDIT1,edit,1352728644

[CLS:CTabLog]
Type=0
HeaderFile=TabLog.h
ImplementationFile=TabLog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_EDIT1

[DLG:IDD_DIALOGEDITPIC]
Type=1
Class=CImageSelect
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CImageSelect]
Type=0
HeaderFile=ImageSelect.h
ImplementationFile=ImageSelect.cpp
BaseClass=CDialog
Filter=D
LastObject=CImageSelect
VirtualFilter=dWC

[DLG:IDD_DIALOG_EDITPIC]
Type=1
Class=CImageSelect
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352

[DLG:IDD_DIALOG_VIDEO]
Type=1
Class=CVideoSelect
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC_VIDEO,static,1342177285

[CLS:CVideoSelect]
Type=0
HeaderFile=VideoSelect.h
ImplementationFile=VideoSelect.cpp
BaseClass=CDialog
Filter=D
LastObject=CVideoSelect
VirtualFilter=dWC

