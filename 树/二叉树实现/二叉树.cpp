#include "stdafx.h"
#include "������.h"
#include <vector>

using std::vector;

/** �����ǰ���Ľڵ�
 *  ����2�����
 *  ����3�����ӷ��� 
 */
void bstree::show(PNODE Node, int w, char c)
{
	if (Node != nullptr) {
		show(Node->RightChild, w + 4, '/');
		printf("%*s%c%02d\n", w, " ", c, Node->Element);
		show(Node->LeftChild, w + 4, '\\');
	}
}

/**
 * �����в�����Сֵ
 */
int bstree::min(PNODE Node)
{
	while (Node->LeftChild)
		Node = Node->LeftChild;

	return Node->Element;
}

/**
* �����в������ֵ
*/
int bstree::max(PNODE Node)
{
	while (Node->RightChild)
		Node = Node->RightChild;

	return Node->Element;
}

/**
 * �����в���һ���ڵ㣬���ر�����Ľڵ�
 */
PNODE bstree::insert(PNODE &Node, int Elem)
{
	// ����ڵ���4�п���

	// 1.��ǰ��λ��Ϊnullptr,˵�����Բ���
	if (Node == nullptr)
	{
		// ����ռ䲢��ʼ������
		Node = new NODE{ Elem, nullptr, nullptr };
		// �ж������Ƿ�ɹ�
		if (!Node)  printf("�ռ�����ʧ��!\n");
	}

	// 2.��ǰҪ�����ֵ�ϴ���Ҫ���뵽������
	else if (Elem > Node->Element)
	{
		// ��������ָ��Ҫ����Ľڵ�
		Node->RightChild = insert(Node->RightChild, Elem);
	}

	// 3.��ǰҪ�����ֵ��С����Ҫ���뵽������
	else if (Elem < Node->Element)
	{
		// ��������ָ��Ҫ����Ľڵ�
		Node->LeftChild = insert(Node->LeftChild, Elem);
	}

	// 4.����Ѵ���Ҫ�����ֵ���Ͳ����κβ���
	return Node;
}

/** 
 * ������ɾ��һ���ڵ㣬���ر�����Ľڵ�
 */
PNODE bstree::erase(PNODE &Node, int Elem)
{
	// ɾ���ڵ��4�ֱȽϿ���

	// 1.��ǰ��λ��Ϊnullptr��˵��û���ҵ��ڵ�
	if (Node == nullptr) {
		return Node;
	}

	// 2.��ǰҪɾ����ֵ�ϴ���Ҫ����������ɾ��
	else if (Elem > Node->Element) {
		// ����ɾ��λ�õ�ǰ��ֵ���¸�ֵ
		Node->RightChild = erase(Node->RightChild, Elem);
	}

	// 3.��ǰҪɾ����ֵ��С����Ҫ����������ɾ��
	else if (Elem < Node->Element) {
		// ����ɾ��λ�õ�ǰ��ֵ���¸�ֵ
		Node->LeftChild = erase(Node->LeftChild, Elem);
	}

	// 4.�����ȣ����ж��������ɾ��
	else
	{
		// 1.�������ӽڵ�
		if (Node->LeftChild && Node->RightChild) {
			// 1.���������в������ֵ
			int MaxNode = max(Node->LeftChild);
			Node->Element = MaxNode;
			Node->LeftChild = erase(Node->LeftChild, MaxNode);

			// 2.���������в�����Сֵ
// 			int MinNode = min(Node->RightChild);
// 			Node->Element = MinNode;
// 			Node->RightChild = erase(Node->RightChild, MinNode);
		}

		// 2.�е����ӽڵ�
		// 3.��Ҷ�ӽڵ�
		else {
			PNODE temp = Node;

			// �������������
			if (Node->LeftChild) Node->LeftChild;
			else if (Node->RightChild) Node = Node->RightChild;
			else Node = nullptr;

			delete temp;
		}
	}

	return Node;
}

/**
 * ǰ�����
 */

void bstree::Pre(PNODE Node)
{
	// �� �� ��
	if (Node != nullptr) {
		printf("%d ", Node->Element);
		Pre(Node->LeftChild);
		Pre(Node->RightChild);
	}
}

/**
* �������
*/
void bstree::Mid(PNODE Node)
{
	// �� �� ��
	if (Node != nullptr) {
		Mid(Node->LeftChild);
		printf("%d ", Node->Element);
		Mid(Node->RightChild);
	}
}

/**
* �������
*/
void bstree::Rear(PNODE Node)
{
	// �� �� ��
	if (Node != nullptr) {
		Rear(Node->LeftChild);
		Rear(Node->RightChild);
		printf("%d ", Node->Element);
	}
}


/**
* �������
*/
void bstree::Level(PNODE Node)
{
	// ���ڴ�ŵ�ǰ���ҵ��������ӽڵ�
	vector<PNODE> ChildNode;
	// �ڱ�ʾ��ǰ��������У���������
	vector<PNODE> NowLevel = { RootNode };

	// ѭ��������еĽڵ�
	while (NowLevel.size()) {
		// ������ǰ������нڵ�
		for (size_t i = 0; i < NowLevel.size(); ++i) {
			printf("%d ", NowLevel[i]->Element);
			if (NowLevel[i]->LeftChild)
				ChildNode.push_back(NowLevel[i]->LeftChild);
			if (NowLevel[i]->RightChild)
				ChildNode.push_back(NowLevel[i]->RightChild);
		}

		NowLevel = ChildNode;
		ChildNode.clear();
		printf("\n");
	}
}