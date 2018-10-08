#include "stdafx.h"
#include "Queue.h"
#include <iostream>

using namespace std;

/* ���캯�� */

Queue::Queue()
{
	front = 0;
	rear = 0; // ��ʼ���ն���
}

/* �������� */
Queue::~Queue()
{
}

/* �ж�ѭ�������Ƿ�Ϊ�� */
int Queue::Empty()
{
	if (rear == front)
		return 1;
	else
		return 0;
}

/* ������� */
void Queue::Display()
{

}

/* ���� */
void Queue::Add(ElemType x)
{
	if ((rear + 1) % MAXSIZE == front) { // �ж��Ƿ�����
		cout << "\n Queu is Full!" << endl;
	}
	else {
		rear = (rear + 1) % MAXSIZE; // βָ���1
		elem[rear] = x;  // x����
	}

}

/* ���� */
ElemType Queue::Del()
{
	if (front == rear) { // �ж϶����Ƿ�Ϊ��
		cout << "\n Queue is Empty!" << endl;
		return -1; // �����ӿգ�δ������
	}
	else {
		front = (front + 1) % MAXSIZE; // ���Ӳ���
		return elem[front];
	}
}
