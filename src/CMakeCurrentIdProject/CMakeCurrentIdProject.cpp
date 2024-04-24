// CMakeCurrentIdProject.cpp: 定义应用程序的入口点。
//

#include "CMakeCurrentIdProject.h"

using namespace std;

int current_id = 0;

struct Student
{
	Student(void) :id(current_id)
	{
		cout << " Student() id=" << id << endl;
		++current_id;
	}
	~Student()
	{
		cout << "~Student() id=" << id << endl;
	}
	int id = 0;
};

int main(void)
{
	//(1) your code. 
	// 提示创建对象之后，更早释放的办法之一就是使用大括号作用域（在大括号内创建对象）；
	// 或者使用动态内存手动管理决定何时释放

	Student s1;
	{
		Student s2;
		Student s3;
	}
	Student s4;

	return 0;
}