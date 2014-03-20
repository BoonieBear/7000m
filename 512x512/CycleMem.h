// Copyright (C) 1991 - 1999 Rational Software Corporation

#if defined (_MSC_VER) && (_MSC_VER >= 1000)
#pragma once
#endif

#include <memory.h>
#include <string.h>

//这是一个类模板：定义了一个循环缓冲区，其缓冲区大小和类型可以任意指定
//T为缓冲区存的数据类型，例如：int float BYTE等,也可以是用户自定义的类型。
//n为缓冲区的大小
//size为T所占的字节（byte）数：例如int为4，char为1，float为4等


template <class T,int n,int size> class CCycleMem
{
private:
		//T Buffer[n];//缓冲区
		int iSize;//T的字节数
		int iWriteOffsetPos;//头指针的偏移位置，下一个要写数的起始位置。取值范围[0,n-1]
		int iReadOffsetPos;//尾指针的偏移位置，当前可读数的起始位置。取值范围[0,n-1]
		int iTotalLen;//缓冲区总长度iTotalLen＝n
		int iDataLen;//缓冲区中的数据长度
		int iEmptyLen;//缓冲区的空闲长度iEmptyLen＋iDataLen＝iTotalLen
		
public:
		T Buffer[n];// 测试使用

public:
		CCycleMem() ;
		CCycleMem(T InitValue);

		~CCycleMem(){};

		void Reset();//头尾指针归零，将缓冲区清空
		void Empty();//尾指针移到头指针，将缓冲区清空
		bool isEmpty();//缓冲区是否为空：真为空，否为非空
		bool isFull();//缓冲区是否已满

		int GetDataLen();//获取数据长度
		int GetEmptyLen();//获取空闲长度
		int GetTotalLen();//缓存区总长

		int WriteData(T *scr,int count);//向缓冲区中写入数据
		int ReadData(T *dest,int count);//从缓冲区中读走数据
};


//////////////////////////////////////////////////////////////////////////////////////
/*－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－
   生成一个循环缓冲区对象时，必须指定模板参数的值，
   例如:CCycleMem<int,100，4> IntCycleMem;//IntCycleMem为一个最多存放100个整数的循环缓存区
   或者动态生成：CCycleMem<int,100,4> * IntCycleMem;
				 IntCycleMem＝new CCycleMem<int,100,4>;
				 ....
				 delete IntCycleMem;//切记使用完毕后释放该指针
－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－－*/

/*－－－－－－－－－－-------成员函数定义－－－－－－－－－－－－－－－－－－－－－－*/

//构造函数
template <class T,int n,int size> 
	 CCycleMem<T,n,size>::CCycleMem()
{
	//将头指针和尾指针的偏移位置置为0
	iReadOffsetPos=0;
	iWriteOffsetPos=0;

	
	iTotalLen=n;//置缓冲区总长
	iSize=size;

	iDataLen=0;//数据长度为0
	iEmptyLen=iTotalLen;//空闲长度为总长

	//每一位数据等于0
	memset(Buffer,0,iTotalLen*iSize);
}

//构造函数,给缓冲区赋初值
template <class T,int n,int size>
	 CCycleMem<T,n,size>::CCycleMem(T InitValue)
{
	//将头指针和尾指针的偏移位置置为0
	iReadOffsetPos=0;
	iWriteOffsetPos=0;
	
	iTotalLen=n;//置缓冲区总长
	iSize=size;

	iDataLen=0;//数据长度为0
	iEmptyLen=iTotalLen;//空闲长度为总长

	//每一位数据等于初始值
	memset(Buffer,InitValue,iTotalLen*iSize);
}
////////////////////////////////////////////////////////////////
//缓冲区清空
template <class T,int n,int size>
	void CCycleMem<T,n,size>::Empty()
{
	iReadOffsetPos=iWriteOffsetPos;
	iDataLen=0;//数据长度为0
	iEmptyLen=iTotalLen;//空闲长度为总长
}

//缓冲区置位
template <class T,int n,int size>
	void CCycleMem<T,n,size>::Reset()
{
	iReadOffsetPos=iWriteOffsetPos=0;
	iDataLen=0;//数据长度为0
	iEmptyLen=iTotalLen;//空闲长度为总长
}

//缓冲区是否为空
template <class T,int n,int size>
	bool CCycleMem<T,n,size>::isEmpty()
{
	if((iReadOffsetPos-iWriteOffsetPos)==0)
		return true;
	else
		return false;
}
//缓冲区是否满
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
//获取数据长度
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
//获取空闲长度
template <class T,int n,int size>
	 int CCycleMem<T,n,size>:: GetEmptyLen()
{
	//int iEmptyLen;
	iEmptyLen = iReadOffsetPos - iWriteOffsetPos-1;
	if(iEmptyLen<0)		iEmptyLen += iTotalLen-1;
	
	return iEmptyLen;
}
//获取总长度
template <class T,int n,int size>
	 int CCycleMem<T,n,size>:: GetTotalLen()
{
	return iTotalLen;
}
///////////////////////////////////////////////////////////////////////
//向缓冲区中写入数据，scr为数据源指针，count为数据长度
template <class T,int n,int size>
	 int CCycleMem<T,n,size>::WriteData(T *scr,int count)

{
//	ASSERT(scr);
	iEmptyLen = GetEmptyLen();
	if(count>iEmptyLen) return -1;//数据长度大于空闲长度，则返回错误
	int spare=iTotalLen-iWriteOffsetPos;//头指针到缓冲区尾的长度

	if(count<spare)	//数据能一次拷贝完毕
	{
		memcpy(Buffer+iWriteOffsetPos,scr,count*iSize);
		iWriteOffsetPos=iWriteOffsetPos+count;//移动头指针
	}
	else//数据分批拷贝
	{
		int i=count-spare;
		memcpy(Buffer+iWriteOffsetPos,scr,spare*iSize);//从头指针的位置拷贝到缓冲区尾
		memcpy(Buffer,scr+spare,i*iSize);//从缓冲区头将剩余的数据拷贝完毕
		iWriteOffsetPos=i;//移动头指针

	}

	return count;

}
//从缓冲区中读走数据，dest为数据目的地指针，count为数据长度
template <class T,int n,int size>
	 int CCycleMem<T,n,size>::ReadData(T *dest,int count)
{
//	ASSERT(dest);

	//if (count>iDataLen)	return -1;
	iDataLen = GetDataLen();
	count=min(count,iDataLen);
	
	if(count==0) return -1;

	int spare=iTotalLen-iReadOffsetPos;//尾指针到缓冲区尾的长度

	if(count<spare)	//数据能一次拷贝完毕
	{
		memcpy(dest,Buffer+iReadOffsetPos,count*iSize);
		iReadOffsetPos=iReadOffsetPos+count;//移动尾指针
	}
	else//数据分批拷贝
	{
		int i=count-spare;
		memcpy(dest,Buffer+iReadOffsetPos,spare*iSize);//从头指针的位置拷贝到缓冲区尾
		memcpy(dest+spare,Buffer,i*iSize);//从缓冲区头将剩余的数据拷贝完毕
		iReadOffsetPos=i;//移动头指针

	}

	return count;

}
