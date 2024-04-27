// CMakeDataSLListIntProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataSLListIntProject.h"

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
                cout<<"line "<<temp->line << " memory leak " << temp->byte_count << " byte(s) !!!" << endl;
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
#include <iostream>
#include <string>
//一个容器总是要能够对其元素进行：增加/删除/修改/查询
class SLListInt
{
public:
    SLListInt() {};//默认构造函数
    SLListInt(const SLListInt& from);//复制构造函数
    SLListInt& operator = (const SLListInt& from);//赋值操作符重载
    ~SLListInt();//析构函数
public:
    void print(std::ostream& out);
    void push_front(const int& t);
    void push_back(const int& t);
    void pop_back(void);
    void pop_front(void);
    int& front(void);
    const int& front(void) const;
    int& back(void);
    const int& back(void) const;
    bool exist(const int& e);
    bool empty(void) const { return m_size == 0; }//判断链表是否为空
    int size(void) const { return m_size; }//返回链表元素的数量
    void clear(void);//删除所有元素
    //删除第一个值为value的元素，如果没有，do nothing
    void erase_first(int value);
private:
    class SLNode
    {
        //SLListInt can access all members of SLNode
        friend class SLListInt;
    private:
        SLNode();
        SLNode(const int& t);
        ~SLNode();
        int m_data;
        SLNode* m_next = nullptr;
    };
private:
    void copy(const SLListInt & from);
    //return the prev node of the first node with valude v in list
    // 注意：
    //a. 如果正好第一个节点就是要删除的节点，则返回第一个节点
    //b. 如果第二个节点是要删除的节点，也会返回第一个节点
    SLNode* find_first_for_erase(const int& v);//返回被删除节点的前一个节点

private:
    SLNode* m_head = nullptr;//pointer to the first node
    //pointer to the last node
    SLNode* m_tail = nullptr;//for push_back O(1)
    /*this size of list，for size() O(1)*/
    int m_size = 0;
};

SLListInt::SLNode::SLNode()
{
}
SLListInt::SLNode::SLNode(const int& t)
    : m_data(t)
{
}
SLListInt::SLNode::~SLNode()
{
}

SLListInt::SLListInt(const SLListInt& from)
{
    if (!from.empty())
    {
        copy(from);
    }
    std::cout << "SLListInt(const SLListInt & from)\n";
}

SLListInt& SLListInt::operator=(const SLListInt& from)
{
    std::cout << "SLListInt & DLListInt::operator=(const SLListInt & from)\n";
    if (this == &from)
    {
        return *this;
    }
    else
    {
        copy(from);
        return *this;
    }
}

SLListInt::~SLListInt()
{
    std::cout << "~SLListInt()\n";
    clear();
}

void SLListInt::print(std::ostream& out)
{
    auto p = m_head;
    while (p)
    {
        out << p->m_data << " ";
        //(1) your code.  move p to next node
        p = p->m_next;
    }
    out << std::endl;
}

void SLListInt::push_front(const int& t)
{
    if (empty())
    {
        //(2) your code. use push_back
        push_back(t);
    }
    else
    {
        auto p = new SLNode(t);
        //(3) update m_head, m_size
    
        p->m_next = m_head;
        m_head = p;
        ++m_size;
    }
}

void SLListInt::push_back(const int& t)
{
    //找到被插入的节点的前驱节点，默认的前驱节点就是头节点
    if (empty())
    {
        //(4) your code. update m_head, m_tail
        m_tail = new SLNode(t);
        m_head = m_tail;
        m_tail->m_next = nullptr;
    }
    else
    {
        //(5) your code. update m_tail
        m_tail->m_next = new SLNode(t);
        m_tail = m_tail->m_next;
    }
    //(6) your code. update m_size
    ++m_size;
}

void SLListInt::pop_back(void)
{
    assert(!empty());
    //1 only one element
    if (size() == 1)
    {
        //(7) your code. destroy the node. update m_head, m_tail
        delete m_head;
        m_head = nullptr;
        m_tail = nullptr;
    }
    else
    {
        auto p = m_head;
        //(8) your code. 找到被删除节点的前一个节点（前驱节点），才能删除被删除节点
        //use loop to find prev node
        while (p->m_next->m_next != nullptr) {
            p = p->m_next;
            break;
        }

        //当 p->next->next == nullptr 时，说明我找到了前驱节点 
        //delete p->next 删除 前驱节点的后一个节点
        delete p->m_next;
        p->m_next = nullptr;
        //update m_tail
        //(9) your code.
        m_tail = p;
    }
    //1 2 3 4 5 6 more than one element
    //(6) your code. update m_size
    --m_size;
}

void SLListInt::pop_front(void)
{
    if (empty())
    {
        throw std::runtime_error("SLListInt::pop_front while list is empty!");
    }
    auto next = m_head->m_next;
    auto front = m_head;
    //(10) your code. update the m_head
    m_head = next;
    //(11) your code. destroy the node
    delete front;
    --m_size;

    if (m_size == 0)
    {
        //(12) your code. update the m_head, m_tail
        m_head = nullptr;
        m_tail = nullptr;
    }
}

int& SLListInt::front(void)
{
    if (empty())
    {
        throw std::runtime_error("SLListInt::front called while *this is empty!");
    }
    return m_head->m_data;
}

const int& SLListInt::front(void) const
{
    if (empty())
    {
        throw std::runtime_error("SLListInt::front called while *this is empty!");
    }
    return m_head->m_data;
}

int& SLListInt::back(void)
{
    if (empty())
    {
        throw std::runtime_error("SLListInt::back called while *this is empty!");
    }
    return m_tail->m_data;
}

const int& SLListInt::back(void) const
{
    if (empty())
    {
        throw std::runtime_error("SLListInt::back called while *this is empty!");
    }
    return m_tail->m_data;
}

bool SLListInt::exist(const int& e)
{
    auto p = m_head;
    while (p != nullptr)
    {
        if (p->m_data == e)
        {
            //(13) your code. return directly.
            return true;
        }
        //(13) your code. update p
        p = p->m_next;
    }
    return false;
}

void SLListInt::clear(void)
{
    //(14) your code. use empty() + pop_front() to impliment this function
    
    while (!empty()) {
        pop_front();
    }

}
SLListInt::SLNode* SLListInt::find_first_for_erase(const int& value)
{
    auto prev = m_head;
    auto p = m_head;
    while (p != nullptr)
    {
        if (p->m_data == value)
        {
            return prev;
        }
        //(15)your code. update prev and p
        prev = p;
        p = p->m_next;
    
    }
    return nullptr;
}
void SLListInt::erase_first(int value)
{
    //(1) p == head 
    //(2) p->next->data == value
    auto p = find_first_for_erase(value);
    if (p == nullptr)
    {
        return;
    }
    // find_first_for_erase 函数是有歧义的，见其函数生命
    if (value == m_head->m_data)//第一个节点就是要删除的节点，直接删除
    {
        //(16)your code. use pop_front() to erase
        pop_front();
    }
    else
    {
        auto q = p->m_next;
        //1 (value) 2
        //p    q 
        if (q == m_tail)
        {
            m_tail = p;
        }
        p->m_next = q->m_next;
        delete q;
        --m_size;
    }
}

void SLListInt::copy(const SLListInt& from)
{
    //(17)your code. use clear(), push_back() to implement this function.
    clear();
    //p is used to iterator the list object from
    auto p = from.m_head;
    for (int i = 0; i < from.m_size; i++)
    {
        push_back(p->m_data);
        p = p->m_next;
    }
}



void test_default(void)
{
    //test empty/size;
    std::cout << "test_default" << std::endl;
    SLListInt slist;
    check(slist.size() == 0);
    check(slist.empty());
}
void test_push_back(void)
{
    std::cout << "test_push_back" << std::endl;
    SLListInt slist;
    slist.push_back(1);
    slist.push_back(2);
    slist.push_back(3);
    slist.print(cout);//1 2 3
    check(slist.size() == 3);
    check(slist.empty() == false);
}
void test_back(void)
{
    std::cout << "test_back" << std::endl;
    SLListInt slist;
    slist.push_back(1);
    check(slist.back() == 1);
    slist.push_back(2);
    check(slist.back() == 2);
    slist.push_back(3);
    check(slist.back() == 3);
}
void test_push_front(void)
{
    std::cout << "test_push_front" << std::endl;
    SLListInt slist;
    slist.push_front(1);
    slist.push_front(2);
    slist.push_front(3);
    slist.print(cout);//3 2 1 
    check(slist.size() == 3);
    check(slist.empty() == false);
}
void test_front(void)
{
    std::cout << "test_front" << std::endl;
    SLListInt slist;
    slist.push_front(1);
    check(slist.front() == 1);
    slist.push_front(2);
    check(slist.front() == 2);
    slist.push_front(3);
    check(slist.front() == 3);
}
void test_pop_back(void)
{
    std::cout << "test_pop_back" << std::endl;
    SLListInt slist;
    slist.push_back(1);
    slist.push_back(2);
    slist.push_back(3);
    slist.pop_back();
    check(slist.back() == 2);//1 2
    slist.pop_back();//1
    check(slist.back() == 1);
    check(slist.size() == 1);
    slist.pop_back();//
    check(slist.empty());
}
void test_pop_front(void)
{
    std::cout << "test_pop_front" << std::endl;
    SLListInt slist;
    slist.push_back(1);
    slist.push_back(2);
    slist.push_back(3);//1 2 3
    slist.pop_front();//2 3
    check(slist.front() == 2);
    slist.pop_front();//3
    check(slist.front() == 3);
    slist.pop_front();
    check(slist.empty());
}
void test_exist(void)
{
    std::cout << "test_exist" << std::endl;
    SLListInt slist;
    slist.push_back(1);
    check(slist.exist(1));
    slist.push_back(2);
    check(slist.exist(2));
    slist.push_back(3);//1 2 3
    check(slist.exist(3));
    slist.push_back(4);//1 2 3 4
    check(slist.exist(4));
    slist.push_front(0);//0 1 2 3 4
    check(slist.exist(0));
    slist.print(cout);//0 1 2 3 4
}
void test_erase(void)
{
    std::cout << "test_erase" << std::endl;
    SLListInt slist;
    slist.push_back(1);
    slist.push_back(2);
    slist.push_back(3);//1 2 3
    slist.push_back(3);//1 2 3 3
    slist.push_back(4);//1 2 3 3 4
    slist.push_front(0);//0 1 2 3 3 4

    slist.print(cout);//0 1 2 3 3 4

    slist.erase_first(0);//1 2 3 3 4
    check(slist.front() == 1);
    slist.erase_first(3);
    slist.print(cout);//1 2 3 4
    slist.erase_first(4);
    slist.print(cout);//1 2 3
    check(slist.back() == 3);
    slist.erase_first(1);
    slist.erase_first(2);
    check(slist.front() == slist.back());
    check(slist.front() == 3);
    slist.erase_first(3);
    check(slist.empty());
}
void test_erase2(void)
{
    std::cout << "test_erase" << std::endl;
    SLListInt slist;
    slist.push_back(1);
    slist.push_back(2);
    slist.push_back(3);//1 2 3
    slist.print(cout);//0 1 2 3 3 4
    slist.erase_first(2);
    check(slist.front() == 1);
    slist.erase_first(1);
}
void test_copy(void)
{
    std::cout << "test_copy" << std::endl;
    SLListInt slist;
    slist.push_back(1);
    slist.push_back(2);
    slist.push_back(3);//1 2 3
    slist.push_back(4);//1 2 3 4

    SLListInt slist2(slist);
    slist2.print(cout);//1 2 3 4
    check(slist2.size() == 4);
    check(slist2.back() == 4);
    check(slist2.front() == 1);
}
void test_assign(void)
{
    std::cout << "test_assign" << std::endl;
    SLListInt slist;
    slist.push_back(1);
    slist.push_back(2);
    slist.push_back(3);//1 2 3
    slist.push_back(4);//1 2 3 4

    SLListInt slist2;
    slist2 = slist;
    slist2.print(cout);//1 2 3 4
    check(slist2.size() == 4);
    check(slist2.back() == 4);
    check(slist2.front() == 1);
}
int main()
{
    test_default();
    test_push_back();
    test_back();
    test_push_front();
    test_front();
    test_pop_back();
    test_pop_front();
    test_exist();
    test_erase();
    test_erase2();
    test_copy();
    test_assign();
}
