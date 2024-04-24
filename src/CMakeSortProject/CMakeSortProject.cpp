// CMakeSortProject.cpp: 定义应用程序的入口点。
//

#include "CMakeSortProject.h"
#include <vector>
#include <algorithm>

using namespace std;

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

    return 0;
}