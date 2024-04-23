// CMakeDerivedProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDerivedProject.h"
#include <vector>

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

int vectorDemo()
{
	vector<int> a;

	cout << "vector size:" << a.size() << endl;

	for (size_t i = 0; i < 10; ++i)
	{
		a.push_back(i);
	}

	cout << "vector size:" << a.size() << endl;
	for (size_t i = 0; i < a.size(); ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	return 0;
};

int maxDemo()
{
	vector<int> arr{ 3,1,4,1,5,9,2,6 };

	int max = arr[0];
	for (int i = 1; i < arr.size(); ++i)
	{
		if (arr[i] > max)
		{
			max = arr[i];

		}
	}

	cout << "max=" << max;

	return 0;
}

int max2(int a, int b)
{
	return a >= b ? a : b;
}

int max2Demo()
{
	vector<int> arr{ 3,1,4,1,5,9,2,6 };

	int result_max = arr[0];

	for (int i = 1; i < arr.size(); ++i)
	{
		result_max = max2(result_max, arr[i]);
	}

	cout << "max=" << result_max;

	return 0;
}

int stringDemo()
{
	string you_say("I love you");
	cout << "字符串内容:" << you_say << endl;//字符串可以直接输出
	cout << "字符串长度:" << you_say.size() << endl;
	cout << "字符串内容:";
	for (size_t i = 0; i < you_say.size(); ++i)
	{
		cout << you_say[i];//使用下标遍历字符串
	}
	cout << endl;
	//拼接字符串
	string i_say = you_say;//复制构造一个新字符串
	i_say += " too";//字符串拼接
	cout << "字符串内容:" << i_say << endl;//字符串可以直接输出

	return 0;
}

int iteratorDemo()
{
	vector<int> v{ 1,2,3,4,5,6,7,8,9 };//初始化9个元素

	for (auto itr = v.begin(); itr != v.end(); ++itr)
	{
		cout << *itr << " ";
	}

	return 0;
}

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

	vectorDemo();

	maxDemo();

	max2Demo();

	stringDemo();

	int  a = 1;
	auto b = a;//b的类型为a的类型 int
	int c = b;
	cout << b << endl;
	cout << a << endl;

	iteratorDemo();
}