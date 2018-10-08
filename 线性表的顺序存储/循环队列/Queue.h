#pragma once

typedef int ElemType; //����Ԫ�ص�����
const int MAXSIZE = 100; //���������

// ѭ������
class Queue
{
public:
	Queue(); // ���캯��
	~Queue(); // ��������
	int Empty(); // �ж�ѭ�������Ƿ�Ϊ��
	void Display(); // �������
	void Add(ElemType x); // ����
	ElemType Del();  // ����
	ElemType GetFront(); // ȡ����Ԫ��

private:
	ElemType elem[MAXSIZE];
	int front; // ͷָ��
	int rear; // βָ��
};

