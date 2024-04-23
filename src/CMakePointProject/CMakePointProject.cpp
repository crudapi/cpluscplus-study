// CMakePointProject.cpp: 定义应用程序的入口点。
//

#include "CMakePointProject.h"

using namespace std;


void g(void) {     //3
	cout << "g" << endl;
	int a;
	int b;
	
}                 //4
void f(void) {     //2
	cout << "f" << endl;
	int x;
	int y;
	g();
}                 //5

int main()
{
	cout << "Hello CMake." << endl;

	int a { 123 };//定义整形变量 a 并初始化为 123。这种是C++11写法
	int b = 123;//定义整形变量 b 并初始化为 123。这种是C++11之前的写法。
	//以上两种写法效果一样的。

	int* p = new int{ 456 };

	cout << a << endl;
	cout << b << endl;
	cout << *p << endl;
	cout << p << endl;

	f();

	return 0;
}
