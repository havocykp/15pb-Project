#include "stdafx.h"
#include "��̬���Ա�.h"

/* ���캯��*/
CMyVector::CMyVector()
{
	m_nBuf = nullptr;
	m_nLenth = 0;
	m_nSize = 0;
}

/* �������� */
CMyVector::~CMyVector()
{
	int nError;
	clearVector(nError);
}

/* ��ʼ�����������Ա� */
bool CMyVector::initVector(_Out_ int& nError)
{
	clearVector(nError);
	m_nBuf = new int[INIT_SIZE];
	memset(m_nBuf, 0, sizeof(int) * INIT_SIZE);
	m_nLenth = 0;
	m_nSize = INIT_SIZE;
	return true;
}

/* �ж����Ա���Ƿ�Ϊ�� */
bool CMyVector::isEmpty(_Out_ int& nError)
{
	nError = OR_SUCCESS;

	if (m_nLenth == 0) {
		return true;
	}
	else {
		return false;
	}
}

/* �ж����Ա��Ƿ��� */
bool CMyVector::isFull(_Out_ int& nError)
{
	nError = OR_SUCCESS;

	if (m_nLenth == m_nSize) {
		return true;
	}
	else {
		return false;
	}
}

/* ������Ա� */
bool CMyVector::clearVector(_Out_ int& nError)
{
	if (m_nBuf) {
		delete[] m_nBuf;
	}
	m_nLenth = 0;
	m_nSize = 0;
	nError = OR_SUCCESS;
	return true;
}

/* ���±��ȡԪ�� */
bool CMyVector::getEleByIndex(_In_ int nPos, _Out_ int& nEle, _Out_ int& nError)
{
	// 1.����Ƿ�Խ��
	if (nPos >= m_nLenth || nPos < 0) {
		nError = OR_INDEX_IS_WRONG;
		return false;
	}

	// 2.ֱ�Ӹ�ֵ
	nEle = m_nBuf[nPos];

	// 3.����true
	return true;
}

/* ��Ԫ��ֵ��ȡ�±� */
bool CMyVector::getEleByValue(_Out_ int& nPos, _In_ int& nEle, _Out_ int& nError)
{
	// 1.�Ƚ�Loc����ֵ��Ϊһ��������ֵ�ֵ�����û���ҵ����򴫳���ֵ������û���ҵ�
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
bool CMyVector::insertEleByIndex(_In_ int nPos, _In_ int nEle, _Out_ int& nError)
{
	// 1.����Ƿ�����
	if (isFull(nError)) {
		// ���ˣ�ֱ�ӷ���
		if (!reSize(nError)) {
			return true;
		}
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

/* ��λ��ɾ��Ԫ�� */
bool CMyVector::delEleByIndex(_In_ int nPos, _Out_ int& nEle, _Out_ int& nError)
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

	// 3.�ô�ɾԪ�ط���ֵ
	nEle = m_nBuf[nPos];

	// 4.����ɾ���Ĳ������һ��Ԫ�أ���ô��Ҫǰ��
	// ע�����һ��Ԫ�ز��ù�
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

/* ��Ԫ��ֵɾ��Ԫ�� */
bool CMyVector::delEleByValue(_In_ int nEle, _Out_ int& nError)
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

/* ��������vector�Ĵ�С */
bool CMyVector::reSize(_In_ int& nError)
{
	// 1.�鿴�Ƿ��ܹ������ڴ�
	int newSize = 0;
	if (m_nSize == MAX_SIZE) {
		nError = OR_BUFFER_IS_FULL;
		return false;
	}
	if (2 * m_nSize >= MAX_SIZE) {
		newSize = MAX_SIZE;
	}
	else {
		newSize = 2 * m_nSize;
	}

	// 2.���¿����ڴ�
	int *tempBuf = new int[newSize];

	// 3.������ת�ƹ���
	for (int i = 0; i < m_nLenth; ++i) {
		tempBuf[i] = m_nBuf[i];
	}

	// 4.���ԭ�ڴ�
	int lenth = m_nLenth;
	bool isSuccess = clearVector(nError);

	// 5.���ڴ����ݸ�����Ա����
	m_nBuf = tempBuf;
	m_nSize = newSize;
	m_nLenth = lenth;

	// 5.���÷���ֵ
	if (isSuccess) {
		return true;
	}
	else {
		m_nBuf = nullptr;
		m_nSize = 0;
		m_nLenth = 0;
		return false;
	}
}

/* ���ص�ǰ���� */
bool CMyVector::getLength(_Out_ int& nLenth, _Out_ int& nError)
{
	nLenth = m_nLenth;
	nError = OR_SUCCESS;
	return true;
}

/* ������󳤶� */
bool CMyVector::max_size(_Out_ int& nLenth, _Out_ int& nError)
{
	nError = OR_SUCCESS;
	nLenth = MAX_SIZE;
	return true;
}

/* ��β������ */
bool CMyVector::push_back(_In_ int nEle, _Out_ int& nError)
{
	int nlen;
	getLength(nlen, nError); // ��Ա�������浱ǰ����
	insertEleByIndex(nlen, nEle, nError);
	return true;
}

/* ����β��Ԫ�� */
bool CMyVector::pop_back(_Out_ int& nEle, _Out_ int& nError)
{
	int nlen;
	getLength(nlen, nError);
	delEleByIndex(nlen - 1, nEle, nError);
	return true;
}

/* ���±괦����Ԫ�� */
bool CMyVector::insert(_In_ int pos, _In_ int elem, _Out_ int& nError)
{
	insertEleByIndex(pos, elem, nError);
	return true;
}

/* ���±괦������Ԫ�� */
bool CMyVector::insert(_In_ int pos, _In_ int n, _In_ int elem, _Out_ int& nError)
{
	for (int i = 0; i < n; ++i) {
		insertEleByIndex(pos + i, elem, nError);
	}
	return true;
}

/* �ڿ�ʼ�������յ�����֮�������Ԫ�� */
bool CMyVector::insertEx(_In_ int beg, _In_ int end, _In_ int elem, _Out_ int& nError)
{
	for (int i = 0; i < end - beg; ++i) {
		insertEleByIndex(beg + i, elem, nError);
	}
	return true;
}

/* ����ָ��λ�õ�Ԫ�� */
bool CMyVector::at(_In_ int idx, _Out_ int& elem, _Out_ int& nError)
{
	return getEleByIndex(idx, elem, nError);
}

/* ����[]���� */
int CMyVector::operator[](_In_ int pos)
{
	int elem;
	int nError;
	if (getEleByIndex(pos, elem, nError)) {
		return m_nBuf[pos]; // return elem
	}
}