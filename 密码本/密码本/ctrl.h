#pragma once
#include "data.h"

//�鿴��������
void searchAllInfo(PASSWORD pwd[], int nCount);
//��������
void insertInfo(PASSWORD pwd[], int *pnCount);
//ɾ������
void deleteInfo(PASSWORD pwd[], int *pnCount);
//�޸�����
void alterInfo(PASSWORD pwd[], int nCount);
//��ѯ����
void searchInfo(PASSWORD pwd[], int nCount);
//��������(�ı��ķ�ʽ)
void saveInfoA(PASSWORD pwd[], int nCount);
//��������(�����Ƶķ�ʽ)
void saveInfoB(PASSWORD pwd[], int nCount);
//�ӱ����ļ��ж�ȡ���룬���ڳ�ʼ�����뱾
void readInfo(PPASSWORD *ppPwd, int *pnCount);
