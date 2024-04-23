// CMakeClassProject.cpp: 定义应用程序的入口点。
//

#include "CMakeClassProject.h"

using namespace std;

struct Student
{
    long long id;//学号
    string name;// 姓名
    int age;//年龄
};

int main(void)
{
    Student student;
    student.id = 2022092345;
    student.name = "Newton";
    student.age = 20;

    cout << "id = " << student.id << endl;
    cout << "name = " << student.name << endl;
    cout << "age = " << student.age << endl;


    return 0;//main end
}