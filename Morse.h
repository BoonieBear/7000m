// Morse.h: interface for the CMorse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MORSE_H__49BD5005_BC46_4B54_9813_E86A22658CA1__INCLUDED_)
#define AFX_MORSE_H__49BD5005_BC46_4B54_9813_E86A22658CA1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "data_define.h"

class CMorse  
{
public:
	void ParseWord(char p, short  * pword,int* sum);
	CMorse();
	virtual ~CMorse();
	CMap<char,char,CString, CString> MorseMap;

};

#endif // !defined(AFX_MORSE_H__49BD5005_BC46_4B54_9813_E86A22658CA1__INCLUDED_)
