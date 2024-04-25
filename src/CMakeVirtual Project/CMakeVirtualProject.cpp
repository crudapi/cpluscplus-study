// CMakeVirtual Project.cpp: 定义应用程序的入口点。
//

#include "CMakeVirtualProject.h"
#include <vector>

using namespace std;

//IShape只提供计算面积的行为
struct IShape
{
    //多态的条件1：基类提供虚函数
    // = 0 表示纯虚函数，用于禁止直接创建IShape的对象（一般都建议这么做）
    virtual void printArea(void) const = 0;
    //基类的析构函数一般都应该是虚函数（以使用多态调用派生类的析构函数）
    virtual ~IShape(void) { cout << "~IShape()" << endl;}
};
//圆形继承了IShape
struct Circle : public IShape
{
    //多态的条件2：派生类实现基类的函数
    //圆形计算面积的方式
    void printArea(void) const override
    {
        cout << "I',m a Circle. r=" << r << ", area="
            << (3.1415926 * r * r) << endl;
    }
    float r;

    ~Circle(void) { cout << "~Circle()" << endl; }
};
//正方形形继承了IShape
struct Square : public IShape
{
    //多态的条件2：派生类实现基类的函数
    //正方形计算面积的方式
    void printArea(void) const override
    {
        cout << "I',m a Square. side=" << side << ", area="
            << (side * side) << endl;
    }
    float side;
};

int main()
{
    Circle circle;//创建一个圆形对象
    circle.r = 2;//圆形的半径是2

    Circle circle2;//创建一个圆形对象
    circle2.r = 2.5;//圆形的半径是2.5

    Square square;//创建一个正方形对象
    square.side = 3;//正方形的边长是3.5

    Square square2;//创建一个正方形对象
    square2.side = 4;//正方形的边长是4.2

    //创建一个数组对象，把上面所有形状对象都放进去
    vector<IShape*> arrShape{ &circle, &circle2, &square , &square2 };
    //用范围循环遍历所有形状对象
    for (int i = 0; i < arrShape.size(); ++i)
    {
        arrShape[i]->printArea();//这里会执行各个派生类对象的成员函数：多态因此而来
    }
    return 0;
}