// CMakeOperatorProject.cpp: 定义应用程序的入口点。
//

#include "CMakeOperatorProject.h"

using namespace std;


class Student {
public:
	Student(int age): m_age(new int(age)){
		cout << "Student." << endl;
	}
	Student& operator=(const Student& stuFrom);
private:
	int* m_age;//指针成员：管理动态内存
};
Student& Student::operator=(const Student& stuFrom) {
	if (this == &stuFrom)//自己赋值给自己，直接返回自己
	{
		return *this;
	}
	*m_age = *stuFrom.m_age;//深拷贝，将存储的数据拷贝，而不是直接地址拷贝
	return *this;
}

int main()
{
	cout << "Hello CMake." << endl;
	Student s1(1);
	Student s2(2);

	s2 = s1;

	return 0;
}
