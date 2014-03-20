// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#include <memory.h>
#include <string.h>

//����һ����ģ�壺������һ��ѭ�����������仺������С�����Ϳ�������ָ��
//TΪ����������������ͣ����磺int float BYTE��,Ҳ�������û��Զ�������͡�
//nΪ�������Ĵ�С
//sizeΪT��ռ���ֽڣ�byte����������intΪ4��charΪ1��floatΪ4��


template <class T,int n,int size> class CCycleMem
{
private:
		//T Buffer[n];//������
		int iSize;//T���ֽ���
		int iWriteOffsetPos;//ͷָ���ƫ��λ�ã���һ��Ҫд������ʼλ�á�ȡֵ��Χ[0,n-1]
		int iReadOffsetPos;//βָ���ƫ��λ�ã���ǰ�ɶ�������ʼλ�á�ȡֵ��Χ[0,n-1]
		int iTotalLen;//�������ܳ���iTotalLen��n
		int iDataLen;//�������е����ݳ���
		int iEmptyLen;//�������Ŀ��г���iEmptyLen��iDataLen��iTotalLen
		
public:
		T Buffer[n];// ����ʹ��

public:
		CCycleMem() ;
		CCycleMem(T InitValue);

		~CCycleMem(){};

		void Reset();//ͷβָ����㣬�����������
		void Empty();//βָ���Ƶ�ͷָ�룬�����������
		bool isEmpty();//�������Ƿ�Ϊ�գ���Ϊ�գ���Ϊ�ǿ�
		bool isFull();//�������Ƿ�����

		int GetDataLen();//��ȡ���ݳ���
		int GetEmptyLen();//��ȡ���г���
		int GetTotalLen();//�������ܳ�

		int WriteData(T *scr,int count);//�򻺳�����д������
		int ReadData(T *dest,int count);//�ӻ������ж�������
};


//////////////////////////////////////////////////////////////////////////////////////
/*������������������������������������������������������������������������������������
   ����һ��ѭ������������ʱ������ָ��ģ�������ֵ��
   ����:CCycleMem<int,100��4> IntCycleMem;//IntCycleMemΪһ�������100��������ѭ��������
   ���߶�̬���ɣ�CCycleMem<int,100,4> * IntCycleMem;
				 IntCycleMem��new CCycleMem<int,100,4>;
				 ....
				 delete IntCycleMem;//�м�ʹ����Ϻ��ͷŸ�ָ��
��������������������������������������������������������������������������������������*/

/*��������������������-------��Ա�������壭������������������������������������������*/

//���캯��
template <class T,int n,int size> 
	 CCycleMem<T,n,size>::CCycleMem()
{
	//��ͷָ���βָ���ƫ��λ����Ϊ0
	iReadOffsetPos=0;
	iWriteOffsetPos=0;

	
	iTotalLen=n;//�û������ܳ�
	iSize=size;

	iDataLen=0;//���ݳ���Ϊ0
	iEmptyLen=iTotalLen;//���г���Ϊ�ܳ�

	//ÿһλ���ݵ���0
	memset(Buffer,0,iTotalLen*iSize);
}

//���캯��,������������ֵ
template <class T,int n,int size>
	 CCycleMem<T,n,size>::CCycleMem(T InitValue)
{
	//��ͷָ���βָ���ƫ��λ����Ϊ0
	iReadOffsetPos=0;
	iWriteOffsetPos=0;
	
	iTotalLen=n;//�û������ܳ�
	iSize=size;

	iDataLen=0;//���ݳ���Ϊ0
	iEmptyLen=iTotalLen;//���г���Ϊ�ܳ�

	//ÿһλ���ݵ��ڳ�ʼֵ
	memset(Buffer,InitValue,iTotalLen*iSize);
}
////////////////////////////////////////////////////////////////
//���������
template <class T,int n,int size>
	void CCycleMem<T,n,size>::Empty()
{
	iReadOffsetPos=iWriteOffsetPos;
	iDataLen=0;//���ݳ���Ϊ0
	iEmptyLen=iTotalLen;//���г���Ϊ�ܳ�
}

//��������λ
template <class T,int n,int size>
	void CCycleMem<T,n,size>::Reset()
{
	iReadOffsetPos=iWriteOffsetPos=0;
	iDataLen=0;//���ݳ���Ϊ0
	iEmptyLen=iTotalLen;//���г���Ϊ�ܳ�
}

//�������Ƿ�Ϊ��
template <class T,int n,int size>
	bool CCycleMem<T,n,size>::isEmpty()
{
	if((iReadOffsetPos-iWriteOffsetPos)==0)
		return true;
	else
		return false;
}
//�������Ƿ���
template <class T,int n,int size>
	bool CCycleMem<T,n,size>::isFull()
{
	if((iReadOffsetPos-iWriteOffsetPos)==1||(iReadOffsetPos-iWriteOffsetPos)==-iTotalLen+1)
		return true;
	else
		return false;
	// return (iDataLen==iTotalLen);
}
///////////////////////////////////////////////////////////////////////
//��ȡ���ݳ���
template <class T,int n,int size> 
	 int CCycleMem<T,n,size>:: GetDataLen()
{
	//int iDataLen;
	iDataLen = iWriteOffsetPos-iReadOffsetPos;
	if (iDataLen<0) {
		iDataLen += iTotalLen;
	}
	return iDataLen;
}
//��ȡ���г���
template <class T,int n,int size>
	 int CCycleMem<T,n,size>:: GetEmptyLen()
{
	//int iEmptyLen;
	iEmptyLen = iReadOffsetPos - iWriteOffsetPos-1;
	if(iEmptyLen<0)		iEmptyLen += iTotalLen-1;
	
	return iEmptyLen;
}
//��ȡ�ܳ���
template <class T,int n,int size>
	 int CCycleMem<T,n,size>:: GetTotalLen()
{
	return iTotalLen;
}
///////////////////////////////////////////////////////////////////////
//�򻺳�����д�����ݣ�scrΪ����Դָ�룬countΪ���ݳ���
template <class T,int n,int size>
	 int CCycleMem<T,n,size>::WriteData(T *scr,int count)

{
//	ASSERT(scr);
	iEmptyLen = GetEmptyLen();
	if(count>iEmptyLen) return -1;//���ݳ��ȴ��ڿ��г��ȣ��򷵻ش���
	int spare=iTotalLen-iWriteOffsetPos;//ͷָ�뵽������β�ĳ���

	if(count<spare)	//������һ�ο������
	{
		memcpy(Buffer+iWriteOffsetPos,scr,count*iSize);
		iWriteOffsetPos=iWriteOffsetPos+count;//�ƶ�ͷָ��
	}
	else//���ݷ�������
	{
		int i=count-spare;
		memcpy(Buffer+iWriteOffsetPos,scr,spare*iSize);//��ͷָ���λ�ÿ�����������β
		memcpy(Buffer,scr+spare,i*iSize);//�ӻ�����ͷ��ʣ������ݿ������
		iWriteOffsetPos=i;//�ƶ�ͷָ��

	}

	return count;

}
//�ӻ������ж������ݣ�destΪ����Ŀ�ĵ�ָ�룬countΪ���ݳ���
template <class T,int n,int size>
	 int CCycleMem<T,n,size>::ReadData(T *dest,int count)
{
//	ASSERT(dest);

	//if (count>iDataLen)	return -1;
	iDataLen = GetDataLen();
	count=min(count,iDataLen);
	
	if(count==0) return -1;

	int spare=iTotalLen-iReadOffsetPos;//βָ�뵽������β�ĳ���

	if(count<spare)	//������һ�ο������
	{
		memcpy(dest,Buffer+iReadOffsetPos,count*iSize);
		iReadOffsetPos=iReadOffsetPos+count;//�ƶ�βָ��
	}
	else//���ݷ�������
	{
		int i=count-spare;
		memcpy(dest,Buffer+iReadOffsetPos,spare*iSize);//��ͷָ���λ�ÿ�����������β
		memcpy(dest+spare,Buffer,i*iSize);//�ӻ�����ͷ��ʣ������ݿ������
		iReadOffsetPos=i;//�ƶ�ͷָ��

	}

	return count;

}
