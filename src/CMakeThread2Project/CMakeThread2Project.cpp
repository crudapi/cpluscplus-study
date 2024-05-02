// CMakeThread2Project.cpp: 定义应用程序的入口点。
//

#include "CMakeThread2Project.h"

#include <iostream>
#include <sstream>
#include <string>
#include <thread>
#include <chrono>
using namespace std;
using namespace chrono;
auto start = system_clock::now();
void print_elapsed(string msg)
{
    cout << msg << " at[" << duration_cast<milliseconds>(system_clock::now() - start).count() << "]" << endl;
}
void task_fun(int i)
{
    print_elapsed("task_fun " + to_string(i) + " start!");
    // simulate expensive operation
    this_thread::sleep_for(seconds(i));
    print_elapsed("task_fun " + to_string(i) + " finished!");
}
int main()
{
    print_elapsed("main begin...");

    thread task9(task_fun, 9);//线程这时候就已经开始启动
    thread task6(task_fun, 6);//线程这时候就已经开始启动

    task9.join();//main第一次阻塞，给前面的线程机会执行到各自打印的语句
    print_elapsed("task9.join() finished");//第9秒钟之后，main终于等到了task1的退出，在这之前task3(第3秒执行完毕)，task2(第6秒),执行完毕
    task6.join();//这里不会有阻塞，因为在第6秒的时候task2就已经退出了
    print_elapsed("task6.join() finished");

    print_elapsed("all tasks to finished.");
}