// 线性表的顺序存储.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "线性表.h"

int _tmain(int argc, _TCHAR* argv[])
{
	CMyTemplateArray<int> myArray;
	int nError;
	myArray.initArray(nError);

	myArray.insertEleByIndex(1, 1, nError); // 在错误位置插入
	myArray.insertEleByIndex(0, 2, nError);
	myArray.insertEleByIndex(1, 3, nError);
	myArray.insertEleByIndex(2, 4, nError);
	myArray.insertEleByIndex(3, 5, nError);
	myArray.insertEleByIndex(4, 6, nError);
	myArray.insertEleByIndex(2, 7, nError);

	int nEle;
	myArray.delEleByIndex(9, nEle, nError); // 使用错误下标删除

	nEle = 100;
	myArray.delEleByValue(nEle, nError);  // 使用错误值删除

	myArray.delEleByIndex(5, nEle, nError);

	nEle = 4;
	myArray.delEleByValue(nEle, nError);
	int nLen;
	myArray.getLength(nLen, nError);
	myArray.getEleByIndex(2, nEle, nError);

	int index = -1;
	myArray.getEleByValue(index, nEle, nError);

	myArray.clearArray(nError);

	return 0;
}

