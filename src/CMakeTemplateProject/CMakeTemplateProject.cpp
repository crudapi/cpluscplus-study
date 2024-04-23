// CMakeTemplateProject.cpp: 定义应用程序的入口点。
//

#include "CMakeTemplateProject.h"

using namespace std;

template<typename T1, typename T2>
struct Pair // 模拟 std::pair
{
    T1 first;
    T2 second;
};

int pairDemo()
{
    pair<int, string> myPair;// std::pair  给模板类 pair 指定 T1 为 int, T2 为 string

    myPair.first = 45;
    myPair.second = "Donald Trump";

    cout << "The "
        << myPair.first << "th President of the United States is "
        << myPair.second << "." << endl;

    return 0;
}

int main()
{
    Pair<int, string> myPair;//给模板类 Pair 指定 T1 为 int, T2 为 string  模板实例化

    myPair.first = 45;
    myPair.second = "Donald Trump";

    cout << "The "
        << myPair.first << "th President of the United States is "
        << myPair.second << "." << endl;


    pairDemo();


    return 0;
}