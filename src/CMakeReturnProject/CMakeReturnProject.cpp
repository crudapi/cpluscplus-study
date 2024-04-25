// CMakeReturnProject.cpp: 定义应用程序的入口点。
//

#include "CMakeReturnProject.h"

#include <string>
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
    int age = 18;
};
Student test_function(void)
{//s在该函数被调用的时候创建，该函数执行完之后释放；但是最新版本的VS2022会延迟释放（如果返回值拿去用的话）
    cout << "flag2" << endl;
    Student stu;
    cout << "flag3" << endl;
    return stu;//如果你的Visual Studio 2022 升级到了最新版，这里不会执行拷贝构造，而是直接延迟析构，拿这个对象给外面的代码使用
}//s释放的时刻
int main()
{

    cout << "flag1" << endl;

    //最新版本的Visual Studio 2022 这里不会执行拷贝，copy 就是函数内的那个对象stu，没有创建新对象，就像copy是stu的引用一样
    auto copy = test_function();
    cout << "copy age = " << copy.age << endl;
    auto copy2(copy);//执行拷贝构造函数
    cout << "copy2 age = " << copy2.age << endl;

    cout << "flag4" << endl;



}