// CMakeDerivedProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDerivedProject.h"

using namespace std;

class Base //基类
{
public:
	void fun(void) { cout << "Base fun()" << endl; }
public:
	int a;
};

//派生类Derived
//Derived类继承于基类Base
class Derived : public Base
{
public:
	void g(void) { cout << "Derived g()" << endl; }
public:
	int b;
};

int main()
{
	Derived d;
	//使用基类Base的成员
	d.a = 1;
	d.fun();

	cout << d.a << endl;

	//使用派生类Derived的成员
	d.b = 2;
	d.g();
	cout << d.b << endl;
}