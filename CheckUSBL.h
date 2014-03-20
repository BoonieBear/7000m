// CheckUSBL.h: interface for the CCheckUSBL class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CHECKUSBL_H__D51BA805_3690_4FA3_A631_EE0AAF88C46A__INCLUDED_)
#define AFX_CHECKUSBL_H__D51BA805_3690_4FA3_A631_EE0AAF88C46A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Check.h"
class CCheckUSBL: public CCheck
{
public:
	BOOL IsCorrect();
	CCheckUSBL();
	virtual ~CCheckUSBL();


};

#endif // !defined(AFX_CHECKUSBL_H__D51BA805_3690_4FA3_A631_EE0AAF88C46A__INCLUDED_)
