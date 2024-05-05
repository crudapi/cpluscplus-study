#ifndef MEMORY_LEAK_CHECKER_H
#define MEMORY_LEAK_CHECKER_H

//memory checke library begin
#include <assert.h>
#include <iostream>
#include <atomic>
#include <string>
class object_usage_counter {
public:
    object_usage_counter(const char* name) :m_name(name), m_counter(0) {};
    ~object_usage_counter() { std::cout << "class " << m_name << " memory leak num = " << m_counter << std::endl; };
    void inc() { ++m_counter; }
    void dec() { --m_counter;	assert(m_counter >= 0); }
private:
    std::atomic<long long> m_counter;
    std::string m_name;
};
template<typename T>
class counter_by_copy {
public:
    counter_by_copy() { m_the_only_object_for_one_class.inc(); }
    ~counter_by_copy() { m_the_only_object_for_one_class.dec(); }
    counter_by_copy(const counter_by_copy&) { m_the_only_object_for_one_class.inc(); }
private:
    //the only object to count usage.
    static object_usage_counter m_the_only_object_for_one_class;
};
//TIPS:template class's static member object can be define at the .h file
template<typename T>
object_usage_counter counter_by_copy<T>::m_the_only_object_for_one_class(typeid(T).name());
//memory checke library end

#endif // !MEMORY_LEAK_CHECKER_H


//example usage
/*
class A
{
public:
    //A's copy control member functions call counter increasing or decreasing usage.
    counter_by_copy<A> m_checker;
};
*/
