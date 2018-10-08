#pragma once
#include <sal.h>

typedef int Operator; // �������������
#define OR_SUCCESS 1  // �����ɹ�
#define OR_BUFFER_IS_FULL  -1  // ����������
#define OR_BUFFER_IS_EMPTY -2  // ������Ϊ��
#define OR_ERROR           -3  // δ֪����
#define OR_INDEX_IS_WRONG  -4  // ����ֵ����
#define OR_MEM_ERROR       -5  // �����ڴ�ʧ��
#define MAX_SIZE          100  // ���Ա���󳤶�


template <class T>
class CMyTemplateArray
{
public:
	CMyTemplateArray(); // ���캯��
	~CMyTemplateArray(); // ��������

	// ��ʼ��������һ�����Ա� 
	bool initArray(_Out_ int& nError);
	// �ж����Ա��Ƿ�Ϊ��
	bool isEmpty(_Out_ int& nError);
	// ������Ա�
	bool clearArray(_Out_ int& nError);
	// ���±��ȡԪ��
	bool getEleByIndex(_In_ int nPos, _Out_ T& nEle, _Out_ int& nError);
	// ��Ԫ��ֵ��ȡ�±�
	bool getEleByValue(_Out_ int& nPos, _In_ T& nEle, _Out_ int& nError);
	// ����Ԫ��
	bool insertEleByIndex(_In_ int nPos, _In_ T nEle, _Out_ int& nError);
	// ��λ��ɾ��Ԫ��
	bool delEleByIndex(_In_ int nPos, _Out_ T& nEle, _Out_ int& nError);
	// ��Ԫ��ֵɾ��Ԫ��
	bool delEleByValue(_In_ T nEle, _Out_ int& nError);
	// ���ص�ǰ����
	bool getLength(_In_ int& nLenth, _In_ int& nError);

private:
	T m_nBuf[MAX_SIZE];
	int m_nLenth;
};


/* ���캯�� */
template <class T>
CMyTemplateArray<T>::CMyTemplateArray()
{
	memset(m_nBuf, 0, sizeof(int) * MAX_SIZE);
	m_nLenth = 0;
}

/* �������� */
template <class T>
CMyTemplateArray<T>::~CMyTemplateArray()
{

}

/* ��ʼ��������һ�����Ա� */ 
template <class T>
bool CMyTemplateArray<T>::initArray(_Out_ int& nError)
{
	return clearArray(nError);
}

// �ж����Ա��Ƿ�Ϊ��
template <class T>
bool CMyTemplateArray<T>::isEmpty(_Out_ int& nError)
{
	nError = OR_SUCCESS;

	if (m_nLenth == 0) {
		return true;
	}
	else{
		return false;
	}
}

/* ������Ա� */
template <class T>
bool CMyTemplateArray<T>::clearArray(_Out_ int& nError)
{
	for (int i = 0; i < m_nLenth; ++i) {
		m_nBuf[i] = 0;
	}
	m_nLenth = 0;
	nError = OR_SUCCESS;

	return true;
}

/* ���±��ȡԪ�� */
template <class T>
bool CMyTemplateArray<T>::getEleByIndex(_In_ int nPos, _Out_ T& nEle, _Out_ int& nError)
{
	// 1.����Ƿ�Խ��
	if (nPos >= m_nLenth) {
		nError = OR_INDEX_IS_WRONG;
		return false;
	}
	// 2.ֱ�Ӹ�ֵ
	nEle = m_nBuf[nPos];

	// 3.����true
	nError = OR_SUCCESS;

	return true;
}

/* ��Ԫ��ֵ��ȡ�±� */
template <class T> 
bool CMyTemplateArray<T>::getEleByValue(_Out_ int& nPos, _In_ T& nEle, _Out_ int& nError)
{
	// 1.�Ƚ�Loc����ֵ��Ϊһ��������ֵ�ֵ�����û���ҵ��򴫳���ֵ������û���ҵ�
	nPos = -1;

	// 2.�����Ա��в���Ŀ��Ԫ�أ�����ƥ�䵽�ĵ�һ��λ��
	for (int i = 0; i < m_nLenth; ++i) {
		if (nEle == m_nBuf[i]) {
			nPos = i;
			break;
		}
	}

	// 3.���ô�����
	if (nPos > -1) {
		nError = OR_SUCCESS;
		return true;
	}
	else {
		nError = OR_INDEX_IS_WRONG;
		return false;
	}
}

/* ����Ԫ�� */
template <class T>
bool CMyTemplateArray<T>::insertEleByIndex(_In_ int nPos, _In_ T nEle, _Out_ int& nError)
{
	// 1.����Ƿ�����
	if (m_nLenth == MAX_SIZE) {
		nError = OR_BUFFER_IS_FULL;
		return false;
	}

	// 2.����Ƿ�Խ��
	if (nPos > m_nLenth || nPos < 0) {
		nError = OR_INDEX_IS_WRONG;
		return false;
	}

	// 3.�������Ĳ������һ��Ԫ�أ���֮ǰ��ÿһ��Ԫ�ض�������
	if (nPos != m_nLenth) {
		for (int i = m_nLenth - 1; i >= nPos; --i) {
			m_nBuf[i + 1] = m_nBuf[i];
		}
	}

	// 4.ֱ����������Ӧ��λ�ø�ֵ
	m_nBuf[nPos] = nEle;

	// 5.Ԫ�ظ�������
	m_nLenth++;

	// 6.���ô�����
	nError = OR_SUCCESS;
	return true;
}

/* ��λ��ɾ��Ԫ��,������ɾ��Ԫ�� */
template <class T>
bool CMyTemplateArray<T>::delEleByIndex(_In_ int nPos, _Out_ T& nEle, _Out_ int& nError)
{
	// 1.������Ա��Ƿ�Ϊ��
	if (m_nLenth == 0) {
		nError = OR_BUFFER_IS_EMPTY;
		return false;
	}

	// 2.����Ƿ�Խ��
	if (nPos >= m_nLenth || nPos < 0) {
		nError = OR_INDEX_IS_WRONG;
		return false;
	}

	// 3.�ô�ɾԪ�����÷���ֵ
	nEle = m_nBuf[nPos];

	// 4.����ɾ���Ĳ������һ��Ԫ�أ���ô��Ҫ��ǰ�ƶ�
	// ע�����һ��Ԫ�ظ������ù�
	if (nPos != (m_nLenth - 1)) {
		for (int i = nPos; i < m_nLenth - 1; ++i) {
			m_nBuf[i] = m_nBuf[i + 1];
		}
	}

	// 5.�����Լ�
	m_nBuf[m_nLenth - 1] = 0;
	m_nLenth--;

	// 6.���ô����룬�Լ�����ֵ
	nError = OR_SUCCESS;
	return true;
}

/* ��Ԫ��ֵɾ��Ԫ�أ�������ɾ����Ԫ�� */
template <class T>
bool CMyTemplateArray<T>::delEleByValue(_In_ T nEle, _Out_ int& nError)
{
	// 1.��ȡ��ɾ��Ԫ�ص��±�
	int nPos = -1;
	bool isSuccess;
	isSuccess = getEleByValue(nPos, nEle, nError);

	// 2.�����Ҳ��������
	if (!isSuccess) {
		return false;
	}

	// 3.����ȷ�ҵ��±�
	isSuccess = delEleByIndex(nPos, nEle, nError);

	// 4.����ɾ��ʧ�ܵ����
	if (!isSuccess) {
		return false;
	}

	// 5.��ȷ����
	nError = OR_SUCCESS;
	return true;
}

/* ���ص�ǰ���� */
template <class T>
bool CMyTemplateArray<T>::getLength(_In_ int& nLenth, _In_ int& nError)
{
	nLenth = m_nLenth;
	nError = OR_SUCCESS;
	return true;
}

