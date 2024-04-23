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

int CommFactor(int m, int n)
{
    cout << m << " 和 " << n << " 的最大公约数 ：";

    int z = m % n;
    while (z != 0)//不管m和n谁大谁小，都不影响求余，参考上文图片
    {
        m = n;
        //(1) your code 
        n = z;

        z = m% n;
    }
    //n总是最后一次不会0的值，作为返回值
    cout << n << endl;
    return n;
}

int main()
{
    print(123456);
    print(25566);
    print(143);
    print(345);
    print(1);

    CommFactor(1, 1);
    CommFactor(2, 4);
    CommFactor(4, 2);
    CommFactor(2, 8);
    CommFactor(8, 2);
    CommFactor(10000, 10);
    CommFactor(7, 9);
    CommFactor(1997, 615);


}
