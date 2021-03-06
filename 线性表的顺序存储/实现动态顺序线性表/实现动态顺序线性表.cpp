// 实现动态顺序线性表.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "动态线性表.h"


int main()
{
	CMyVector myvector;
	int nErr;

	myvector.initVector(nErr);
	myvector.push_back(1, nErr);
	myvector.push_back(2, nErr);
	myvector.push_back(3, nErr);
	myvector.push_back(4, nErr);
	myvector.push_back(5, nErr);
	myvector.push_back(6, nErr);
	
	int nEle;
	myvector.pop_back(nEle, nErr);
	myvector.at(2, nEle, nErr);

	int maxLen;
	myvector.max_size(maxLen, nErr);

	myvector.insert(3, 4, 2, nErr); // 在下标为3的地方插入4个2
	myvector.insertEx(1, 4, 5, nErr); // 从下标1开始到4，插入元素5

	
    return 0;
}

