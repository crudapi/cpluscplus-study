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
    return 0;
}