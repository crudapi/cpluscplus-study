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
	Student s1;
	Student s2;
	Student s3;

	return 0;
}