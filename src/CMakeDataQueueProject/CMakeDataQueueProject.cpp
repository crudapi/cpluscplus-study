// CMakeDataQueueProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataQueueProject.h"

#include <iostream>
#include <iomanip>
#include <list>
using namespace std;
 
//------下面的代码是用来测试你的代码有没有问题的辅助代码，你无需关注------
#include <algorithm>
#include <cstdlib>
#include <iostream> 
#include <vector>
#include <utility>
using namespace std;
struct Record { Record(void* ptr1, size_t count1, const char* location1, int line1, bool is) :ptr(ptr1), count(count1), line(line1), is_array(is) { int i = 0; while ((location[i] = location1[i]) && i < 100) { ++i; } }void* ptr; size_t count; char location[100] = { 0 }; int line; bool is_array = false; bool not_use_right_delete = false; }; bool operator==(const Record& lhs, const Record& rhs) { return lhs.ptr == rhs.ptr; }std::vector<Record> myAllocStatistic; void* newFunctionImpl(std::size_t sz, char const* file, int line, bool is) { void* ptr = std::malloc(sz); myAllocStatistic.push_back({ ptr,sz, file, line , is }); return ptr; }void* operator new(std::size_t sz, char const* file, int line) { return newFunctionImpl(sz, file, line, false); }void* operator new [](std::size_t sz, char const* file, int line)
{
    return newFunctionImpl(sz, file, line, true);
}void operator delete(void* ptr) noexcept { Record item{ ptr, 0, "", 0, false }; auto itr = std::find(myAllocStatistic.begin(), myAllocStatistic.end(), item); if (itr != myAllocStatistic.end()) { auto ind = std::distance(myAllocStatistic.begin(), itr); myAllocStatistic[ind].ptr = nullptr; if (itr->is_array) { myAllocStatistic[ind].not_use_right_delete = true; } else { myAllocStatistic[ind].count = 0; }std::free(ptr); } }void operator delete[](void* ptr) noexcept { Record item{ ptr, 0, "", 0, true }; auto itr = std::find(myAllocStatistic.begin(), myAllocStatistic.end(), item); if (itr != myAllocStatistic.end()) { auto ind = std::distance(myAllocStatistic.begin(), itr); myAllocStatistic[ind].ptr = nullptr; if (!itr->is_array) { myAllocStatistic[ind].not_use_right_delete = true; } else { myAllocStatistic[ind].count = 0; }std::free(ptr); } }
#define new new(__FILE__, __LINE__)
struct MyStruct { void ReportMemoryLeak() { std::cout << "Memory leak report: " << std::endl; bool leak = false; for (auto& i : myAllocStatistic) { if (i.count != 0) { leak = true; std::cout << "leak count " << i.count << " Byte" << ", file " << i.location << ", line " << i.line; if (i.not_use_right_delete) { cout << ", not use right delete. "; }	cout << std::endl; } }if (!leak) { cout << "No memory leak." << endl; } }~MyStruct() { ReportMemoryLeak(); } }; static MyStruct my; void check_do(bool b, int line = __LINE__) { if (b) { cout << "line:" << line << " Pass" << endl; } else { cout << "line:" << line << " Ohh! not passed!!!!!!!!!!!!!!!!!!!!!!!!!!!" << " " << endl; exit(0); } }
#define check(msg)  check_do(msg, __LINE__);
//------上面的代码是用来测试你的代码有没有问题的辅助代码，你无需关注------
 
class Queue
{
public:
    const int& first(void) const;
    bool empty(void) const;
    size_t size(void) const;
    void enqueue(const int& _item);
    void dequeue(void);
    void clear(void);
private:
    //使用双链表实现队列
    std::list<int> m_queue;
};
 
const int& Queue::first(void) const
{
    return m_queue.front();
}
 
bool Queue::empty(void) const
{
    return m_queue.empty();
}
 
void Queue::clear(void)
{
    m_queue.clear();
}
 
size_t Queue::size(void) const
{
    return m_queue.size();
}
 
void Queue::enqueue(const int& _item)
{
    m_queue.push_back(_item);
}
 
void Queue::dequeue(void)
{
    m_queue.pop_front();
}
 
int main(int argc, char** argv)
{
    //test clear
    {
        Queue s;
        check(s.size() == 0);
        check(s.empty());
        s.enqueue(1);
        check(s.size() == 1);
        check(s.empty() == false);
        s.clear();
        check(s.size() == 0);
        check(s.empty());
    }
    //test first
    {
        Queue q;
        check(q.size() == 0);
        q.enqueue(1);
        check(q.size() == 1);
        auto q2 = q;
        check(q2.size() == 1);
        q = q2;
        q.enqueue(2);
        auto first = q2.first();
        check(first == 1);
        check(q.size() == 2);
        check(q.first() == 1);
        q.clear();
        check(q.size() == 0 && q.empty());
    }
    //test enqueue dequeue
    {
        Queue q;
        for (size_t i = 0; i < 10; i++)
        {
            q.enqueue(i);
        }
        int i = 0;
        while (!q.empty())
        {
            check(q.first() == i++)
                q.dequeue();
        }
        check(q.size() == 0 && q.empty());
    }
}