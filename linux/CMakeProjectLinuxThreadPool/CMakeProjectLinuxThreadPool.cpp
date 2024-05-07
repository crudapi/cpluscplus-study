// CMakeProjectLinuxThreadPool.cpp: 定义应用程序的入口点。
//

#include "CMakeProjectLinuxThreadPool.h"
#include "thread_pool.h"
using namespace std;

#include <iostream> 
#include <thread>
#include <mutex> 
#include <unistd.h>
#include <stdio.h>


class CMyTask : public CTask
{
public:
	CMyTask() = default;
	int Run() 
	{
		printf("%s\n",  (char*)m_ptrData);
		int x = rand() % 4 + 1;
		sleep(x);
		return 0;
	}
	~CMyTask() {};
};

int main(int argc, const char* argv[])
{
	CMyTask taskObj;

	char strName[] = "hello";

	taskObj.setData((void*)strName);

	CThreadPool threadPool(5);

	//sleep(10);

	for (int i = 0; i < 10; ++i) 
	{
		//sleep(2);
		threadPool.AddTask(&taskObj);
	}

	//获取cpu内核数量
	int m_max_thread_count = 0;
	int icore_num = std::thread::hardware_concurrency();
	if (icore_num > 0)
		m_max_thread_count = 2 * icore_num;
	else
		m_max_thread_count = 4;

	cout << "m_max_thread_count = " << m_max_thread_count << endl;

	cout << "icore_num = " << icore_num << endl;

	while (1) 
	{
		printf("\n %d task need handele\n", threadPool.getTaskSize());


		if (threadPool.getTaskSize() == 0)
		{
			if (threadPool.StopAll() == -1)
			{
				printf("clear exit!\n");
				exit(0);
			}
		}

		sleep(2);

		printf("sleep 2s\n");
	}

	return 0;
}
