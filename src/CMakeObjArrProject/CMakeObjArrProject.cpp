// CMakeObjArrProject.cpp: 定义应用程序的入口点。
//

#include "CMakeObjArrProject.h"
#include <string>

using namespace std;

//定义学生类
struct Student
{
	int age;//学生的年龄
	string name;//学生的姓名
};
//参数 stu 是数组的第一个元素的地址
//通过地址来访问第一个学生（这很直观）
//通过这个地址偏移一段距离（一个学生对象所占字节数）来访问后面的一个学生
//stu+1 得到后面的一个学生的地址
//对 stu+1解引用得到后面的一个学生对象的引用
//也就是 *(stu+1)
//同样的 等价简洁写法为 stu[1]  参考：https://zhuanlan.zhihu.com/p/659538644
//类似的，得到后面第i个学生对象 stu[i]
void InitStudentArray(Student* stu, int totalStudent)
{
	for (int i = 0; i < totalStudent; ++i)
	{
		stu[i].name = "n" + to_string(i);//std::to_string STL自带的函数
		stu[i].age = i + 15;
	}
}
void PrintAllStudents(Student* stu, int totalStudent)
{
	for (int i = 0; i < totalStudent; ++i)
	{
		cout << stu[i].name << ", " << stu[i].age
			<< endl;
	}
}

int main(void)
{
	int totalStudent = 5;
	Student* stuArray = new Student[totalStudent];//(1)
	InitStudentArray(stuArray, totalStudent);//(2)
	PrintAllStudents(stuArray, totalStudent);//(3)
	delete[] stuArray;
	return 0;
}