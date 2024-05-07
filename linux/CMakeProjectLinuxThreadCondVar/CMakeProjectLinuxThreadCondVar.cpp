// CMakeProjectLinuxThreadCondVar.cpp: 定义应用程序的入口点。
//

#include "CMakeProjectLinuxThreadCondVar.h"

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;/*³õÊ¼»¯»¥³âËø*/
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;/*³õÊ¼»¯Ìõ¼þ±äÁ¿*/

void* thread1(void*);
void* thread2(void*);

int i = 1;
int main(void)
{
	pthread_t t_a;
	pthread_t t_b;

	pthread_create(&t_a, NULL, thread2, (void*)NULL);//´´½¨Ïß³Ìt_a
	pthread_create(&t_b, NULL, thread1, (void*)NULL); //´´½¨Ïß³Ìt_b
	pthread_join(t_b, NULL);/*µÈ´ý½ø³Ìt_b½áÊø*/
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	exit(0);
}

void* thread1(void* junk)
{
	for (i = 1; i <= 20; i++)
	{
		pthread_mutex_lock(&mutex);//Ëø×¡»¥³âÁ¿
		if (i % 3 == 0)
			pthread_cond_signal(&cond); //»½ÐÑµÈ´ýÌõ¼þ±äÁ¿condµÄÏß³Ì
		else
			printf("thead1:%d\n", i); //´òÓ¡²»ÄÜÕû³ý3µÄi
		pthread_mutex_unlock(&mutex);//½âËø»¥³âÁ¿

		sleep(1);
	}

}

void* thread2(void* junk)
{
	while (i < 20)
	{
		pthread_mutex_lock(&mutex);

		if (i % 3 != 0)
			pthread_cond_wait(&cond, &mutex);//µÈ´ýÌõ¼þ±äÁ¿
		printf("------------thread2:%d\n", i); //´òÓ¡ÄÜÕû³ý3µÄi
		pthread_mutex_unlock(&mutex);

		sleep(1);
		i++;
	}

}
