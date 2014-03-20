// DataEncode.h: interface for the CDataEncode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DATAENCODE_H__17541344_8BE4_4B59_A454_0BCF37B70F16__INCLUDED_)
#define AFX_DATAENCODE_H__17541344_8BE4_4B59_A454_0BCF37B70F16__INCLUDED_
// --------------------------------------------------------------

//      CRC16计算方法:使用2个256长度的校验表

// --------------------------------------------------------------
#define TRACKLEN 50

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include <math.h>
#define DEC_OUT_MAX_LEN (4320)
#define VITERBI_STATUS_NUM (64)
class CDataEncode  
{
public:
	unsigned  char CRC8_Tab(unsigned char *ucPtr, unsigned char ucLen);
	void ViterbiK7(int *R,int LengthR,int *Decision);
	int min64index(int * G);
	void BUTTERFLY(int * G_last,int O_current,int * s_all,int  * o_all,int * s_last,int * G_current );
	unsigned short CRC16(BYTE* pchMsg, int nDataLen);
	void DeInterleave(int SourceData[],int DestData[]);
	void Interleave(int SourceData[],int DestData[]);
	void One2FourConvolution(int SourceData[],int DestData[],int nlen);
	void scrambling(int SourceData[],int nlen);
	int *InterleaveMap;
	int ScamblingBit[511];//加扰bit数组
	int r0,r1,r2,r3,r4,r5,r6,r7,r8;//加扰寄存器变量
	int d0,d1,d2,d3,d4,d5;//卷积码寄存器变量
	void Init();
	int *Z;
	int *State_log;
	int Track_log[VITERBI_STATUS_NUM][TRACKLEN];
	int Track_log_D[VITERBI_STATUS_NUM][TRACKLEN];
	int nBitLength;//交织bit长度
	CDataEncode();
	virtual ~CDataEncode();

};

#endif // !defined(AFX_DATAENCODE_H__17541344_8BE4_4B59_A454_0BCF37B70F16__INCLUDED_)
