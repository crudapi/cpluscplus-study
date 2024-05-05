// CMakeAddProject.cpp: 定义应用程序的入口点。
//

#include "CMakeAddProject.h"

#include <iostream>
#include <thread>
#include <list>
#include <mutex>//std::mutex std::lock_guard
using namespace std;


list<int> data_queue;
mutex queue_mutex;

void print_queue(void)
{
	static long long count = 0;
	++count;
	while (true)
	{
		{
			cout << "queue : ";
			for (auto& item : data_queue)
			{
				cout << item << " ";
			}
			cout << endl;
		}
		this_thread::sleep_for(chrono::seconds(3));
	}
}

void producer(void)
{
	while (true)
	{
		//生产5个数据放到队列里，就开始休息100毫秒
		{
			lock_guard<mutex> lock(queue_mutex);
			for (size_t i = 0; i < 5; i++)
			{
				data_queue.push_front(i);
			}
			//cout << "111" << endl;
		}

		this_thread::sleep_for(chrono::milliseconds(100));
	}
}

void consumer(void)
{
	while (true)
	{
		//每隔10毫秒就取一次数据
		{
			lock_guard<mutex> lock(queue_mutex);
			if (!data_queue.empty())
			{
				data_queue.pop_front();
			}
			//cout << "222" << endl;
		}

		this_thread::sleep_for(chrono::milliseconds(10));
	}
}


int listDemo()
{
	thread producer_thread(producer);
	thread consumer_thread(consumer);
	thread print_thread(print_queue);

	producer_thread.join();
	consumer_thread.join();
	print_thread.join();

	return 0;
}


size_t sum = 0;
size_t large = 10000 * 10000;// 1亿以内的正整数
mutex mutex1;//定义mutex类型的变量mutex用来保护临界区

void sum_even(void)
{
	for (size_t i = 2; i <= large; i += 2)
	{
		lock_guard<mutex> lock(mutex1);
		sum += i;
	}
}

void sum_odd(void)
{
	for (size_t j = 1; j < large; j += 2)
	{
		lock_guard<mutex> lock(mutex1);//同上
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

