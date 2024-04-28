// CMakeDataPtrProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataPtrProject.h"

#include <iostream>

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
#include <iostream>
#include <vector>
using namespace std;

template<class T>
class my_shared_ptr
{
public:
    my_shared_ptr();
    my_shared_ptr(T*);
    my_shared_ptr(const my_shared_ptr& from);
    ~my_shared_ptr();
    my_shared_ptr& operator=(const my_shared_ptr& from);
    T* get(void);
    T& operator*(void);
    T* operator->(void);
private:
    void decrease(void);
    void copy(const my_shared_ptr& from);

    class share_count
    {
    public:
        share_count(void)
        {
            check(m_count == 1);
        }
        void add_count(void) { ++m_count; /*(4) your code. increase shared count*/ }
        void decrease_count(void) { --m_count; /*(5) your code. decrease shared count.*/ }
        long count(void) const { return m_count; }
        bool have_to_delete(void) const {/*(6) Re-implement this function*/ return m_count == 0; }
    private:
        long m_count = 1;//(2) your code. in this line you should initialize member m_count
    };

private:
    T* m_ptr = nullptr;//(1) your code. in this line you should initialize member m_ptr
    share_count* m_share_count;
};
template<class T>
my_shared_ptr<T>::my_shared_ptr()
    :m_share_count(new share_count)
{
    check(m_ptr == nullptr);
}

template<class T>
my_shared_ptr<T>::my_shared_ptr(T* t)
//(3) your code. implement the initialize list to init m_shared_count and m_ptr

{
    m_ptr = t;
    m_share_count = new share_count;
}

template<class T>
my_shared_ptr<T>::my_shared_ptr(const my_shared_ptr& from)
{
    copy(from);
}

template<class T>
my_shared_ptr<T>::~my_shared_ptr()
{
    decrease();
}

template<class T>
my_shared_ptr<T>& my_shared_ptr<T>::operator=(const my_shared_ptr& from)
{
    if (&from == this)
    {
        return *this;
    }
    else
    {
        decrease();
        copy(from);
    }
}

template<class T>
T* my_shared_ptr<T>::get(void)
{
    return m_ptr;
}

template<class T>
T& my_shared_ptr<T>::operator*(void)
{
    if (m_ptr)
    {
        return *m_ptr;
    }
    else
    {
        throw "operator* return *nullptr";
    }
}

template<class T>
T* my_shared_ptr<T>::operator->(void)
{
    if (m_ptr)
    {
        return m_ptr;
    }
    else
    {
        return nullptr;
    }
}

template<class T>
void my_shared_ptr<T>::decrease(void)
{
    //(7) your code.
    // case 1 : decrease the shared count first
    
    m_share_count->decrease_count();


    // case 2 : if have to delete , do delete. 
    if (m_share_count->have_to_delete())
    {
        //(8) your code.
        //do delete the object held.
        if (m_ptr != nullptr) {
            delete m_ptr;
            m_ptr = nullptr;
        }
       



        //(9) your code.
        //remember delete shared count object here
        if (m_share_count != nullptr) {
            delete m_share_count;
            m_share_count = nullptr;
        }

    }
}

template<class T>
void my_shared_ptr<T>::copy(const my_shared_ptr& from)
{
    //10 your code. shared the m_ptr and m_shared_count. and then increase the shared count.

    m_ptr = from.m_ptr;

    m_share_count = from.m_share_count;

    m_share_count->add_count();
}

class A
{
public:
    A();
    ~A();
    void Print(void) { std::cout << "I am an A objcet." << std::endl; }
    void PrintData(void) { std::cout << "I am an A objcet. My data is " << m_data << std::endl; }
    void SetData(int data);
private:
    int m_data = 100;
};
A::A()
{
    std::cout << "A::A()" << std::endl;
}
A::~A()
{
    std::cout << "A::~A()" << std::endl;
}
void A::SetData(int data)
{
    this->m_data = data;
}

void test_nullptr(void)
{
    //指向空指针的场景
    my_shared_ptr<A> p;
    auto p1 = p;
    auto p2(p);
}

void test_A(void)
{
    //指向动态对象的场景
    my_shared_ptr<A> p(new A);
    auto p1 = p;
    auto p2(p);
}
void test_pass_by_value(my_shared_ptr<int> p)
{
    *p = 100;
}
my_shared_ptr<A> test_create(void)
{
    my_shared_ptr<A> p(new A);
    return p;
}

int main(int argv, char* argc[])
{
    test_nullptr();
    test_A();
    auto p = test_create();
    p->PrintData();
    auto p1 = p;
    p->Print();
    p1->Print();
    (*p).Print();

    {
        my_shared_ptr<int> p(new int(1));
        cout << "int value :" << *p << endl;
        test_pass_by_value(p);
        cout << "int value now is :" << *p << endl;
        check(*p == 100);
    }

    return 0;
}