// ���뱾.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "data.h"
#include <stdlib.h>
#include "ctrl.h"
#include <string.h>
#include <windows.h>
#include <conio.h>
#pragma comment(lib, "winmm.lib")


//void setColor(int color);
//void setCurson(int x, int y);

//����Ҫ��ʾ�Ĳ˵�   
char *menu[] =
{
	"\t\t\t\t 1. �鿴��������\t      \n\n",
	"\t\t\t\t 2. ��������\t\t      \n\n",
	"\t\t\t\t 3. ɾ������\t\t      \n\n",
	"\t\t\t\t 4. �޸�����\t\t      \n\n",
	"\t\t\t\t 5. ��ѯ����\t\t      \n\n",
	"\t\t\t\t 6. �����ļ�\t\t      \n\n",
	"\t\t\t\t 7. �˳�\t\t      \n",
};
//��� 
CONSOLE_CURSOR_INFO cci;
//����Ĭ�ϵ�����λ��       
COORD pos = { 0,0 };
//��ʾ�˵�   
void showmenu(HANDLE hOut, char **menu, int size, int index);
//��ȡ�û�����   
int  get_userinput(int *index, int size);
int main()
{
	int ret;
	int index = 0;
	PPASSWORD pPwd = nullptr;  //��������
	int nCount = 0;  //��ǰ�������
	g_nNum = 0;  //��ǰ���뱾����

	readInfo(&pPwd, &nCount); //�ӱ����ļ��ж�ȡ���룬���ڳ�ʼ�����뱾

	HANDLE hOut;
	//��ȡ��ǰ�ľ��---����Ϊ��׼������   
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	//��ȡ�����Ϣ  
	GetConsoleCursorInfo(hOut, &cci);
	//���ù���С     
	cci.dwSize = 1;
	//���ù�겻�ɼ� FALSE     
	cci.bVisible = 0;
	//����(Ӧ��)�����Ϣ  
	SetConsoleCursorInfo(hOut, &cci);
	PlaySoundA("sound\\xiao.wav", NULL, SND_ASYNC | SND_NODEFAULT); //���ű�����
	while (1)
	{
		showmenu(hOut, menu, _countof(menu),index);
		ret = get_userinput(&index, _countof(menu));
		if (ret == ESC)
			break;
		if (ret == ENTER)
		{
			switch (index)
			{
			case �鿴����:
				searchAllInfo(pPwd, nCount);
				break;
			case ����:
				insertInfo(pPwd, &nCount);
				break;
			case ɾ��:
				deleteInfo(pPwd, &nCount);
				break;
			case �޸�:
				alterInfo(pPwd, nCount);
				break;
			case ��ѯ:
				searchInfo(pPwd, nCount);
				break;
			case �����ı�:
				saveInfoA(pPwd, nCount);
				break;
			case �˳�:
				exit(0);
				break;
			default:
				break;
			}
			system("cls");
		}
	}
	return 0;
}

void showmenu(HANDLE hOut, char **menu, int size, int index)
{
	int i;
	system("cls");
	//������ʾ���ı�����ɫ   
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN | 0x8);
	//��ʼ������̨��ʾ��X,Y�������   
	pos.X = 30;
	pos.Y = 0;
	//������ʾ������̨�ն˵ľ���λ��   
	SetConsoleCursorPosition(hOut, pos);

	for (i = 0; i < size; i++)
	{
		//���i==index��ʾ�ڵ�ǰѡ���λ�ã�Ĭ�ϳ�ʼ����ʾ�ǵ�һ���ʾΪ��ɫ��  
		//���������°���ѡ���ʱ�򣬹����ƶ���Ҳ�Ϳ������б�ѡ�������   
		if (i == index)
		{
			//��ɫ   
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | 0x8);
			pos.X = 25;
			pos.Y = 5 + i;
			//���ù������  
			SetConsoleCursorPosition(hOut, pos);
			printf("%s", menu[i]);
		}
		//������ʾΪ��ɫ   
		else
		{
			//��ɫ   
			SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
			pos.X = 30;
			pos.Y = 5 + i;
			//���ù������  
			SetConsoleCursorPosition(hOut, pos);    //���ù������  
			printf("%s", menu[i]);
		}
	}
	//ˢ�±�׼���������   
	fflush(stdout);
}

//��ȡ�û�����Ľӿ�   
int  get_userinput(int *index, int size)
{
	int ch;
	ch = _getch();
	switch (ch)
	{
		//��   
		//���ѡ���ϣ���ô��������ƶ�   
	case UP: if (*index > 0)  *index -= 1;  break;
		//��   
		//���ѡ���£���ô��������ƶ�   
	case DOWN:if (*index < size - 1)  *index += 1;  break;
		//�س�   
	case ENTER: return ENTER;
		//ESC  
	case ESC: return ESC;
	}
	return 0;
}

int main11()
{
	PPASSWORD pPwd= nullptr;  //��������
	int nCount = 0;  //��ǰ�������
	g_nNum = 0;  //��ǰ���뱾����

	//�ӱ����ļ��ж�ȡ���룬���ڳ�ʼ�����뱾
	readInfo(&pPwd, &nCount); 
	/*
	while (true)
	{
		PlaySoundA("sound\\xiao.wav", NULL, SND_ASYNC | SND_NODEFAULT); //���ű�����
		
		setColor(12);
		system("title ��ӭʹ�����뱾"); //�޸ı���
		printf("\n\n\n\n");
		printf("\t\t+--------------------���뱾-------------------+\n");
		printf("\t\t|\t\t\t\t\t      |\n");
		setColor(5);
		printf("\t\t|\t\t 1. �鿴��������\t      |\n\n");
		setColor(1);
		printf("\t\t|\t\t 2. ��������\t\t      |\n\n");
		setColor(3);
		printf("\t\t|\t\t 3. ɾ������\t\t      |\n\n");
		setColor(7);
		printf("\t\t|\t\t 4. �޸�����\t\t      |\n\n");
		setColor(11);
		printf("\t\t|\t\t 5. ��ѯ����\t\t      |\n\n");
		setColor(6);
		printf("\t\t|\t\t 6. �����ļ�\t\t      |\n\n");
		setColor(10);
		printf("\t\t|\t\t 0. �˳�\t\t      |\n");
		printf("\t\t|\t\t\t\t\t      |\n");
		printf("\t\t+---------------------------------------------+\n\n");
		setColor(4);
		printf("\t\t\t��ѡ��[0��6]��[ ]\b\b");

		int op;
		scanf_s("%d", &op);

		switch (op)
		{
		case �鿴����:
			searchAllInfo(pPwd, nCount);
			break;
		case ����:
			insertInfo(pPwd, &nCount);
			break;
		case ɾ��:
			deleteInfo(pPwd, &nCount);
			break;
		case �޸�:
			alterInfo(pPwd, nCount);
			break;
		case ��ѯ:
			searchInfo(pPwd, nCount);
			break;
		case �����ı�:
			saveInfoA(pPwd, nCount);
			break;
		case �˳�:
			exit(0);
			break;
		default:
			break;
		}
		system("cls");
	}
	*/

    return 0;
}

//������ɫ
void setColor(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

/*

//���ù��
void setCurson(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
*/