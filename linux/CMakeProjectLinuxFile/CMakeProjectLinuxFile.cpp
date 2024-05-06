// CMakeProjectLinuxFile.cpp: 定义应用程序的入口点。
//

#include "CMakeProjectLinuxFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

using namespace std;

int openFile() 
{
	int fd = -1;
	char filename[] = "test1.txt";

	fd = open(filename, O_CREAT | O_RDWR, S_IRWXU);
	if (fd == -1)
	{
		printf("fail to open file %s, fd: %d\n", filename, fd);
	}
	else {
		printf("create file %s successfully, fd: %d\n", filename, fd);
	}

	return fd;
}

int main()
{
	cout << "Hello CMake." << endl;

	printf("stdin fileno = %d\n", fileno(stdin));
	printf("stdout fileno = %d\n", fileno(stdout));
	printf("stderr fileno = %d\n", fileno(stderr));

	int fd = -1; 
	char filename[] = "/home/doubleming/temp/test.txt";

	fd = creat(filename, 0666);
	if (fd == -1)
	{
		printf("fail to open file %s\n", filename);
	} 
	else {
		printf("create file %s successfully\n", filename);
	}

	openFile();

	return 0;
}
