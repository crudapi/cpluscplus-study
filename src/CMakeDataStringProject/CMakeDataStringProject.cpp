// CMakeDataStringProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataStringProject.h"
#include <iostream>

//------下面的代码是用来测试你的代码有没有问题的辅助代码，你无需关注------
#include <algorithm>
#include <cstdlib>
#include <iostream> 
#include <vector>
#include <utility>
using namespace std;
struct Record
{
	Record(void* ptr1, size_t count1, const char* location1, int line1, bool is)
		:ptr(ptr1), count(count1), line(line1), is_array(is)
	{
		int i = 0;
		while ((location1[i] != '\0') && i < 100)
		{
			location[i] = location1[i];
			++i;
		}
	}
	void* ptr; size_t count; char location[100] = { 0 }; int line; bool is_array = false; bool not_use_right_delete = false;
}; bool operator==(const Record& lhs, const Record& rhs) { return lhs.ptr == rhs.ptr; }std::vector<Record> myAllocStatistic; void* newFunctionImpl(std::size_t sz, char const* file, int line, bool is) { void* ptr = std::malloc(sz); myAllocStatistic.push_back({ ptr,sz, file, line , is }); return ptr; }void* operator new(std::size_t sz, char const* file, int line) { return newFunctionImpl(sz, file, line, false); }void* operator new [](std::size_t sz, char const* file, int line)
{
	return newFunctionImpl(sz, file, line, true);
}void operator delete(void* ptr) noexcept { Record item{ ptr, 0, "", 0, false }; auto itr = std::find(myAllocStatistic.begin(), myAllocStatistic.end(), item); if (itr != myAllocStatistic.end()) { auto ind = std::distance(myAllocStatistic.begin(), itr); myAllocStatistic[ind].ptr = nullptr; if (itr->is_array) { myAllocStatistic[ind].not_use_right_delete = true; } else { myAllocStatistic[ind].count = 0; }std::free(ptr); } }void operator delete[](void* ptr) noexcept { Record item{ ptr, 0, "", 0, true }; auto itr = std::find(myAllocStatistic.begin(), myAllocStatistic.end(), item); if (itr != myAllocStatistic.end()) { auto ind = std::distance(myAllocStatistic.begin(), itr); myAllocStatistic[ind].ptr = nullptr; if (!itr->is_array) { myAllocStatistic[ind].not_use_right_delete = true; } else { myAllocStatistic[ind].count = 0; }std::free(ptr); } }
#define new new(__FILE__, __LINE__)
struct MyStruct { void ReportMemoryLeak() { std::cout << "Memory leak report: " << std::endl; bool leak = false; for (auto& i : myAllocStatistic) { if (i.count != 0) { leak = true; std::cout << "leak count " << i.count << " Byte" << ", file " << i.location << ", line " << i.line; if (i.not_use_right_delete) { cout << ", not use right delete. "; }	cout << std::endl; } }if (!leak) { cout << "No memory leak." << endl; } }~MyStruct() { ReportMemoryLeak(); } }; static MyStruct my; void check_do(bool b, int line = __LINE__) { if (b) { cout << "line:" << line << " Pass" << endl; } else { cout << "line:" << line << " Ohh! not passed!!!!!!!!!!!!!!!!!!!!!!!!!!!" << " " << endl; exit(0); } }
#define check(msg)  check_do(msg, __LINE__);
//------上面的代码是用来测试你的代码有没有问题的辅助代码，你无需关注------

class String
{
	friend std::ostream& operator<<(std::ostream& os, const String& str);
public:
	String(void);
	String(const char* data, int length);
	String(const char* data);

	String(const String& from);//1 复制构造
	String& operator = (const String& from);//2 赋值操作符
	size_t size(void) const { return m_length; }
	bool empty(void) const { return m_length == 0; }
	~String();//3 析构函数
	bool operator == (const String& other);
	bool operator != (const String& other) { return !(*this == other); }//代码复用
	String operator+(const String& other);
	void push_back(char c);
	void clear(void);

protected:
	void copy(const char* data, size_t length);
private:
	//注意这里在定义的时候初始化早于任何构造函数的执行，这是很方便的做法
	char* m_data = nullptr;
	size_t m_length = 0;
	int m_capacity = 0;
};
void String::push_back(char c)
{
	if (m_capacity > m_length)//直接追加到最后一个
	{
		m_data[m_length++] = c;
	}
	else//只有满了的那一瞬间，才翻倍开辟新空间
	{
		m_capacity = (m_capacity == 0 ? 10 : m_capacity + m_capacity);
		auto pNewArray = new char[m_capacity];
		//拷贝老数据
		for (size_t i = 0; i < m_length; i++)
		{
			pNewArray[i] = m_data[i];
		}
		//追加最新的末尾元素
		pNewArray[m_length++] = c;
		delete[] m_data;
		m_data = pNewArray;
	}
}
std::ostream& operator<<(std::ostream& os, const String& str)
{
	for (size_t i = 0; i < str.m_length; ++i)
	{
		os << str.m_data[i];
	}
	return os;
}
String::String(void)
{
}
String::~String()
{
	clear();
}
bool String::operator==(const String& other)
{
	if (this == &other)
	{
		return true;
	}
	if (other.m_length != this->m_length)
	{
		return false;
	}
	for (size_t i = 0; i < m_length; i++)
	{
		auto c1 = m_data[i];
		auto c2 = other.m_data[i];
		if (c1 != c2)
		{
			return false;
		}
	}
	return true;
}
String String::operator+(const String& other)
{
	if (other.empty())
	{
		return *this;
	}

	String result;
	result.m_length = result.m_capacity = m_length + other.m_length;
	result.m_data = new char[result.m_length];
	for (size_t i = 0; i < m_length; i++)
	{
		result.m_data[i] = m_data[i];
	}
	for (size_t i = 0; i < other.m_length; i++)
	{
		result.m_data[m_length + i] = other.m_data[i];
	}
	return result;
}
String::String(const char* data, int _length)
{
	copy(data, _length);
}
String::String(const char* data)
{
	int stringLength = 0;
	auto p = data;
	while (*p != '\0')
	{
		++stringLength;
		++p;
	}
	copy(data, stringLength);
}
String::String(const String& from)
{
	if (from.m_data != m_data)
	{
		copy(from.m_data, from.m_length);
	}
}
String& String::operator=(const String& from)
{
	if (&from != this)
	{
		copy(from.m_data, from.m_length);
	}
	return *this;
}

void String::clear(void)
{
	if (nullptr != m_data)
	{
		delete[] m_data;
		m_data = nullptr;
		m_length = 0;
	}
}
void String::copy(const char* data, size_t length)
{
	clear();
	m_data = new char[length];
	for (size_t i = 0; i < length; ++i)
	{
		m_data[i] = data[i];
	}
	m_length = length;
}

String GetLeftValue(void)
{
	String s("String");
	return s;
}
void Test0(void)
{
	auto leftValue1 = GetLeftValue();
	String left2;
	left2 = (left2 = leftValue1);
	std::vector<String> arrStr(2);
	left2 = (arrStr[0]);
	String arr[2];
	left2 = (arr[0]);
	auto p = arr;
	left2 = (*p);
	arrStr.push_back(left2);
}
void Test_empty(void)
{
	String s("");
	check(s.empty());
	check(s.size() == 0);
	check(s == "");
}
void Test_clear(void)
{
	String s2;
	{
		String s("123");
		check(s == "123");
		s2 = s;
		s.clear();
		s.clear();
		check(s.size() == 0);
		check(s.empty());
		check(s == "");
		check(s2 != s);
	}
	check(s2 == "123");
}
void Test_copy(void)
{
	{
		String s1("Hello World!");//constructor
		String s2(s1);//copy constructor
		cout << s2 << endl;//operator<<
		check(s1.size() == s2.size());//size
		String s3;
		s3 = s2;
		check(s3 == s1);
		check(!s3.empty());
		check(!s1.empty());
		s1 = s2 = s2 = s1;
		check(s1.size() == s2.size());//size
		check(s3 == s1);
		check(!s3.empty());
		check(!s1.empty());
		check(s1 == "Hello World!");
		s1.clear();
		check(s1.empty());
		check(s1 != s2);
		check(s2 == s3);
	}
	{
		String s;
		check(s.empty());
	}
	// +
	{
		String s1("Hello World!");//constructor
		String s2("Hello World!");//constructor
		String s3(s1 + s2);
		check(s3.size() == s1.size() + s2.size());
		check(s3 == s1 + s2);
		check(s3 == "Hello World!Hello World!");
	}
	{
		const char* p = "Hello World !";
		String s(p);
		check(s == p);
	}
	//push_back
	{
		String s;
		check(s.size() == 0);
		check(s.empty());
		s.push_back('a');
		check(s == "a");
		for (size_t i = 0; i < 100; i++)
		{
			s.push_back('a');
		}
		check(s.size() == 101);
	}
}

String GetValue(void)
{
	String a;
	String b;
	b = a;
	return a;
}

void test_add(void)
{
	String s1;
	String s2;
	String s12 = s1 + s2;
	check(s12.empty());
}
int main()
{
	Test0();
	Test_empty();
	Test_copy();
	Test_clear();

	{
		String s("123");
		check(s == s);
	}
	test_add();

	return 0;
}