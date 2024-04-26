// CMakeDataRandProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataRandProject.h"

#include <algorithm>
#include <iostream>
#include <cassert>
#include <initializer_list>
// >>>>>>>>>>>>> do not care the code about memory leak checking. begin <<<<<<<<<<<<<<<
#include <iostream>
#include <cassert>
#include <iostream>
#include <iomanip>

#include <ctime>
#include <chrono>
using namespace std;
void print_now(void)
{
	using namespace std::chrono;
	std::time_t tt = system_clock::to_time_t(system_clock::now());
	struct std::tm  valtm;
#ifdef  _WIN32
	localtime_s(&valtm, &tt);
#else
	localtime_r(&tt, &valtm);
#endif //  _WIN32
	cout << std::put_time(&valtm, "%F %T %A") << endl;//2021-03-16 12:37:38
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

template<typename T>
class Vector
{
public:
	/* default constructor for the following code :
		Vector<int> arr;
	*/
	Vector(void)
	{
		cout << "Vector(void)" << endl;
	}
	Vector(const Vector& from);//copy constructor
	Vector(T* start, T* end);//constructor
	Vector(int count, const T& value);//constructor
	Vector(std::initializer_list<T> value_array)
	{
		for (auto& item : value_array)
		{
			push_back(item);//use push_back to make code simple
		}
	}
	Vector& operator = (const Vector& from);// deep copy please
	bool operator==(const Vector& other) const // the same length and every element is the samae
	{
		//(1) your code . you have to modify the following code
		if (this->m_size != other.m_size) {
			return false;
		}

		for (int i = 0; i < this->m_size; ++i)
		{
			if (other.m_data[i] != this->m_data[i]) {
				return false;
			}
		}

		return true;
	}
	bool operator!=(const Vector& other) const// use operator == for this function
	{
		return !(*this == other);
	}
	~Vector();//destructor
public:
	int size(void) const;
	bool empty(void) const;
	const T& operator[] (int n) const;
	T& operator[] (int n);
	void push_back(const T& val);
	void clear(void);
private:
	void deep_copy_from(const Vector<T>& from);

public:
	struct iterator : std::iterator<std::random_access_iterator_tag, T>
	{
		friend class  Vector;
		friend bool operator == (const iterator& lhs, const iterator& rhs) { return lhs.m_hold == rhs.m_hold; }
		friend bool operator != (const iterator& lhs, const iterator& rhs) { return !(lhs == rhs); }
		friend size_t operator - (const iterator& lhs, const iterator& rhs) { return lhs.m_hold - rhs.m_hold; }
		friend bool operator < (const iterator& lhs, const iterator& rhs) { return lhs.m_hold < rhs.m_hold; }
		friend bool operator > (const iterator& lhs, const iterator& rhs) { return lhs.m_hold > rhs.m_hold; }
		friend bool operator <= (const iterator& lhs, const iterator& rhs) { return !(lhs > rhs); }
		friend bool operator >= (const iterator& lhs, const iterator& rhs) { return !(lhs < rhs); }
		friend iterator operator + (const iterator& lhs, size_t n) { iterator itr; itr.m_hold = lhs.m_hold + n; return itr; }//随机访问迭代器牛逼的地方
		friend iterator operator - (const iterator& lhs, size_t n) { iterator itr; itr.m_hold = lhs.m_hold - n; return itr; }//随机访问迭代器牛逼的地方
	public:
		//for ++itr
		iterator& operator++() { m_hold = m_hold + 1; return *this; };
		iterator& operator--() { m_hold = m_hold - 1; return *this; };
		//for itr++
		iterator operator++(int) { iterator itr = *this; m_hold += 1; return itr; }
		iterator operator--(int) { iterator itr = *this; m_hold -= 1; return itr; }
		T& operator*() const//here must const in C++14
		{
			return *m_hold;
		}
	private:
		T* m_hold;
	};
	struct const_iterator : std::iterator<std::random_access_iterator_tag, T>
	{
		friend class  Vector;
		friend bool operator == (const const_iterator& lhs, const const_iterator& rhs) { return lhs.m_hold == rhs.m_hold; }
		friend bool operator != (const const_iterator& lhs, const const_iterator& rhs) { return !(lhs == rhs); }
		friend size_t operator - (const const_iterator& lhs, const const_iterator& rhs) { return lhs.m_hold - rhs.m_hold; }
		friend bool operator < (const const_iterator& lhs, const const_iterator& rhs) { return lhs.m_hold < rhs.m_hold; }
		friend bool operator > (const const_iterator& lhs, const const_iterator& rhs) { return lhs.m_hold > rhs.m_hold; }
		friend bool operator <= (const const_iterator& lhs, const const_iterator& rhs) { return !(lhs > rhs); }
		friend bool operator >= (const const_iterator& lhs, const const_iterator& rhs) { return !(lhs < rhs); }
		friend const_iterator operator + (const const_iterator& lhs, size_t n) { const_iterator itr; itr.m_hold = lhs.m_hold + n; return itr; }//随机访问迭代器牛逼的地方
		friend const_iterator operator - (const const_iterator& lhs, size_t n) { const_iterator itr; itr.m_hold = lhs.m_hold - n; return itr; }//随机访问迭代器牛逼的地方
	public:
		//for ++itr
		const_iterator& operator++() { m_hold = m_hold + 1; return *this; };
		const_iterator& operator--() { m_hold = m_hold - 1; return *this; };
		//for itr++
		const_iterator operator++(int) { const_iterator itr = *this; m_hold += 1; return itr; }
		const_iterator operator--(int) { const_iterator itr = *this; m_hold -= 1; return itr; }
		const T& operator*() const
		{
			return *m_hold;
		}
	private:
		T* m_hold;
	};

	iterator begin() noexcept
	{
		iterator itr;
		itr.m_hold = empty() ? nullptr : &m_data[0];
		return itr;
	}
	const_iterator cbegin() const noexcept;
	iterator end() noexcept
	{
		iterator itr;
		itr.m_hold = empty() ? nullptr : &m_data[m_size];
		return itr;
	}
	const_iterator cend() const noexcept;
private:
	int m_size = 0;//count element 
	int m_capacity = 0;//element count + space for push_back
	T* m_data = nullptr;//array for hold data
};

template<typename T>
Vector<T>::Vector(T* start, T* end)
{
	std::cout << "Vector(T* start, T* end)" << std::endl;
	check(start != nullptr && end != nullptr);
	m_capacity = m_size = static_cast<int>((end - start));//size_t is enough
	check(m_size > 0);
	m_data = new T[m_size];
	for (int i = 0; i < m_size; i++)
	{
		m_data[i] = *start++;
	}
}
template<typename T>
Vector<T>::Vector(int count, const T& value)
{
	std::cout << "Vector("<<count<<", "<<typeid(T).name()<<")" << std::endl;
	if (count <= 0)
	{
		throw std::runtime_error("size of vector to init must bigger than zero!");
	}
	m_data = new T[count];
	for (int i = 0; i < count; i++)
	{
		m_data[i] = value;
	}
	m_capacity = m_size = count;
}
template<typename T>
Vector<T>& Vector<T>::operator=(const Vector<T>& from)
{
	std::cout << "Vector::operator=Vector<"<<typeid(T).name()<<">" << std::endl;
	if (this == &from)
	{
		return *this;
	}
	//release self data first
	deep_copy_from(from);
	return *this;
}

template<typename T>
Vector<T>::~Vector()
{
	//(2) your code
	if (m_data != nullptr)
	{
		delete[] m_data;
	}
}
template<typename T>
int Vector<T>::size(void) const
{
	return m_size;
}
template<typename T>
bool Vector<T>::empty(void) const
{
	//(3) your code . you have to modify the following code
	return m_size == 0;
}
template<typename T>
const T& Vector<T>::operator[](int n) const
{
	//(4) your code . you have to modify the following code
	return m_data[n];
}
template<typename T>
T& Vector<T>::operator[](int n)
{
	//(4) your code . you have to modify the following code
	return m_data[n];
}
template<typename T>
void Vector<T>::push_back(const T & val)
{
	//(5) your code
	// you have to mind that no space in the first time.
	//case 1 : no space to push
	//case 2 : exist space and push back
	//case 3 : space is full, destory old space and create new bigger space
	// , copy data and push back
	 //如果capacity为0，则一次性开辟10个元素
	if (m_capacity == 0)
	{
		m_data = new T[10];
		m_data[0] = val;
		m_capacity = 10;
		m_size = 1;
	}
	else if (m_size < m_capacity)
	{
		//给最后一个元素的后面赋值为新元素value
		//增加元素数量
		//(5) your code
		m_data[m_size] = val;
		++m_size;
	}
	else
	{
		//每次内存不够用就翻倍
		T* p = new T[2 * m_capacity];
		//先把原来的每个元素拷贝到新地方
		for (int j = 0; j < m_size; j++)
		{
			//(5.1) your code
			p[j] = m_data[j];

		}
		//把新添加的元素也添加到新地方
		//(6) your code
		p[m_size] = val;


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
 
template<typename T>
void Vector<T>::clear(void)
{
	//(6) your code
	if (m_size > 0) {
		delete[] m_data;
		m_data = nullptr;
		m_capacity = 0;
		m_size = 0;
	}
}
 
template<typename T>
void Vector<T>::deep_copy_from(const Vector<T>& from)
{
	cout << "Vector::deep_copy_from Vector<" << typeid(T).name() << ">" << endl;
	clear();
	//(7) your code . you have to modify the following code
	for (int i = 0; i < from.m_size; i++)
	{
		push_back(from[i]);
	}
}
 
template<typename T>
Vector<T>::Vector(const Vector& from)
{
	//(8) your code . you have to modify the following code
	//this->m_size = from.m_capacity;
	deep_copy_from(from);
}
 
template<typename T>
typename Vector<T>::const_iterator Vector<T>::cend() const noexcept
{
    const_iterator itr = const_iterator();
	itr.m_hold = empty() ? nullptr : &m_data[m_size];
 
	return itr;
}
 
template<typename T>
typename Vector<T>::const_iterator Vector<T>::cbegin() const noexcept
{
    const_iterator itr = const_iterator();
	itr.m_hold = empty() ? nullptr : &m_data[0];
	return itr;
}

 
template<typename T>
void print(const Vector<T>& v, const char* msg)
{
	std::cout << "The contents of " << msg << " are:";
	for (int i = 0; i < v.size(); ++i)
	{
		std::cout << ' ' << v[i];
	}
	std::cout << '\n';
}
template<typename T>
void print_itr(Vector<T>& v, const char* msg)
{
	std::cout << "The contents of " << msg << " are:";
	for (auto itr = v.begin(); itr != v.end(); ++itr)
	{
		std::cout << ' ' << *itr;
	}
	std::cout << '\n';
}
template<typename T>
void print_const_itr(const Vector<T>& v, const char* msg)
{
	std::cout << "The contents of " << msg << " are:";
	for (auto itr = v.cbegin(); itr != v.cend(); ++itr)
	{
		std::cout << ' ' << *itr;
	}
	std::cout << '\n';
}
void test_vector_vector(void)
{
	Vector<Vector<char>> matrix(1, Vector<char>(1, 'c'));
	char str[100] = { 0 };
	int index = 0;
	for (auto& item : matrix)
	{
		for (auto& c : item)
		{
			str[index++] = c;
		}
	}
	check(index == 1);
	for (int j = 0; j < 1; j++)
	{
		assert(str[j] == 'c');
	}
}
void test_index(void)
{
	Vector<int> arr;
	arr.push_back(1);
	arr[0] = 2;
	check(arr[0] == 2);
}
struct Student
{
	Student(void)
	{
		cout << "Student() address of this = " << (long long)this << endl;
	}
	int age = 18;
};
void test_const_index(void)
{
	Vector<Student> arr;
	arr.push_back(Student());
	check(&arr[0].age == &(*arr.begin()).age);
	const Vector<Student>& arr_const = arr;
	check(&arr_const[0].age == &(*arr.cbegin()).age);
}
void test_object(void)
{
	Student stu;
	stu.age = 18;
	Vector<Student> arr(10, stu);
	check(arr[9].age == 18);
}

int main()
{
	Vector<int> a;
 
	Vector<int> first;                   // empty vector of ints
	check(first.size() == 0);
	check(first.empty() == true);
	Vector<int> second(4, 100);                       // four ints with value 100
	check(second.empty() == false);
	check(second.size() == 4);
	check(*second.begin() == 100);
	//copy constructor
	{
		Vector<int> a;
		Vector<int> b(a);                       // a copy of third
	}
	Vector<int> fourth(second);                       // a copy of third
	check(fourth.size() == second.size());
	check(fourth[0] == 100);
	check(fourth[1] == 100);
	check(fourth[2] == 100);
	check(fourth[3] == 100);
 
	int myints[] = { 16,2,77,29 };
	Vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));
	check(fifth.empty() == false);
	check(fifth[0] == 16);
	check(fifth[3] == 29);
	check(fifth.size() == sizeof(myints) / sizeof(int));
	print(fifth, "fifth");//The contents of fifth are:16 2 77 29 
	fifth.push_back(30);
	check(fifth[4] == 30);
	check(fifth.size() == 5);
	print(fifth, "fifth");//The contents of fifth are:16 2 77 29 30 
	check(fifth.size() == sizeof(myints) / sizeof(int) + 1);
	first = fifth = fifth;
	print(first, "first");//The contents of first are:16 2 77 29 30 
	check(first.empty() == false && first.size() == fifth.size());
	print_itr(fifth, "fifth");//The contents of fifth are:16 2 77 29 30 
	print_const_itr(fifth, "fifth");//The contents of fifth are:16 2 77 29 30 
	std::sort(fifth.begin(), fifth.end());
	// a == b
	{
		Vector<int> t{ 2, 16, 29, 30, 77 };
		check(fifth == t);
		Vector<int> a;
		Vector<int> b;
		check(a == b);//empty == empty
	}
	std::cout << "fifith after sort:" << std::endl;
	print_const_itr(fifth, "fifth");//The contents of fifth are:16 2 77 29 30 
	Vector<int> a1(myints, myints + sizeof(myints) / sizeof(int));
	{
		Vector<int> b(a1);
		b.push_back(2);
		check(b[4] == 2);
		auto result = (b == Vector<int>{ 16, 2, 77, 29, 2});
		check(result);
 
		//iterator
		{
			check(b.begin() + b.size() == b.end());
			auto begin = b.begin();
			auto itr = b.begin() + 1;
			check(*begin == 16);
			check(*itr == 2);
		}
		//const iterator
		{
			check(b.cbegin() + b.size() == b.cend());
			auto begin = b.cbegin();
			auto itr = b.cbegin() + 1;
			check(*begin == 16);
			check(*itr == 2);
			check(++begin == itr);
		}
		{
			Vector<long> aa;
			check(aa.begin() == aa.end());
			check(aa.cbegin() == aa.cend());
		}
	}
	{
		Vector<int> b{ 1,3,5,7 };
		b.push_back(9);
	}
	{
		Vector<int> c;
		for (auto i : c){std::cout << i << " ";	}
		c = a1;
		for (auto i : c){	std::cout << i << " ";}
		std::cout << std::endl;
	}
	check(a1.size() == sizeof(myints) / sizeof(int));
	{
		Vector<int> c;
		c = fifth;
		c[0] = 1;
		check(c[0] == 1);
	}
	{
		Vector<int> aa{1, 2, 3};
		Vector<int> b{1, 2, 3, 4};
		check(aa != b);
		auto c = b;
		c.push_back(5);
		check(c != b);
		c = b;
		check(c == b);
	}
	//test char
	{
		Vector<char> arr(10, 'a' );
		char buffer[10] = { 0 };
		int index = 0;
		for (auto& c : arr)
		{
			buffer[index++] = c;
		}
		check(index == 10);
		for (int j = 0; j < 10; j++)
		{
			assert(buffer[j] == arr[j]);
			assert(buffer[j] == 'a');
		}
	}
	test_vector_vector();
	{
		Vector<int> arr1{ 1,1,3 };
		Vector<int> arr2{ 2,2,3 };
		check(arr1 != arr2);
		Vector<int> arr3{ 2,2,3 };
		check(arr2 == arr3);
		Vector<int> arr4{ 2,2,3, 3 };
		check(arr3 != arr4);
		check(arr4 != arr3);
	}
	test_index();
	test_const_index();
	test_object();
}