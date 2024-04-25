// CMakeDeepControlProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDeepControlProject.h"

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
struct MemoryNode {
    void* ptr = 0;
    bool m_released = false;
    size_t byte_count = 0;
    char file[100] = { 0 };
    int line = -1;
    bool is_array = false;
    MemoryNode* next = nullptr;
};
struct MemoryList {
    ~MemoryList() {
        bool exist_leak = false;
        auto temp = head.next;
        while (temp) {
            if (temp->m_released == false) {
                cout << "memory leak " << temp->byte_count << " byte(s) !!!" << endl;
                exist_leak = true;
            }
            temp = temp->next;
        }
        if (!exist_leak) {
            cout << "OK good job ! No memory leak." << endl;
        }
        print_now();
    }
    static MemoryNode* C_NewNode(void* ptr, size_t size, const char* file, int line, bool is_array) {
        auto pnode = (MemoryNode*)malloc(sizeof(MemoryNode));
        pnode->ptr = ptr;
        pnode->m_released = false;
        pnode->byte_count = size;
        for (char* p = pnode->file; *file != '\0'; p++, file++) { *p = *file; }
        pnode->line = line;
        pnode->is_array = is_array;
        pnode->next = nullptr;
        return pnode;
    }
    void push_back(MemoryNode* pnode) {
        if (tail == nullptr) {
            head.next = tail = pnode;
        }
        else {
            tail->next = pnode;
            tail = tail->next;
        }
        ++m_size;
    }
    MemoryNode* find(void* ptr) {
        auto temp = head.next;
        while (temp) {
            if (temp->ptr == ptr) {
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
void* operator new(size_t size, char const* file, int line) {
    void* ptr = malloc(size);
    auto pnode = MemoryList::C_NewNode(ptr, size, file, line, false);
    g_MemoryList.push_back(pnode);
    return ptr;
}
void* operator new[](std::size_t size, char const* file, int line) {
    void* ptr = malloc(size);
    auto pnode = MemoryList::C_NewNode(ptr, size, file, line, true);
    g_MemoryList.push_back(pnode);
    return ptr;
    }
    void operator delete(void* ptr) noexcept {
        if (ptr == nullptr)
        {
            cout << "can not delete nullptr !!!" << endl;
            assert(false);
        }
        auto node = g_MemoryList.find(ptr);
        if (node == nullptr) {
            cout << "you want to free memory which is not allocated from new !!!" << endl;
            assert(false);
        }
        else
        {
            if (node->is_array) {
                cout << "momory allocated at line " << node->line << ", you want to free memory by delete not delete[] which is allocatd from new[] !!!" << endl;
                assert(false);
            }
            if (node->m_released) {
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
    void operator delete[](void* ptr) noexcept {
        if (ptr == nullptr)
        {
            cout << "can not delete nullptr !!!" << endl;
            assert(false);
        }
        auto node = g_MemoryList.find(ptr);
        if (node == nullptr) {
            cout << "you want to free memory which is not allocated from new !!!" << endl;
            assert(false);
        }
        else {
            if (!node->is_array) {
                cout << "momory allocated at line " << node->line << ", you want to free memory by delete[] not delete which is allocatd from new !!!" << endl;
                assert(false);
            }
            if (node->m_released) {
                cout << "momory allocated at line " << node->line << ", you want to free one memory twice !!!" << endl;
                assert(false);
            }
            node->m_released = true;
        }
        }
        void operator delete(void* pMem, const char* pszFilename, int nLine) { //msvc need
            cout << (int*)pMem << pszFilename << nLine << endl;
            free(pMem);
            assert(false);
        }
        void operator delete[](void* pMem, const char* pszFilename, int nLine) { //msvc need
            cout << (int*)pMem << pszFilename << nLine << endl;
            free(pMem);
            assert(false);
            }
#define new new(__FILE__, __LINE__)
        void check_do(bool b, int line = __LINE__) { if (b) { cout << "line:" << line << " Pass" << endl; } else { cout << "line:" << line << " Ohh! not passed!!!!!!!!!!!!!!!!!!!!!!!!!!!" << " " << endl; exit(0); } }
#define check(msg)  check_do(msg, __LINE__);
        // >>>>>>>>>>>>> do not care the code about memory leak checking. begin <<<<<<<<<<<<<<<
        using namespace std;

        int current_desk_id = 0;
        int current_house_id = 0;
        //文具盒
        struct Desk
        {
            Desk(void) :id(++current_desk_id)
            {
                cout << "Desk() id=" << id << endl;
            }
            Desk(const Desk& desk) :id(++current_desk_id)
            {
                cout << "Desk(const Desk& " << desk.id << ") id=" << id << endl;
            }
            ~Desk()
            {
                cout << "~Desk() id=" << id << endl;
            }
            int id = 0;
        };
        //学生
        struct House
        {
            House(void) :id(++current_house_id)
                , m_desk(new Desk)
            {
                cout << "House() id=" << id << endl;
            }

            /*(1) your code. 深拷贝需要实现House(const House& house)；这里需要另起炉灶 创建新的动态对象*/
            House(const House& house) :id(++current_house_id)
                , m_desk(new Desk(*house.m_desk))
            {
                cout << "House(const House& "<<house.id<<") id=" << id << endl;
            }
            ~House()
            {
                cout << "~House() id=" << id << endl;
                assert(m_desk);
                delete m_desk;
                m_desk = nullptr;
            }
            int id = 0;
            Desk* m_desk = nullptr;//管理动态对象：桌子
        private:
            House& operator=(const House& stu) = delete;//房子可以照葫芦画瓢被造出来，但是不可以赋值
};
void pass_by_value(House house)
{
    cout << "pass_by_value house " << house.id << endl;
}
void pass_by_reference(House& house)
{
    cout << "pass_by_reference house " << house.id << endl;
}

int main(void)
{
    cout << "main begin" << endl;
    //(2) your code.

    House h1;
    House h2(h1);
    pass_by_value(h1);
    pass_by_reference(h1);

    cout << "main end" << endl;

    return 0;
}
