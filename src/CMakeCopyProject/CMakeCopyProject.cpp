// CMakeCopyProject.cpp: 定义应用程序的入口点。
//

#include "CMakeCopyProject.h"

using namespace std;

class Student
{
public:
    Student(const Student& from)//拷贝构造函数
    {
        cout << "copy constructor called." << endl;
    }
    //如果只提供上面的拷贝构造函数，编译器就不再生成默认构造函数
    //，会而导致类对象就不可以直接创建，所以还需要提供一个默认构造函数
    Student(void)
    {
        cout << "default constructor called." << endl;
    }
    Student(const string& name) :m_name(name)
    {
        cout << "string constructor called." << endl;
    }
    string m_name;//存放学生姓名
};
void test_function(Student s)
{//s在该函数被调用的时候创建，该函数执行完之后释放
    cout << "flag2" << endl;
    s.m_name = "李四";//修改s的名字
    cout << "flag3" << endl;
}//s释放的时刻
int main()
{
    cout << "flag0" << endl;
    Student stu("张三");
    cout << "flag1" << endl;
    test_function(stu);//(1)创建stu的副本，函数内使用副本
    cout << "flag4" << endl;
    cout << stu.m_name;//还是输出“张三”，因为修改的是，函数内的副本
}