#include "stdafx.h"
#include "ctrl.h"
#include <stdlib.h>
#include <string.h>


//�鿴��������
void searchAllInfo(PASSWORD pwd[], int nCount)
{
	printf("==����: %2d ����¼==============\n", nCount);
	for (size_t i = 0; i < nCount; i++)
	{
		// typedef unsigned int     size_t;
		printf("--ID: %2d -------------------\n", i);
		printf("Ŀ  ��:%s \n", pwd[i].webSite);
		printf("�û���:%s \n", pwd[i].userName);
		printf("��  ��:%s \n", pwd[i].passWord);
		printf("��  ע:%s \n", pwd[i].note);
	}

	system("pause");
}

//��������
void insertInfo(PASSWORD pwd[], int *pnCount)
{
	int i = *pnCount;
	if (i < 0 || i >= NUM)
	{
		printf("����λ���쳣:%d \n", i);
		return;
	}
	printf("������<Ŀ��վ��>\n");
	scanf_s("%s", pwd[i].webSite, 100);
	printf("������< �û��� >\n");
	scanf_s("%s", pwd[i].userName, 100);
	printf("������<  ����  >\n");
	scanf_s("%s", pwd[i].passWord, 100);
	printf("������<  ��ע  >\n");
	scanf_s("%s", pwd[i].note, 100);

	(*pnCount)++;
	saveInfoB(pwd, *pnCount);

	system("pause");
	system("cls");
}
//ɾ������
void deleteInfo(PASSWORD pwd[], int *pnCount)
{
	int i = -1;
	printf("�������ɾ����<����ID>\n");
	scanf_s("%d", &i);
	if (i < 0 || i > NUM)
	{
		printf("ɾ��λ���쳣:%d \n", i);
		return;
	}

	for (size_t j = i; j < *pnCount - 1; j++)
	{
		pwd[j] = pwd[j + 1];
	}

	(*pnCount)--;
	saveInfoB(pwd, *pnCount);

	system("pause");
	system("cls");
}

//�޸�����
void alterInfo(PASSWORD pwd[], int nCount)
{
	int i = -1;
	printf("��������޸���<����ID>\n");
	scanf_s("%d", &i);
	if (i < 0 || i >= NUM)
	{
		printf("�޸�λ���쳣:%d \n", i);
		return;
	}

	printf("--ID: %3d ---------------------\n", i);
	printf("Ŀ  ��:%s \n", pwd[i].webSite);
	printf("�û���:%s \n", pwd[i].userName);
	printf("��  ��:%s \n", pwd[i].passWord);
	printf("��  ע:%s \n", pwd[i].note);
	printf("~�޸�~\n");
	printf("������<Ŀ��վ��>\n");
	scanf_s("%s", pwd[i].webSite, 100);
	printf("������< �û��� >\n");
	scanf_s("%s", pwd[i].userName, 100);
	printf("������<  ����  >\n");
	scanf_s("%s", pwd[i].passWord, 100);
	printf("������<  ��ע  >\n");
	scanf_s("%s", pwd[i].note, 100);

	saveInfoB(pwd, nCount);

	system("pause");
	system("cls");
	
}

//��ѯ����
void searchInfo(PASSWORD pwd[], int nCount)
{
	char key[100] = { 0 };
	printf("�������������Ĺؼ���:\n");
	scanf_s("%s", key, 100);

	//�ҳ�����ƥ����
	int findPwd[100] = { 0 };
	int nfindCount = 0;
	for (size_t i = 0; i < nCount; i++)
	{
		if (strstr(pwd[i].webSite, key))
		{
			findPwd[nfindCount++] = i;
			continue;
		}
		if (strstr(pwd[i].userName, key))
		{
			findPwd[nfindCount++] = i;
			continue;
		}
		if (strstr(pwd[i].passWord, key))
		{
			findPwd[nfindCount++] = i;
			continue;
		}
		if (strstr(pwd[i].note, key))
		{
			findPwd[nfindCount++] = i;
			continue;
		}
	}//for

	//��ӡ����ƥ����
	printf("==����ƥ��:%2d ����¼===============\n", nfindCount);
	for (size_t i = 0; i < nfindCount; i++)
	{
		int pos = findPwd[i];
		printf("--ID:%2d -----------------------\n", pos);
		printf("Ŀ  ��:%s \n", pwd[i].webSite);
		printf("�û���:%s \n", pwd[i].userName);
		printf("��  ��:%s \n", pwd[i].passWord);
		printf("��  ע:%s \n", pwd[i].note);
	}
	system("pause");
	system("cls");
}

//��������(�ı��ķ�ʽ)
void saveInfoA(PASSWORD pwd[], int nCount)
{
	/*
	��д�ļ��Ĺ̶���·
	1. ���ļ�
	2. ��д�ļ�
	3. �ر��ļ�
	*/

	//���ļ�
	FILE *pFile;
	errno_t err = fopen_s(&pFile, "data.txt", "w");
	if (err != 0)
	{
		return;
	}
	//��д�ļ�
	fprintf(pFile, "==����:%2d ����¼=================\n", nCount);
	for (size_t i = 0; i < nCount; i++)
	{
		fprintf(pFile, "--ID:%2d ---------------------\n", i);
		fprintf(pFile, "Ŀ  ��: %s \n", pwd[i].webSite);
		fprintf(pFile, "�û���: %s \n", pwd[i].userName);
		fprintf(pFile, "��  ��: %s \n", pwd[i].passWord);
		fprintf(pFile, "��  ע: %s \n", pwd[i].note);
	}

	//�ر��ļ�
	fclose(pFile);

	printf("�����ı�����ɹ���ʹ�ú��뾡��ɾ��!!\n");
	system("pause");
}

//��������(�����Ƶķ�ʽ)
void saveInfoB(PASSWORD pwd[], int nCount)
{
	//���ļ�
	FILE  *pFile;
	errno_t err = fopen_s(&pFile, "data.i", "wb");
	if (err != 0)
	{
		return;
	}

	//��д�ļ�
	fwrite(&nCount, sizeof(nCount), 1, pFile); //��ǰ�������
	fwrite(&g_nNum, sizeof(g_nNum), 1, pFile); //��ǰ���뱾����

	//�ȼ���(ʹ���м��ļ�)���ٴ洢
	int byteSize = sizeof(PASSWORD) * g_nNum;
	char *buf = (char *)malloc(byteSize);
	memcpy_s(buf, byteSize, pwd, byteSize);

	for (size_t i = 0; i < byteSize; i++)
	{
		buf[i] -= 1;
	}
	/*����ԭ��
	#include <stdio.h>
	int fwrite(const void *buffer, size_t size, size_t count, FILE *stream);

	fwrite()����������buffer(������)��, 
	дcount����СΪsize(��С)�Ķ���stream(��)ָ������. 
	����ֵ����д�Ķ��������. 
	*/
	size_t rlen = fwrite(buf, sizeof(PASSWORD), g_nNum, pFile); //��������
	if (rlen != g_nNum)
	{
		printf("д�������ļ�����\n");
	}
	else
	{
		printf("�ļ�д��ɹ�!!\n");
	}

	//�ر��ļ�
	fclose(pFile);
	free(buf);

}

//�ӱ����ļ��ж�ȡ���룬���ڳ�ʼ�����뱾
void readInfo(PPASSWORD *ppPwd, int *pnCount)
{
	//���ļ�
	FILE *pFile;
	errno_t err = fopen_s(&pFile, "data.i", "rb");
	if (err != 0)
	{
		*ppPwd = (PPASSWORD)malloc(sizeof(PASSWORD) * NUM);
		g_nNum = NUM;
		return;
	}

	//��д�ļ�
	//�ȶ�ȡ���ٽ���
	fread(pnCount, sizeof(int), 1, pFile);  
	fread(&g_nNum, sizeof(g_nNum), 1, pFile);
	*ppPwd = (PPASSWORD)malloc(sizeof(PASSWORD) * g_nNum);
	memset(*ppPwd, 0, sizeof(PASSWORD) * g_nNum);
	size_t rlen = fread(*ppPwd, sizeof(PASSWORD), g_nNum, pFile); //��������
	if (rlen != g_nNum)
	{
		printf("��ȡ�����ļ�����\n");
		fclose(pFile);
		return;
	}
	int byteSize = sizeof(PASSWORD) * g_nNum;
	char *buf = (char *)*ppPwd;
	for (size_t i = 0; i < byteSize; i++)
	{
		buf[i] += 1;
	}

	//�ر��ļ�
	fclose(pFile);

}

//�ı����̨������ɫ
