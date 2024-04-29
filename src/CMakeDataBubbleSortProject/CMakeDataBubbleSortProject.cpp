// CMakeDataBubbleSortProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataBubbleSortProject.h"

#include <iostream>
using namespace std;

void BubbleSort(int* arr, int n)
{
    for (int i = 0; i < n; i++) { // i-th pass
        for (int j = 1; j < n - i; j++) {
            if (arr[j - 1] > arr[j]) { // swap if out of order
                //(1) your code 
                // swap arr[j-1] and arr[j]

                int temp = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = arr[j - 1];
            }
        }
    }
}

int main()
{
    int n = 8;
    int* arr = new int[n] {49, 38, 65, 97, 76, 13, 27, 49};//申请8个int变量,并初始化

    //执行排序
    BubbleSort(arr, 8);

    //输出排序后的序列
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    delete[] arr;//释放动态数组需要用delete[]
    return 0;
}