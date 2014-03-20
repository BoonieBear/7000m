// ReadUSBLBOX.h: interface for the CReadUSBLBOX class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_READUSBLBOX_H__BA159E65_1610_465A_BCC7_A38A56618E0C__INCLUDED_)
#define AFX_READUSBLBOX_H__BA159E65_1610_465A_BCC7_A38A56618E0C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ReadUSBL.h"

class CReadUSBLBOX : public CReadUSBL  
{
public:
	CString GetData(CString data ,int nindex,char split);
	void GetShipStance(CString Data,unsigned short &head,short &pitch,short &roll );
	void GetRelativeData(CString Data, short &x, short &y,unsigned short &z);	//Get Relative x and y coordinates
	void GetThePost(CString Data,float &Lat,float &Long);	//Get the Geo Post of ship or auv
	short GetAUVDepth(CString Data);									//
	int IsShipData(CString Data);						//0:AUV`s infor 1:ship`s infor
	int CheckDataType(CString Data);					//1:PTSAG 2:PTSAX 
	void GetTime(CString data, FILETIME &fTime);			//get time from PTSAG infor
	CReadUSBLBOX();
	virtual ~CReadUSBLBOX();

};

#endif // !defined(AFX_READUSBLBOX_H__BA159E65_1610_465A_BCC7_A38A56618E0C__INCLUDED_)
