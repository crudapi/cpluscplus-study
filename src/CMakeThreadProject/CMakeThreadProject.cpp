// CMakeThreadProject.cpp: 定义应用程序的入口点。
//

#include "CMakeThreadProject.h"
#include <windows.h>
#include <thread>
#include <iostream>
using namespace std;

void thread_fun(void)
{
    cout << "one STL thread!" << endl;
}

DWORD WINAPI ThreadFun(LPVOID lpParamter)
{
    cout << "one Windows thread!" << endl;
    return 0;
}

int stlThread(void)
{
    std::thread thread1(thread_fun);
    thread1.join();
    return 0;
}

int winThread()
{
    HANDLE hThread = CreateThread(NULL, 0, ThreadFun, NULL, 0, NULL);

    //等待线程执行结束
    WaitForSingleObject(hThread, INFINITE);

    CloseHandle(hThread);

    return 0;
}

int main(void)
{
    winThread();
}