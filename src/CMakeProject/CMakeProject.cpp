// CMakeProject.cpp: 定义应用程序的入口点。
//

#include "CMakeProject.h"
#include <string>

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

namespace F {
    void start() { cout << "F::start" << endl;  }
    void stop() { cout << "F::stop" << endl; }
}
namespace G {
    void start() { cout << "G::start" << endl; }
    void stop() { cout << "G::stop" << endl; }
}
//我们也可以在std名称空间中添加类，虽然一般不这么做，这里仅仅用于帮助我们理解什么是名称空间
namespace std {
    struct Student {
        Student() {
            { cout << "std::Student" << endl; }
        }
    };
}

void nsDemo(void)
{
    F::start();//通过名称空间名称F访问该名称空间中的函数start,下同
    F::stop();

    G::start();
    G::stop();

    std::Student my;

    using namespace F;//将名称空间F中的名称暴露出来，不需要使用F::也可以访问
    start();//再次执行名称空间F中的start函数
}

void getlineDemo(void)
{
    cout << "please input 2 lines:" << endl;
    string line;
    std::getline(cin, line);//这里程序等待你手动输入一行，按回车键结束这一行的输入
    cout << "your first input line is:" << line << endl;
    std::getline(cin, line);//这里程序等待你手动输入一行，按回车键结束这一行的输入
    cout << "your second input line is:" << line << endl;
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

    nsDemo();

    getlineDemo();

    cinDemo();

    cinStrDemo();

	return 0;
}
