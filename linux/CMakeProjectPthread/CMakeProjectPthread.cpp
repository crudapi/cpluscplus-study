// CMakeProjectPthread.cpp: 定义应用程序的入口点。
//

#include "CMakeProjectPthread.h"

#include <pthread.h>
#include <stdio.h>
#include <unistd.h> //sleep

using namespace std;

int g_n = 10;

void* thfunc(void* arg)
{
	int* pn = (int*)(arg);
	++g_n;
	printf("in thfunc %d\n", *pn);
	return (void*)0;
}

typedef struct  //定义结构体的类型
{
	int n;
	const char* str;
}MYSTRUCT;

void* thfunc2(void* arg)
{
	MYSTRUCT* p = (MYSTRUCT*)arg;
	++g_n;
	printf("in thfunc:n=%d,str=%s\n", p->n, p->str); //打印结构体的内容
	return (void*)0;
}
int mainDemo()
{
	pthread_t tidp;
	int ret;
	MYSTRUCT mystruct; //定义结构体
	//初始化结构体
	mystruct.n = 220;
	mystruct.str = "hello world";

	ret = pthread_create(&tidp, NULL, thfunc2, (void*)&mystruct);//创建线程并传递结构体地址 
	if (ret)
	{
		printf("pthread_create failed:%d\n", ret);
		return -1;
	}
	pthread_join(tidp, NULL); //等待子线程结束
	printf("in main:thread is created\n");

	return 0;
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



	cout << g_n << endl;
	mainDemo();

	++g_n;
	cout << g_n << endl;
	return 0;
}


