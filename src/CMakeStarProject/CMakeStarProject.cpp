// CMakeStarProject.cpp: 定义应用程序的入口点。
//

#include "CMakeStarProject.h"

#include <thread>
#include <iostream>
using namespace std;

void thread_fun1(void)
{
    while (true)
    {
        cout << "1";
    }
}
void thread_fun2(void)
{
    while (true)
    {
        cout << "2";
    }
}

int main(void)
{
    std::thread thread1(thread_fun1);
    std::thread thread2(thread_fun2);
    thread1.join();
    thread2.join();

    return 0;
}