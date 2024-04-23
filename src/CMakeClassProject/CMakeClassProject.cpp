// CMakeClassProject.cpp: 定义应用程序的入口点。
//

#include "CMakeClassProject.h"

using namespace std;

struct Student1
{
    long long id;//学号
    string name;// 姓名
    int age;//年龄
};

//类的外部
struct Student
{//左花括号之后：类的内部（开始的地方）
public://这一行之后的代码都对类的外部公开，可以在main函数，或者其他函数内部访问下面的内容
    //成员函数的一对花括号内部也是类的内部
    long get_id(void) { return m_id; }//类的成员函数 get_id   
    int get_age(void) { return m_age; }//类的成函数get_age
    void set_id(long long id) { m_id = id; }//类的成员函数set_id
    void set_age(int age) { m_age = age; }//类的成员函数set_age
private://这一行之后的代码都不对类的外部公开，不可以在main函数，或者其他函数内部访问下面的内容
    long m_id;//类的成员变量m_id
    int m_age;//类的成员变量m_age
    //右花括号之前：类的内部（结束的地方）
};
//类的外部

//测试类对象在函数中使用是，哪些成员可以被访问
//这里也是类的外部
void test_class_fun(void)
{//这里也是类的外部
    Student stu;
    stu.get_age();//可以访问类的public成员
    //stu.m_age;//错误：编译不通过！ 类的外部不可以访问类的private成员！
//这里也是类的外部
}
int StudentDemo()
{//这里也是类的外部
    Student stu_zhang_san;
    stu_zhang_san.set_id(2022092345);//这里是类的外部，可以访问public成员函数set_id
    stu_zhang_san.set_age(20);//这里是类的外部，可以访问public成员函数set_age
    //类的外部，可以访问类的public成员函数get_id 和 get_age
    cout << "student infor : id=" << stu_zhang_san.get_id() << " age=" << stu_zhang_san.get_age();

    //测试类对象在函数中使用是，哪些成员可以被访问
    test_class_fun();

    return 0;
    //这里也是类的外部
}

int main(void)
{
    Student1 student1;
    student1.id = 2022092345;
    student1.name = "Newton";
    student1.age = 20;

    cout << "id = " << student1.id << endl;
    cout << "name = " << student1.name << endl;
    cout << "age = " << student1.age << endl;

    StudentDemo();

    return 0;//main end
}