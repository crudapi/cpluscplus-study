// CMakeVfptr Project.cpp: 定义应用程序的入口点。
//

#include "CMakeVfptrProject.h"

using namespace std;
class Base {
private:
	int num;
public:
	Base() { num = 10; }
	~Base() {}
	virtual void virFunc1() {				//基类虚函数1
		cout << "Base中虚函数1" << endl;
	}
	virtual void virFunc2() {
		cout << "Base中虚函数2" << endl;	//基类虚函数2
	}
	virtual void virFunc3() {
		cout << "Base中虚函数3" << endl;	//基类虚函数3
	}
};
class Son :public Base {
public:
	virtual void virFunc2() {				//派生类重写虚函数2
		cout << "Son中虚函数2" << endl;
	}
};
void test01() {
	Base base;
	intptr_t* vfptr = (intptr_t*)&base;		//在对象储存空间开始处取出一个指针变量，这个指针指向虚函数表（也就是存放虚函数地址的数组）
	intptr_t* vftable = (intptr_t*)*vfptr;	//对虚函数表的指针取值，取得虚函数表，可理解为数组名
	void(*func)() = (void(*)()) * vftable;	//对虚函数表的数组名取值，得到第一个元素，也就是第一个虚函数的地址
	func();
	func = (void(*)()) * (vftable + 1);			//数组名+1就是第二个元素的地址，
	func();
}
int main(int argc, char const** argv) {
	test01();
	return 0;
}