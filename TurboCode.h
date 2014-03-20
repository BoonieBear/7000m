#ifndef _TURBOCODE_H_
#define _TURBOCODE_H_

//#include "Afxtempl.h" 
#define LLL 1936    /*   交织长度   */

void convenc(int *a,int *b);//卷积码生成函数。
void Rand_Interl(int *d);//交织函数。
void Rand_Deinterl(int *e);//解交织函数。
void OUT_interleave(int *w);//外部交织。

void convenc8(int *a,int *b);//卷积码编码器，其生成多项式为[23，35，33]。
void Rand_Interl8(int *d);//伪随机交织器。
void Rand_Deinterl8(int *e);//解交织器。
void OUT_interleave8(int *g);//外交织。


#endif