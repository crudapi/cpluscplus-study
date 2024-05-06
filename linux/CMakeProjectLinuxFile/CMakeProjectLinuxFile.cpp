// CMakeProjectLinuxFile.cpp: 定义应用程序的入口点。
//

#include "CMakeProjectLinuxFile.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main()
{
	cout << "Hello CMake." << endl;

	printf("stdin fileno = %d\n", fileno(stdin));
	printf("stdout fileno = %d\n", fileno(stdout));
	printf("stderr fileno = %d\n", fileno(stderr));

	return 0;
}
