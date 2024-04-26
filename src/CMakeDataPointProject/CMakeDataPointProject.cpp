// CMakeDataPointProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataPointProject.h"

#include <iostream>
using namespace std;

void check_do(bool b, int line = __LINE__) { if (b) { cout << "line:" << line << " Pass" << endl; } else { cout << "line:" << line << " Ohh! not passed!!!!!!!!!!!!!!!!!!!!!!!!!!!" << " " << endl; exit(0); } }
#define check(msg)  check_do(msg, __LINE__);


void test_char_ptr(void)
{
    cout << "test_char_ptr:" << endl;

    //p 指向第一个元素，其值为第一个元素的地址
    char* p = new char[5] {'a', 'b', 'c', 'd', 'e'};
    char* q = p;//指向相同的地址
    check(*q == 'a');//对地址解引用，获得第一个元素的引用

    cout << "q=" << (long long)q << endl;//将地址的内容当做正数输出
    q = q + 1;// 指针运算：指向下一个 char，移动了 1 个字节
    cout << "q=" << (long long)q << endl;//数值增加了 1

    check(*q == 'b');// b

    check(p[4] == 'e');
    check(p[4] == *(p + 4));//两种写法等价


    delete[] p;
}
void test_int_ptr(void)
{
    cout << "test_int_ptr:" << endl;

    //p 指向第一个元素，其值为第一个元素的地址
    int* p = new int[5] {111, 222, 333, 444, 555};
    int* q = p;//指向相同的地址
    check(*q == 111);//对地址解引用，获得第一个元素的引用

    cout << "q=" << (long long)q << endl;//将地址的内容当做正数输出
    q = q + 1;// 指针加法：指向下一个元素，移动了 4 个字节
    cout << "q=" << (long long)q << endl;//数值增加了 4

    check(*q == 222);

    check(p[4] == 555);
    check(p[4] == *(p + 4));//两种写法等价

    check(&p[4] - p == 4);//指针减法得到间隔的元素数量

    delete[] p;
}
void test_long_long_ptr(void)
{
    cout << "test_long_long_ptr:" << endl;

    //p 指向第一个元素，其值为第一个元素的地址
    long long* p = new long long[5] {1111, 2222, 3333, 4444, 5555};
    long long* q = p;//指向相同的地址
    check(*q == 1111);//对地址解引用，获得第一个元素的引用

    cout << "q=" << (long long)q << endl;//将地址的内容当做正数输出
    q = q + 1;// 指针加法：指向下一个元素, 移动了 8 个字节
    cout << "q=" << (long long)q << endl;//数值增加了 8

    check(*q == 2222);

    check(p[4] == 5555);
    check(p[4] == *(p + 4));//两种写法等价

    check(&p[4] - p == 4);//指针减法得到间隔的元素数量

    delete[] p;

}

int main()
{
    test_char_ptr();
    test_int_ptr();
    test_long_long_ptr();

    return 0;
}