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

        z = m % n;
    }
    //n总是最后一次不会0的值，作为返回值
    cout << n << endl;
    return n;
}

/*输出正整数n各个位上的数字
  暂时不支持0和负数*/
void print2(unsigned int n)
{
    if (n == 0)//递归函数必须要有结束条件，不然会一直调用自己，最终把栈空间撑爆溢出，程序终止
    {
        return;
    }
    unsigned int m = n % 10;//求出最后一位数字
    n = n / 10;//抛弃最后一位数字
    print2(n);//使用剩下的数字构成的整数，再重复此过程
    cout << m << "  ";//输出最后一位数字

}

bool is_prime_number(int n)
{
    //最小的素数为 2
    if (n < 2)
    {
        return false;//不是素数
    }

    for (int i = 2; i < n; ++i)
    {
        if (n % i == 0) //不是素数
        {
            //(1) your code  
            return false;
        }
    }
    //前面都没有返回false的情况下，才会走到这里，此时已经确定该数字为素数
    return true;
}

void test(int n)
{
    bool is = is_prime_number(n);
    if (is)
    {
        cout << n << " is prime number." << endl;
    }
    else
    {
        cout << n << " is not prime number." << endl;
    }
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

    cout << endl <<  "print2" << endl;
    print2(123456);
    cout << endl << "print2" << endl;
    print2(300);
    cout << endl << "print2" << endl;
    print2(1);

    test(3);
    test(4);
    test(5);
    test(99);
    test(100);
    test(101);
}
