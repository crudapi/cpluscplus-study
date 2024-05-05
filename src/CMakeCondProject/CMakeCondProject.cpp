// CMakeCondProject.cpp: 定义应用程序的入口点。
//

#include "CMakeCondProject.h"

// condition_variable::notify_one
#include <iostream>           // std::cout
#include <thread>             // std::thread
#include <mutex>              // std::mutex, std::unique_lock
#include <condition_variable> // std::condition_variable
#include <chrono>             //milliseconds
using namespace std;
using namespace chrono;

std::mutex mutex1;
std::condition_variable event;

void thread_sender_fun(void)
{
    while (true)
    {
        cout << "1";
        event.notify_one();
        this_thread::sleep_for(milliseconds(1));
    }
}

void thread_receiver_fun()
{
    while (true)
    {
        std::unique_lock<std::mutex> lock(mutex1);
        event.wait(lock);
        cout << "2";
    }
}

int main()
{
    std::thread thread_sender(thread_sender_fun);
    std::thread thread_receiver(thread_receiver_fun);

    // join them back:
    thread_sender.join();
    thread_receiver.join();

    return 0;
}