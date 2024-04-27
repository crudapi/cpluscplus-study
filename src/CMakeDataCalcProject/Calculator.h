#pragma once

#include <iostream>
#include <list>
#include <string>
#include <sstream>
using namespace std;

#include "ExpressionException.h"

typedef list<string> Expression;

ostream& operator<<(ostream& _os, const Expression& _item);

class Calculator
{
public:
	Calculator(const char* _infix);
	Calculator(const string& _infix);
	~Calculator(void);

public:
	string GetExpression(void) const;
	void SetExpression(const string& _expression);

	template<typename T>
	T GetValue(void) const;

	Expression ToPostfix(void) const;

public:
	static Expression ToPostfix(const string& pre);
	static bool Check(const string& _expression, string& _invalidInfor);

private:
	static void ToPostfix(const string& pre, Expression& post);
	static bool IsOperator(char op);                         // 判断是否为运算符 
	static int Priority(char op);                            // 求运算符优先级 
	static void ReadSpace(string::const_iterator& _itr, string::const_iterator& _end);
	static void ReadNumber(string::const_iterator& itr, string::const_iterator& _end, string& _value);

private:
	string m_infix;
};