// NetSocket.h: interface for the CNetSocket class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NETSOCKET_H__2E6F11E1_2742_4228_AB53_D6582BBD42CC__INCLUDED_)
#define AFX_NETSOCKET_H__2E6F11E1_2742_4228_AB53_D6582BBD42CC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <winsock2.h> 

#include "data_define.h"//������ֳ�������Ϣ�ŵ�


class CNetSocket  
{
public:
	CNetSocket();
	virtual ~CNetSocket();
	void Init(int port,int wMsg);

public:
	int GetLocalIPAddress();
	void Close();
	SOCKET CreateServer();//���׽�������ΪTCP������
	SOCKET CreateUDP();//���׽�������ΪUDP���ݽ��ն�

	int BroadSend(char *sMsg,int nMsgLen);//���ݹ㲥
	SOCKET CreateUDPbcast();//���׽�������ΪUDP���ݹ㲥��
	SOCKET CreateClient();//���׽�������ΪTCP�ͻ���

	SOCKET m_sSocket;//�׽���
	int m_nPort;//�˿ں�
	char m_szAddr[256];//IP��ַ
	BOOL m_bSave;//���յ��������Ƿ���ļ�
	int m_nWMsg;//��Ϣ��
	BOOL m_bConnect;//��m_sSocket�Ƿ���Ч

	char m_szLen[4];	//��Ű��ĳ���
	DWORD	m_nTotalLen;//�ܵ����ݳ���
	DWORD	m_nRecvLen;//�յ������ݳ���
	NET_PACKET m_strNetpacket;//��Ž��յ����������ݰ�

	//CFileData m_sFile;//�ļ�

};

#endif // !defined(AFX_NETSOCKET_H__2E6F11E1_2742_4228_AB53_D6582BBD42CC__INCLUDED_)
