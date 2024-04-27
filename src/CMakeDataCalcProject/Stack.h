#pragma once

#include "Stackitem.h"

template<typename T>

class CStack
{
public:
	CStack(void);
	CStack(const CStack& _stack);
	~CStack(void);

public:
	const T& top(void) const;
	bool empty(void) const;
	size_t size(void) const;
	void push(const CStackitem<T>& _item);
	const T pop(void);

private:
	CStack& operator=(const CStack& _stack);//a = b; is not allowed

private:

	CStackitem<T>* m_pTail;
	size_t m_size;
};