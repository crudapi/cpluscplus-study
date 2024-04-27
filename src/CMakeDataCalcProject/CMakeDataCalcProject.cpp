// CMakeDataCalcProject.cpp: 定义应用程序的入口点。
//

#include "CMakeDataCalcProject.h"

#include <iostream>
#include <string>
#include <cassert>
#include <list>
using namespace std;

#include "Stack.h"
#include "Calculator.h"

void InputAndCalculator(list<Calculator>& listCalculator);
void Output(const list<Calculator>& listCalculator);
void TestAll(list<Calculator>& listCalculator);

int main(int argc, char** argv)
{
	cout << "support: + - * / ^ ( )" << endl;
	cout << "Input 0 for end your input." << endl;

	list<Calculator> listCalculator;

	InputAndCalculator(listCalculator);//Extra credit 1:(1)any space (2)catch invalid input

	return 0;
}
void InputAndCalculator(list<Calculator>& listCalculator)
{
	while (true)
	{
		string sLine, invalidInfor;
		getline(cin, sLine);
		if (Calculator::Check(sLine, invalidInfor) == false)//Extra credit 1:(1)any space (2)catch invalid input
		{
			cout << invalidInfor << endl;
			continue;
		}
		listCalculator.push_back(sLine);
		Output(listCalculator);
		listCalculator.clear();
	}
}