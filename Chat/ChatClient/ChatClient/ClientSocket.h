#pragma once
#include <vector>

#define BUFNAME 50 // ����
#define BUFMSG 2048 // һ�ν�����Ϣ������ֽ���

using namespace std;

enum CHATPURPOSE
{
	ANNOYMOUS = 1,
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
typedef struct _CHATANNOYMOUS
{
	DWORD dwLen; // �������Ƴ���
	char buf[50]; // ����
}CHATANNOYMOUS;

// ����Ľṹ��
typedef struct _CHATCHAT
{
	DWORD dwLen; // �������ݳ���
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
	CHAR szPwd[50];
}CHATREGISTER;

// ��¼�ṹ�壬���������ؽ������szName��
typedef struct _CHATLOGIN
{
	CHAR szName[50];
	CHAR szPwd[50];
}CHATLOGIN;

// ��Ӻ��ѽṹ��
typedef struct _CHATADDFRIEND
{
	CHAR szName[50]; // �Լ�������
	CHAR szFrd[50]; // Ҫ��Ӻ�������
}CHATADDFRIEND;

// �����û��ṹ��
typedef struct _CHATSEARCHUSER
{
	CHAR szName[50]; // Ҫ�������û���
}CHATSEARCHUSER;

// �ļ�����ṹ��
typedef struct _CHATFILETRANS
{

}CHATFILETRANS;

// �鿴�����¼�ṹ��
typedef struct _CHATMSGRECORD
{
	CHAR szFrom[50];
	CHAR szTo[50];
	CHAR szContent[1024];
}CHATMSGRECORD;

// ���������û��б�
typedef struct _CHATUPDATAUSER
{
	DWORD bAdd; // �Ǽ��뻹���˳�
	DWORD dwLen; // һ��ֻ����1���û���
	CHAR buf[50]; 
}CHATUPDATAUSER;

// ��������
typedef struct _CHATSEND
{
	CHATPURPOSE m_type;
	union {
		char buf[BUFMSG];
		CHATANNOYMOUS any;
		CHATCHAT chat;
		CHATONE2ONE o2o;
		CHATREGISTER reg;
		CHATLOGIN log;
		CHATADDFRIEND adf;
		CHATSEARCHUSER seu;
		CHATFILETRANS trs;
		CHATMSGRECORD rec;
		CHATUPDATAUSER upd;
	}m_content;
}CHATSEND;


class CClientSocket
{
public:
	CClientSocket();
	~CClientSocket();
	// ��ʼ���׽��֣����������ӷ�����
	bool ConnectServer(char* szIp, WORD port);
	// ���𴴽��߳��������շ�������Ϣ
	char* Recv();
	bool Send(CHATPURPOSE purpose, char* bufSend, DWORD dwLen);
	bool Close();

private:
	// ���պ���
	char* RecvForAnonumous();
	char* RecvForChat();
	char* RecvForUpdateUserlist();
	char* RecvForOne2One();
	char* RecvForRegister();
	char* RecvForLogin();
	char* RecvForAddFriend();
	char* RecvForSearchUser();
	char* RecvForGetMsgRecord();

	// ���ͺ���
	void SendForAnnoymous(char* bufSend, DWORD dwLen);
	void SendForChat(char* bufSend, DWORD dwLen);
	void SendForOne2One(char* bufSend, DWORD dwLen);
	void SendForRegister(char* bufSend, DWORD dwLen);
	void SendForLogin(char* bufSend, DWORD dwLen);
	void SendForAddFriend(char* bufSend, DWORD dwLen);
	void SendForSearchUser(char* bufSend, DWORD dwLen);
	void SendForGetMsgRecord(char* bufSend, DWORD dwLen);

public:
	// ���������¼
	HANDLE m_hEvent = 0;
	vector<CHATMSGRECORD> m_vecMsgRecord;
	// �ͻ����׽���
	SOCKET m_sClient = NULL; 
	// ���û�������˳������ҵ�ʱ���õ� 
	CHATUPDATAUSER *m_pObjUpdate = nullptr;
	// 1v1�����ʱ��
	CHATONE2ONE *m_pObjOne2One = nullptr;
	// ��ǰ�ͻ��˵��û���
	char m_szName[BUFNAME] = {};
	// ����Ϣ��ʱ���õ�
	CHATSEND * m_pObjChatRecv;

private:
	char m_bufRecv[BUFMSG] = {};
};

