// MyPass_Demo1.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"   //���½���cpp�ļ��У�����Ҫ����
#include "control.h"
#include "MyPass_Demo1.h"
#include <windows.h>
#include <conio.h>


int main()
{
	int nChoice = 0;
	inital(); //��ʼ������
	while (true)
	{
		//��ӡ�˵�ѡ��
		menu();
		scanf_s("%d", &nChoice);  //��ȡ����
		switch (nChoice)
		{
		case ����:
			addPassWord();
			break;
		case �޸�:
			system("cls");
			modifyPassWord();
			break;
		case ����:
		{
			int nNum = 0;
			while (true)
			{
				menu();
				scanf_s("%d", &nChoice);
				divmenu();
				scanf_s("%d", &nNum);
				switch (nNum)
				{
				case 1:
					searchPassWordWeb();
					break;
				case 2:
					searchPassWordUser();
					break;
				case 0:
					menu();
					break;
				default:
					break;
				}
			}	
			
		}
			break;
		case ����:
			savePassWord();
			break;
		case ɾ��:
			system("cls");
			delPassword();
			break;
		case ��ʾ:
			showPassWord();
			break;
		case �˳�: 
			quit();
			break;
		default:
			break;

		}
	}


    return 0;
}



