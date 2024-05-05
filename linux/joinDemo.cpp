#include <pthread.h>
#include <iostream>
using namespace std;
 
void* thread_fun1(void *arg)
{
    cout << "one Linux thread 1!" << endl;
    return 0;
}
 
void* thread_fun2(void *arg)
{
    cout << "one Linux thread 2!" << endl;
    return 0;
}
 
int main(void)
{
    pthread_t thread_id1;
    pthread_t thread_id2;
 
    pthread_create(&thread_id1, NULL, thread_fun1, NULL);
    pthread_create(&thread_id2, NULL, thread_fun2, NULL);
 
    //让线程运行直到结束
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
 
    return 0;
}