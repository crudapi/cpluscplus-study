// CMakeDataSharedPtrProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataSharedPtrProject.h"

#include <iostream>
using namespace std;

struct SharedPtr
{
    SharedPtr(int* source)
        :m_p(source), m_ptr_to_count(new int(1))
    {
    }
    SharedPtr(const SharedPtr& other)
        :m_p(other.m_p), m_ptr_to_count(other.m_ptr_to_count)
    {
        ++(*m_ptr_to_count);//所有共享地址的SharedPtr对象都得到了计数器的更新
    }
    ~SharedPtr()
    {
        cout << "now count = " << *m_ptr_to_count << endl;
        --(*m_ptr_to_count);

        if (*m_ptr_to_count == 0)
        {
            delete m_p;
            delete m_ptr_to_count;//最后一个持有者析构，计数器也要跟着一起被消灭
            cout << "all SharedPtr object is destroyed. now count == 0, release all heap memory." << endl;
        }
    }
    int* m_p = nullptr;
    int* m_ptr_to_count = nullptr;
};

void fun(SharedPtr p)//copy SharedPtr
{
    cout << "in fun , value=" << *p.m_p << ", count=" << *p.m_ptr_to_count << endl;
}

int main()
{
    SharedPtr ptr(new int(123));
    cout << "value=" << *ptr.m_p << ", count=" << *ptr.m_ptr_to_count << endl;

    auto ptr2 = ptr;//浅拷贝，哦吼！！两个对象会释放两次同一个地址
    cout << "value=" << *ptr2.m_p << ", count=" << *ptr2.m_ptr_to_count << endl;

    fun(ptr2);

    return 0;
}