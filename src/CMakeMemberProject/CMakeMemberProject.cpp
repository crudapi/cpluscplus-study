// CMakeMemberProject.cpp: 定义应用程序的入口点。
//

#include "CMakeMemberProject.h"

#include <iostream>
using namespace std;

struct Student
{
    //默认构造函数 default constructor
    Student() { cout << "Student()" << endl; };
    //非默认构造函数，给m_age成员初始化
    Student(int age) :m_age(age) { cout << "Student(" << m_age << ")" << endl; };
    //非默认构造函数,给两个成员变量初始化
    Student(int age, bool sex) :m_age(age), m_sex(sex)
    {
        cout << "Student(" << m_age << ", " << boolalpha << sex << ")" << endl;
    };
    //非默认构造函数,给3个成员变量初始化
    Student(string name, int age, bool sex) :m_name(name), m_age(age), m_sex(sex)
    {
        cout << "Student(" << name << "," << m_age << ", " << boolalpha << sex << ")" << endl;
    };

private:
    string m_name;//姓名
    int m_age;//年龄
    bool m_sex;//性别
};

int main()
{
    Student stu1;//调用默认构造函数
    Student stu2(10);//调用带一个整形参数的构造函数
    Student stu3(10, true);//调用两个参数的那个构造函数
    Student stu4("ZhangFei", 10, true);//调用3个参数的那个构造函数

    return 0;
}