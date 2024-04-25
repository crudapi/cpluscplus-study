// CMakePersonProject.cpp: 定义应用程序的入口点。
//

#include "CMakePersonProject.h"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Person
{
public:
    friend ostream& operator<<(ostream& os, const Person& _person);
    friend istream& operator>>(istream& is, Person& _person);

public:
    string m_id;
    string m_name;
    string m_tel;
};

ostream& operator<<(ostream& os, const Person& person)
{
    os << left << setw(5) << person.m_id << setw(15) << person.m_name << setw(20) << person.m_tel;
    return os;
}

istream& operator>>(istream& is, Person& person)
{
    //(1) your code 
    // 使用输入操作符重载，将流中的数据，提取赋值给person对象的成员变量中
    //see https://zhuanlan.zhihu.com/p/412724745
    string lineText;
    while (getline(is, lineText))
    {
        istringstream iss(lineText);
        iss >> person.m_id >> person.m_name >> person.m_tel;
    }
    return is;
}

class PersonManager
{
public:
    void InputOnePerson(void);
    bool LoadAllPersonFromFile(const string& fileName);
    bool DeletePerson(void);
    bool QueryPersonByName() const;
    bool QueryPersonByTel() const;
    void ShowAllPerson(void) const;
    bool SaveAllPersonToFile(void) const;

private:
    vector<Person> m_allPerson;
};

bool PersonManager::DeletePerson(void)
{
    cout << "Please input person id for delete:";


    string id;
    cin >> id;
    for (auto itr = m_allPerson.begin(); itr != m_allPerson.cend(); ++itr)
    {
        if (itr->m_id == id)
        {
            //(2) your code
            // 容器的erase方法支持删除容器的元素时，传入指向元素的迭代器
            //see https://zhuanlan.zhihu.com/p/441293600

        }
    }
    return false;
}
bool PersonManager::QueryPersonByName() const
{
    //注意该函数需要返回bool值
    cout << "Please input name for query:";

    string name;
    cin >> name;
    for (auto itr = m_allPerson.cbegin(); itr != m_allPerson.cend(); ++itr)
    {
        if (itr->m_name == name)
        {
            cout << "Find:" << endl;
            //(3) your code
            //see https://zhuanlan.zhihu.com/p/376440190
            //see https://zhuanlan.zhihu.com/p/376446724

        }
    }
    cout << "not found " << name << endl;
    return false;
}
bool PersonManager::QueryPersonByTel() const
{
    cout << "Please input tel for query:";
    string tel;
    cin >> tel;
    for (auto itr = m_allPerson.cbegin(); itr != m_allPerson.cend(); ++itr)
    {
        if (itr->m_tel == tel)
        {
            cout << "Find:" << endl;
            //(4) your code
            //see https://zhuanlan.zhihu.com/p/376440190
            //see https://zhuanlan.zhihu.com/p/376446724

        }
    }
    cout << "not found " << tel << endl;
    return false;
}

void PersonManager::ShowAllPerson(void) const
{
    cout << "All Person:" << endl;
    cout << left << setw(5) << "id" << setw(15) << "name" << setw(20) << "tel" << endl;
    for (auto& item : m_allPerson)
    {
        cout << item << endl;
    }
}
bool PersonManager::SaveAllPersonToFile(void) const
{
    ofstream fout("data_saved.txt");
    //下面的常量迭代器 cbegin cend 中的 c 指的是 const的意思，表示不可以修改容器的元素
    for (auto itr = m_allPerson.cbegin(); itr != m_allPerson.cend(); ++itr)
    {
        //(5) your code 
        //see https://zhuanlan.zhihu.com/p/262508774

    }
    return true;
}

bool PersonManager::LoadAllPersonFromFile(const string& fileName)
{
    ifstream fin(fileName);
    if (!fin)
    {
        cout << "load data failed . file " << fileName << " not exits." << endl;
        return false;
    }

    Person person;
    while (fin >> person)
    {
        m_allPerson.push_back(person);
    }
    cout << "load data from file success." << endl;
    return true;
}

void PersonManager::InputOnePerson(void)
{
    cout << "Please input one person：" << endl;
    cout << "Please input id：";
    string id;
    cin >> id;
    Person person;
    person.m_id = id;

    for (auto itr = m_allPerson.cbegin(); itr != m_allPerson.cend(); ++itr)
    {
        if (itr->m_id == id)
        {
            cout << id << " already existed! Save failed." << endl;
            return;
        }
    }

    cout << "Please input name：";
    string name;
    cin >> name;
    person.m_name = name;

    cout << "Please input tel：";
    string tel;
    cin >> tel;
    person.m_tel = tel;

    cout << "Input finished, save successed." << endl;

    m_allPerson.push_back(person);
}

int main(int argv, char* argc[])
{
    PersonManager personMgr;
    personMgr.LoadAllPersonFromFile("input_data.txt");
    personMgr.ShowAllPerson();

    while (true)
    {
        cout << "input a commond : " << endl;
        cout << "1 [AddPerson]" << endl;
        cout << "2 [ShowAllPerson]" << endl;
        cout << "3 [QueryPerson by name]" << endl;
        cout << "4 [QueryPerson by tel]" << endl;
        cout << "5 [SaveAllPersonToFile]" << endl;
        cout << "6 [DeletePerson]" << endl;
        cout << "0 [ExitAndSaveChange]" << endl;
        int commond;
        cin >> commond;
        switch (commond)
        {
        case 1: { personMgr.InputOnePerson(); break; }
        case 2: { personMgr.ShowAllPerson(); break; }
        case 3: { personMgr.QueryPersonByName(); break; }
        case 4: { personMgr.QueryPersonByTel(); break; }
        case 5: { personMgr.SaveAllPersonToFile(); break; }
        case 6: { personMgr.DeletePerson(); break; }
        case 0: { personMgr.SaveAllPersonToFile(); return 0; }
        default: { cout << "System Exit." << endl; return 0; }
        }
    }
    return 0;
}