# Microsoft Developer Studio Project File - Name="ACS" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=ACS - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ACS.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ACS.mak" CFG="ACS - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ACS - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "ACS - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ACS - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 wd_utils.lib ImageProc.lib MFSKConv.lib ws2_32.lib MPSKTurbo.lib /nologo /stack:0x200000 /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "ACS - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /I ".\CxImage\header" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /D "JAS_WIN_MSVC_BUILD" /Fr /FD /GZ /c
# SUBTRACT CPP /YX /Yc /Yu
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 wd_utils.lib ImageProc.lib MFSKConv.lib ws2_32.lib MPSKTurbo.lib .\CxImage\lib\Jpeg.lib .\CxImage\lib\cximage.lib libjasper.lib HYUtil.lib Shlwapi.lib /nologo /stack:0x200000 /subsystem:windows /debug /machine:I386 /nodefaultlib:"library" /pdbtype:sept
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "ACS - Win32 Release"
# Name "ACS - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ACS.cpp
# End Source File
# Begin Source File

SOURCE=.\ACS.rc
# End Source File
# Begin Source File

SOURCE=.\ACSDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\AdcpPage.cpp
# End Source File
# Begin Source File

SOURCE=.\ADSamplePage.cpp
# End Source File
# Begin Source File

SOURCE=.\AdvancedSet.cpp
# End Source File
# Begin Source File

SOURCE=.\BasicSet.cpp
# End Source File
# Begin Source File

SOURCE=.\BmpToJp2.cpp
# End Source File
# Begin Source File

SOURCE=.\BmpToJp2.h
# End Source File
# Begin Source File

SOURCE=.\Check.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckUSBL.cpp
# End Source File
# Begin Source File

SOURCE=.\ComParam.cpp
# End Source File
# Begin Source File

SOURCE=.\DataEncode.cpp
# End Source File
# Begin Source File

SOURCE=.\DataView.cpp
# End Source File
# Begin Source File

SOURCE=.\DIB.cpp
# End Source File
# Begin Source File

SOURCE=.\DispPanel.cpp
# End Source File
# Begin Source File

SOURCE=.\FFT.cpp
# End Source File
# Begin Source File

SOURCE=.\FileDataN.cpp
# End Source File
# Begin Source File

SOURCE=.\font.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\ImageShow.cpp
# End Source File
# Begin Source File

SOURCE=.\LogView.cpp
# End Source File
# Begin Source File

SOURCE=.\lpt_lib.cpp
# End Source File
# Begin Source File

SOURCE=.\MediaChannel.cpp
# End Source File
# Begin Source File

SOURCE=.\Morse.cpp
# End Source File
# Begin Source File

SOURCE=.\NetSocket.cpp
# End Source File
# Begin Source File

SOURCE=.\ntgraph.cpp
# End Source File
# Begin Source File

SOURCE=.\OptionSet.cpp
# End Source File
# Begin Source File

SOURCE=.\picture.cpp
# End Source File
# Begin Source File

SOURCE=.\PictureView.cpp
# End Source File
# Begin Source File

SOURCE=.\PlayMMSound.cpp
# End Source File
# Begin Source File

SOURCE=.\PlaySound.cpp
# End Source File
# Begin Source File

SOURCE=.\PostView.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadUSBL.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadUSBLBOX.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordSound.cpp
# End Source File
# Begin Source File

SOURCE=.\rs_erasure.c
# End Source File
# Begin Source File

SOURCE=.\rs_erasure.h
# End Source File
# Begin Source File

SOURCE=.\ShowPic.cpp
# End Source File
# Begin Source File

SOURCE=.\StaticTime.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\TabLog.cpp
# End Source File
# Begin Source File

SOURCE=.\TurboCode.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoContainer.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\VideoWindow.cpp
# End Source File
# Begin Source File

SOURCE=.\WaveView.cpp
# End Source File
# Begin Source File

SOURCE=.\WordDialog.cpp
# End Source File
# Begin Source File

SOURCE=.\WriteSoundFile.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ACS.h
# End Source File
# Begin Source File

SOURCE=.\ACSDlg.h
# End Source File
# Begin Source File

SOURCE=.\AdcpPage.h
# End Source File
# Begin Source File

SOURCE=.\ADSamplePage.h
# End Source File
# Begin Source File

SOURCE=.\AdvancedSet.h
# End Source File
# Begin Source File

SOURCE=.\BasicSet.h
# End Source File
# Begin Source File

SOURCE=.\Check.h
# End Source File
# Begin Source File

SOURCE=.\CheckUSBL.h
# End Source File
# Begin Source File

SOURCE=.\ComParam.h
# End Source File
# Begin Source File

SOURCE=.\CycleMem.h
# End Source File
# Begin Source File

SOURCE=.\data_define.h
# End Source File
# Begin Source File

SOURCE=.\DataEncode.h
# End Source File
# Begin Source File

SOURCE=.\DataView.h
# End Source File
# Begin Source File

SOURCE=.\DIB.h
# End Source File
# Begin Source File

SOURCE=.\DispPanel.h
# End Source File
# Begin Source File

SOURCE=.\FFT.h
# End Source File
# Begin Source File

SOURCE=.\FileDataN.h
# End Source File
# Begin Source File

SOURCE=.\font.h
# End Source File
# Begin Source File

SOURCE=.\HYUtil.h
# End Source File
# Begin Source File

SOURCE=.\ImageSelect.h
# End Source File
# Begin Source File

SOURCE=.\ImageShow.h
# End Source File
# Begin Source File

SOURCE=.\LogView.h
# End Source File
# Begin Source File

SOURCE=.\lpt_lib.h
# End Source File
# Begin Source File

SOURCE=.\MediaChannel.h
# End Source File
# Begin Source File

SOURCE=.\Melp_sub.h
# End Source File
# Begin Source File

SOURCE=.\Morse.h
# End Source File
# Begin Source File

SOURCE=.\MPSKTurbo.h
# End Source File
# Begin Source File

SOURCE=.\MyMemDC.h
# End Source File
# Begin Source File

SOURCE=.\NetSocket.h
# End Source File
# Begin Source File

SOURCE=.\ntgraph.h
# End Source File
# Begin Source File

SOURCE=.\OptionSet.h
# End Source File
# Begin Source File

SOURCE=.\picture.h
# End Source File
# Begin Source File

SOURCE=.\PictureView.h
# End Source File
# Begin Source File

SOURCE=.\PlayMMSound.h
# End Source File
# Begin Source File

SOURCE=.\PlaySound.h
# End Source File
# Begin Source File

SOURCE=.\PostView.h
# End Source File
# Begin Source File

SOURCE=.\ReadUSBL.h
# End Source File
# Begin Source File

SOURCE=.\ReadUSBLBOX.h
# End Source File
# Begin Source File

SOURCE=.\RecordSound.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ShowPic.h
# End Source File
# Begin Source File

SOURCE=.\StaticTime.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\TabLog.h
# End Source File
# Begin Source File

SOURCE=.\TurboCode.h
# End Source File
# Begin Source File

SOURCE=.\VideoContainer.h
# End Source File
# Begin Source File

SOURCE=.\VideoSelect.h
# End Source File
# Begin Source File

SOURCE=.\VideoWindow.h
# End Source File
# Begin Source File

SOURCE=.\WaveView.h
# End Source File
# Begin Source File

SOURCE=.\WordDialog.h
# End Source File
# Begin Source File

SOURCE=.\WriteSoundFile.h
# End Source File
# Begin Source File

SOURCE=.\CxImage\header\ximage.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ACS.ico
# End Source File
# Begin Source File

SOURCE=.\res\ACS.rc2
# End Source File
# Begin Source File

SOURCE=.\res\bitmap1.bmp
# End Source File
# Begin Source File

SOURCE=".\res\Champicons Icon 19.ico"
# End Source File
# Begin Source File

SOURCE=.\res\chart.bmp
# End Source File
# Begin Source File

SOURCE=.\res\expand.bmp
# End Source File
# Begin Source File

SOURCE=.\res\get.bmp
# End Source File
# Begin Source File

SOURCE=.\res\IACAS.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ico00001.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\res\icon4.ico
# End Source File
# Begin Source File

SOURCE=.\res\LedOff.ico
# End Source File
# Begin Source File

SOURCE=.\res\LedOn.ico
# End Source File
# Begin Source File

SOURCE=.\res\link.bmp
# End Source File
# Begin Source File

SOURCE=.\res\linkdown.bmp
# End Source File
# Begin Source File

SOURCE=.\res\Off.bmp
# End Source File
# Begin Source File

SOURCE=.\res\On.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pause.bmp
# End Source File
# Begin Source File

SOURCE=.\res\play.bmp
# End Source File
# Begin Source File

SOURCE=.\res\POINT01.ICO
# End Source File
# Begin Source File

SOURCE=.\res\post.bmp
# End Source File
# Begin Source File

SOURCE=.\res\skinmagi.bin
# End Source File
# Begin Source File

SOURCE=.\res\workon.bmp
# End Source File
# Begin Source File

SOURCE=.\res\zoomin.bmp
# End Source File
# Begin Source File

SOURCE=.\res\zoomout.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\res\Devior.smf
# End Source File
# Begin Source File

SOURCE=.\res\xpsteel.smf
# End Source File
# Begin Source File

SOURCE=.\res\XpStyle
# End Source File
# End Target
# End Project
# Section ACS : {7BF80981-BF32-101A-8BBB-00AA00300CAB}
# 	2:5:Class:CPicture
# 	2:10:HeaderFile:picture.h
# 	2:8:ImplFile:picture.cpp
# End Section
# Section ACS : {C9FE01C2-2746-479B-96AB-E0BE9931B018}
# 	2:21:DefaultSinkHeaderFile:ntgraph.h
# 	2:16:DefaultSinkClass:CNTGraph
# End Section
# Section ACS : {BEF6E003-A874-101A-8BBA-00AA00300CAB}
# 	2:5:Class:COleFont
# 	2:10:HeaderFile:font.h
# 	2:8:ImplFile:font.cpp
# End Section
# Section ACS : {AC90A107-78E8-4ED8-995A-3AE8BB3044A7}
# 	2:5:Class:CNTGraph
# 	2:10:HeaderFile:ntgraph.h
# 	2:8:ImplFile:ntgraph.cpp
# End Section
