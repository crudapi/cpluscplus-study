#include <pthread.h>
#include <iostream>
using namespace std;
 
void* thread_fun(void *arg)
{
    cout << "one Linux thread!" << endl;
    return 0;
}
 
int main(void)
{
    pthread_t thread_id;
    pthread_create(&thread_id, NULL, thread_fun, NULL);
    pthread_join(thread_id, NULL);
    
    return 0;
}
