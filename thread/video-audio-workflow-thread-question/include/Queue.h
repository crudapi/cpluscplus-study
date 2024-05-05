#pragma once
#include "Data.h"
#include <list>
#include <mutex>
using namespace std;

class SyncQueue
{
public:
    void push(T data);
    T pop(void);
    bool empty(void) const;
private:
    list<T> m_data_queue;
    mutex m_mutex;
};

inline void SyncQueue::push(T data)
{
    lock_guard<mutex> lock(m_mutex);
    m_data_queue.push_back(data);
}

inline T SyncQueue::pop(void)
{
    //(1) your code



    return T();
}

inline bool SyncQueue::empty(void) const
{
    return m_data_queue.empty();
}
