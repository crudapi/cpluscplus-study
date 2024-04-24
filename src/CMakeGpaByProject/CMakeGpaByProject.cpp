// CMakeGpaByProject.cpp: 定义应用程序的入口点。
//

#include "CMakeGpaByProject.h"

#include <vector> //存放学生的课程和学分
#include <string> //存放学生的名字
#include <iomanip> //格式控制：小数部分2位小数
#include <map> //存放学生数据，排序数据
#include <algorithm>

using namespace std;

struct Student
{
    double get_GPA(void) const { return GPA; }
    void set_GPA(void);//计算学生的GPA数值，存到学生的GPA成员变量中

    int id;//学号
    vector<int> score_list;//修的所有课程的成绩列表
    vector<int> credit_hour_list;//修的所有课程对应的学分列表
    double GPA;
    string name;//姓名
};
void Student::set_GPA(void)
{
    //累加课程学分绩点=课程学分绩点1+课程学分绩点2+...+课程学分绩点n
    double total_credit_hour_point = 0;

    for (int i = 0; i < score_list.size(); i++)
    {
        //课程绩点=课程成绩/10 -5
        double grade_point = score_list[i] / 10.0 - 5;//注意这里整数通过除以浮点数结果转换成了浮点数
        //课程学分绩点
        double credit_hour_point = credit_hour_list[i] * grade_point;
        //累加课程学分绩点
        total_credit_hour_point += credit_hour_point;
    }

    //平均学分绩点
    //各门课学分之和sum_credit_hour 
    int sum_credit_hour = 0;
    for (int i = 0; i < score_list.size(); i++)
    {
        sum_credit_hour += credit_hour_list[i];//累加
    }

    //平均学分绩点= 累加课程学分绩点/各门课学分之和
    GPA = total_credit_hour_point / sum_credit_hour;
}
void init_student_data(map<int, Student>& student_map)
{
    student_map[111] = Student{ 111, { 88, 86, 87, 82, 82, 86, 83, 86, 80, 89 }, { 3, 3, 1, 1, 2, 1, 3, 2, 3, 3 } , 0.0, "杜特尔特" };
    student_map[112] = Student{ 112, { 92, 80, 81, 75, 93, 80, 81, 89, 84, 85 }, { 3, 2, 3, 1, 2, 2, 2, 1, 1, 1 } , 0.0, "文在寅" };
    student_map[113] = Student{ 113, { 88, 92, 93, 86, 84, 81, 81, 80, 81, 89 }, { 3, 2, 1, 2, 1, 3, 3, 3, 2, 3 } , 0.0, "佐科" };
    student_map[114] = Student{ 114, { 94, 81, 89, 89, 80, 71, 88, 89, 89, 88 }, { 1, 3, 3, 2, 1, 1, 3, 1, 3, 3 } , 0.0, "莱希" };
    student_map[115] = Student{ 115, { 83, 85, 84, 82, 63, 81, 83, 64, 81, 83 }, { 1, 2, 1, 3, 1, 3, 1, 1, 1, 2 } , 0.0, "雅各布" };
    student_map[116] = Student{ 116, { 90, 81, 84, 91, 85, 88, 84, 72, 94, 87 }, { 2, 2, 2, 1, 2, 2, 1, 1, 2, 3 } , 0.0, "卢卡申科" };
    student_map[117] = Student{ 117, { 89, 81, 86, 88, 81, 91, 84, 75, 90, 88 }, { 2, 2, 2, 2, 1, 3, 3, 2, 2, 3 } , 0.0, "马克龙" };
    student_map[118] = Student{ 118, { 82, 80, 82, 94, 87, 80, 94, 80, 71, 92 }, { 1, 2, 3, 3, 1, 2, 3, 3, 2, 1 } , 0.0, "萨科奇" };
    student_map[119] = Student{ 119, { 89, 91, 80, 90, 85, 87, 87, 94, 81, 70 }, { 2, 3, 3, 2, 3, 2, 2, 3, 1, 3 } , 0.0, "默克尔" };
    student_map[120] = Student{ 120, { 88, 95, 84, 89, 92, 79, 80, 96, 83, 80 }, { 3, 4, 1, 3, 3, 2, 2, 4, 3, 3 } , 0.0, "金正恩" };
}
void set_student_gpa(map<int, Student>& student_map, map<double, int>& gpa_order)
{
    for (auto& student : student_map)
    {
        student.second.set_GPA();
        double gpa = student.second.get_GPA();
        //(1) your code. 填充<gpa,id>数据到 gpa_order里

        gpa_order[gpa] = student.first;

    }
}
void print_student_research_quota(map<double, int>& gpa_order, map<int, Student>& student_map)
{
    int pass_count = 3;
    int i = 0;
    //从后向前迭代容器：逆序迭代。因为map默认是从小到大排序，最小的元素放在最开始的位置
    for (auto itr = gpa_order.rbegin(); itr != gpa_order.rend(); ++itr)
    {
        auto& student = student_map[itr->second];
        cout << "排名=" << i + 1 << ", GPA="
            //fixed使用小数计数法(而不是科学计数法)显示浮点数
            << fixed
            //setprecision(2) 小数部分保留2位，最后一位四舍五入
            << setprecision(2) << student.get_GPA()
            << ", id=" << student.id;
        if (i < pass_count)
        {
            cout << ", 保研";
        }
        else
        {
            cout << ", 不保";
        }

        ++i;

        cout << ", name=" << student.name << endl;
    }
}

int lambda()
{
    //定义一个lambda表达式对象mod，用于对两个数求余
    auto mod = [](int a, int b) { return a % b; };

    cout << mod(3, 7) << endl;// 3%7=3
    cout << mod(7, 3) << endl;// 7%3=1
    cout << mod(3, 3) << endl;// 3%3=0
    cout << mod(7, 7) << endl;// 7%7=0

    return 0;
}

int lambda2()
{
    int start = 100;
    //值捕获start变量
    auto add = [start](int a, int b) -> int { return start + a + b; };

    cout << add(20, 3) << endl;// 100+20+3=123

    return 0;
}
int lambdaRef()
{
    int sum = 0;
    //引用捕获sum变量
    auto add = [&sum](int a, int b) { sum = a + b; };

    add(20, 3);// sum = 20+3 = 23
    cout << sum << endl;// 23

    return 0;
}

int lambda4()
{
    vector<int> arr{ 2, 7, 1, 8, 2, 8 };
    //按升序排序  sort 需要一个 函数  bool fun(int a, int b);
    std::sort(arr.begin(), arr.end(), [](int a, int b) { return a < b; });

    for (auto i : arr)
    {
        cout << i << " ";
    }

    return 0;
}

void multimapDemo()
{
    multimap<double, string> gpa_order
    {
        {3.79, "金正恩"},
        {3.79, "金正恩2"},
        {3.58, "马克龙"},
        {3.58, "马克凤"},
    };

    cout << "-----------------------------" << endl;
    //按照分数从低到高
    for (auto& item : gpa_order)
    {
        cout << item.second << " GPA=" << item.first << endl;
    }

    cout << "-----------------------------" << endl;
    //按照分数成绩好的在前面
    for (auto itr = gpa_order.rbegin(); itr != gpa_order.rend(); ++itr)
    {
        cout << itr->second << " GPA=" << itr->first << endl;
    }
}

int main()
{
    map<int, Student> student_map;
    init_student_data(student_map);

    map<double, int> gpa_order;
    //计算学生的GPA，并存放到gpa_order里
    set_student_gpa(student_map, gpa_order);

    //输出哪些学生被保研了，哪些没有
    print_student_research_quota(gpa_order, student_map);

    lambda();

    lambda2();

    lambdaRef();

    lambda4();

    multimapDemo();

    return 0;
}