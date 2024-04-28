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
        delete m_p;
    }
    int* m_p = nullptr;
};

int main()
{
    AutoPtr ptr(new int(123));
    cout << *ptr.m_p << endl;

    return 0;
}