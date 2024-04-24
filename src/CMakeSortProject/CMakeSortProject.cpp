// CMakeSortProject.cpp: 定义应用程序的入口点。
//

#include "CMakeSortProject.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

int stringSort(void)
{
    std::vector<std::string> nameArray{ "zhang_san","li_si"
                 ,"wang_er","ma_zi","cao_cao", "liu_bei" };
    std::sort(nameArray.begin(), nameArray.end());
    for (auto name : nameArray)//范围for循环，name会遍历nameArray中的每一个元素
    {
        std::cout << name << std::endl;//输出nameArray中的每一个元素
    }

    return 0;
}
int sortlambda(void)
{
    std::vector<int> numberArray{ 1,3,5,7,9,2,4,6,8 };
    /* sort 接受一个函数对象（比如，lambda表达式）*/
    std::sort(numberArray.begin(), numberArray.end(), [](int a, int b) {return a > b; });
    for (auto i : numberArray)//范围for循环，i会遍历每一个numberArray中的元素
    {
        std::cout << i << " ";//输出numberArray中的每一个元素
    }

    return 0;
}

bool myfunction(int i, int j) { return (i < j); }

struct myclass {
    bool operator() (int i, int j) { 
        cout << i << "<" << j << "?" << endl;
        return (i < j); 
    }
} myobject;

int myfunctionDemo() {
    int myints[] = { 32,71,12,45,26,80,53,33 };
    std::vector<int> myvector(myints, myints + 8);               // 32 71 12 45 26 80 53 33

    // using default comparison (operator <):
    std::sort(myvector.begin(), myvector.begin() + 4);           //(12 32 45 71)26 80 53 33

    // using function as comp
    std::sort(myvector.begin() + 4, myvector.end(), myfunction); // 12 32 45 71(26 33 53 80)

    // using object as comp
    std::sort(myvector.begin(), myvector.end(), myobject);     //(12 26 32 33 45 53 71 80)

    // print out content:
    std::cout << "myvector contains:";
    for (std::vector<int>::iterator it = myvector.begin(); it != myvector.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';

    return 0;
}

int eraseDemo()
{
    vector<int> arr{ 1,2,3,4,5,3,9,3 };
    /*find 找到第一个指定值的元素，
      并返回这个元素对应的迭代器
    */
    auto itr = find(arr.begin(), arr.end(), 3);
    arr.erase(itr);// 删除第1个3

    for (auto item : arr)
    {
        cout << item << " ";
    }
    return 0;
}

int removeDemo()
{
    vector<int> arr{ 1,3,2,3,4,5,3,9,3 };
    /*remove 把需要保留的数据紧凑的保留在数组的前面，
     并返回第一个不应该再属于数组的元素的迭代器，
     供后续按照范围删除
     remove 之后数组元素排列如下：
     1, 2, 4, 5, 9, #, #, #
    */
    auto itr = remove(arr.begin(), arr.end(), 3);
    arr.erase(itr, arr.end());// 删除 { # # # }

    //now print all int in arr : no 3 anymore.
    for (auto item : arr)
    {
        cout << item << " ";
    }
    return 0;
}

int main(void)
{
    std::vector<int> numberArray{ 1,3,5,7,9,2,4,6,8 };
    //对vector的所有元素排序 a < b < c ...
    //执行完这条语句，数组numberArray中的数据就已经是升序的了
    std::sort(numberArray.begin(), numberArray.end());
    for (auto i : numberArray)//范围for循环，i会遍历每一个numberArray中的元素
    {
        std::cout << i << " ";//输出numberArray中的每一个元素
    }

    stringSort();
    sortlambda();
    myfunctionDemo();

    eraseDemo();
    removeDemo();

    return 0;
}