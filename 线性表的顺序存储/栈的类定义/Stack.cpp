#include "stdafx.h"
#include "Stack.h"
#include <iostream>
#include <iomanip>

using namespace std;

/* ���캯�� */
Stack::Stack()
{
	top = 0; // ��ʼ��һ����ջ
}

/* �������� */
Stack::~Stack()
{

}

/* �����е�ջΪ��ջ */
void Stack::SetEmpty()
{
	top = 0;
}

/* �ж�ջ�Ƿ�Ϊ�� */
int Stack::IsEmpty()
{
	if (top == 0)
		return 1;
	else
		return 0;
}

/* ��ջ */
void Stack::push(ElemType e)
{
	if (top == MAXSIZE - 1) {
		cout << "\nջ�����" << endl;
	}
	else{
		top++;
		elem[top] = e; //����Ԫ��e��ջ
	}
}

/* ��ջ */
ElemType Stack::pop()
{
	ElemType x;
	if (top == 0) {
		cout << "\n ջΪ�գ����ܽ��г�ջ����" << endl;
		x = 0; //��ʾδ����ջ
	}
	else {
		x = elem[top]; // ��ջ
		top--;
	}
	return x;
}

/* ���ջ������Ԫ�� */
void Stack::PrintOut()
{
	// ����������ɸı�top
	cout << "\n PrintOut Data:\n";
	if (top == 0) {
		cout << "\n���ǿ�ջ��";
		if (IsEmpty()) {
			cout << "\n���ǿ�ջ";
		}
	}
	else {
		for (int k = top; k >= 1; --k) {
			cout << setw(6) << elem[k];
			cout << endl;
		}
	}
}
