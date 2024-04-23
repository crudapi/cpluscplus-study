// CMakePointProject.cpp: 定义应用程序的入口点。
//

#include "CMakePointProject.h"

using namespace std;


void g(void) {     //3
	cout << "g" << endl;
	int* a = new int;
	int b;
	*a = 1;
	b = 2;

	cout << *a << endl;
	cout << a << endl;

	delete a;//释放a指向的无名变量
	
	cout << *a << endl;
	cout << a << endl;

	a = nullptr;//地址变量初始化

	if (a == nullptr)//地址变量判断相等
	{
		cout << "pointed to nothing!" << endl;
	}

}                 //4
void f(void) {     //2
	cout << "f" << endl;
	int x;
	int y;
	g();
}                 //5

int nullptrDemo(void)
{
	int* ptr = nullptr;//地址变量初始化

	if (ptr == nullptr)//地址变量判断相等
	{
		cout << "pointed to nothing!" << endl;
	}

	//开辟一个堆变量交给 ptr 管理
	ptr = new int(5);

	if (ptr != nullptr)//地址变量判断不相等
	{
		cout << "pointed to " << *ptr << endl;
	}
	delete ptr;

	return 0;
}

int unRefDemo()
{
	int* a = new int{ 123 };//创建一个栈上的地址变量 a，a 存储了堆上一个无名变量的地址。


	//下面的 *a 叫做：解引用。
	//用 * 和地址变量结合得到无名变量本身。并给无名变量赋值为 2

	cout << "a = " << *a << endl;//输出无名变量的值

	*a = 2;

	cout << "a = " << *a << endl;//输出无名变量的值

	return 0;
}

void fun(int& a)//(1) 这里的 & 表示参数a是引用类型
{
	a = 4;
}

void fun2(int* p)
{
	*p = 6;
}

void pointDemo() {
	int n = 2;
	cout << "n=" << n << endl;

	int& nn = n;//(2) 这里的 & 是引用类型， nn 是 n 的别名
	nn = 3;


	cout << "n=" << n << endl;

	fun(n);
	cout << "n=" << n << endl;

	int* p = &n;//(3) 这里的 & 是取地址运算符，&n 是 n 的地址
	*p = 5;
	cout << "n=" << n << endl;

	fun2(&n);//(3) 这里的 & 是取地址运算符，&n 是 n 的地址
	cout << "n=" << n << endl;
}

void fun(int* p)
{
	*p = 123;//*p解引用，得到地址所在的变量，并对变量赋值为123
}

int funDemo()
{
	int a = 0;

	cout << "a=" << a << endl;

	fun(&a);//&a 取变量a的地址，传递给函数fun

	cout << "a=" << a << endl;

	return 0;
}

void funArr(int* p)
{
	//下面的 4 种修改堆数组的写法是一样的
	*p = 4;//修改堆数组的第1个元素；等价于 *(p+0) ，等价于 p[0]
	*(p + 1) = 5;//修改堆数组的第2个元素
	p[2] = 6;//修改堆数组的第3个元素

	p = p + 3;//指针移动跳过 3 个整型变量
	*p = 7;//此时p指向对数组的最后一个元素
}

int funArrDemo()
{
	//开辟包含4个元素的堆数组，每个元素的值分别是0 1 2 3
	int* arr = new int[4] {0, 1, 2, 3};

	//输出数组内容
	cout << "arr : " << arr[0] << ", " << arr[1] << ", " << arr[2] << ", " << arr[3] << endl;

	int arr2[4] = {0, 1, 2, 3};
	cout << "arr2 : " << arr2[0] << ", " << arr2[1] << ", " << arr2[2] << ", " << arr2[3] << endl;
	cout << "arr2 : " << *arr2 << ", " << *(arr2 + 1) << ", " << *(arr2 + 3) << ", " << *(arr2 + 3) << endl;

	int* p = arr;
	funArr(p);//堆数组的第一个元素的地址，传递给函数fun

	funArr(arr2);

	//输出数组内容
	cout << "arr : " << arr[0] << ", " << arr[1] << ", " << arr[2] << ", " << arr[3] << endl;
	cout << "arr2 : " << arr2[0] << ", " << arr2[1] << ", " << arr2[2] << ", " << arr2[3] << endl;

	return 0;
}

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

	nullptrDemo();

	unRefDemo();

	pointDemo();
	
	funDemo();

	funArrDemo();

	return 0;
}
