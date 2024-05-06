// CMakeProjectLinuxJob.cpp: 定义应用程序的入口点。
//

#include "CMakeProjectLinuxJob.h"

#include <unistd.h>
#include <iostream>
using namespace std;

int main(void)
{
	cout << "hello,world" << endl;
	sleep(10000);
	cout << "byebye" << endl;
}
