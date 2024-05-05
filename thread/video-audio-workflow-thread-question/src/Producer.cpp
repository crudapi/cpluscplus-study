#include "Producer.h"
#include <iostream>
using namespace std;

void Producer::run_loop(void)
{
    cout << "ProduceTask::process() begin run...." << endl;
    while (!have_to_exit())
    {
        produce_one();
    }
    cout << "ProduceTask::process() exited." << endl;
}


