// CMakeStaticProject.cpp: 定义应用程序的入口点。
//

#include "CMakeStaticProject.h"

using namespace std;

struct MyStruct {
    // 下面的这条初始化语句等价于下面的两条语句：
    //（1）ider= ider+ 1; 
    //（2）id = ider;
    MyStruct() : id(++ider)
    {
    }

    int id;
    static int ider;//将
};

int MyStruct::ider = 0;
//(0) main函数开始执行之前
int main()
{
    //(1)创建对象my1，执行完下面这条语句之后，MyStruct::ider== 1, my1.id == 1 
    MyStruct my1;//(1)
    //(2)创建对象my2，执行完下面这条语句之后，MyStruct::ider== 2, my1.id == 2 
    MyStruct my2;//(2)
    //(3)创建对象my3，执行完下面这条语句之后，MyStruct::ider== 3, my1.id == 3 
    MyStruct my3;//(3)

    //my1.increaser和MyStruct::increaser是同一个变量
    //，只不过一个是通过对象访问，一个是通过类名访问
    cout << my1.id << " " << MyStruct::ider << endl;
    cout << my2.id << " " << MyStruct::ider << endl;
    cout << my3.id << " " << MyStruct::ider << endl;

    return 0;
}