// NetSocket.cpp: implementation of the CNetSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "NetSocket.h"
#include "ACSDlg.h"//�������ھ��ȫ�ֱ���

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
//**************����˿ڳ�ʼ��****************//
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

//***********����һ��TCP��������***************//
SOCKET CNetSocket::CreateServer()
{
WSADATA wsd;
SOCKET s;
struct sockaddr_in tcpaddr;
struct hostent *host=NULL;

//1.װ��winsock2.2��
if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
{
	AfxMessageBox("���ܵ���winsock���");
	return	SOCKET_ERROR;
}

//2.��TCPЭ�鴴��һ���׽��֣����������̶���
s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

if(s==SOCKET_ERROR)
	return SOCKET_ERROR;
		


//3.�����첽I/Oģ��
WSAAsyncSelect(s,hWnd,m_nWMsg,FD_ACCEPT|FD_CLOSE|FD_READ|FD_WRITE);

//4.IP��ַָ��
tcpaddr.sin_family=AF_INET;
tcpaddr.sin_port=htons(m_nPort);
if(m_szAddr=="")//�������������������ÿ������ӿ��ϵĿͻ���
	tcpaddr.sin_addr.s_addr=htonl(INADDR_ANY);
else
{
	tcpaddr.sin_addr.s_addr=inet_addr(m_szAddr);
//
//��������ķ�������ַ������IP��ַ����ʽ�����������������������
//
	if(tcpaddr.sin_addr.s_addr==INADDR_NONE)
	{
		host=gethostbyname(m_szAddr);
		if(host==NULL)
		{
			AfxMessageBox("���ܽ�����������");
			return	SOCKET_ERROR;
		}
		CopyMemory(&tcpaddr.sin_addr,host->h_addr_list[0],host->h_length);
	}
}

//5.��IP��ַ���׽��ְ�
if(bind(s,(SOCKADDR *)&tcpaddr,sizeof(tcpaddr))==SOCKET_ERROR)
	return SOCKET_ERROR;

//6.�����׽�����Ϊ����ģʽ
if(listen(s,5))
	return SOCKET_ERROR;

m_bConnect=TRUE;

return s;
}

//*********************����һ��TCP�ͻ���************************//
SOCKET CNetSocket::CreateClient()
{
WSADATA wsd;
SOCKET s;
struct sockaddr_in server;
struct hostent *host=NULL;


//1.װ��winsock2.2��
if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
{
	AfxMessageBox("���ܵ���winsock���");
	return SOCKET_ERROR;
}

//2.��TCPЭ�鴴��һ���׽��֣����������̶���
s=socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
if(s==SOCKET_ERROR)
	return SOCKET_ERROR;
		

//3.�����첽I/Oģ��
if(WSAAsyncSelect(s,hWnd,m_nWMsg,FD_READ|FD_WRITE|FD_CONNECT|FD_CLOSE)==SOCKET_ERROR)
	return SOCKET_ERROR;

//4.IP��ַָ��
server.sin_family=AF_INET;
server.sin_port=htons(m_nPort);
server.sin_addr.s_addr=inet_addr(m_szAddr);//szAddrΪ��������IP��ַ��192.168.2.15��
//
//��������ķ�������ַ������IP��ַ����ʽ�����������������������
//
if(server.sin_addr.s_addr==INADDR_NONE)
{
	host=gethostbyname(m_szAddr);
	if(host==NULL)
	{
		AfxMessageBox("���ܽ�����������\n�������ȷ�ķ�������");
		return SOCKET_ERROR;
	}
	CopyMemory(&server.sin_addr,host->h_addr_list[0],host->h_length);
}
//5.��������
	connect(s,(struct sockaddr *)&server,sizeof(server));
/*	return SOCKET_ERROR;*/

m_bConnect=TRUE;		

return s;
}

//**************************����UDP BROADCAST*************************//
SOCKET CNetSocket::CreateUDPbcast()
{
WSADATA wsd;
SOCKET s;
BOOL bBroadcast;

//1.װ��winsock2.2��
if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
{
	AfxMessageBox("���ܵ���winsock���");
	return SOCKET_ERROR;
}

//2.��UDPЭ�鴴��һ���׽��֣����������̶���
s=socket(AF_INET,SOCK_DGRAM,0);
if(s==SOCKET_ERROR)
	return SOCKET_ERROR;


//3.�����׽���ѡ���UDP��Ϊ�㲥��ʽ
bBroadcast=TRUE;
if(setsockopt(s,SOL_SOCKET,SO_BROADCAST,(char *)&bBroadcast,sizeof(BOOL))==SOCKET_ERROR)
	return SOCKET_ERROR;

m_bConnect=TRUE;

return s;
}
//****************************UDP���ݹ㲥***************************//
int CNetSocket::BroadSend(char *sMsg,int nMsgLen)
{
		int ret;
		SOCKADDR_IN bcast;
		

		//IP��ַָ��,��Ϊ�㲥��ַ��255.255.255.255��
		bcast.sin_family=AF_INET;
		//bcast.sin_addr.s_addr=inet_addr(INADDR_BROADCAST1);
		bcast.sin_addr.s_addr=htonl(INADDR_BROADCAST);
		bcast.sin_port=htons(m_nPort);

		ret=sendto(m_sSocket,sMsg,nMsgLen,0,(SOCKADDR *)&bcast,sizeof(bcast));
		return ret;

}
//***************************����UDP********************************// 
SOCKET CNetSocket::CreateUDP()
{
WSADATA wsd;
SOCKET s;

SOCKADDR_IN bcast;

//1.װ��winsock2.2��
if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
{
	AfxMessageBox("���ܵ���winsock���");
	return SOCKET_ERROR;
}

//2.��UDPЭ�鴴��һ���׽��֣����������̶���
s=socket(AF_INET,SOCK_DGRAM,0);
if(s==SOCKET_ERROR)
	return SOCKET_ERROR;

//3.IP��ַָ�����ؽӿ�
//int dwSize=sizeof(bcast);
//getsockname(s,(SOCKADDR *)&bcast,&dwSize);
bcast.sin_family=AF_INET;
//bcast.sin_addr.s_addr=inet_addr(m_szAddr);
bcast.sin_addr.s_addr=htonl(INADDR_ANY);
bcast.sin_port=htons(m_nPort);

int timeout=1000000;
setsockopt(s,SOL_SOCKET,SO_BROADCAST,(char *)&timeout,sizeof(timeout));//ps�㲥ģʽ

//5.��IP��ַ���׽��ְ�
if(bind(s,(SOCKADDR *)&bcast,sizeof(bcast))==SOCKET_ERROR)
	return SOCKET_ERROR;

//4.�����첽I/Oģ��
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
	//1.װ��winsock2.2��
	if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
	{
		AfxMessageBox("���ܵ���winsock���");
		return -1;
	}
	//2.��ȡ������
	char szHostName[256];
	int  nRetCode;

	nRetCode = gethostname(szHostName, sizeof(szHostName));

	if (nRetCode != 0) {
		// An error has occurred
		return WSAGetLastError();
	}
	//3.��ȡIP��ַ
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
