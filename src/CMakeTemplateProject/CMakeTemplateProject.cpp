// CMakeTemplateProject.cpp: 定义应用程序的入口点。
//

#include "CMakeTemplateProject.h"
#include <map>
#include <utility>// std::pair

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

int mapDemo2()
{
    //初始化map
    //map会自动对插入的元素按照key大小进行排序
    //这里key是string类型，所以使用string的小于号来排序
        //string的小于号比较大小按照ASCII码的字母表排序
    map<string, string> universities{
        {"MIT", "麻省理工学院 Massachussets  Institute of Technology"},
        {"UCB", "加州大学伯克利分校 University of  California - Berkeley"},
        {"CMU", "卡内基梅隆大学 Carnegie Mellon  University"},
        {"CC", "哥伦比亚大学 Columbia University  /Community College"},
        {"CU", "康奈尔大学 Cornell University"},
        {"UNC", "北卡罗来纳大学 University of North  Carolina - Chapel Hill"},
        {"UWM", "威斯康辛大学麦迪逊分校 University of  Wisconsin - Madison"},
        {"GWU", "乔治华盛顿大学 George Washington  University"},
        {"JHU", "约翰霍普金斯大学 Johns Hopkins  University"},
        {"MSU", "密歇根州立大学 Michigan State  University"},
    };

    //运行时根据业务需要，插入一条记录
    universities["Penn"] = "宾夕法尼亚大学 University of  Pennsylvania";

    //按照字母表顺序输出所有大学
    cout << "All " << universities.size() << " universities:" << endl;
    for (auto& item : universities)
    {
        cout << "key=" << item.first << " , value= " << item.second << endl;
    }

    return 0;
}

int mapDemo()
{
    map<int, int> student_score{
        //学号不可以有重复
        //学号可以不按顺序创建
        //学号在创建完成之后会在内部自动排好顺序
        //学号排序按照大小顺序，int类型的数据就按数值大小排序
        {003, 90},
        {004, 88},
        {001, 88},//分数可以有相同的分数
        {002, 78},
    };
    //item变量来迭代student_score 的每一个元素
    for (auto item : student_score)
    {
        //item是一个pair<int, int>类型
        cout << "id=" << item.first << " " << " score=" << item.second << endl;
    }


    map<string, string> universities;
    /*下面的代码完成了元素创建的工作，因为map中还没有这个元素
    */
    universities["MIT"] = "麻省理工学院 Massachussets  Institute of Technology";
    universities.insert({ "MITinsert", "麻省理工学院 Massachussets  Institute of Technology" });
    cout << "size=" << universities.size() << endl;//可见元素数量是1了
    cout << universities["MIT"] << endl;//可以取出这个key为“MIT”的元素的value并输出

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

    mapDemo();

    mapDemo2();

    return 0;
}