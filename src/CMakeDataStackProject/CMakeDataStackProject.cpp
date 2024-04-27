// CMakeDataStackProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataStackProject.h"

#include <iostream>
#include <iomanip>
 
// >>>>>>>>>>>>> do not care the code about memory leak checking. begin <<<<<<<<<<<<<<<
#include <iostream>
#include <cassert>
#include <iostream>
#include <ctime>
#include <iomanip>
#include <chrono>
using namespace std;

void print_now(void)
{
    using namespace std::chrono;
    std::time_t tt = system_clock::to_time_t(system_clock::now());
    auto microsecond = duration_cast<microseconds>(system_clock::now().time_since_epoch()).count() % 1000000;
    struct std::tm  valtm;
    localtime_s(&valtm, &tt);
    cout << std::put_time(&valtm, "%F %X") << " " << microsecond / 1000 << " " << microsecond;//2021-03-16 12:37:38 星期2
}
struct MemoryNode{
    void* ptr = 0;
    bool m_released = false;
    size_t byte_count = 0;
    char file[100] = { 0 };
    int line = -1;
    bool is_array = false;
    MemoryNode* next = nullptr;
};
struct MemoryList{
    ~MemoryList(){
        bool exist_leak = false;
        auto temp = head.next;
        while (temp){
            if (temp->m_released == false){
                cout << "memory leak " << temp->byte_count << " byte(s) !!!" << endl;
                exist_leak = true;
            }
            temp = temp->next;
        }
        if (!exist_leak){
            cout << "OK good job ! No memory leak." << endl;
        }
		print_now();
    }
    static MemoryNode* C_NewNode(void* ptr, size_t size, const char* file, int line, bool is_array){
        auto pnode = (MemoryNode*)malloc(sizeof(MemoryNode));
        pnode->ptr = ptr;
        pnode->m_released = false;
        pnode->byte_count = size;
        for (char* p = pnode->file; *file != '\0'; p++, file++) {*p = *file;}
        pnode->line = line;
        pnode->is_array = is_array;
        pnode->next = nullptr;
        return pnode;
    }
    void push_back(MemoryNode* pnode){
        if (tail == nullptr){
            head.next = tail = pnode;
        }else{
            tail->next = pnode;
            tail = tail->next;
        }
        ++m_size;
    }
    MemoryNode* find(void* ptr){
        auto temp = head.next;
        while (temp){
            if (temp->ptr == ptr){
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }
private:
    int m_size = 0;
    MemoryNode head;
    MemoryNode* tail = nullptr;
};
static MemoryList g_MemoryList;
void* operator new(size_t size, char const* file, int line){
    void* ptr = malloc(size);
    auto pnode = MemoryList::C_NewNode(ptr, size, file, line, false);
    g_MemoryList.push_back(pnode);
    return ptr;
}
void* operator new[](std::size_t size, char const* file, int line){
    void* ptr = malloc(size);
    auto pnode = MemoryList::C_NewNode(ptr, size, file, line, true);
    g_MemoryList.push_back(pnode);
    return ptr;
}
void operator delete(void* ptr) noexcept{
    if (ptr == nullptr)
    {
        cout << "can not delete nullptr !!!" << endl;
        assert(false);
    }
    auto node = g_MemoryList.find(ptr);
    if (node == nullptr){
        cout << "you want to free memory which is not allocated from new !!!" << endl;
        assert(false);
    }
    else
    {
        if (node->is_array){
            cout << "momory allocated at line " << node->line << ", you want to free memory by delete not delete[] which is allocatd from new[] !!!" << endl;
            assert(false);
        }
        if (node->m_released){
            cout << "momory allocated at line " << node->line << ", you want to free one memory twice !!!" << endl;
            assert(false);
        }
        node->m_released = true;
    }
}
//void operator delete(void*, std::size_t)//Ubuntu need
//{
//    assert(false);
//}
//void operator delete[](void*, std::size_t)//Ubuntu need
//{
//    assert(false);
//}
void operator delete[](void* ptr) noexcept{
    if (ptr == nullptr)
    {
        cout << "can not delete nullptr !!!" << endl;
        assert(false);
    }
    auto node = g_MemoryList.find(ptr);
    if (node == nullptr){
        cout << "you want to free memory which is not allocated from new !!!" << endl;
        assert(false);
    }
    else{
        if (!node->is_array){
            cout << "momory allocated at line " << node->line << ", you want to free memory by delete[] not delete which is allocatd from new !!!" << endl;
            assert(false);
        }
        if (node->m_released){
            cout << "momory allocated at line " << node->line << ", you want to free one memory twice !!!" << endl;
            assert(false);
        }
        node->m_released = true;
    }
}
void operator delete(void* pMem, const char* pszFilename, int nLine){ //msvc need
    cout << (int*)pMem << pszFilename << nLine << endl;
    free(pMem);
    assert(false);
}
void operator delete[](void* pMem, const char* pszFilename, int nLine){ //msvc need
    cout << (int*)pMem << pszFilename << nLine << endl;
    free(pMem);
    assert(false);
}
#define new new(__FILE__, __LINE__)
void check_do(bool b, int line = __LINE__) { if (b) { cout << "line:" << line << " Pass" << endl; } else { cout << "line:" << line << " Ohh! not passed!!!!!!!!!!!!!!!!!!!!!!!!!!!" << " " << endl; exit(0); } }
#define check(msg)  check_do(msg, __LINE__);
// >>>>>>>>>>>>> do not care the code about memory leak checking. begin <<<<<<<<<<<<<<<
 
 
//2020-07-09
template<typename T>
class Stack
{
public:
    Stack(void);
    Stack(const Stack& _stack);
    Stack& operator=(const Stack& _stack);
    ~Stack(void);

public:
    inline const T& top(void) const;
    inline bool empty(void) const;
    inline size_t size(void) const;
    void push(const T& _item);
    void pop(void);
    void clear(void);
private:
    void copy(const Stack& stack1);
private:
    struct CStackitem
    {
    public:
        CStackitem(void);
        CStackitem(const T& _data, CStackitem* next = nullptr);
    public:
        CStackitem(CStackitem& _item) = delete;// =  delete 表示禁止编译器生成默认版本的函数，主要用来禁止该类型对象拷贝
        CStackitem& operator=(CStackitem& _item) = delete;
    public:
        CStackitem* next = nullptr;//这里的初始化会在所有构造函数执行之前先执行，所以构造函数里就不用再对该成员初始化了
        T data;
    };
private:
    CStackitem m_head;//注意这里不是指针类型
    size_t m_size = 0;//注意这里的初始化会先于所有构造函数
};

template<typename T>
Stack<T>::CStackitem::CStackitem(void)
:data()//这里data如果是类对象，会调用类的默认构造函数；如果是基础类型，编译器会给一个合适的值
{
}

template<typename T>
Stack<T>::CStackitem::CStackitem(const T& _data, CStackitem* _next)
    :data(_data), next(_next)
{
}
template<typename T>
Stack<T>::Stack(void)
{
}

template<typename T>
Stack<T>::Stack(const Stack& _stack)
{
    //(1) your code  使用 copy 即可
    copy(_stack);
}

template<typename T>
Stack<T>& Stack<T>::operator=(const Stack& _stack)
{
    //(2) your code 记得判断同一个对象赋值给自己
    if (this == &_stack) {
        return *this;
    }


    copy(_stack);

    return *this;
}

template<typename T>
Stack<T>::~Stack(void)
{
    clear();
}
template<typename T>
bool Stack<T>::empty(void) const
{
    return m_size == 0;
}
template<typename T>
void Stack<T>::pop(void)
{
    //(6) your code 注意对象获取成员用"."操作符，指针获取成员用"->"操作符
    delete m_head.next;

    m_head.next = m_head.next->next;

    --m_size;

}
template<typename T>
void Stack<T>::clear(void)
{
    //(3) your code 可以利用 pop() + empty() 来实现。只要栈里还有元素，就弹出，直到栈空为止。
    while (!empty()) {
        pop();
    }

}
template<typename T>
void Stack<T>::copy(const Stack& from)
{
    //(4) your code 请先使用 clear ，再遍历链表来实现
    clear();

    CStackitem* p = from.m_head.next;
    CStackitem* last = &m_head;
    while (p != nullptr) {
        CStackitem* item = new CStackitem();
        item->data = p->data;

        last->next = item;
        last = item;

        ++m_size;
        p = p->next;
    }
}
template<typename T>
size_t Stack<T>::size(void) const
{
    return m_size;
}
template<typename T>
void Stack<T>::push(const T& item)
{
    //(5) your code， 注意 这样写新创建的节点 CStackitem* p = new CStackitem(item, first);
    CStackitem* p = new CStackitem(item, m_head.next);

    m_head.next = p;

    ++m_size;

}
template<typename T>
const T& Stack<T>::top(void) const
{
    return m_head.next->data;
}

int main(int argc, char** argv)
{
    Stack<int> stack1;
    check(stack1.size() == 0);
    stack1.push(1);
    check(stack1.size() == 1);
    auto stack2 = stack1;
    auto top = stack2.top();
    check(top == 1);
    check(stack2.size() == 1);
    stack1 = stack2;// 1 and 1
    stack1.push(2);// 2 1
    top = stack2.top();
    check(top == 1);
    check(stack1.size() == 2);
    check(stack1.top() == 2);
    stack1.clear();
    check(stack1.size() == 0 && stack1.empty());
    for (size_t i = 0; i < 10; i++)
    {
        stack1.push(i);
    }

    auto stackCopy = stack1;
  
    while (!stack1.empty())
    {
        std::cout << stack1.top() << " ";
        stack1.pop();
    }
    cout << endl;
    

    cout << "stack1 Copy" << endl;;
    while (!stackCopy.empty())
    {
        std::cout << stackCopy.top() << " ";
        stackCopy.pop();
    }

    cout << endl;
    check(stack1.size() == 0 && stack1.empty());
    //copy constructor
    {
        Stack<int> from;
        from.push(1);
        from.push(2);
        Stack<int> to(from);

        check(to.size() == 2);
        check(to.top() == 2);
        to.pop();
        check(to.top() == 1);
        to.pop();
        check(to.empty());
    }
}