// 二叉树实现.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "二叉树.h"

int main()
{
	bstree tree;

	tree.insert(6);
	tree.show();
	tree.insert(3);
	tree.show();
	tree.insert(1);
	tree.show();
	tree.insert(4);
	tree.show();
	tree.insert(2);
	tree.show();
	tree.insert(7);
	tree.show();

	tree.erase(1);
	tree.show();
    return 0;
}

