// CMakeSenderEventProject.cpp: 定义应用程序的入口点。
//

#include "CMakeSenderEventProject.h"

#include <windows.h>
#include <iostream>
using namespace std;

HANDLE event;//事件对象

DWORD WINAPI sender_event_thread_fun(LPVOID lpParam)
{
    while (true)
    {
        cout << "1";//干活
        SetEvent(event);//发出写完成信号，通知另一个线程该打印2了
        Sleep(1);
    }
    return 0;
}

DWORD WINAPI receive_event_thread_fun(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    while (true)
    {
        DWORD dwWaitResult = WaitForSingleObject(event, INFINITE);// 等待信号，无限等待
        cout << "2";//干活
    }
    return 0;
}

int main(void)
{
    event = CreateEvent(NULL,
        //是否需要人工ResetEvent重置为无信号状态：
        //是：当该事件为有信号状态时，所有等待该信号的线程都变为可调度线程。
        //      并且，需要手动调用ResetEvent为无信号状态；
        //否：当该事件为有信号状态时，只有一个线程变为可调度线程。
        //      并且，系统自动调用ResetEvent将该对象设置为无信号状态。(一次性的信号)
        FALSE,
        FALSE,//初始状态:无信号状态
        TEXT("WriteFinishedEvent")// 事件对象名称
    );

    //创建线程
    HANDLE thread_sender = CreateThread(NULL, 0, sender_event_thread_fun, NULL, 0, NULL);
    HANDLE thread_receive = CreateThread(NULL, 0, receive_event_thread_fun, NULL, 0, NULL);

    HANDLE handleArr[] = { thread_sender , thread_receive };

    //等待线程执行结束
    WaitForMultipleObjects(2, handleArr, TRUE, INFINITE);

    //释放资源
    CloseHandle(thread_sender);
    CloseHandle(thread_receive);
    CloseHandle(event);

    return 0;
}