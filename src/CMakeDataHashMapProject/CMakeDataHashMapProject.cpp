// CMakeDataHashMapProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataHashMapProject.h"

#include<string>
#include<list>
#include<memory>
#include<vector>
#include<utility>
#include <algorithm>
#include <iostream>
#include <cassert>
#include <set>
using namespace std;

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

class HashMap
{
public:
    HashMap(void);
    ~HashMap(void);
    HashMap(const HashMap& from);
    HashMap& operator=(const HashMap& from);
public:
    bool empty(void) const { return m_size == 0; }
    size_t size(void) const;
    //为了简化问题，由于没有提供 const_iterator；所以这里的 contains 并没有加 const
    bool contains(const int& key);
    std::string& operator[](const int& key);
    void erase(const int& key);
public:
    using value_type = std::pair<int, std::string>;
public:
    class iterator
    {
        friend class HashMap;
    public:
        iterator& operator++(void);//++itr
        bool operator==(const iterator& itr);
        bool operator!=(const iterator& itr);
        value_type& operator*(void);
    private:
        iterator(HashMap* hashmap, size_t bucket_index, std::list<value_type>::iterator itr);
    private:
        std::list<value_type>::iterator m_itr;
        size_t m_bucket_index;//-1 for end()
        HashMap* m_hashmap;
    };
    iterator begin(void);
    iterator end(void);
    void clear(void);
private:
    size_t hash(const int& key) const;
    void copy(const HashMap& from);
    //装载因子
    double load_factor(void) const { return (double)m_size / m_bucket_array.size(); };
    void re_hash(void);//扩大容量
    void reset(void);
    //如果元素存在，则返回迭代器；如果不存在，则返回end()迭代器（内部携带桶信息，用来push_back到末尾）
    iterator search(const int& key);
private:
    //8 empty lists at the beginning
    const int m_init_bucket_count = 8;
    std::vector<std::list<value_type>> m_bucket_array
        = std::vector<std::list<value_type>>(m_init_bucket_count);
    size_t m_size = 0;
};


HashMap::HashMap(void)
{
    //(1) your code 直接调用reset完成默认开辟8个元素空间
    reset();
    cout << "HashMap()" << endl;
}

HashMap::~HashMap(void)
{
    // 析构函数什么也不用做，因为存放数据的容器 vector list 会自动释放其拥有的元素
    cout << "~HashMap()" << endl;
}

HashMap::HashMap(const HashMap& from)
{
    //(2) your code 直接调用 copy 即可完成拷贝
    copy(from);
    cout << "HashMap(const HashMap &)" << endl;
}

HashMap& HashMap::operator=(const HashMap& from)
{
    //(2) your code 直接调用 copy 即可完成拷贝
    if (this == &from) {
        return *this;
    }

    copy(from);
    cout << "HashMap::operator=(const HashMap & from)" << endl;
    return *this;
}

size_t HashMap::size(void) const
{
    return m_size;
}
HashMap::iterator HashMap::search(const int& key)
{
    size_t index;
    //(3) your code 通过hash 函数获取key对应的桶的index
    index = hash(key);

    auto& bucket = m_bucket_array[index];
    auto itr = std::find_if(bucket.begin(), bucket.end(), [key](const value_type& value) {
        return value.first == key;
    });

    return iterator(this, index, itr);
}
bool HashMap::contains(const int& key)
{
    //(4) your code 通过 search 得到数据如果存在应该在哪个桶里
    // 再到桶里 list 查找有没有这个元素 ，在链表中 线性查找
    HashMap::iterator it = search(key);

    auto& bucket = m_bucket_array[it.m_bucket_index];
    if (it.m_itr != bucket.end()) {
        return true;
    }
    else {
        return false;
    }
}

std::string& HashMap::operator[](const int& key)
{
    //(5) your code 如果装载因子 大于了 0.8 就 re_hash 扩大容量
    double factor = load_factor();
    if (factor > 0.8) {
        //cout << "re_hash()" << factor << endl;
        re_hash();
    }


    //(6) your code 通过 search 得到数据如果存在应该在哪个桶里
    HashMap::iterator itr = search(key);

    auto& bucket = m_bucket_array[itr.m_bucket_index];//如果(6) 没有重写，这里会崩溃
    if (itr.m_itr == bucket.end())
    {
        //(6) your code. key not exist, insert empty std::string as default value at end of this bucket
        value_type value(key, std::string());
        bucket.push_back(value);

        //(7) your code. increase the size of current hash map.
        ++m_size;
        //(8) your code. return element

        return bucket.back().second;
    }
    else
    {
        //(9) your code. return element
        return itr.m_itr->second;
    }
}

void HashMap::erase(const int& key)
{
    //(6) your code 通过 search 得到数据如果存在应该在哪个桶里
    HashMap::iterator itr = search(key);

    
    auto& bucket = m_bucket_array[itr.m_bucket_index];
    if (itr.m_itr == bucket.end())
    {
        throw std::runtime_error("erasing not exist key!");
    }
    else
    {
        --m_size;
        bucket.erase(itr.m_itr);
    }
}

HashMap::iterator HashMap::begin(void)
{
    for (size_t i = 0; i < m_bucket_array.size(); i++)
    {
        if (!m_bucket_array[i].empty())
        {
            return HashMap::iterator(this, i, m_bucket_array[i].begin());
        }
    }
    return end();
}

HashMap::iterator HashMap::end(void)
{
    return HashMap::iterator(this, -1, std::list<value_type>::iterator());
}

size_t HashMap::hash(const int& key) const
{
    // 使用key 得到元素在哪个桶里。使用求余数来得到。
    // 这种算法可以认为是足够简单而且元素会均匀分布在各个桶里的
    int index = key % m_bucket_array.size();
    return index;
}

void HashMap::clear(void)
{
    reset();
}

void HashMap::copy(const HashMap& from)
{
    clear();
    m_bucket_array.resize(from.m_bucket_array.size());
    for (size_t i = 0; i < m_bucket_array.size(); i++)
    {
        //10 your code. 使用链表的赋值操作符直接拷贝链表
        m_bucket_array[i] = from.m_bucket_array[i];
    }
    m_size = from.m_size;
}

void HashMap::re_hash(void)
{
    //另起炉灶，新创建一个HashMap
    HashMap re_hashmap;
    //将新的炉灶扩大容量
    //11 your code. 将新的炉灶实际的桶开辟出来
    re_hashmap.m_bucket_array.resize(m_bucket_array.size() * 2);

    //使用迭代器，遍历原来的（this）所有元素，将所有元素拷贝到新的炉灶里
    for (auto itr = begin(); itr != end(); ++itr)
    {
        //12 your code. 先根据key获得桶，再把value追加到桶里list的末尾
        re_hashmap[itr.m_itr->first] = itr.m_itr->second;
    }
    //交换新旧两个容器的内容，接管新炉灶
    std::swap(re_hashmap.m_bucket_array, m_bucket_array);
    //其他成员变量更新
    re_hashmap.m_size = this->m_size;
}

void HashMap::reset(void)
{
    m_size = 0;
    m_bucket_array.clear();
    m_bucket_array.resize(m_init_bucket_count);
}

HashMap::iterator& HashMap::iterator::operator++(void)
{
    //valid itr can always do ++itr
    auto index = m_hashmap->hash(m_itr->first);
    auto& bucket = m_hashmap->m_bucket_array[index];

    ++m_itr;

    //find next list or the end() occor
    if (m_itr == bucket.end())
    {
        for (size_t i = m_bucket_index + 1; i < m_hashmap->m_bucket_array.size(); i++)
        {
            if (!m_hashmap->m_bucket_array[i].empty())
            {
                m_bucket_index = i;
                m_itr = m_hashmap->m_bucket_array[i].begin();
                return *this;
            }
        }
        m_bucket_index = -1;//end()
    }

    return *this;
}

bool HashMap::iterator::operator==(const iterator& itr)
{
    if (itr.m_bucket_index != this->m_bucket_index)
    {
        return false;
    }
    if (itr.m_bucket_index == -1 && this->m_bucket_index == -1)
    {
        return true;//both end()
    }
    else
    {
        bool equal = &*(m_itr) == &*(itr.m_itr);
        return equal;//pointed to the same value address
    }
}

bool HashMap::iterator::operator!=(const iterator& itr)
{
    bool equal = (*this == itr);
    return  !equal;
}

HashMap::value_type& HashMap::iterator::operator*(void)
{
    return *m_itr;
}

HashMap::iterator::iterator(HashMap* hashmap, size_t bucket_index, std::list<value_type>::iterator itr)
{
    m_hashmap = hashmap;
    m_itr = itr;
    m_bucket_index = bucket_index;
}

void test_copy_constructor(void)
{
    HashMap hashmap1;
    for (int i = 0; i < 16; i++)
    {
        hashmap1[i] = to_string(i);
    }
    HashMap hashmap2(hashmap1);
    auto itr1 = hashmap1.begin();
    for (auto itr2 = hashmap2.begin(); itr2 != hashmap2.end(); ++itr2, ++itr1)
    {
        check((*itr2).first == (*itr1).first);
        check((*itr2).second == (*itr1).second);
    }
    check(itr1 == hashmap1.end());
}
int main()
{
    //create insert find
    {
        HashMap students;
        check(students.empty());
        check(students.size() == 0);
        int id = 123;
        check(students.contains(id) == false);
        std::string name("zhangsan");
        students[id] = name;
        check(!students.empty());
        check(students.size() == 1);
        check(students.contains(id));
        check(students[id] == name);
    }
    //modify value
    {
        HashMap students;
        int id = 123;
        std::string name("zhangsan");
        students[id] = name;
        std::string name2("lisi");
        students[id] = name2;
        check(students[id] == name2);
        check(students.size() == 1);
    }
    //erase
    {
        HashMap students;
        int id = 123;
        std::string name("zhangsan");
        students[id] = name;
        students.erase(id);
        check(!students.contains(id));
        check(students.size() == 0);
    }
    //clear value
    {
        HashMap students;
        int id = 123;
        std::string name("zhangsan");
        students[id] = name;
        std::string name2("lisi");
        students[id] = name2;
        check(students[id] == name2);
        check(students.size() == 1);
        students.clear();
        check(students.size() == 0);
        students.clear();
    }
    //copy
    {
        HashMap students;
        int id = 123;
        std::string name("zhangsan");
        students[id] = name;
        HashMap students2(students);//copy constructor
        check(students.contains(id));
        check(students.size() == 1);
        students[456] = "lisi";
        check(students.contains(456));
        check(!students2.contains(456));
        students2[789] = "wanger";
        check(!students.contains(789));
        check(students2.contains(789));
        check(students.size() == 2);
        check(students2.size() == 2);
        test_copy_constructor();
    }
    //assignment
    {
        HashMap students;
        int id = 123;
        std::string name("zhangsan");
        students[id] = name;
        students[456] = "lisi";
        HashMap students2;
        students2 = students;
        check(students2.contains(id));
        check(students2.contains(456));
        check(students.size() == 2);
    }
    //iterator
    const int total = 50;
    {
        int id_creator = 1;
        HashMap students;
        std::string name("zhangsan");
        for (int i = 1; i <= total; ++i)
        {
            students[id_creator++] = name + std::to_string(i);
        }
        check(students.size() == total);
        std::multiset<int> all_keys;
        for (auto& item : students)
        {
            all_keys.insert(item.first);
            cout << item.first << " " << item.second << endl;
        }
        int i = 1;
        for (auto item : all_keys)
        {
            assert(item == i++);
        }
        check(i == total + 1);
        students.clear();
        for (int i = 1; i <= total; ++i)
        {
            students[i] = std::to_string(i);
        }
        check(students.contains(1));
        check(students.contains(total));
        check(students[1] == "1");
        check(students[total] == to_string(total));
        check(students.size() == total);
    }
    
}