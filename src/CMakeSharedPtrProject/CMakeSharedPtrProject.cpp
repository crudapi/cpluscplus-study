// CMakeSharedPtrProject.cpp: 定义应用程序的入口点。
//

#include "CMakeSharedPtrProject.h"

#include <list>
#include <string>
using namespace std;

struct Student
{
	Student(const string& name, int age);
	Student(const Student& from);
	~Student();

	string m_name;
	int m_age;
};
Student::Student(const string& name, int age)
	:m_name(name), m_age(age)
{
	cout << "Student(" << m_name << ")" << endl;
}
Student::Student(const Student& from)
	:m_name("copy " + from.m_name), m_age(from.m_age)
{
	cout << "Student(" << m_name << ")" << endl;
}
Student::~Student()
{
	cout << "~Student(" << m_name << ")" << endl;
}
int main()
{
	shared_ptr<list<Student>> arrStudents = make_shared<list<Student>>();
	arrStudents->push_back(Student("Front Desk", 18));//容器都是值语义，放进去的是一个副本
	arrStudents->push_back(Student("Coder", 35));
	arrStudents->push_back(Student("Coder2", 35));
	arrStudents->push_back(Student("Boss", 85));

	return 0;
}