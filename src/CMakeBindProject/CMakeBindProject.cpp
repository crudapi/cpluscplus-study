// CMakeBindProject.cpp: 定义应用程序的入口点。
//

#include "CMakeBindProject.h"

#include <map>
#include <iostream>
#include <string>
#include <functional>

using namespace std;

int add(int i, int j) { return i + j; }

class divide
{
public:
    int operator()(int i, int j) { return i / j; }
};

class Big
{
public:
    bool bigger_than(int i, int j) { return i > j; }
};
int main(int, char* [])
{
    int i = 10, j = 5;

    auto mod = [](int i, int j) {return i % j; };
    typedef function<int(int, int)> fun;
    map<string, fun> binary_operators;

    binary_operators.insert(make_pair<string, fun>("+", add));//函数指针
    binary_operators.insert(make_pair<string, fun>("-", std::minus<int>()));//函数对象
    binary_operators.insert(make_pair<string, fun>("/", divide()));//用户定义的函数对象
    binary_operators.insert(make_pair<string, fun>("*", [](int i, int j) {return i * j; }));//未命名的lambda
    binary_operators.insert(make_pair<string, fun>("%", mod));//命了名的lambda
    Big big;
    auto f = std::bind(&Big::bigger_than, big, std::placeholders::_1, std::placeholders::_2);//调用big.bigger_than(i,j)
    binary_operators.insert(make_pair<string, fun>(">", f));//任意类的成员函数

    cout << i << "+" << j << "=" << binary_operators["+"](i, j) << endl;
    cout << i << "-" << j << "=" << binary_operators["-"](i, j) << endl;
    cout << i << "/" << j << "=" << binary_operators["/"](i, j) << endl;
    cout << i << "*" << j << "=" << binary_operators["*"](i, j) << endl;
    cout << i << "%" << j << "=" << binary_operators["%"](i, j) << endl;
    cout << i << ">" << j << "=" << binary_operators[">"](i, j) << endl;
    return 0;
};