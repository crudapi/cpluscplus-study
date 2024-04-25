// CMakeFileProject.cpp: 定义应用程序的入口点。
//

#include "CMakeFileProject.h"

#include <fstream>
#include <string>
using namespace std;

void getlineDemo()
{
	string line;

	//打开文件data.txt
	ifstream fin("data.txt");

	//从文件fin读取一行数据到line中
	getline(fin, line);

	//输出读取到的内容
	cout << line << endl;
}

int ofstreamDemo()
{
	ofstream fout("data.txt");//创建ofstream类的对象fout，圆括号表示调用了接收一个字符串的构造函数

	int myAge = 18;
	fout << myAge << endl;//就像使用cout一样往文件里输出18，并输出一个换行符

	double pi = 3.14159;
	fout << pi << endl;

	long long i = 123456789123456789;
	fout << i << endl;

	char a = 'a';
	fout << a << endl;

	return 0;
}

int main(void)
{
	ofstreamDemo();

	getlineDemo();

	//打开文件out.txt
	ifstream fin("data.txt");
	if (!fin.is_open())
	{
		cout << "文件data.txt不存在!" << endl;
		return 0;
	}

	int myAge = 0;
	//就像使用cin一样,从文件里当前读取位置读取后续一串连续字符，解释成整数，赋值给整型变量myAge
	//连续字符前面的空白符（空格、tab、回车换行）都将被吃掉
	//连续字符后面遇到空白符则不吃（表示还未被读取）
	fin >> myAge;

	double pi = 0;
	fin >> pi;//从myAge对应的字符串后面的内容，接着读一个连续的字符串

	long long i = 0;
	fin >> i;

	char c = '0';
	fin >> c;

	cout << "下面的数据来自文件data.txt" << endl;
	cout << myAge << endl;
	cout << pi << endl;
	cout << i << endl;
	cout << c << endl;

	return 0;
}
