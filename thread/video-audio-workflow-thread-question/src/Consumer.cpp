#include "Consumer.h"
#include <iostream>
using namespace std;

void Consumer::receive(T data)
{
    m_queue.push(data);
    notify();//sent event, notify consumer data come, produce it now.
}

void Consumer::run_loop(void)
{
    cout << "Consumer::run_loop() begin run...." << endl;

    unique_lock<std::mutex> lock(m_mutex);
    while (!have_to_exit()/*(2) your code*/)
    {
        m_condition_var.wait(lock);
        //cout << "consumer received one event" << endl;

        lock.unlock();
        if (have_to_exit())
        {
            cout << "run loop break" << endl;
            break;//received exit_task_thread_loop
        }
        while (true)//produce message in loop until queue is empty.
        {
            lock.lock();
            if (m_queue.empty())
            {
                break;
            }
            else
            {
                auto front = m_queue.pop();
                consume_one(front);
            }
            lock.unlock();
        }
    }
    cout << "Consumer::run_loop() exited." << endl;
}
void ConsumerSet::push(T data)
{
    for (auto& consumer : m_consumer_set)
    {
        //(3) your code. every consumer received the data for consume the data.
        consumer->receive(data);
    }
}
void ConsumerSet::add_consumer(Consumer* c)
{
    lock_guard<mutex> lock(m_mutex_for_set);
    m_consumer_set.push_back(c);
}
void Pusher::push(T data)
{
    m_consumerSet.push(data);
}

void Pusher::add_consumer(Consumer* c)
{
    m_consumerSet.add_consumer(c);
}