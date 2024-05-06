// CMakeProjectLinuxAlive.cpp: 定义应用程序的入口点。
//

#include "CMakeProjectLinuxAlive.h"

#include <iostream>  
#include <pthread.h>  
#include <signal.h>  
#include <unistd.h> //sleep
#include "errno.h"
using namespace std;

void* thfunc(void* arg)
{
	int tm = 50;
	while (tm > 48)
	{
		cout << "thrfunc--left:" << tm << " s--" << endl;
		sleep(1);
		tm--;
	}
	return (void*)0;
}

int main(int argc, char* argv[])
{
	pthread_t     pid;
	int res;

	res = pthread_create(&pid, NULL, thfunc, NULL);
	sleep(5);
	int kill_rc = pthread_kill(pid, 0);

	if (kill_rc == ESRCH)
		cout << "the specified thread did not exists or already quit\n";
	else if (kill_rc == EINVAL)
		cout << "signal is invalid\n";
	else
		cout << "the specified thread is alive\n";

	return 0;
}