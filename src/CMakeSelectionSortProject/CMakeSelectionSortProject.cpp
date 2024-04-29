// CMakeSelectionSortProject.cpp: 定义应用程序的入口点。
//

#include "CMakeSelectionSortProject.h"

using namespace std;
#include <iostream>
#include <cassert>
#include <vector>

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

//select the min element, return the index of the min element
int SelectMin(int* arr, int start, int total)
{
	int min = arr[start];
	int index = start;
	for (int i = start; i < total; ++i)
	{
		if (min > arr[i])
		{
			//(1) your code 筛选出最小值元素对应的下标
			min = arr[i];
			index = i;
		}
	}
	return index;
}

void SelectSort(int* arr, int n)
{
	for (int i = 0; i < n; i++) { //  i != min  =>  swap(arr[i], arr[min])
		int index = SelectMin(arr, i, n);
		if (index != i)
		{
			//(2) your code 将 arr[i] 和 arr[index] 交换
			Swap(arr[i], arr[index]);

		}
		print_array("one trip", arr, n);
	}
}

void test(vector<int> arr)
{
	//输出原始序列
	print_array("original array:", arr.data(), arr.size());
	//执行排序,并输出排序过程
	SelectSort(arr.data(), arr.size());
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
