// CMakeProjectPthread.cpp: 定义应用程序的入口点。
//

#include "CMakeProjectPthread.h"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h> //sleep

void* thfunc(void* arg)
{
	int* pn = (int*)(arg);
	printf("in thfunc %d\n", *pn);
	return (void*)0;
}
int main(int argc, char* argv[])
{
	pthread_t tidp;
	int ret, n = 110;


	ret = pthread_create(&tidp, NULL, thfunc, &n);
	if (ret)
	{
		printf("pthread_create failed:%d\n", ret);
		return -1;
	}

	pthread_join(tidp, NULL);
	printf("in main:thread is created\n");

	return 0;
}
