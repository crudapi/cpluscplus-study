// CMakeDataInsertProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataInsertProject.h"

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

//将newValue插入到子数组arr中，arr的长度为length
void Insert(int* arr, int newValueindex, int newValue)
{
	// newValueindex=1     {arr[0]}    <== arr[1]           
	// newValueindex=2     {arr[0], arr[1]}    <== arr[2]
	// ......
	// newValueindex=n-1   {arr[0], arr[1],... arr[n-2]}    <== arr[n-1]

	// [a,   b,   c,   d]    e
	//  0              j     length   

	int j = newValueindex - 1;
	for (; j >= 0; j--)
	{
		if (arr[j] > newValue)
		{
			//move arr[j] to the next position,for newVaule
			arr[j + 1] = arr[j];
		}
		else
		{
			break;//break 发生时， j 的值可能是 0
		}
	}
	//发生了移动，j会停止在最后一个需要被移动的位置的前面一个位置
	if (j != newValueindex - 1)
	{
		arr[j + 1] = newValue;
	}
}

void InsertSort(int* arr, int n)
{
	if (n <= 1)
	{
		return;
	}
	//将下标为1的元素插入到{arr[0]}中
	//将下标为2的元素插入到{arr[0], arr[1]}中
	//......
	//将下标为n-1的元素插入到{arr[0], arr[1], arr[n-2]}中
	for (int i = 1; i < n; i++)
	{
		//将未排序序列中的第一个元素插入到已排序的序列中
		Insert(arr, i, arr[i]);//insert first element in unsorted list to the sorted list
		print_array("one trip", arr, n);
	}
}

void test(vector<int> arr)
{
	//输出原始序列
	print_array("original array:", arr.data(), arr.size());
	//执行排序,并输出排序过程
	InsertSort(arr.data(), arr.size());
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
	return 0;
}
