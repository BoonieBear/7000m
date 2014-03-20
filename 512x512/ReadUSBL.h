// ReadUSBL.h: interface for the CReadUSBL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READUSBL_H__635BB422_7663_4D78_A65F_B27BE6628C4B__INCLUDED_)
#define AFX_READUSBL_H__635BB422_7663_4D78_A65F_B27BE6628C4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "CheckUSBL.h"

class CReadUSBL  
{
public:
	void GetShipStance(CString Data,unsigned short &head,short &pitch,short &roll );
	void GetRelativeData(CString Data, short &x, short &y,unsigned short &z);	//Get Relative x and y coordinates
	void GetThePost(CString Data,float &Lat,float &Long);	//Get the Geo Post of ship or auv
	short GetAUVDepth(CString Data);									//
	int IsShipData(CString Data);						//0:AUV`s infor 1:ship`s infor
	int CheckDataType(CString Data);					//1:PTSAG 2:PTSAX 3:PTSAZ 0:OTHER
	void GetTime(CString data, FILETIME &fTime);			//get time from PTSAG infor
	CReadUSBL();
	virtual ~CReadUSBL();
	CCheckUSBL USBLCheck;	//check the usbl`s checksum
	CCheck check;

};

#endif // !defined(AFX_READUSBL_H__635BB422_7663_4D78_A65F_B27BE6628C4B__INCLUDED_)
