#pragma once
//�Զ�����������
//�������е��û�����Ϊö��
#define �鿴����    0
#define ����        1
#define ɾ��        2
#define �޸�        3
#define ��ѯ        4
#define �����ı�    5
#define �˳�        6

//���̰���
enum 
{
	UP = 72,
	DOWN = 80,
	ENTER = 13,
	ESC = 27

};

//����洢�˺�����Ľṹ��
typedef struct _PASSWORD
{
	char webSite[100]; //վ����
	char userName[100]; //�ʻ���
	char passWord[100]; //����
	char note[100]; //��ע
}PASSWORD, *PPASSWORD;

//ȫ�ֱ���������������
#define NUM 100   //��ʼ���뱾����
extern int g_nNum;  //��ǰ���뱾����