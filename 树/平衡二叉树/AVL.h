#pragma once
#include <cstdio>

// �ڵ�Ķ���
typedef struct NODE
{
	int Element;
	NODE *LeftChild;
	NODE *RightChild;
} NODE, *PNODE;

class avltree
{
private:
	// ָ����ڵ��ָ��
	PNODE RootNode = nullptr;

private:
	// �����ǰ���Ľڵ�
	void show(PNODE Node, int w, char c);

	// �����в���һ���ڵ㣬���ر�����Ľڵ�
	PNODE insert(PNODE &Node, int Elem);

	// ������ɾ��һ���ڵ㣬���ر�����Ľڵ�
	PNODE erase(PNODE &Node, int Elem);

	// �����ֲ�����Сֵ
	int min(PNODE Node);

	// �����в������ֵ
	int max(PNODE Node);

	// ǰ�������
	void Pre(PNODE Node);

	// ���������
	void Mid(PNODE Node);

	// ���������
	void Rear(PNODE Node);

	// �������
	void Level(PNODE Node);

	// ��ȡ���ĸ߶�
	int high(PNODE Node);

	// ��
	PNODE left(PNODE Node);

	// ��
	PNODE right(PNODE Node);

	// ����
	PNODE leftright(PNODE Node);

	// ����

	PNODE rightleft(PNODE Node);

public:
	// ʹ��Ĭ�ϵĹ������������
	avltree() = default;
	~avltree() = default;

	// �ṩ���û���Ĳ���ӿ�
	PNODE insert(int Elem)
	{
		return insert(RootNode, Elem);
	}

	// �����в���һ���ڵ㣬���ر�����Ľڵ�
	PNODE erase(int Elem)
	{
		return erase(RootNode, Elem);
	}

	// �ṩ���û��������ӿ�
	void show()
	{
		show(RootNode, 0, '*');
		printf("-----------------\n");
	}

	//  �ṩ���û����ǰ�����
	void Pre()
	{
		Pre(RootNode);
		printf("\n");
	}
	//  �ṩ���û�����������
	void Mid()
	{
		Mid(RootNode);
		printf("\n");
	}

	//  �ṩ���û���ĺ������
	void Rear()
	{
		Rear(RootNode);
		printf("\n");
	}

	//  �ṩ���û���Ĳ������
	void Level()
	{
		Level(RootNode);
		printf("\n");
	}
};

