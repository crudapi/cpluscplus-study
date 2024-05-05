// CMakeJoinProject.cpp: 定义应用程序的入口点。
//

#include "CMakeJoinProject.h"

#include <thread>
#include <iostream>
#include <windows.h>

using namespace std;

void thread_fun1(void)
{
    cout << "one STL thread 1!" << endl;
}

void thread_fun2(void)
{
    cout << "one STL thread 2!" << endl;
}

int stdJoin(void)
{
    std::thread thread1(thread_fun1);
    std::thread thread2(thread_fun2);

    thread1.join();
    thread2.join();

    return 0;
}

DWORD WINAPI ThreadFun1(LPVOID lpParamter)
{
    cout << "one Windows thread 1!" << endl;
    return 0;
}
DWORD WINAPI ThreadFun2(LPVOID lpParamter)
{
    cout << "one Windows thread 2!" << endl;
    return 0;
}

int winWait()
{
    HANDLE hThread1 = CreateThread(NULL, 0, ThreadFun1, NULL, 0, NULL);
    HANDLE hThread2 = CreateThread(NULL, 0, ThreadFun2, NULL, 0, NULL);

    HANDLE handleArr[] = { hThread1 , hThread2 };
    //等待两个线程结束
    WaitForMultipleObjects(2, handleArr, TRUE, INFINITE);

    CloseHandle(hThread1);
    CloseHandle(hThread2);

    return 0;
}



int main(void)
{
    stdJoin();

    winWait();

    return 0;
}
