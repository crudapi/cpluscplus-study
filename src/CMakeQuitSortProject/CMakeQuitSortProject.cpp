// CMakeQuitSortProject.cpp: 定义应用程序的入口点。
//

#include "CMakeQuitSortProject.h"

#include <iostream>
#include <cassert>
#include <vector>
using namespace std;

void print_array(const char* msg, int* arr, int n)
{
	cout << msg << " ";
	for (int i = 0; i < n; i++)
	{
		cout << arr[i] << " ";
	}
	cout << endl;
}
//swap two number
void Swap(int& a, int& b)
{
	int tmp = a; a = b; b = tmp;
}

//返回数组中间位置的元素作为划分的标的值
int FindPivot(int* arr, int from, int to)
{
	return (from + to) / 2;
}
int Partition(int* arr, int l, int r, int pivot)
{
	do
	{
		cout << "[" << l << "]" << ", [" << r << "]"<< endl;
		//在左半边找到第一个大于标的的值（将来放到右边）
		while (arr[++l] < pivot) {};
		//在右半边找到第一个小于标的的值（将来放到左边）
		while (r != 0 && arr[--r] > pivot) {}
		//左右两个（逆序）值交换
		cout << "arr[" << l << "] = " << arr[l] << ", arr[" << r << "] = " <<  arr[r] << endl;
		Swap(arr[l], arr[r]);
	} while (l < r);
	Swap(arr[l], arr[r]);

	return l;
}
void QuickSort(int* arr, int i, int j)
{
	if (j <= i) {
		return;
	}
	int pivot_index = FindPivot(arr, i, j);
	//把标的值放到数组末尾，将来再放回
	Swap(arr[pivot_index], arr[j]);
	//将左右两侧通过一次划分，划分成左侧的所有值小于标的值，右侧的值都大于标的值
	int k = Partition(arr, i - 1, j, arr[j]);

	print_array("QuickSort:", arr, 10);

	//把标的值放回来
	Swap(arr[k], arr[j]);
	//递归对左侧区间执行同样的过程
	QuickSort(arr, i, k - 1);
	//递归对右侧区间执行同样的过程
	QuickSort(arr, k + 1, j);
}

void test(vector<int> arr)
{
	//输出原始序列
	print_array("original array:", arr.data(), arr.size());
	//执行排序,并输出排序过程
	QuickSort(arr.data(), 0, arr.size() - 1);
	//输出排序后的列表
	print_array("after sorted:", arr.data(), arr.size());
	cout << endl;
}

int main()
{
	test({ 1 });
	test({ 1 , 2 });
	test({ 2 , 1 });
	test({ 2 , 2 });
	test({ 42, 20, 17, 13, 28, 14, 23, 15 });
	test({ 1, 8, 3, 6, 5, 4, 7, 2 , 9 });
	test({ 8, 8, 6, 6, 7, 5, 5, 7, 9 , 9 });
	test({ 72, 6, 57, 88, 60, 42, 83, 73, 48, 85 });
	return 0;
}