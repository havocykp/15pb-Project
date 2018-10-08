#pragma once
#include <sal.h>

typedef int Opercode;  // �����������
#define OR_SUCCESS  1  // �����ɹ�
#define OR_BUFFER_IS_FULL -1   // �������Ѿ�����
#define OR_BUFFER_IS_EMPTY -2  // ������Ϊ��
#define OR_ERROR           -3  // δ֪����
#define OR_INDEX_IS_WRONG  -4  // ����ֵ����
#define OR_MEM_ERROR       -5  // �����ڴ�ʧ��
#define INIT_SIZE 100  // ���Ա��ʼ����
#define MAX_SIZE  9999 // ���Ա���󳤶�

class CMyVector
{
public:
	CMyVector();  // ���캯��
	~CMyVector(); // ��������

	// ��ʼ�����������Ա�
	bool initVector(_Out_ int& nError);
	// �ж����Ա��Ƿ�Ϊ��
	bool isEmpty(_Out_ int& nError);
	// �ж����Ա��Ƿ���
	bool isFull(_Out_ int& nError);
	// ������Ա�
	bool clearVector(_Out_ int& nError);
	// ���±��ȡԪ��
	bool getEleByIndex(_In_ int nPos, _Out_ int& nEle, _Out_ int& nError);
	// ��Ԫ��ֵ��ȡ�±�
	bool getEleByValue(_Out_ int& nPos, _In_ int& nEle, _Out_ int& nError);
	// ����Ԫ��
	bool insertEleByIndex(_In_ int nPos, _In_ int nEle, _Out_ int& nError);
	// ��λ��ɾ��Ԫ��
	bool delEleByIndex(_In_ int nPos, _Out_ int& nEle, _Out_ int& nError);
	// ��Ԫ��ֵɾ��Ԫ��
	bool delEleByValue(_In_ int nEle, _Out_ int& nError);
	// ���ص�ǰ����
	bool getLength(_Out_ int& nLenth, _Out_ int& nError);
	// ������󳤶�
	bool max_size(_Out_ int& nLenth, _Out_ int& nError);
	// ��β������
	bool push_back(_In_ int nEle, _Out_ int& nError);
	// ����β��Ԫ��
	bool pop_back(_Out_ int& nEle, _Out_ int& nError);
	// ���±괦����Ԫ��
	bool insert(_In_ int pos, _In_ int elem, _Out_ int& nError);
	// ���±괦������Ԫ��
	bool insert(_In_ int pos, _In_ int n, _In_ int elem, _Out_ int& nError);
	// �ڿ�ʼ�������յ�����֮�������Ԫ��
	bool insertEx(_In_ int beg, _In_ int end, _In_ int elem, _Out_ int& nError);
	// ����ָ��λ�õ�Ԫ��
	bool at(_In_ int idx, _Out_ int& elem, _Out_ int& nError);
	// ����[]����
	int operator[](_In_ int pos);

private:
	// ��������vector�Ĵ�С
	bool reSize(_In_ int& nError);


private:
	int *m_nBuf;
	int m_nLenth;
	int m_nSize;
};