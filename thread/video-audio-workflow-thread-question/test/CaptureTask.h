#pragma once
#include "Task.h"
#include "Producer.h"
#include "Data.h"
#include <iostream>
using namespace std;

struct CaptureTask : public Producer
{
    CaptureTask(int total_count):m_total_count_have_to_capture(total_count)
    {
        cout << "CaptureTask()" << endl;
    }
    ~CaptureTask()
    {
        cout << "~CaptureTask()" << endl;
    }
    void produce_one(void) override
    {
        captured_frame_count++;
        Producer::push(std::shared_ptr<Data>(new Data(captured_frame_count)));
        cout << "produce_one " << captured_frame_count << endl;
        if (captured_frame_count > m_total_count_have_to_capture)
        {
            exit_task_thread_loop();
            return;
        }
        // 发送数据到 packet 队列
        this_thread::sleep_for(std::chrono::milliseconds(1));
    }
private:
    int m_total_count_have_to_capture = 90;
    int captured_frame_count = 0;
    int fps;
};