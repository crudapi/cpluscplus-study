// CMakeProject.cpp: 定义应用程序的入口点。
//

#include "CMakeProject.h"

using namespace std;

void refDemo() {
	int a = 1;
	int& b = a;//创建别名（引用）
	int c = a;//创建副本（拷贝）

	b = 222;//修改 a 
	c = 333;//修改 c

	cout << "a=" << a << endl;
	cout << "b=" << b << endl;
	cout << "c=" << c << endl;
}

int main()
{
	cout << "Hello CMake." << endl;

    int myAge = 18;
    cout << myAge << endl;

    double pi = 3.14159;
    cout << pi << endl;

    long long i = 123456789123456789;
    cout << i;

    char c = 'c';
    cout << c << endl;

	refDemo();

	return 0;
}
