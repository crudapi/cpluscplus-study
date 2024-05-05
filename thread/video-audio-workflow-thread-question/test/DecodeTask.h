#pragma once
#include "Consumer.h"
#include "Data.h"

struct DecodeTask : public Consumer
{
    DecodeTask() { cout << "DecodeTask()" << endl; }
    ~DecodeTask();
    void consume_one(T packet) override;
}; 

DecodeTask::~DecodeTask()
{
    cout << "~DecodeTask()" << endl;
}

void DecodeTask::consume_one(T packet)
{
    cout <<get_name() <<" decode " <<packet->id<< endl;
}