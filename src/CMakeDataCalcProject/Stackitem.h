#pragma once

#include <iostream> //ostream
using namespace std;

template<typename T> class CStack;

template<typename T>
class CStackitem
{
public:
	friend class CStack<T>;

	CStackitem(void);
	CStackitem(T _data);
	CStackitem(const CStackitem& _item);
	~CStackitem(void);

	const T GetData(void) const;

private:
	CStackitem& operator=(const CStackitem& _item);//disallow a = b;

private:
	CStackitem* pPre;
	CStackitem* pNext;
	T data;
};