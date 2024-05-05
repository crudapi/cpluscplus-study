#include <pthread.h>
#include <semaphore.h>
#include <iostream>
#include <unistd.h>//usleep
using namespace std;
 
sem_t event;
 
void* thread_sender_fun(void* arg)
{
    while (true)
    {
        cout << "1";
        sem_post(&event);
        usleep(1000);//休眠一毫秒
    }
    
    return 0;
}
 
void* thread_receive_fun(void* arg)
{
    while (true)
    {
        sem_wait(&event);
        cout << "2";
    }
    
    return 0;
}
 
int main(int argc, char *argv[])
{
    pthread_t thread_sender;
    pthread_t thread_receiver;
 
    sem_init(&event, 0, 0);
 
    pthread_create(&thread_sender, NULL, thread_sender_fun, NULL);
    pthread_create(&thread_receiver, NULL, thread_receive_fun, NULL);
 
    pthread_join(thread_sender, NULL);
    pthread_join(thread_receiver, NULL);
 
    return 0;
}