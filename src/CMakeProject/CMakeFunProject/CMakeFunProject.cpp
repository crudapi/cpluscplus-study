// CMakeFunProject.cpp: 定义应用程序的入口点。
//

#include "CMakeFunProject.h"

using namespace std;

//定义函数sum：下面的sum是函数的名字，代表函数的功能是求和，函数名字总是应该概况它的目的
int sum(int left, int right)//left right 叫形参
{
    int s = left + right;//s是整形变量，代表函数返回的值
    return s;
}

//定义函数print
void print(void)//函数不需要参数用void表示
{
    cout << "Hello World!" << endl;
}

int forDemo()
{//这里i不可见
    for (int i = 0; i < 10; ++i)//for循环内部可见
    {
        cout << i;//for循环内部可见
    }//这里i不可见

    return 0;
}

//v只在函数f1内部可见，并在函数f1执行完的时候释放
void f1(int v)
{
    v = 2;//修改v的值
}

//以引用方式传递，v是调用时传递变量a的别名
void f2(int& v)
{
    v = 2;//修改的是a
}

void f3(const int& v)
{
    cout << v;
}

int max(int a, int b)
{
    if (a >= b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int max2(int a, int b)
{
    return (a >= b) ? a : b;//三元表达式： 表达式为true 吗 ? 返回值1 : 返回值2;
}

int swap()
{
    int a = 1;
    int b = 2;

    cout << "a=" << a << ", b=" << b << endl;

    int t = a;
    a = b;
    b = t;

    cout << "a=" << a << ", b=" << b << endl;

    return 0;
}

void Swap2(int& i, int& j)//注意这里一定要传递引用，否则传值是不能完成任务的
{
    int t = i;
    i = j;
    j = t;

}

int main()
{
    print();//调用（使用）函数print
    cout << sum(1, 2) << endl;//调用函数sum， 1和2叫实参

    forDemo();

    int a1 = 1;

    f1(a1); //f1创建一个新的变量v，并把a的值赋值给v
    //函数f1修改的是v的值，a的值不变
    cout << endl << a1 << endl;//仍然是1

    f2(a1);//把a本身传递给函数
    cout << a1 << endl;//a被函数修改了，此时是2

    //f3用v作为a的别名,在f3内部直接打印a
    f3(a1);

    int n1 = 786;
    int n2 = 765;

    int n = max(n1, n2);

    cout << "max(" << n1 << "," << n2 << ") = " << n << endl;

    int m1 = 786;
    int m2 = 765;
    int m3 = 766;

    int m = max2(m1, m2);
    m = max2(m, m3);

    cout << "max of "
        << m1 << ", "
        << m2 << ", "
        << m3 << " is "
        << m << endl;

    swap();

    int a = 2;
    int b = 3;
    cout << "a=" << a << ", b=" << b << endl;

    Swap2(a, b);
    cout << "a=" << a << ", b=" << b << endl;

    return 0;
}

