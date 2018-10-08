#pragma once
#include <cstdio>

// �ڵ�Ķ���
typedef struct NODE
{
	int Element;
	NODE *LeftChild;
	NODE *RightChild;
}NODE, *PNODE;

// ����������
class bstree
{
public:
	// ʹ��Ĭ�ϵĹ��캯��
	bstree() = default;
	~bstree() = default;

	// �ṩ���û���Ĳ���ӿ�
	PNODE insert(int Elem)
	{
		return insert(RootNode, Elem);
	}

	// ������ɾ��һ���ڵ㣬���ر�����Ľڵ�
	PNODE erase(int Elem)
	{
		return erase(RootNode, Elem);
	}

	// �ṩ���û��������ӿ�
	void show()
	{
		show(RootNode, 0, '*');
		printf("------------------\n");
	}

	// �ṩ���û����ǰ�����
	void Pre()
	{
		Pre(RootNode);
		printf("\n");
	}

	// �ṩ���û�����������
	void Mid()
	{
		Mid(RootNode);
		printf("\n");
	}

	// �ṩ���û���ĺ������
	void Rear()
	{
		Rear(RootNode);
		printf("\n");
	}

	// �ṩ���û���Ĳ������
	void Level()
	{
		Level(RootNode);
		printf("\n");
	}

private:
	// �����ǰ���Ľڵ�
	// ����2�����
	// ����3�����ӷ���
	void show(PNODE Node, int w, char c);
	
	//�����в���һ���ڵ㣬���ر�����Ľڵ�
	PNODE insert(PNODE &Node, int Elem);

	// ������ɾ��һ���ڵ㣬���ر�����Ľڵ�
	PNODE erase(PNODE &Node, int Elem);

	// �����в�����Сֵ
	int min(PNODE Node);

	// �����в������ֵ
	int max(PNODE Node);

	// ǰ�����
	void Pre(PNODE Node);

	// �������
	void Mid(PNODE Node);

	// �������
	void Rear(PNODE Node);

	// �������
	void Level(PNODE Node);


private:
	PNODE RootNode = nullptr; // ָ����ڵ��ָ��
};
