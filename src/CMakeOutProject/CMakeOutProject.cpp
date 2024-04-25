// CMakeOutProject.cpp: 定义应用程序的入口点。
//

#include "CMakeOutProject.h"
#include <iostream>
#include <string>
#include <fstream>

using namespace std;


//学生类
class Student
{
	//输出操作符重载：将Student对象的数据输出到目的地os
	//os可以是控制台屏幕cout和文件ofstream对象，他们都可以看做是ostream对象
	//友元friend表示这个函数不是类的成员函数，而是一个全局函数，
	//而且可以访问类的私有成员：不然在函数内访问类的私有成员就只能写stu.get_id() stu.get_name() stu.get_age()这样的代码
	friend std::ostream& operator<<(std::ostream& os, const Student& stu);

	//由于输入操作符函数会写(修改)对象的成员变量，所以不可以传const参数
	friend std::istream& operator>>(std::istream& os, Student& stu);
public:
public:
	std::string m_id;//学号
	std::string m_name;//姓名
	int m_age;//年龄
	std::string m_date;//生日
};

std::ostream& operator<<(std::ostream& os, const Student& stu)
{
	//向os输出Student对象的每一个成员变量，从而将Student输出到os
	os
		//如果这个函数不是friend，这里就只能写 stu.get_id()这样的代码来获取类的成员变量，比较麻烦
		<< stu.m_id << " "
		<< stu.m_name << " "
		<< stu.m_age << " "
		<< stu.m_date;
	return os;//这样os就可以连续输出多个对象。例如， cout<<stu1<<stu2;
}
std::istream& operator>>(std::istream& is, Student& stu)
{
	is
		>> stu.m_id
		>> stu.m_name
		>> stu.m_age
		>> stu.m_date;
	return is;
}

int main(int argc, char** argv)
{
	//定义一个学生对象
	Student stu{ "001", "zhangsan", 18, "1995-09-08" };
	//将学生信息再次输出到控制台
	//这里可以直接输出stu对象
	std::cout << "学生信息：" << stu << std::endl;
	
	std::ofstream fout("students.txt");
	//输出学生信息到文件
	fout << stu << std::endl;

	//定义一个学生对象
	Student stu2;
	std::ifstream fin("students.txt");
	if (!fin.is_open())
	{
		std::cout << "error! can not open file students.txt!" << std::endl;
		return -1;
	}
	fin >> stu2;//从文件中读取信息赋值给stu
	//输出学生信息到文件
	std::cout << stu2 << std::endl;

	return 0;
}