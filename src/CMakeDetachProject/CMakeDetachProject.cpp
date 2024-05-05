// CMakeDetachProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDetachProject.h"

#include <iostream>
#include <thread>
#include <chrono>
using namespace std;
using namespace std::chrono;

void record()
{
    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(11));
    cout << "record finished!" << endl;
}

void ui_fun()
{
    std::cout << "starting record ...\n";
    std::thread record_thread(record);
    record_thread.detach();

    // simulate expensive operation
    std::this_thread::sleep_for(std::chrono::seconds(5));
    cout << "ui_fun finished!" << endl;
}

int main()
{
    auto start = std::chrono::system_clock::now();

    std::cout << "starting ui_fun ...\n";
    std::thread helper1(ui_fun);

    std::cout << "waiting for ui_fun to finish..." << std::endl;
    helper1.join();

    auto elapsed = chrono::duration_cast<chrono::seconds>(system_clock::now() - start).count();
    std::cout << "done! elapsed " << elapsed << " seconds.";
}