// CMakeOperatorLProject.cpp: 定义应用程序的入口点。
//

#include "CMakeOperatorLProject.h"

#include <vector> //vector
#include <algorithm> //std::sort
#include <iostream> // std::cout
#include <iomanip> // std::setw
#include <string> // std::string

struct Student
{
	//for cout<<student fout<<student
	friend std::ostream& operator<<(std::ostream& os, const Student& student);
	//for std::sort
	bool operator<(const Student& other);

	//members
	std::string name;
	int score;
};

std::ostream& operator<<(std::ostream& os, const Student& student)
{
	// score use 4 width when print, name use 10 width for print
	os << std::setw(4) << student.score << std::setw(10) << student.name;
	return os;
}

bool Student::operator<(const Student& other)
{
	//(1) compare score
	if (score < other.score)
	{
		//for higher score first show
		return true;
	}
	else if (score == other.score)
	{
		//(2) compare other detail member
		return name > other.name;
	}
	//(1) compare score
	else
	{
		//for higher score first show
		return false;
	}
}

int main()
{
	//init all students's data
	std::vector<Student> students{
		{"zhangsan", 700},
		{"lisi", 680},
		{"wanger", 699},
		{"mazi", 699},
		{"zhangfei", 700},
		{"liubei", 590},
	};

	//use stu1 < stu2 for sorting
	std::sort(students.begin(), students.end());

	for (std::vector<Student>::const_iterator itr = students.begin();
		itr != students.end(); ++itr)
	{
		//use operator<<(std::ostream& os, const Student& student)
		std::cout << *itr << std::endl;
	}

	return 0;
}