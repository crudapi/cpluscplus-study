// CMakeStdStackProject.cpp: 定义应用程序的入口点。
//

#include "CMakeStdStackProject.h"

#include <iostream>
#include <iomanip>
#include <list>
using namespace std;
 
//内存泄漏检测 begin
#include <assert.h>
#include <iostream>
#include <atomic>
#include <string>
/*author: toy_lee5566(weixin)*/
class should_static_data {
public:
    should_static_data(const char* name) :m_name(name), counter_(0) {};
    ~should_static_data() { std::cout << "class " << m_name << " memory leak num = " << counter_ << std::endl; };
    void inc() { ++counter_; }
    void dec() { --counter_;	assert(counter_ >= 0); }
private:
    std::atomic<long long> counter_;
    std::string m_name;
};
template<typename T>
class should_value_data_counter {
public:
    should_value_data_counter() { m_data.inc(); }
    ~should_value_data_counter() { m_data.dec(); }
    should_value_data_counter(const should_value_data_counter&) { m_data.inc(); }
private:
    //一个类只有这一个对象，这个对象维护计数器
    static should_static_data m_data;
};
//TIPS:模板类的静态成员可以定义在头文件中，被链接程序特殊处理
template<typename T>
should_static_data should_value_data_counter<T>::m_data(typeid(T).name());
//示例用法
/*
class A
{
public:
    //这个对象的复制析构引发该类should_value_data_counter静态成员m_data的计数
    should_value_data_counter<A> m_checker;
};
*/
//内存泄漏检测 end
//检查是否通过测试 begin
void check_do(bool b, int line = __LINE__)
{
    if (b) { cout << "line:" << line << " Pass" << endl; }
    else { cout << "line:" << line << " Ohh! not passed!!!!!!!!!!!!!!!!!!!!!!!!!!!" << " " << endl; exit(0); }
}
#define check(msg)  check_do(msg, __LINE__);
//检查是否通过测试 end
 
 
class CStack
{
public:
    const int& top(void) const;
    bool empty(void) const;
    size_t size(void) const;
    void push(const int& _item);
    void pop(void);
    void clear(void);
private:
    std::list<int> m_stack;
    //下面的这个成员不要删除，请忽略即可。
    should_value_data_counter<CStack> m_checker;
};
 
bool CStack::empty(void) const
{
    return m_stack.empty();
}
 
void CStack::pop(void)
{
    m_stack.pop_back();
}
 
void CStack::clear(void)
{
    m_stack.clear();
}
 
size_t CStack::size(void) const
{
    return m_stack.size();
}
 
void CStack::push(const int& item)
{
    m_stack.push_back(item);
}
 
const int& CStack::top(void) const
{
    return m_stack.back();
}
 
int main(int argc, char** argv)
{
    //test clear
    {
        CStack s;
        check(s.size() == 0);
        check(s.empty());
        s.push(1);
        check(s.size() == 1);
        check(s.empty() == false);
        s.clear();
        check(s.size() == 0);
        check(s.empty());
    }
    CStack stack1;
    check(stack1.size() == 0);
    stack1.push(1);
    check(stack1.size() == 1);
    auto stack2 = stack1;
    check(stack2.size() == 1);
    stack1 = stack2;
    stack1.push(2);
    auto top = stack2.top();
    check(top == 1);
    check(stack1.size() == 2);
    check(stack1.top() == 2);
    stack1.clear();
    check(stack1.size() == 0 && stack1.empty());
    for (size_t i = 0; i < 10; i++)
    {
        stack1.push(i);
    }
    while (!stack1.empty())
    {
        std::cout << stack1.top() << std::endl;
        stack1.pop();
    }
    check(stack1.size() == 0 && stack1.empty());
}