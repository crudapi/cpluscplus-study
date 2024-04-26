// CMakeDataIteratorProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataIteratorProject.h"

#include <cassert>
using namespace std;
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
#include <cassert>
 
class Vector
{
public:
    Vector(void);//1 默认构造函数
    Vector(int count, int value);//2 非默认构造函数
    Vector(const Vector& from);//4 复制构造函数
    Vector(int* start, int* end);// 3 非默认构造函数
    Vector& operator = (const Vector& from);
    ~Vector();
public:
    size_t size(void) const;
    bool empty(void) const;
    const int& operator[] (size_t n) const;
    int& operator[] (size_t n);
    void push_back(const int& val);
public:
    class iterator
    {
        friend class  Vector;
        friend bool operator == (const iterator& lhs, const iterator& rhs);//用于实现!=,因为==非常容易实现
        friend bool operator != (const iterator& lhs, const iterator& rhs);
    public:
        iterator& operator++(); //用于前置形式
        int& operator*();//解引用操作符重载：解引用必须返回元素的引用
    private:
        int* m_hold = nullptr;
    };
    class const_iterator
    {
        friend class  Vector;
    public:
        bool operator == (const const_iterator& rhs)  const { return this->m_hold == rhs.m_hold; }//用于实现!=,因为==非常容易实现
        //这里用 == 来实现 != ，主要是为了复用 == 的代码。尤其是当 == 的逻辑变的复杂之后，复用的优势更加明显。
        bool operator != (const const_iterator& rhs)  const { return !(*this == rhs); };
        const_iterator& operator++(); //用于前置形式 ++itr  先改变自己，指向下一个位置，再返回自己
        //解引用必须返回元素的引用；同时，由于const_iterator不能修改元素，所以返回的元素引用也是const的
        const int& operator*() const;
    private:
        const int* m_hold = nullptr;
    };
    //noexcept 表示这个函数内不会抛出异常，这样有助于编译器优化代码生成
    const_iterator begin() const noexcept;
    iterator begin() noexcept;
    const_iterator end() const noexcept;
    iterator end() noexcept;
private:
    void clear(void);
private:
    //(0) your code 请给下面的三个成员变量定义的同时初始化，这样就不用在每个构造函数里都再初始化一遍了 C++11
    size_t m_size = 0;//当前元素数量
    size_t m_capacity = 0;//容量
    int* m_data = nullptr;//数据部分
};
Vector::Vector(void)
{
    std::cout << "Vector()" << std::endl;
}
 
Vector::Vector(const Vector& from)
{
    if (from.empty())
    {
        //成员变量已经在被你在定义时初始化了
        return;
    }
 
    m_capacity = m_size = from.m_size;
    m_data = new int[m_capacity];
    for (size_t i = 0; i < m_size; ++i)
    {
        m_data[i] = from.m_data[i];
    }
    std::cout << "Vector(const Vector & from)" << std::endl;
}
 
Vector::Vector(int count, int value)
//成员变量已经在被你在定义时初始化了，所以这里不需要再在初始化列表里初始化了
{
    if (count <= 0)
    {
        throw std::runtime_error("size of vector to init must bigger than zero!");
    }
    m_data = new int[count];
    for (int i = 0; i < count; i++)
    {
        m_data[i] = value;
    }
    m_capacity = m_size = count;
    std::cout << "Vector(const, value)" << std::endl;
}
 
Vector::Vector(int* start, int* end)
//成员变量已经在被你在定义时初始化了，所以这里不需要再在初始化列表里初始化了
{
    check(start != nullptr && end != nullptr);
    //https://zhuanlan.zhihu.com/p/666033549
    m_capacity = m_size = end - start;//指针减法得到间隔元素数量。这里如果用int来存放可能会盛不下，size_t可以保证盛放的下
    check(m_size > 0);
    m_data = new int[m_capacity];
    for (size_t i = 0; i < m_size; i++)
    {
        m_data[i] = *start++;
    }
    std::cout << "Vector(start, end)" << std::endl;
}
 
Vector& Vector::operator=(const Vector& from)
{
    if (this == &from)
    {
        return *this;
    }
    //先释放自己的数据
    clear();
    m_size = from.m_size;
    m_capacity = from.m_capacity;
    m_data = new int[m_capacity];
    for (size_t i = 0; i < m_size; i++)
    {
        m_data[i] = from.m_data[i];
    }
    return *this;
}
 
Vector::~Vector()
{
    if (m_data)
    {
        delete[] m_data;
    }
    std::cout << "~Vector()" << std::endl;
}
 
size_t Vector::size(void) const
{
    return m_size;
}
 
bool Vector::empty(void) const
{
    return m_size == 0;
}
 
const int& Vector::operator[](size_t n) const
{
    return m_data[n];
}
 
int& Vector::operator[](size_t n)
{
    return  m_data[n];
}

//下面的代码 函数名是 Vector::begin
//           返回值类型是 Vector::const_iterator
//返回值类型之所以要加类作用域是因为，返回值类型在函数作用域之外。这是由C语言继承而来的
Vector::const_iterator Vector::begin() const noexcept
{
    if (empty())
    {
        return end();
    }
    const_iterator itr;
    //(1) your code 下面的代码仅仅是让编译通过，可能需要你重新实现。如需修改itr的成员，考虑到Vector是iterator类的友元，可以直接修改。
    itr.m_hold = &m_data[0];
 
    return itr;
}
 
Vector::iterator Vector::begin() noexcept
{
    if (empty())
    {
        return end();
    }
    iterator itr;
    //(1) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    itr.m_hold = &m_data[0];
 
    return itr;
}
 
Vector::const_iterator Vector::end() const noexcept
{
    const_iterator itr;
    //(2) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    // 如果容器为空，不能返回下标返回的元素位置
    itr.m_hold = &m_data[m_size];
 
    return itr;
}
 
Vector::iterator Vector::end() noexcept
{
    iterator itr;
    //(2) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    // 如果容器为空，不能返回下标返回的元素位置
    itr.m_hold = &m_data[m_size];
 
    return itr;
}
 
void Vector::clear(void)
{
    //(3) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    if (m_size > 0) {
        delete[] m_data;
        m_data = nullptr;
        m_capacity = 0;
        m_size = 0;
    }
 
}
 
bool operator==(const Vector::iterator& lhs, const Vector::iterator& rhs)
{
    //(4) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    return lhs.m_hold == rhs.m_hold;;
}
 
bool operator!=(const Vector::iterator& lhs, const Vector::iterator& rhs)
{
    //(5) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    return !(lhs == rhs);
}
 
Vector::iterator& Vector::iterator::operator++()
{
    //(6) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    m_hold++;
    return *this;
}
Vector::const_iterator& Vector::const_iterator::operator++()
{
    //(7) your code 下面的代码仅仅是让编译通过，可能需要你重新实现
    m_hold++;
 
    return *this;
}
int& Vector::iterator::operator*()
{
    //(9) your code 下面的代码是错误的！不可以返回临时变量的引用！仅仅是让编译通过，需要你重新实现
    return *m_hold;
}
const int& Vector::const_iterator::operator*() const
{
    //(9) your code 下面的代码是错误的！不可以返回临时变量的引用！仅仅是让编译通过，需要你重新实现
    return *m_hold;
}

void Vector::push_back(const int& value)
{
    //如果capacity为0，则一次性开辟10个元素
    if (m_capacity == 0)
    {
        m_data = new int[10];
        m_data[0] = value;
        m_capacity = 10;
        m_size = 1;
    }
    else if (m_size < m_capacity)
    {
        //给最后一个元素的后面赋值为新元素value
        //增加元素数量
        //(5) your code
        m_data[m_size] = value;
        ++m_size;
    }
    else
    {
        //每次内存不够用就翻倍
        int* p = new int[2 * m_capacity];
        //先把原来的每个元素拷贝到新地方
        for (int j = 0; j < m_size; j++)
        {
            //(5.1) your code
            p[j] = m_data[j];

        }
        //把新添加的元素也添加到新地方
        //(6) your code
        p[m_size] = value;


        //记得元素数量加1
        //(7) your code
        ++m_size;


        //容量翻倍
        //(8) your code
        m_capacity = 2 * m_capacity;

        //释放原来的内存
        //(9) your code
        delete[] m_data;

        //成员变量接管新开普的内存
        //(10) your code
        m_data = p;

    }
}
void print(const Vector& v, const char* msg)
{
    std::cout << "print The contents of " << msg << " are:";
    for (size_t i = 0; i < v.size(); ++i)
    {
        std::cout << ' ' << v[i];
    }
    std::cout << '\n';
}
void print_itr(Vector& v, const char* msg)
{
    std::cout << "print_itr The contents of " << msg << " are:";
    for (auto itr = v.begin(); itr != v.end(); ++itr)
    {
        std::cout << ' ' << *itr;
    }
    std::cout << '\n';
}
void print_const_itr(const Vector& v, const char* msg)
{
    std::cout << "print_const_itr The contents of " << msg << " are:";
    for (auto itr = v.begin(); itr != v.end(); ++itr)
    {
        //*itr = 4;
        std::cout << ' ' << *itr;
    }
    std::cout << '\n';
}

void test_itr_plus(void)
{
    Vector v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    auto itr = v.begin();
    check(*itr == 1);
    check(itr != v.end());
}

int main()
{
    Vector a;
 
    Vector first;                   // empty vector of ints
    check(first.empty() == true && first.size() == 0);
    Vector second(4, 100);                       // four ints with value 100
    check(second.empty() == false);
    check(second.size() == 4);
    check(*second.begin() == 100);
    Vector fourth(second);                       // a copy of third
    check(fourth.size() == second.size());
 
    const int count = 4;
    int myints[count] = { 16,2,77,29 };
    Vector fifth(myints, myints + count);
    check(fifth.empty() == false);
    check(fifth[0] == 16);
    check(fifth[3] == 29);
    check(fifth.size() == count);
    print(fifth, "fifth");//The contents of fifth are:16 2 77 29 
    fifth.push_back(30);
    check(fifth[4] == 30);
    check(fifth.size() == 5);
    print(fifth, "fifth");//The contents of fifth are:16 2 77 29 30 
    check(fifth.size() == count + 1);
    first = fifth = fifth;
    print(first, "first");//The contents of first are:16 2 77 29 30 
    check(first.empty() == false && first.size() == fifth.size());
    print_itr(fifth, "fifth");//The contents of fifth are:16 2 77 29 30 
    print_const_itr(fifth, "fifth");//The contents of fifth are:16 2 77 29 30 
    Vector a1(myints, myints + count);
    {
        Vector b(a1);
        b.push_back(2);
        check(b[4] == 2);
    }
    {
        Vector c;
        for (auto i : c)
        {
            std::cout << i << " ";
        }
        c = a1;
        a1 = c;
        c = a1;
 
        for (auto i : c)
        {
            std::cout << i << " ";
        }
        std::cout << std::endl;
    }
    check(a1.size() == count);
    {
        Vector c;
        c = fifth;
        c[0] = 1;
        check(c[0] == 1);
    }
    test_itr_plus();
}