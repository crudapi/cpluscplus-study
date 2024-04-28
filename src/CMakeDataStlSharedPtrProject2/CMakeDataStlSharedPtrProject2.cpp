// CMakeDataStlSharedPtrProject2.cpp: 定义应用程序的入口点。
//

#include "CMakeDataStlSharedPtrProject2.h"

#include<iostream>
#include<memory>//shared_ptr 
using namespace std;

struct Student
{
    Student(void)
    {
        cout << "construct Student()" << endl;
    }
    ~Student(void)
    {
        cout << "destruct ~Student()" << endl;
    }
    int age = 123;
};
//pass by value
//copy constructor shared_ptr， reference count +1
void test_shared_ptr_copy(shared_ptr<Student> p)
{
    cout << "in function int : " << p->age << endl;
}//destructor shared_ptr , reference count -1

int main()
{
    cout << "main begin" << endl;

    //you get a heap int stored 123 for p
    shared_ptr<Student> p(new Student);

    //point to member
    cout << "int : " << p->age << endl;

    p->age = 456;

    cout << "int : " << p->age << endl;
    auto q = p;//copy constructor shared_ptr， reference count +1
    test_shared_ptr_copy(q);

    //you do not need to delete something here,
    // and p will delete the heap int automatically

    cout << "main end" << endl;

    return 0;
}