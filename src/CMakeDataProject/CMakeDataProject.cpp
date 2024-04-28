// CMakeDataProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataProject.h"

#include <iostream>
using namespace std;

struct AutoPtr
{
    AutoPtr(int* source) :m_p(source)
    {
    }
    ~AutoPtr()
    {
        cout << "autoPtr" << endl;
        delete m_p;
    }
    int* m_p = nullptr;
};

int main()
{
    AutoPtr ptr(new int(123));
    cout << *ptr.m_p << endl;

    auto ptr2 = ptr;//浅拷贝，哦吼！！两个对象会释放两次同一个地址
    cout << *ptr2.m_p << endl;

}