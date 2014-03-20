// NetSocket.h: interface for the CNetSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETSOCKET_H__2E6F11E1_2742_4228_AB53_D6582BBD42CC__INCLUDED_)
#define AFX_NETSOCKET_H__2E6F11E1_2742_4228_AB53_D6582BBD42CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <winsock2.h> 

#include "data_define.h"//定义各种常量：消息号等


class CNetSocket  
{
public:
	CNetSocket();
	virtual ~CNetSocket();
	void Init(int port,int wMsg);

public:
	int GetLocalIPAddress();
	void Close();
	SOCKET CreateServer();//将套接字设置为TCP服务器
	SOCKET CreateUDP();//将套接字设置为UDP数据接收端

	int BroadSend(char *sMsg,int nMsgLen);//数据广播
	SOCKET CreateUDPbcast();//将套接字设置为UDP数据广播端
	SOCKET CreateClient();//将套接字设置为TCP客户端

	SOCKET m_sSocket;//套接字
	int m_nPort;//端口号
	char m_szAddr[256];//IP地址
	BOOL m_bSave;//接收到的数据是否存文件
	int m_nWMsg;//消息号
	BOOL m_bConnect;//该m_sSocket是否有效

	char m_szLen[4];	//存放包的长度
	DWORD	m_nTotalLen;//总的数据长度
	DWORD	m_nRecvLen;//收到的数据长度
	NET_PACKET m_strNetpacket;//存放接收到的网络数据包

	//CFileData m_sFile;//文件

};

#endif // !defined(AFX_NETSOCKET_H__2E6F11E1_2742_4228_AB53_D6582BBD42CC__INCLUDED_)
