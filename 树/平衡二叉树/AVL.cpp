#include "stdafx.h"
#include "AVL.h"
#include <vector>

using namespace std;

// �����ǰ���Ľڵ�
void avltree::show(PNODE Node, int w, char c)
{
	if (Node != nullptr)
	{
		show(Node->RightChild, w + 4, '/');
		printf("%*s%c%02d\n", w, " ", c, Node->Element);
		show(Node->LeftChild, w + 4, '\\');
	}
}


// �����ֲ�����Сֵ
int avltree::min(PNODE Node)
{
	while (Node->LeftChild)
		Node = Node->LeftChild;

	return Node->Element;
}

// �����в������ֵ
int avltree::max(PNODE Node)
{
	while (Node->RightChild)
		Node = Node->RightChild;

	return Node->Element;
}

// �����в���һ���ڵ㣬���ر�����Ľڵ�
PNODE avltree::insert(PNODE &Node, int Elem)
{
	// ����ڵ���4�ֿ���

	// 1. ��ǰ��λ��Ϊnullptr��˵�����Բ���
	if (Node == nullptr)
	{
		// ����ѿռ䲢��ʼ������
		Node = new NODE{ Elem, nullptr, nullptr };
		// �ж������Ƿ�ɹ�
		if (!Node) printf("�ռ�����ʧ��!\n");
	}
	// 2. ��ǰҪ�����ֵ�ϴ���Ҫ���뵽������
	else if (Elem > Node->Element)
	{
		// ��������ָ���²���Ľڵ�
		Node->RightChild = insert(Node->RightChild, Elem);
		// ������뵽����������ô���������ܻ����ߣ������������߶�����
		if (high(Node->RightChild) - high(Node->LeftChild) == 2)
		{
			// �����û����
			if (Elem > Node->RightChild->Element) // ������bug
				Node = left(Node);
			else
				Node = rightleft(Node);
		}
	}
	// 3. ��ǰҪ�����ֵ��С����Ҫ���뵽������
	else if (Elem < Node->Element)
	{
		// ��������ָ���²���Ľڵ�
		Node->LeftChild = insert(Node->LeftChild, Elem);
		// ������뵽����������ô���������ܻ����ߣ������������߶�����
		if (high(Node->LeftChild) - high(Node->RightChild) == 2)
		{
			// �����û����
			if (Elem > Node->LeftChild->Element) // ������bug
				Node = right(Node);
			else
				Node = leftright(Node);
		}
	}
	// 4. ����Ѵ���Ҫ����� ֵ���Ͳ����κβ���
	return Node;
}

// ������ɾ��һ���ڵ㣬���ر�����Ľڵ�
PNODE avltree::erase(PNODE &Node, int Elem)
{
	// ɾ���ڵ��4�ֱȽϿ���

	// 1. ��ǰ��λ��Ϊnullptr��˵��û���ҵ��ڵ�
	if (Node == nullptr)
	{
		return Node;
	}
	// 2. ��ǰҪɾ����ֵ�ϴ���Ҫ����������ɾ��
	else if (Elem > Node->Element)
	{
		// ����ɾ��λ�õ�ǰ��ֵ���¸�ֵ
		Node->RightChild = erase(Node->RightChild, Elem);
		// �����������ɾ������ô���������ܻ�䰫�������������߶�����
		if (high(Node->LeftChild) - high(Node->RightChild) == 2)
		{
			// �����û����
			if (Node->LeftChild->LeftChild)
				Node = right(Node);
			else
				Node = leftright(Node);
		}
	}
	// 3. ��ǰҪɾ����ֵ�ϴ���Ҫ����������ɾ��
	else if (Elem < Node->Element)
	{
		// ����ɾ��λ�õ�ǰ��ֵ���¸�ֵ
		Node->LeftChild = erase(Node->LeftChild, Elem);
		// �����������ɾ������ô���������ܻ�䰫�������������߶�����
		if (high(Node->RightChild) - high(Node->LeftChild) == 2)
		{
			// �����û����
			if (Node->RightChild->RightChild)
				Node = left(Node);
			else
				Node = rightleft(Node);
		}
	}
	// 4. ���������ж��������ɾ��
	else
	{
		// 1. �������ӽڵ�
		if (Node->LeftChild && Node->RightChild)
		{
			// 1. ���������в������ֵ
			int MaxNode = max(Node->LeftChild);
			Node->Element = MaxNode;
			Node->LeftChild = erase(Node->LeftChild, MaxNode);

			// 2. ���������ֲ�����Сֵ
			// int MinNode = min(Node->RightChild);
			// Node->Element = MinNode;
			// Node->RightChild = erase(Node->RightChild, MinNode);
		}
		// 2. �е����ӽڵ� - 3. ��Ҷ�ӽڵ�
		else
		{
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

// ǰ�������
void avltree::Pre(PNODE Node)
{
	// �� �� ��
	if (Node != nullptr)
	{
		printf("%d ", Node->Element);
		Pre(Node->LeftChild);
		Pre(Node->RightChild);
	}
}

// ���������
void avltree::Mid(PNODE Node)
{
	if (Node != nullptr)
	{
		// �� �� ��
		Mid(Node->LeftChild);
		printf("%d ", Node->Element);
		Mid(Node->RightChild);
	}
}

// ���������
void avltree::Rear(PNODE Node)
{
	if (Node != nullptr)
	{
		// �� �� ��
		Rear(Node->LeftChild);
		Rear(Node->RightChild);
		printf("%d ", Node->Element);
	}
}

// �������
void avltree::Level(PNODE Node)
{
	// ���ڴ�ŵ�ǰ���ҵ��������ӽڵ�
	vector<PNODE> ChildNode;
	// �ڱ�ʾ��ǰ��������У�������ڵ�
	vector<PNODE> NowLevel = { RootNode };

	// ѭ��������еĽڵ�
	while (NowLevel.size())
	{
		// ������ǰ������нڵ�
		for (size_t i = 0; i < NowLevel.size(); ++i)
		{
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

// ��ȡ���ĸ߶�
int avltree::high(PNODE Node)
{
	// �����ǰ�ڵ�Ϊ�վͷ���0
	if (Node == nullptr)
		return 0;

	// ��ȡ���������ĸ߶�
	int left = high(Node->LeftChild);
	int right = high(Node->RightChild);

	// ���ϴ�������߶�+1���ǵ�ǰ���ĸ߶�
	return left > right ? left + 1 : right + 1;
}

// ��
PNODE avltree::left(PNODE k2)
{
	// �Ȼ�ȡ�µĸ��ڵ�
	// 1. ����Ϊ��
	PNODE k1 = k2->RightChild;
	// 2. ���������
	k2->RightChild = k1->LeftChild;
	// 3. ��Ϊ����
	k1->LeftChild = k2;


	return k1;
}

// ��
PNODE avltree::right(PNODE k2)
{
	// �Ȼ�ȡ�µĸ��ڵ�
	// 1. ����Ϊ��
	PNODE k1 = k2->LeftChild;
	// 2. ���������
	k2->LeftChild = k1->RightChild;
	// 3. ��Ϊ����
	k1->RightChild = k2;

	return k1;
}

// ����
PNODE avltree::leftright(PNODE Node)
{
	Node->LeftChild = left(Node->LeftChild);

	return right(Node);
}

// ����

PNODE avltree::rightleft(PNODE Node)
{
	Node->RightChild = right(Node->RightChild);

	return left(Node);
}