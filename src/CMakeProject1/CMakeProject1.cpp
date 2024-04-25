// CMakeProject1.cpp: 定义应用程序的入口点。
//

#include "CMakeProject1.h"

#include<fstream>//需要包含头文件

using namespace std;

int main()
{
	ofstream fout("out.txt");//创建ofstream类的对象fout，圆括号表示调用了接收一个字符串的构造函数

	int myAge = 18;
	fout << myAge << endl;//就像使用cout一样往文件里输出18，并输出一个换行符

	double pi = 3.14159;
	fout << pi << endl;

	long long i = 123456789123456789;
	fout << i << endl;

	return 0;
}