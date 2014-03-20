// ReadUSBL.cpp: implementation of the CReadUSBL class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ACS.h"
#include "ReadUSBL.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadUSBL::CReadUSBL()
{

}

CReadUSBL::~CReadUSBL()
{

}

void CReadUSBL::GetTime(CString data, FILETIME &fTime)
{
	SYSTEMTIME sTime;
	GetSystemTime(&sTime);
	CTime ct = CTime::GetCurrentTime();
	sTime.wHour= ct.GetHour();
	sTime.wMinute= ct.GetMinute();
	sTime.wSecond= ct.GetSecond();
	sTime.wMilliseconds= atoi(data.Mid(21,3));
	SystemTimeToFileTime(&sTime,&fTime);

}

int CReadUSBL::CheckDataType(CString Data)
{
	if (Data.Mid(1,5)=="PTSAG")//PTSAG
	{
		return 1;
	}
	else if (Data.Mid(1,5)=="PTSAX")
	{
		return 2;
	}
	else if (Data.Mid(1,5)=="PTSAZ")
	{
		return 3;
	}
	else
		return 0;
}

int CReadUSBL::IsShipData(CString Data)
{
	if(Data.Mid(36,2)=="00")
		return 1;
	else
		return 0;

}

short CReadUSBL::GetAUVDepth(CString Data)
{

	short depth = short(atof(Data.Mid(64,4))*65536.0/8000);
	if (depth > 10000*65536/8000)
	{
		return 0;
	}
	
	return depth;
}

void CReadUSBL::GetThePost(CString Data,float &Lat, float &Long)
{


		if (Data.Mid(48,1)=="N")//纬度
		{
			Lat=atof(Data.Mid(39,2))*60 + atof(Data.Mid(41,6));
			if( Lat > 90.1*60)
			{
				Lat =0 ;
			}
		} 
		else
		{
			Lat =atof(Data.Mid(39,2))*60 - atof(Data.Mid(41,6));
			if( Lat < -90.1*60)
			{
				Lat =0 ;
			}
		}
		if (Data.Mid(60,1)=="E")//经度
		{
			Long = atof(Data.Mid(50,3))*60 + atof(Data.Mid(53,6));
			if(Long > 180.1*60)
			{
				Long = 0;
			}
		} 
		else
		{
			Long = 0-atof(Data.Mid(50,3))*60 - atof(Data.Mid(53,6));
			if( Long < -180.1*60)
			{
				Long = 0;
			}
		}


}

void CReadUSBL::GetRelativeData(CString Data,  short &x, short &y, unsigned short &z)
{

		x =short(atof(Data.Mid(39,5))*32768.0/15000);
		y =short(atof(Data.Mid(45,5))*32768.0/15000);
		z =short(atof(Data.Mid(53,4))*65536.0/8000);

}

void CReadUSBL::GetShipStance(CString Data, unsigned short &head, short &pitch, short &roll)
{
	char *p;
	head =(short)(atof(Data.Mid(45,5))*65536.0/(2*PI));//弧度->角度
	p = strchr(Data,'R');
	p = strchr(p,',');
	++p;
	p = strchr(p,',');
	pitch=(short)(atof(++p)*32768.0/PI);
	p= strchr(p,',');
	roll =(short)(atof(++p)*32768.0/PI);
}
