// CMakeStuProject.cpp: 定义应用程序的入口点。
//

#include "CMakeStuProject.h"

using namespace std;

struct Student
{
    int get_age() { return m_age; }
    void set_age(int age) { m_age = age; }

    string m_name;
private:
    int m_age;
};

int main()
{
    Student* stu = new Student;
    stu->m_name = "zhangsan";
    stu->set_age(18);

    cout << "My name is " << stu->m_name
        << ", I'm " << stu->get_age() << " years old." << endl;

    (*stu).set_age(28);

    cout << "My name is " << stu->m_name
        << ", I'm " << stu->get_age() << " years old." << endl;

    return 0;
}