// NetSocket.cpp: implementation of the CNetSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NetSocket.h"
#include "ACSDlg.h"//包含窗口句柄全局变量

//#include <winsock2.h>
#pragma comment(lib,"ws2_32.lib")
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CNetSocket::CNetSocket()
{

}

CNetSocket::~CNetSocket()
{
	/*if(m_sRecvBuff!=NULL){
		free(m_sRecvBuff);
		m_sRecvBuff=NULL;
	}*/
}
//**************网络端口初始化****************//
void CNetSocket::Init(int port,int wMsg)
{
	m_nPort=port;
	m_nWMsg=wMsg;
	m_szAddr[0]=0;
	m_bConnect=FALSE;
	m_bSave=TRUE;
	
	//m_sRecvBuff=NULL;
	m_nTotalLen=0;
	m_nRecvLen=0;
}

//***********建立一个TCP服务器端***************//
SOCKET CNetSocket::CreateServer()
{
WSADATA wsd;
SOCKET s;
struct sockaddr_in tcpaddr;
struct hostent *host=NULL;

//1.装入winsock2.2库
if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
{
	AfxMessageBox("不能调用winsock类库");
	return	SOCKET_ERROR;
}

//2.以TCP协议创建一个套接字（各个参数固定）
s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

if(s==SOCKET_ERROR)
	return SOCKET_ERROR;
		


//3.设置异步I/O模型
WSAAsyncSelect(s,hWnd,m_nWMsg,FD_ACCEPT|FD_CLOSE|FD_READ|FD_WRITE);

//4.IP地址指定
tcpaddr.sin_family=AF_INET;
tcpaddr.sin_port=htons(m_nPort);
if(m_szAddr=="")//允许服务器监听主机上每个网络接口上的客户机
	tcpaddr.sin_addr.s_addr=htonl(INADDR_ANY);
else
{
	tcpaddr.sin_addr.s_addr=inet_addr(m_szAddr);
//
//如果给定的服务器地址不是以IP地址的形式给出，而是主机名则解析它
//
	if(tcpaddr.sin_addr.s_addr==INADDR_NONE)
	{
		host=gethostbyname(m_szAddr);
		if(host==NULL)
		{
			AfxMessageBox("不能解析的主机名");
			return	SOCKET_ERROR;
		}
		CopyMemory(&tcpaddr.sin_addr,host->h_addr_list[0],host->h_length);
	}
}

//5.将IP地址与套接字绑定
if(bind(s,(SOCKADDR *)&tcpaddr,sizeof(tcpaddr))==SOCKET_ERROR)
	return SOCKET_ERROR;

//6.将该套接字设为监听模式
if(listen(s,5))
	return SOCKET_ERROR;

m_bConnect=TRUE;

return s;
}

//*********************建立一个TCP客户端************************//
SOCKET CNetSocket::CreateClient()
{
WSADATA wsd;
SOCKET s;
struct sockaddr_in server;
struct hostent *host=NULL;


//1.装入winsock2.2库
if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
{
	AfxMessageBox("不能调用winsock类库");
	return SOCKET_ERROR;
}

//2.以TCP协议创建一个套接字（各个参数固定）
s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(s==SOCKET_ERROR)
	return SOCKET_ERROR;
		

//3.设置异步I/O模型
if(WSAAsyncSelect(s,hWnd,m_nWMsg,FD_READ|FD_WRITE|FD_CONNECT|FD_CLOSE)==SOCKET_ERROR)
	return SOCKET_ERROR;

//4.IP地址指定
server.sin_family=AF_INET;
server.sin_port=htons(m_nPort);
server.sin_addr.s_addr=inet_addr(m_szAddr);//szAddr为服务器的IP地址“192.168.2.15”
//
//如果给定的服务器地址不是以IP地址的形式给出，而是主机名则解析它
//
if(server.sin_addr.s_addr==INADDR_NONE)
{
	host=gethostbyname(m_szAddr);
	if(host==NULL)
	{
		AfxMessageBox("不能解析的主机名\n请给出正确的服务器名");
		return SOCKET_ERROR;
	}
	CopyMemory(&server.sin_addr,host->h_addr_list[0],host->h_length);
}
//5.连接主机
	connect(s,(struct sockaddr *)&server,sizeof(server));
/*	return SOCKET_ERROR;*/

m_bConnect=TRUE;		

return s;
}

//**************************建立UDP BROADCAST*************************//
SOCKET CNetSocket::CreateUDPbcast()
{
WSADATA wsd;
SOCKET s;
BOOL bBroadcast;

//1.装入winsock2.2库
if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
{
	AfxMessageBox("不能调用winsock类库");
	return SOCKET_ERROR;
}

//2.以UDP协议创建一个套接字（各个参数固定）
s=socket(AF_INET,SOCK_DGRAM,0);
if(s==SOCKET_ERROR)
	return SOCKET_ERROR;


//3.设置套接字选项，将UDP设为广播形式
bBroadcast=TRUE;
if(setsockopt(s,SOL_SOCKET,SO_BROADCAST,(char *)&bBroadcast,sizeof(BOOL))==SOCKET_ERROR)
	return SOCKET_ERROR;

m_bConnect=TRUE;

return s;
}
//****************************UDP数据广播***************************//
int CNetSocket::BroadSend(char *sMsg,int nMsgLen)
{
		int ret;
		SOCKADDR_IN bcast;
		

		//IP地址指定,设为广播地址“255.255.255.255”
		bcast.sin_family=AF_INET;
		//bcast.sin_addr.s_addr=inet_addr(INADDR_BROADCAST1);
		bcast.sin_addr.s_addr=htonl(INADDR_BROADCAST);
		bcast.sin_port=htons(m_nPort);

		ret=sendto(m_sSocket,sMsg,nMsgLen,0,(SOCKADDR *)&bcast,sizeof(bcast));
		return ret;

}
//***************************建立UDP********************************// 
SOCKET CNetSocket::CreateUDP()
{
WSADATA wsd;
SOCKET s;

SOCKADDR_IN bcast;

//1.装入winsock2.2库
if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
{
	AfxMessageBox("不能调用winsock类库");
	return SOCKET_ERROR;
}

//2.以UDP协议创建一个套接字（各个参数固定）
s=socket(AF_INET,SOCK_DGRAM,0);
if(s==SOCKET_ERROR)
	return SOCKET_ERROR;

//3.IP地址指定本地接口
//int dwSize=sizeof(bcast);
//getsockname(s,(SOCKADDR *)&bcast,&dwSize);
bcast.sin_family=AF_INET;
//bcast.sin_addr.s_addr=inet_addr(m_szAddr);
bcast.sin_addr.s_addr=htonl(INADDR_ANY);
bcast.sin_port=htons(m_nPort);

int timeout=1000000;
setsockopt(s,SOL_SOCKET,SO_BROADCAST,(char *)&timeout,sizeof(timeout));//ps广播模式

//5.将IP地址与套接字绑定
if(bind(s,(SOCKADDR *)&bcast,sizeof(bcast))==SOCKET_ERROR)
	return SOCKET_ERROR;

//4.设置异步I/O模型
if(WSAAsyncSelect(s,hWnd,m_nWMsg,FD_READ|FD_WRITE)==SOCKET_ERROR)
	return SOCKET_ERROR;

m_bConnect=TRUE;

return s;
}



void CNetSocket::Close()
{
	if(!m_bConnect)
		return;
	closesocket(m_sSocket);

	m_nTotalLen=0;
	m_nRecvLen=0;
	
	m_bConnect=FALSE;
}

int CNetSocket::GetLocalIPAddress()
{
	WSADATA wsd;
	//1.装入winsock2.2库
	if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
	{
		AfxMessageBox("不能调用winsock类库");
		return -1;
	}
	//2.获取主机名
	char szHostName[256];
	int  nRetCode;

	nRetCode = gethostname(szHostName, sizeof(szHostName));

	if (nRetCode != 0) {
		// An error has occurred
		return WSAGetLastError();
	}
	//3.获取IP地址
	struct hostent FAR *lpHostEnt = gethostbyname (szHostName);

	if (lpHostEnt == NULL) {
		// An error occurred. 
		m_szAddr[0]=0;
		return WSAGetLastError();
	}

	LPSTR lpAddr = lpHostEnt->h_addr_list[0];
	if (lpAddr) {
		struct in_addr  inAddr;
		memmove (&inAddr, lpAddr, 4);
		//m_szAddr = inet_ntoa (inAddr);
		strcpy(m_szAddr,inet_ntoa (inAddr));
		if (strlen(m_szAddr)==0){
			m_szAddr[0]=0;
			return -1;
		}
	}		
	
	return 0;
}
