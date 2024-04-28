// CMakeDataStlSharedPtrProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataStlSharedPtrProject.h"

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
};

int main()
{
    {
        Student* s = new Student;
    }
    cout << "main begin" << endl;

    //you get a heap Student hold by p
    shared_ptr<Student> p(new Student);

    shared_ptr<Student> p2 = p;

    //you do not need to delete something here,
    // and p will delete the heap int automatically

    cout << "main end" << endl;

    

    return 0;
}
