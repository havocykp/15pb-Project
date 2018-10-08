#pragma once
#include <windows.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <WinSock2.h>
#pragma comment(lib, "Ws2_32.lib")
using namespace std;

#define  _WINSOCK_DEPRECATED_NO_WARNINGS
// Э�����
#define BUFMSG 2048  // һ�ν�����Ϣ������ֽ���
#define BUFCHAT 1024//����������󳤶�
#define BUFNAME 50 //��������ֽ���
// ͷ��:ͨѶĿ��,����������¼,���졢1V1���졢ע�ᡢ��¼����Ӻ��ѡ��������ѡ��ļ����䡢�鿴�����¼

enum CHATPURPOSE{
	ANONYMOUS = 1,
	CHAT,
	ONE2ONE,
	REGISTER,
	LOGIN,
	ADDFRIEND,
	SEARCHUSER,
	FILETRANS,
	MSGRECORD,
	UPDATEUSER
};

// ��������
// �����Ľṹ��
typedef struct _CHATANONYMOUS{
	DWORD dwLen;    // �������Ƴ���
	char buf[50];   // ����
}CHATANONYMOUS;

//����Ľṹ��
typedef struct _CHATCHAT{

	DWORD dwLen;   // �������ݳ���
	char buf[1024];

}CHATCHAT;

// 1v1�ṹ��
typedef struct _CHATONE2ONE
{
	CHAR szName[50];
	CHAR szContent[1024];
}CHATONE2ONE;

// ע��ṹ��
typedef struct _CHATREGISTER
{
	CHAR szName[50];
	char szPwd[50];
}CHATREGISTER;

//��¼�ṹ�壬���������ؽ������szName��
typedef struct _CHATLOGIN
{
	CHAR szName[50];
	CHAR szPwd[50];
}CHATLOGIN;

// ��Ӻ��ѽṹ��
typedef struct _CHATADDFRIEND
{
	CHAR szName[50];   // �Լ�����
	CHAR szFrd[50];    // Ҫ�����������
}CHATADDFRIEND;

// �����û��ṹ��
typedef struct _CHATSEARCHUSER
{
	CHAR szName[50];   // Ҫ�������û���

}CHATSEARCHUSER;


//�ļ�����ṹ��
typedef struct _CHATFILETRANS
{
	CHAR szName[BUFNAME];
	CHAR szContent[BUFCHAT];
}CHATFILETRANS;

// �鿴�����¼�ṹ��
typedef struct _CHATMSGRECORD
{
	CHAR szFrom[50];
	CHAR szTo[50];
	CHAR szContent[1024];
}CHATMSGRECORD;

// ���������û��б�
typedef struct _CHATUPDATEUSER
{
	DWORD bAdd;   // �Ǽ��뻹���˳�
	DWORD dwLen;  // һ��ֻ����1���û���
	CHAR buf[50];
}CHATUPDATEUSER;

// ��������
typedef struct _CHATSEND
{
	CHATPURPOSE m_type;

	union{
		char buf[BUFMSG];
		CHATANONYMOUS any;    // ����
		CHATCHAT chat;        // ����
		CHATONE2ONE o2o;     // 1V1
		CHATREGISTER reg;     // ע��
		CHATLOGIN log;        // ��¼
		CHATADDFRIEND adf;    // ��Ӻ���
		CHATSEARCHUSER seu;   // ��������
		CHATFILETRANS  trs;   // �ļ�����
		CHATMSGRECORD  rec;   // �����¼
		CHATUPDATEUSER upd;   // �����û��б�
	}m_content;
}CHATSEND;


class CclientSocket
{
#define BUFNAME 50 // ����
public:
	CclientSocket();
	~CclientSocket();
	// ��ʼ���ͻ����׽��֣����������ӷ�����
	bool ConnectSrver(char* szIp, WORD port);

	// ���𴴽��߳��������շ���������Ϣ
	char* Recv();
	bool Send(CHATPURPOSE purpose, char* bufSend, DWORD dwLen, SOCKET client = NULL);
	bool Close();
	fstream ReceiveFile;
private:
	// recv funciton
	char* RecvForAnonumous();
	char* RecvForChat();
	char* RecvForUpdateUserlist();
	char* RecvForOne2One();
	char* RecvForRegister();
	char* RecvForLogin();
	char* RecvForAddFriend();
	char* RecvForSearchUser();
	char* RecvForGetMsgRecord();
	char* RecvForFiletrans();

	// send function
	void SendForAnonymous(char* bufSend, DWORD dwLen);
	void SendForChat(char* bufSend, DWORD dwLen);
	void SendForOne2One(char* bufSend, DWORD dwLen);
	void SendForRegister(char* bufSend, DWORD dwLen);
	void SendForLogin(char* bufSend, DWORD dwLen);
	void SendForAddFriend(char* bufSend, DWORD dwLen);
	void SendForSearchUser(char* bufSend, DWORD dwlen);
	void SendForGetMsgRecord(char* bufSend, DWORD dwLen);
	void SendForFiletrans(char* bufSend, DWORD dwLen, SOCKET client);
	

public:
	// ���������¼��
	HANDLE m_hEvent = 0;
	vector<CHATMSGRECORD> m_vecMsgRecord;
	// �ͻ����׽���
	SOCKET m_sClient = NULL;
	// ���û�������˳������ҵ�ʱ���õ�
	CHATUPDATEUSER* m_pObjUpdate = nullptr;
	// 1V1 �����ʱ��
	CHATONE2ONE* m_pObjOne20ne = nullptr;
	// ��ǰ�ͻ��˵��û���
	char m_szName[BUFNAME] = {};
	// ����Ϣ��ʱ���õ�
	CHATSEND* m_pObjChatRecv;

private:
	char m_bufRecv[BUFMSG];
};



