// CMakeFriendOperatorProject.cpp: 定义应用程序的入口点。
//

#include "CMakeFriendOperatorProject.h"

#include <iostream>//cin cout
#include <vector> // vector 容器
#include <string> // string 字符串
#include <fstream>// ifstream 读文件的类
#include <iomanip>// setw 设置一个变量输出占多少个字符，如果不足，补空格，通常和对其 left right 搭配使用
using namespace std;

//个人信息类
class Person
{
public:
    //friend 表示函数 operator<< 可以访问类Person对象person的私有private成员变量
    //output person to cout or ofstream 
    //输出个人信息person到os对象里，os可以是cout，或者也可以是ofstream对象
    friend ostream& operator<<(ostream& os, const Person& person);
    //read data from cin or ifstream to person
    //从is对象（可以是cin,或者是ifstream对象）中读取信息到个人信息对象person中
    friend istream& operator>>(istream& is, Person& person);

public:
    //三个字符串成员变量
    string m_id;
    string m_name;
    string m_tel;
};

//store all person read from file
vector<Person> allPersonArray;//global variable

ostream& operator<<(ostream& os, const Person& person)
{
    //left表示左对齐，setw(5)表示后面的person.m_id输出占5个字符，如果不足5个用空格在后面补上，这就是左对齐
    os << left << setw(5) << person.m_id << setw(15) << person.m_name << setw(20) << person.m_tel;
    return os;
}

istream& operator>>(istream& is, Person& person)
{
    //(1) your code 
    is >> person.m_id >> person.m_name >> person.m_tel;
    return is;
}
//从文件"data.txt"中读取多个person数据放到allPersonArray中
bool LoadAllPersonFromFile(string fileName)
{
    ifstream fin(fileName);//fin对象创建的时候打开名字为fileName的值（"data.txt"）的文件
    if (!fin.is_open())//如果打开文件失败
    {
        //打开文件失败就输出错误提示，告诉用户没有成功打开文件，后面的其他事情都不会做。
        cout << "load data failed . file " << fileName << " not exits." << endl;
        return false;
    }

    Person person;
    while (fin >> person)//一次读取文件中的三个字符串，分别赋值给自己的三个成员变量m_id m_name m_tel
    {
        //读取到一个person的数据，将person放到容器中
        //(2) your code 
        allPersonArray.push_back(person);
    }
    cout << "load data from file success." << endl;
    return true;
}

void ShowAllPerson(void)
{
    cout << "All Person:" << endl;
    cout << left << setw(5) << "id" << setw(15) << "name" << setw(20) << "tel" << endl;
    for (auto& item : allPersonArray)//范围for循环迭代容器中的每一个person对象给item
    {
        cout << item << endl;//输出容器中的每一个person对象，并打印一个换行符
    }
}

int main(int argv, char* argc[])
{
    //读取文件内容，用文件内容赋值给person对象，并将person对象放到容器allPersonArray中
    LoadAllPersonFromFile("data.txt");
    //输出allPersonArray中的每一个person对象到控制台
    ShowAllPerson();

    return 0;
}