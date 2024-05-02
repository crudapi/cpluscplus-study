// CMakeJoinProject.cpp: 定义应用程序的入口点。
//

#include "CMakeJoinProject.h"

#include <thread>
#include <iostream>
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


int main(void)
{
    stdJoin();

    return 0;
}
