#ifndef _TURBOCODE_H_
#define _TURBOCODE_H_

//#include "Afxtempl.h" 
#define LLL 1936    /*   ��֯����   */

void convenc(int *a,int *b);//��������ɺ�����
void Rand_Interl(int *d);//��֯������
void Rand_Deinterl(int *e);//�⽻֯������
void OUT_interleave(int *w);//�ⲿ��֯��

void convenc8(int *a,int *b);//�����������������ɶ���ʽΪ[23��35��33]��
void Rand_Interl8(int *d);//α�����֯����
void Rand_Deinterl8(int *e);//�⽻֯����
void OUT_interleave8(int *g);//�⽻֯��


#endif