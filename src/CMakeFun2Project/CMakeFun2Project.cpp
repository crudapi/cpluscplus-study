// CMakeFun2Project.cpp: 定义应用程序的入口点。
//

#include "CMakeFun2Project.h"

using namespace std;


//输出正整数n各个位上的数字
void print(int n)
{
    cout << n << " : ";
    while (n != 0)
    {
        int c = n % 10;
        cout << c << " ";
        //(1) your code

        n = n / 10;
    }
    cout << endl;
}

int main()
{
    print(123456);
    print(25566);
    print(143);
    print(345);
    print(1);

}
