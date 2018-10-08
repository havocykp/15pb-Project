#pragma once

typedef int ElemType; //����Ԫ�ص�����
const int MAXSIZE = 100; //���������

class Stack
{
public:
	Stack(); // ���캯��
	~Stack(); // ��������
	void SetEmpty(); // �����е�ջΪ��ջ
	int IsEmpty();  // �ж�ջ�Ƿ�Ϊ��
	void push(ElemType e); // ��ջ
	ElemType pop();  // ��ջ
	void PrintOut(); // ���ջ������Ԫ��
	//ElemType Getpop(); // ȡջ��Ԫ������

private:
	ElemType elem[MAXSIZE];
	int top;
};

