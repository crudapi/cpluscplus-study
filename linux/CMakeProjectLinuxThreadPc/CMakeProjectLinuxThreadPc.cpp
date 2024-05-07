// CMakeProjectLinuxThreadPc.cpp: 定义应用程序的入口点。
//

#include "CMakeProjectLinuxThreadPc.h"

using namespace std;
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

struct msg {
    int num;
    struct msg* next;
};
struct msg* head = NULL;
struct msg* mp = NULL;
//静态初始化锁
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
//生产者

void* producer(void* arg)
{
    sleep(2);
    printf("producer init....\n");
    while (1)
    {
        //生产一个结点
        mp = (msg*)malloc(sizeof(struct msg));
        mp->num = rand() % 100;
        printf("producer: %d\n", mp->num);


        printf("producer->pthread_mutex_lock...\n");
        //上菜到链表
        pthread_mutex_lock(&mutex);
        printf("producer->pthread_mutex_lock done\n");


        mp->next = head;
        head = mp;

        printf("producer->pthread_mutex_unlock...\n");
        pthread_mutex_unlock(&mutex);
        printf("producer->pthread_mutex_unlock done\n");

        //唤醒消费者
        printf("producer->pthread_cond_signal...\n");
        pthread_cond_signal(&has_product);
        printf("producer->pthread_cond_signal done\n");

        sleep(1);
    }
    return NULL;
}
//消费者
void* consumer(void* arg)
{
    printf("consumer init....\n");
    while (1) {
        //加锁

        printf("consumer->pthread_mutex_lock...\n");
        pthread_mutex_lock(&mutex);
        printf("consumer->pthread_mutex_lock done\n");

        while (head == NULL) {
            //等待被唤醒
            printf("consumer->pthread_cond_wait...\n");
            pthread_cond_wait(&has_product, &mutex);
            printf("consumer->pthread_cond_wait done\n");
        }
        //开始消费
        mp = head;
        head = mp->next;
        printf("consumer->pthread_mutex_unlock...\n");
        pthread_mutex_unlock(&mutex);
        printf("consumer->pthread_mutex_unlock done\n");

        printf("____consumer: %d\n", mp->num);
        free(mp);//释放内存
        mp = NULL;
        sleep(1);
    }
    return NULL;
}

int main(void)
{
    pthread_t ptid, ctid;
    //创建生产者线程
    pthread_create(&ptid, NULL, producer, NULL);
    //创建消费者线程
    pthread_create(&ctid, NULL, consumer, NULL);
    pthread_join(ptid, NULL);
    pthread_join(ctid, NULL);
    return 0;
}

