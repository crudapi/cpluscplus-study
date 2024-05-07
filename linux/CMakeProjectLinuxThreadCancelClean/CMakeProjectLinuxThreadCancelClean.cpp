// CMakeProjectLinuxThreadCancelClean.cpp: 定义应用程序的入口点。
//

#include "CMakeProjectLinuxThreadCancelClean.h"

#include<stdio.h>  
#include<stdlib.h>  
#include <pthread.h>  
#include <unistd.h> //sleep

void mycleanfunc(void* arg) //ÇåÀíº¯Êý
{
	printf("mycleanfunc:%d\n", *((int*)arg));
}

void* thfunc(void* arg)
{
	int i = 1;
	printf("thread start-------- \n");
	pthread_cleanup_push(mycleanfunc, &i); //°ÑÇåÀíº¯ÊýÑ¹Õ»
	while (1)
	{
		i++;
		printf("i=%d\n", i);
	}
	printf("this line will not run\n");
	pthread_cleanup_pop(0);

	return (void*)0;
}
int main()
{
	void* ret = NULL;
	int iret = 0;
	pthread_t tid;
	pthread_create(&tid, NULL, thfunc, NULL);  //´´½¨Ïß³Ì
	sleep(1);

	pthread_cancel(tid); //·¢ËÍÈ¡ÏûÏß³ÌµÄÇëÇó  
	pthread_join(tid, &ret);  //µÈ´ýÏß³Ì½áÊø
	if (ret == PTHREAD_CANCELED) //ÅÐ¶ÏÊÇ·ñ³É¹¦È¡ÏûÏß³Ì
		printf("thread has stopped,and exit code: %d\n", ret);  //´òÓ¡ÏÂ·µ»ØÖµ£¬Ó¦¸ÃÊÇ-1
	else
		printf("some error occured");

	return 0;
}
