// 树.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

// 阶乘
long fac(long num)
{
	long temp = 1;
	for (int i = 1; i <= num; ++i) {
		temp *= i;
	}

	return temp;
}

// 递归--阶乘
long facii(long num)
{
	if (num <= 1)
		return 1;
	else
		return num * facii(num - 1);
}

// 二分查找---有序
int binary_search(int *arr, int v, int min, int max)
{
	// 中间值
	int mid = min + (max - min) / 2;

	// 如果没有找到
	if (min > max) {
		return -1;
	}

	// 当前找到的较大
	if (arr[mid] > v)
		return binary_search(arr, v, min, mid - 1);

	// 当前找到的较小
	else if (arr[mid] < v)
		return binary_search(arr, v, mid + 1, max);

		// 找到
	else
		return mid;
}

// 交换
void swap(int v[], int i, int j)
{
	int temp;

	temp = v[i];
	v[i] = v[j];
	v[j] = temp;
}

// 快速排序
void qsort(int v[], int left, int right)
{
	int i, last;
	void swap(int v[], int i, int j);

	if (left >= right)
		return;
	swap(v, left, (left + right) / 2);
	last = left;
	for (i = left + 1; i <= right; ++i)
		if (v[i] < v[left])
			swap(v, ++last, i);
	swap(v, left, last);
	qsort(v, left, last - 1);
	qsort(v, last + 1, right);
}


int main()
{
	



    return 0;
}

