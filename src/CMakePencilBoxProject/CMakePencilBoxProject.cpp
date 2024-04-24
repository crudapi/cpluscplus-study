// CMakePencilBoxProject.cpp: 定义应用程序的入口点。
//

#include "CMakePencilBoxProject.h"

using namespace std;

int current_pencil_box_id = 0;
int current_student_id = 0;

//文具盒
struct PencilBox
{
	PencilBox(void) :id(++current_pencil_box_id)
	{
		cout << "PencilBox() id=" << id << endl;
	}
	~PencilBox()
	{
		cout << "~PencilBox() id=" << id << endl;
	}
	int id = 0;
};
//学生
struct Student
{
	Student(void) :id(++current_student_id)
	{
		cout << "Student() id=" << id << endl;
	}
	~Student()
	{
		cout << "~Student() id=" << id << endl;
	}
	int id = 0;
	PencilBox m_pencilBox;
};

int main(void)
{
	cout << "main begin" << endl;
	//(1) your code. 
	// 提示创建对象之后，更早释放的办法之一就是使用大括号作用域（在大括号内创建对象）；
	// 或者使用动态内存手动管理决定何时释放

	Student s1;
	Student *s2 = new Student();
	delete s2;
	Student s3;

	cout << "main end" << endl;

	return 0;
}
