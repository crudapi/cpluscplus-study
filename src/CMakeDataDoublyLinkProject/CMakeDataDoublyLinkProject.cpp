// CMakeDataDoublyLinkProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataDoublyLinkProject.h"

//------下面的代码是用来测试你的代码有没有问题的辅助代码，你无需关注------
#include <algorithm>
#include <cstdlib>
#include <iostream> 
#include <vector>
#include <utility>
using namespace std;
struct Record { Record(void* ptr1, size_t count1, const char* location1, int line1, bool is) :ptr(ptr1), count(count1), line(line1), is_array(is) { int i = 0; while ((location[i] = location1[i]) && i < 100) { ++i; } }void* ptr; size_t count; char location[100] = { 0 }; int line; bool is_array = false; bool not_use_right_delete = false; }; bool operator==(const Record& lhs, const Record& rhs) { return lhs.ptr == rhs.ptr; }std::vector<Record> myAllocStatistic; void* newFunctionImpl(std::size_t sz, char const* file, int line, bool is) { void* ptr = std::malloc(sz); myAllocStatistic.push_back({ ptr,sz, file, line , is }); return ptr; }void* operator new(std::size_t sz, char const* file, int line) { return newFunctionImpl(sz, file, line, false); }void* operator new [](std::size_t sz, char const* file, int line)
{
	return newFunctionImpl(sz, file, line, true);
}void operator delete(void* ptr) noexcept { Record item{ ptr, 0, "", 0, false }; auto itr = std::find(myAllocStatistic.begin(), myAllocStatistic.end(), item); if (itr != myAllocStatistic.end()) { auto ind = std::distance(myAllocStatistic.begin(), itr); myAllocStatistic[ind].ptr = nullptr; if (itr->is_array) { myAllocStatistic[ind].not_use_right_delete = true; } else { myAllocStatistic[ind].count = 0; }std::free(ptr); } }void operator delete[](void* ptr) noexcept { Record item{ ptr, 0, "", 0, true }; auto itr = std::find(myAllocStatistic.begin(), myAllocStatistic.end(), item); if (itr != myAllocStatistic.end()) { auto ind = std::distance(myAllocStatistic.begin(), itr); myAllocStatistic[ind].ptr = nullptr; if (!itr->is_array) { myAllocStatistic[ind].not_use_right_delete = true; } else { myAllocStatistic[ind].count = 0; }std::free(ptr); } }
#define new new(__FILE__, __LINE__)
struct MyStruct { void ReportMemoryLeak() { std::cout << "Memory leak report: " << std::endl; bool leak = false; for (auto& i : myAllocStatistic) { if (i.count != 0) { leak = true; std::cout << "leak count " << i.count << " Byte" << ", file " << i.location << ", line " << i.line; if (i.not_use_right_delete) { cout << ", not use right delete. "; }	cout << std::endl; } }if (!leak) { cout << "No memory leak." << endl; } }~MyStruct() { ReportMemoryLeak(); } }; static MyStruct my; void check_do(bool b, int line = __LINE__) { if (b) { cout << "line:" << line << " Pass" << endl; } else { cout << "line:" << line << " Ohh! not passed!!!!!!!!!!!!!!!!!!!!!!!!!!!" << " " << endl; exit(0); } }
#define check(msg)  check_do(msg, __LINE__);
//------上面的代码是用来测试你的代码有没有问题的辅助代码，你无需关注------
 
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
using namespace std;
 
template<typename T>
class DoublyLinkedList
{
	struct Node
	{
		Node() {}
		Node(T t) :data(t) {}
		T data;
		Node* prev = nullptr;
		Node* next = nullptr;
	};
public:
	DoublyLinkedList();
	~DoublyLinkedList();
	void insert(T t);
	string print(void) const;
	void backwardsPrint(void) const;
 
	void searchDelete(T t);
private:
	//当前类不支持复制，仅限于单个对象独立使用，主要是用于降低难度
	DoublyLinkedList<T>(const DoublyLinkedList<T>& from) = delete;
	//当前类不支持复制，仅限于单个对象独立使用，主要是用于降低难度
	DoublyLinkedList<T>& operator=(const DoublyLinkedList<T>& from) = delete;
 
	void searchDeleteLoop(T t);
	void deleteNode(Node*& p);
 
	Node m_head;
	Node m_tail;
};
 
template<typename T>
void DoublyLinkedList<T>::deleteNode(Node*& p)
{
	//p is not nullptr
	assert(p);
	Node* q = p->next;
	//1 inner node
	/*(1)*/ p->prev->next = p->next;
	/*(2)*/ p->next->prev = p->prev;
	delete p;
	p = q;//p指向被删除节点的下一个节点
}
template<typename T>
void DoublyLinkedList<T>::backwardsPrint(void) const
{
	Node* p = m_tail.prev;
	while (p != &m_head)
	{
		cout << p->data << " ";
		//(1) your code
		p = p->prev;
 
	}
	cout << endl;
}
template<typename T>
void DoublyLinkedList<T>::searchDeleteLoop(T t)
{
	Node* p = m_head.next;
	while (p)
	{
		if (p->data == t)
		{
			//p=p->next is finished inner
			//(2) your code
			deleteNode(p);
		}
		else
		{
			p = p->next;
		}
	}
}
 
template<typename T>
void DoublyLinkedList<T>::searchDelete(T t)
{
	searchDeleteLoop(t);
}
template<typename T>
DoublyLinkedList<T>::DoublyLinkedList()
{
	//(3) your code
	m_head.prev = nullptr;
	m_head.next = &m_tail;
 
	m_tail.prev = &m_head;
	m_tail.next = nullptr;
}
template<typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
	Node* p = m_head.next;
	while (p != &m_tail)
	{
		Node* q = p;
		p = p->next;
		delete q;
	}
	m_head.next = &m_tail;
	m_tail.prev = &m_head;
}
template<typename T>
void DoublyLinkedList<T>::insert(T t)
{
	Node* p = new Node(t);
 
	Node* right = m_head.next;
	while (right != &m_tail && right->data < p->data)
	{
		right = right->next;
	}
	//inner insert
	/*(1)*/ right->prev->next = p;
	/*(2)*/ p->prev = right->prev;
	/*(3)*/ p->next = right;
	//(4) your code
	right->prev = p;
}
 
template<typename T>
string DoublyLinkedList<T>::print(void) const
{
	ostringstream oss;
	Node* p = m_head.next;
	while (p != &m_tail)
	{
		oss << p->data << " ";
		p = p->next;
	}
	string result = oss.str();
	return result;
}
 
 
int main()
{
	DoublyLinkedList<int> dlist;
	dlist.insert(5);
	check(dlist.print() == "5 ");
	dlist.insert(2);
	check(dlist.print() == "2 5 ");
	dlist.insert(8);
	check(dlist.print() == "2 5 8 ");
	dlist.insert(7);
	check(dlist.print() == "2 5 7 8 ");
	dlist.insert(7);
	check(dlist.print() == "2 5 7 7 8 ");
	dlist.insert(8);
	check(dlist.print() == "2 5 7 7 8 8 ");
	dlist.insert(9);
	check(dlist.print() == "2 5 7 7 8 8 9 ");
	dlist.backwardsPrint();
	dlist.searchDelete(2);
	check(dlist.print() == "5 7 7 8 8 9 ");
	dlist.backwardsPrint();
	dlist.searchDelete(9);
	check(dlist.print() == "5 7 7 8 8 ");
	dlist.backwardsPrint();
	dlist.searchDelete(7);
	check(dlist.print() == "5 8 8 ");
	dlist.insert(7);
	check(dlist.print() == "5 7 8 8 ");
	dlist.searchDelete(7);
	check(dlist.print() == "5 8 8 ");
	dlist.searchDelete(5);
	check(dlist.print() == "8 8 ");
	dlist.searchDelete(8);
	check(dlist.print() == "");
	dlist.insert(7);
	check(dlist.print() == "7 ");
	dlist.backwardsPrint();
	return 0;
}