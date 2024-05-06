// CMakeProjectLinuxFile.cpp: 定义应用程序的入口点。
//

#include "CMakeProjectLinuxFile.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h> /* for mmap and munmap */  
#include <fcntl.h>
#include <unistd.h>
#include <string.h> /* for memcpy */  

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

int mmapDemo()
{
	int fd;
	char* mapped_mem, * p;
	int flength = 1024;
	void* start_addr = 0;

	fd = open("/home/doubleming/temp/test2.txt", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
	flength = lseek(fd, 1, SEEK_END);
	write(fd, "\0", 1);
	lseek(fd, 0, SEEK_SET);
	start_addr = (void*)0x80000;
	mapped_mem = (char*)mmap(start_addr,
		flength,
		PROT_READ | PROT_WRITE, 
		MAP_SHARED,
		fd,
		0);

	printf("%s\n", mapped_mem);
	while ((p = strstr(mapped_mem, "hello"))) { 
		memcpy(p, "Linux", 5);
		p += 5;
	}

	close(fd);
	munmap(mapped_mem, flength);
	return 0;
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

	mmapDemo();

	return 0;
}



