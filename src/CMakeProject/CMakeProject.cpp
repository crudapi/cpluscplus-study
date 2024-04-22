// CMakeProject.cpp: 定义应用程序的入口点。
//

#include "CMakeProject.h"
#include <string>
#include <iomanip>

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

int getlineDemo2()
{
    int a = 0;
    cin >> a;//第一行：这里输入了1234和回车（光标到下一行）
    cout << a << endl;//第二行：这里输出了1234和一个回车（光标到下一行）
    string line;
    /*下面这里会直接得到cin留下来的回车键而结束，
      导致line的内容为空，这不是我们想要的
    */
    getline(cin, line);//第三行
    cout << "line:" << line << endl; //这里输出一个回车（光标到下一行）
    //第四行
    cout << "getlineDemo2" << endl;
    return 0;
}

void formatDemo()
{
    double i = 100 / 3.0; //33.33333333333......
    double you = 200 / 3.0; //66.66666666666......
    //fixed使用小数计数法(而不是科学计数法)显示浮点数
    //setprecision(4) 小数部分保留4位，最后一位四舍五入
    cout << fixed << setprecision(4)
        << i << endl
        << you << endl
        ;

    std::cout << std::setw(10) << std::setfill('0');
    std::cout << 77 << std::endl;
    bool b = true;
    std::cout <<  b << std::endl;
    std::cout << std::boolalpha << b << std::endl;
}

int opDemo(void)
{
    cout << "opDemo "  << endl;
    int a = 3;
    int b = 4;
    bool c = a > b;
    cout << boolalpha << c << endl;

    c = a > b || a != 0;
    cout << c << endl;

    //字符相等
    char d = '%';
    bool is_char_equal = (d == '%');
    cout << "is char equal ? " << is_char_equal << endl;

    //字符串相等
    string str("abcdefg123456");
    bool is_str_equal = (str == "abcdefg123456");
    cout << "is string equal ? " << is_str_equal << endl;

    return 0;
}

int forDemo()
{
    for (int i = 1; i <= 10; ++i)
    {
        cout << i;
    }
    return 0;
}

int iLoveYouDemo()
{
    for (int i = 0; i < 10; ++i)
    {
        //要把说了多少次打印出来，这样显得有诚意！
        //请填写代码让你的输出和下面的截图一样
        //(1) your code
        //输出字符串参考 https://blog.csdn.net/calmreason/article/details/126637396
        //输出变量参考 https://blog.csdn.net/calmreason/article/details/126637512
        cout << "I love you! " << i + 1 << endl;
    }
    return 0;
}

int sumDemo()
{
    int sum = 0;
    for (int i = 1; i <= 100; ++i)
    {
        sum += i;

    }

    cout << sum;

    return 0;
}



int ninenineDemo()
{
    cout << endl;
    for (int i = 1; i <= 9; ++i)
    {
        for (int j = 1; j <= i; ++j)
        {
            //(1) your code 请在下面一行填写代码，让程序输出和预期输出一致的内容
            cout << j << "*" << i << "=" << i * j << " ";
        }
        cout << endl;
    }

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

    nsDemo();

    formatDemo();

    opDemo();

    forDemo();

    iLoveYouDemo();

    sumDemo();

    ninenineDemo();

    cinDemo();

    cinStrDemo();

    getlineDemo();

    getlineDemo2();

	return 0;
}
