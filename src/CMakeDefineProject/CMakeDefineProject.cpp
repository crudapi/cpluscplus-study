// CMakeDefineProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDefineProject.h"

using namespace std;

struct Student
{
public:
	long long get_id(void);
	int get_age (void);
	void set_id(long long id);
	void set_age(int age);
	void test() { cout << endl << "test" << endl; };
private:
	long long m_id;
	int m_age;
};
// :: 是作用域操作符  Student:: 表示这是属于Student类（内）的
long long Student::get_id(void)
{
	return m_id;
}
int Student::get_age(void)
{
	return m_age;
}
void Student::set_id(long long id)
{
	m_id = id;
}
void Student::set_age(int age)
{
	m_age = age;
}


struct StudentConst
{
public:
	int get_age(void) const { return m_age;/*作者不小心准备谢顶了*/ }
private:
	int m_age = 18;//致我逝去的青春
};

int StudentConstDemo()
{
	StudentConst stu;
	cout << "My age is " << stu.get_age() << endl;

	return 0;
}

int main()
{
	Student student;
	student.set_id(2022092345);
	student.set_age(20);

	cout << "student info : id="
		<< student.get_id() << " age=" << student.get_age();

	student.test();

	StudentConstDemo();

	return 0;
}