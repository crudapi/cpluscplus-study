// CMakeDataStlSharedPtrProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataStlSharedPtrProject.h"

#include<memory>//shared_ptr 
using namespace std;

int main()
{
    //you get a heap int stored 123 for p
    shared_ptr<int> p(new int(123));

    //you do not need to delete something here,
    // and p will delete the heap int automatically

    return 0;
}