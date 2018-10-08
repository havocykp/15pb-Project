// 平衡二叉树.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "AVL.h"

int main()
{
	avltree tree;


	tree.insert(6);
	tree.show();
	tree.insert(3);
	tree.show();
	tree.insert(1);
	tree.show();
	tree.insert(4);
	tree.show();
	tree.insert(7);
	tree.show();
	tree.insert(8);
	tree.show();

	tree.erase(8);
	tree.show();

	tree.erase(7);
	tree.show();
	// 
	// 	tree.Pre();
	// 	tree.Mid();
	// 	tree.Rear();
	// 	tree.Level();

    return 0;
}

