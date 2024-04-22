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

int cinDemo(void)
{
    int i = 0;

    cin >> i;//从键盘输入整数给i
    cout << i;//输出整数i到屏幕

    return 0;
}

int cinStrDemo(void)
{
    string s;
    cin >> s;//输入字符串
    cout << s;//输出字符串

    return 0;
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

    cinDemo();

    cinStrDemo();

	return 0;
}
