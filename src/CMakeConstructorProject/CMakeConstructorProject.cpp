// CMakeConstructorProject.cpp: 定义应用程序的入口点。
//

#include "CMakeConstructorProject.h"

#include <iomanip>           // bool true false
using namespace std;

struct Student
{
    Student() { cout << "Student()" << endl; }//默认构造函数 default constructor
    Student(int age) { cout << "Student(" << age << ")" << endl; };//非默认构造函数
    Student(int age, bool sex) { cout << "Student(" << age << ", " << boolalpha << sex << ")" << endl; };//非默认构造函数
};

struct Student2
{
    Student2(int age) { cout << "Student(" << age << ")" << endl; };//非默认构造函数
    Student2(int age, bool sex) { cout << "Student(" << age << ", " << boolalpha << sex << ")" << endl; };//非默认构造函数
};

int Student2Demo()
{
    cout << "main begin" << endl;

    //Student2 stu1;//调用默认构造函数  类不再有默认构造函数，如果这一行执行的话，编译会报错
    Student2 stu2(10);//调用带一个整形参数的构造函数
    Student2 stu3(10, true);//调用两个参数的那个构造函数

    cout << "main end" << endl;

    return 0;
}

int main()
{
    cout << "main begin" << endl;

    Student stu1;//调用默认构造函数
    Student stu2(10);//调用带一个整形参数的构造函数
    Student stu3(10, true);//调用两个参数的那个构造函数

    cout << "main end" << endl;

    Student2Demo();

    return 0;
}