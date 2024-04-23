// CMakeDerivedProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDerivedProject.h"
#include <vector>
#include <string>

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

	for (vector<int>::iterator itr = v.begin(); itr != v.end(); ++itr)
	{
		cout << *itr << " ";
	}

	return 0;
}

int iteratorDemo2()
{
	//定义一个数组，并放入一些整数
	vector<int> a{ 0,1,2,3,4,5,6,7,8,9 };
	//使用下标遍历数组输出其中的每一个元素
	for (int i = 0; i < a.size(); ++i)
	{
		cout << a[i] << " ";
	}
	cout << endl;
	//使用迭代器输出数组中的每一个元素
	for (auto itr = a.begin(); itr != a.end(); ++itr)
	{
		cout << *itr << " ";//使用解引用操作符*获得迭代器迭代到的元素的引用
	}
	return 0;
}

struct Student
{
	int get_age() { return m_age; }
	void set_age(int age) { m_age = age; }

	string m_name;
private:
	int m_age;
};

int StudentDemo()
{
	int i = 0;
	vector<Student> student_array(3);//创建一个vector，里面存放3个Student对象
	for (auto itr = student_array.begin(); itr != student_array.end(); ++itr)
	{
		//使用成员操作符修改对象的名字
		itr->m_name = "name" + to_string(++i);
		//使用成员操作符调用对象的成员函数
		itr->set_age(i + 18);
	}

	for (auto itr = student_array.begin(); itr != student_array.end(); ++itr)
	{
		//使用成员操作符读取对象的名字
		cout << "My name is " << itr->m_name
			<< ", I'm " << itr->get_age() << " years old." << endl;
	}

	for (auto itr = student_array.begin(); itr != student_array.end(); ++itr)
	{
		(*itr).m_name = "name2" + to_string(++i);// itr->m_name 更直观
		(*itr).set_age(i + 118); // itr->set_age() 更直观
	}

	for (auto itr = student_array.begin(); itr != student_array.end(); ++itr)
	{
		//使用成员操作符读取对象的名字
		cout << "My name is " << itr->m_name
			<< ", I'm " << itr->get_age() << " years old." << endl;
	}



	return 0;
}

void test_reverse_iterate_by_index(void)
{
	cout << "reverses iterate vector by index:";

	vector<int> arr{ 1, 2, 3 };

	for (size_t i = arr.size(); i > 0; --i)
	{
		cout << arr[i - 1] << " ";
	}
	cout << endl;
}


int test_reverse_iterate_by_index2()
{
	vector<int> a{ 0,1,2,3,4,5,6,7,8,9 };
	//rbegin() 获取逆序迭代器的第一个迭代器；
	//rend() 获得逆序迭代器的最后一个迭代器的下一个位置（哨兵）
	for (auto itr = a.rbegin(); itr != a.rend(); ++itr)
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

	iteratorDemo2();

	StudentDemo();

	size_t i = 0;
	--i; //ffff ffff ffff ffff
	cout << std::hex <<  i << endl;

	test_reverse_iterate_by_index();

	test_reverse_iterate_by_index2();

}