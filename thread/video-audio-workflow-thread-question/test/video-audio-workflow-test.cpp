// video-audio-workflow.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include "CaptureTask.h"
#include "DecodeTask.h"

int main()
{
    CaptureTask capture_task(90);
    capture_task.set_name("capture_task");

    DecodeTask decode_task;
    decode_task.set_name("decode_task");

    DecodeTask decode_task2;
    decode_task2.set_name("decode_task2");

    capture_task.add_consumer(&decode_task);
    capture_task.add_consumer(&decode_task2);
    decode_task.start();
    decode_task2.start();
    capture_task.start();

    cout << "wait user cin to exit main =========>" << endl;
    string s;
    getline(cin, s);
}

