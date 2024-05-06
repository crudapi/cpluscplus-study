// CMakeProjectLinuxFork.cpp: 定义应用程序的入口点。
//

#include "CMakeProjectLinuxFork.h"

using namespace std;

#include <unistd.h>  
#include <stdio.h>   
int main()
{
	pid_t fpid;
	int count = 0;
	fpid = fork();
	if (fpid < 0)
		cout << "failed to fork";
	else if (fpid == 0)
	{
		cout << "I am the child process, my pid is  " << getpid() << endl;
		count++;
	}
	else
	{
		cout << "I am the parent process, my pid is " << getpid() << endl;
		cout << "fpid =" << fpid << endl;
		count++;
	}
	printf("count=%d\n", count);

	execl("/bin/pwd", "asdfaf", NULL);

	return 0;
}