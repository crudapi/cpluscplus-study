// CMakeGPAProject.cpp: 定义应用程序的入口点。
//

#include "CMakeGPAProject.h"

using namespace std;

void BubbleSort(int* arr, int n)
{
    for (int i = 0; i < n; ++i) {
        for (int j = 1; j < n - i; j++) {
            if (arr[j - 1] > arr[j]) { // swap if out of order
                //(1) your code 
                // swap arr[j-1] and arr[j]
                int t = arr[j - 1];
                arr[j - 1] = arr[j];
                arr[j] = t;
            }
        }


        //输出排序后的序列
        for (int i = 0; i < n; i++)
        {
            cout << arr[i] << " ";
        }
        cout << endl;
    }
}

int Sort()
{
    int n = 8;
    int* arr = new int[n] {49, 38, 65, 97, 76, 13, 27, 49};//申请8个int变量,并初始化
    //输出排序后的序列
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
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

int main()
{
    //10门课
    int course_number = 10;
    //10门课的考试分数
    int* score_list = new int[course_number] { 88, 95, 84, 89, 92, 79, 80, 96, 83, 80 };

    //10门课的学分
    int* credit_hour_list = new int[course_number] { 3, 4, 1, 3, 3, 2, 2, 4, 3, 3 };

    //累加课程学分绩点=课程学分绩点1+课程学分绩点2+...+课程学分绩点n
    double total_credit_hour_point = 0;

    for (int i = 0; i < course_number; i++)
    {
        //课程绩点=课程成绩/10 -5
        double grade_point = score_list[i] / 10.0 - 5;//注意这里整数通过除以浮点数结果转换成了浮点数
        //课程学分绩点
        double credit_hour_point = credit_hour_list[i] * grade_point;
        //累加课程学分绩点
        //(1) your code
        total_credit_hour_point += credit_hour_point;
    }

    //平均学分绩点
    //各门课学分之和 sum_credit_hour 
    int sum_credit_hour = 0;
    for (int i = 0; i < course_number; i++)
    {
        //(2) your code  //累加
        sum_credit_hour += credit_hour_list[i];
    }

    //平均学分绩点= 累加课程学分绩点/各门课学分之和
    double GPA = total_credit_hour_point / sum_credit_hour;

    cout << "李白的GPA = " << GPA << endl;

    //释放动态内存
    delete[] score_list;
    delete[] credit_hour_list;

    Sort();

    return 0;
}
