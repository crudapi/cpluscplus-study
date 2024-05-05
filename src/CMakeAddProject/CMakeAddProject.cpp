// CMakeAddProject.cpp: 定义应用程序的入口点。
//

#include "CMakeAddProject.h"

#include <iostream>
#include <thread>
#include <list>
using namespace std;


list<int> data_queue;

void producer(void)
{
	while (true)
	{
		//生产5个数据放到队列里，就开始休息100毫秒
		for (size_t i = 0; i < 5; i++)
		{
			data_queue.push_front(i);
		}
		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

void consumer(void)
{
	while (true)
	{
		//每隔10毫秒就取一次数据
		if (!data_queue.empty())
		{
			data_queue.pop_front();
		}
		this_thread::sleep_for(chrono::microseconds(10));
	}
}

int listDemo()
{
	thread producer_thread(producer);
	thread consumer_thread(consumer);

	producer_thread.join();
	consumer_thread.join();

	return 0;
}


size_t sum = 0;
size_t large = 10000 * 10000;// 1亿以内的正整数


void sum_even(void)
{
	for (size_t i = 2; i <= large; i += 2)
	{
		sum += i;
	}
}

void sum_odd(void)
{
	for (size_t j = 1; j < large; j += 2)
	{
		sum += j;
	}
}

int addDemo()
{
	thread producer_thread(sum_even);
	thread consumer_thread(sum_odd);

	producer_thread.join();
	consumer_thread.join();

	cout << "sum 1+2+...+100=" << sum << endl;

	return 0;
}


int main()
{
	addDemo();

	listDemo();

	return 0;
}

