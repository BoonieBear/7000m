// Morse.cpp: implementation of the CMorse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ACS.h"
#include "Morse.h"
#include "ACSDlg.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMorse::CMorse()
{
	MorseMap.SetAt('A', "10003000000");
	MorseMap.SetAt('B', "30001000100010000000");
	MorseMap.SetAt('C', "3000100030001000000");
	MorseMap.SetAt('D', "300010001000000");
	MorseMap.SetAt('E', "1000000");
	MorseMap.SetAt('F', "1000100030001000000");
	MorseMap.SetAt('G', "300030001000000");
	MorseMap.SetAt('H', "1000100010001000000");
	MorseMap.SetAt('I', "10001000000");
	MorseMap.SetAt('J', "1000300030003000000");
	MorseMap.SetAt('K', "300010003000000");
	MorseMap.SetAt('L', "1000300010001000000");
	MorseMap.SetAt('M', "30003000000");
	MorseMap.SetAt('N', "30001000000");
	MorseMap.SetAt('O', "300030003000000");
	MorseMap.SetAt('P', "1000300030001000000");
	MorseMap.SetAt('Q', "3000300010003000000");
	MorseMap.SetAt('R', "100030001000000");
	MorseMap.SetAt('S', "100010001000000");
	MorseMap.SetAt('T', "3000000");
	MorseMap.SetAt('U', "100010003000000");
	MorseMap.SetAt('V', "1000100010003000000");
	MorseMap.SetAt('W', "100030003000000");
	MorseMap.SetAt('X', "3000100010003000000");
	MorseMap.SetAt('Y', "3000100030003000000");	
	MorseMap.SetAt('Z', "3000300010001000000");

	MorseMap.SetAt('0', "30003000300030003000000");
	MorseMap.SetAt('1', "10003000300030003000000");
	MorseMap.SetAt('2', "10001000300030003000000");
	MorseMap.SetAt('3', "10001000100030003000000");
	MorseMap.SetAt('4', "10001000100010003000000");
	MorseMap.SetAt('5', "10001000100010001000000");
	MorseMap.SetAt('6', "30001000100010001000000");
	MorseMap.SetAt('7', "30003000100010001000000");
	MorseMap.SetAt('8', "30003000300010001000000");
	MorseMap.SetAt('9', "30003000300030001000000");

	MorseMap.SetAt('.', "100030001000300010003000000");
	MorseMap.SetAt(':', "300030003000100010001000000");
	MorseMap.SetAt(',', "300030001000100030003000000");
	MorseMap.SetAt(';', "300010003000100030001000000");
	MorseMap.SetAt('?', "100010003000300010001000000");
	MorseMap.SetAt('=', "30001000100010003000000");
	MorseMap.SetAt('\'', "100030003000300030001000000");
	MorseMap.SetAt('/', "30001000100030001000000");
	MorseMap.SetAt('!', "300010003000100030003000000");
	MorseMap.SetAt('-', "300010001000100010003000000");
	MorseMap.SetAt('_', "100010003000300010003000000");
	MorseMap.SetAt('\"', "100030001000100030001000000");
	MorseMap.SetAt('(', "30001000300030001000000");
	MorseMap.SetAt(')', "300010003000300010003000000");
	MorseMap.SetAt('$', "1000100010003000100010003000000");
	MorseMap.SetAt('&', "1000100010001000000");
	MorseMap.SetAt('@', "100030003000100030001000000");
	MorseMap.SetAt(' ',"000");
}

CMorse::~CMorse()
{
	MorseMap.RemoveAll();
}

void CMorse::ParseWord(char p, short *pword,int* sum)
{	
//	MorseMap.InitHashTable(72);
	if(('A'<=p&&p<='Z')||('a'<=p&&p<='z'))
	{
		CharUpper(&p);
	}
	
	CString Sequence;
	int index=0;
	if(!MorseMap.Lookup(p,Sequence))
	{
		return;
	}
	for(int i=0;i<Sequence.GetLength();i++)
	{
		switch(Sequence[i])
		{
			case '0':
				memset(pword+index,0,DOT*2);
				index+=DOT;
				break;
			case '1':
				GenSinWave(pword+index,FREQ,DOT);
				index+=DOT;
				break;
			case '3':
				GenSinWave(pword+index,FREQ,3*DOT);
				index+=3*DOT;
				break;
			default:
				break;
		}		
	}
	*sum = index;

}
