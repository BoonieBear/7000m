// ReadUSBLBOX.cpp: implementation of the CReadUSBLBOX class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ACS.h"
#include "ReadUSBLBOX.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CReadUSBLBOX::CReadUSBLBOX()
{

}

CReadUSBLBOX::~CReadUSBLBOX()
{

}

CString CReadUSBLBOX::GetData(CString data,int nindex, char split)//得到用特殊字符分隔开的第nindex域的数据
{
	CString str = data;
	CString outstr;
	int nCount = 0;
	for (int i =0;i<nindex;i++)
	{
		nCount = str.Find(split);
		str = str.Mid(nCount+1);
	}
	nCount = str.Find(split);
	outstr = str.Left(nCount);
	return outstr;
}
void CReadUSBLBOX::GetTime(CString data, FILETIME &fTime)
{
	SYSTEMTIME sTime;
	GetSystemTime(&sTime);
	CTime ct = CTime::GetCurrentTime();
	sTime.wHour= ct.GetHour();
	sTime.wMinute= ct.GetMinute();
	sTime.wSecond= ct.GetSecond();
	SystemTimeToFileTime(&sTime,&fTime);

}

int CReadUSBLBOX::CheckDataType(CString Data)
{
	if (GetData(Data,0,',')=="$PTSAG")//PTSAG
	{
		return 1;
	}
	else if (GetData(Data,0,',')=="$PTSAX")
	{
		return 2;
	}
	else if (GetData(Data,0,',')=="PTSAZ")
	{
		return 3;
	}
	else
		return 0;
}

int CReadUSBLBOX::IsShipData(CString Data)
{
	if(GetData(Data,6,',')=="0")
		return 1;
	else
		return 0;

}

short CReadUSBLBOX::GetAUVDepth(CString Data)
{

	short depth = short(atof(GetData(Data,12,','))*65536.0/8000);
	if (depth > 10000*65536/8000)
	{
		return 0;
	}
	
	return depth;
}

void CReadUSBLBOX::GetThePost(CString Data,float &Lat, float &Long)
{
		CString str;

		if (GetData(Data,8,',')=="N")//纬度
		{
			str = GetData(Data,7,',');
			Lat=atof(str.Mid(0,2))*60 + atof(str.Mid(2,8));
			if( Lat > 90.1*60)
			{
				Lat =0 ;
			}
		} 
		else
		{
			str = GetData(Data,7,',');
			Lat =atof(str.Mid(0,2))*60 - atof(str.Mid(2,8));
			if( Lat < -90.1*60)
			{
				Lat =0 ;
			}
		}
		if (GetData(Data,10,',')=="E")//经度
		{
			str = GetData(Data,9,',');
			Long = atof(str.Mid(0,3))*60 + atof(str.Mid(3,8));
			if(Long > 180.1*60)
			{
				Long = 0;
			}
		} 
		else
		{
			str = GetData(Data,9,',');
			Long = 0-atof(str.Mid(0,3))*60 - atof(str.Mid(3,8));
			if( Long < -180.1*60)
			{
				Long = 0;
			}
		}


}

void CReadUSBLBOX::GetRelativeData(CString Data,  short &x, short &y, unsigned short &z)
{

		y =short(atof(GetData(Data,7,','))*32768.0/15000);
		x =short(atof(GetData(Data,8,','))*32768.0/15000);
		z =short(atof(GetData(Data,10,','))*65536.0/8000);

}

void CReadUSBLBOX::GetShipStance(CString Data, unsigned short &head, short &pitch, short &roll)
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
