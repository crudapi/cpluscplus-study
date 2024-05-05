// CMakeThreadTaskProject.cpp: 定义应用程序的入口点。
//

#include "CMakeThreadTaskProject.h"
#include <string>
#include <functional>
#include <thread>
#include <list>
#include <iostream>
#include <mutex>
#include <memory>

using namespace std;

int g_N = 1000 * 1000;//生产者生产的最后一个自然数

//线程类
class Task
{
public:
	Task(const string& name);
	//启动线程
	void start(void);
	virtual ~Task();//析构函数结束线程
	virtual void run_loop(void) = 0;//线程循环，派生类来重写
	void set_name(const string& name);//线程的名字
	const string& get_name(void) const;
protected:
	void exit_thread(void);//退出线程：会等待，直到线程退出
	void exit_task_thread_loop(void);//设置线程循环结束条件
	bool have_to_exit(void) const;//判断线程结束循环条件是否已经成立
	void notify(void);//给线程发送一个通知，告诉线程来新任务了
protected:
	//for Task run loop
	std::condition_variable m_condition_var;
	std::mutex m_mutex;
	string m_name;
private:
	unique_ptr<thread> m_thread;
	bool m_have_to_exit = false;
};
Task::Task(const string& name)
	:m_name(name)
{
}
//启动线程
void Task::start(void)
{
	cout << get_name() << " started." << endl;
	function<void()> work_fun = std::bind(&Task::run_loop, this);
	m_thread = make_unique<thread>(work_fun);
}

Task::~Task()
{
	cout << "~Task() " << m_name << " begin" << endl;
	if (m_thread/*never started*/)
	{
		exit_thread();
	}
	cout << "~Task() " << m_name << " end" << endl;
}

void Task::set_name(const string& name)
{
	m_name = name;
}

const string& Task::get_name(void) const
{
	return m_name;
}

void Task::exit_thread(void)
{
	if (m_thread->joinable())/*the exit_task_thread_loop has already been called*/
	{
		m_have_to_exit = true;
		//(12) your code. 给线程发信号，让线退出。因为此时线程收到信号的时候m_have_to_exit已经是true了
		notify();

		//(13) your code. 等待线程退出

		m_thread->join();
	}
}

void Task::exit_task_thread_loop(void)
{
	m_have_to_exit = true;
}

bool Task::have_to_exit(void) const
{
	return m_have_to_exit;
}

void Task::notify(void)
{
	m_condition_var.notify_one();
}
//消费者线程
//线程安全的消息队列
class SyncQueue
{
public:
	void push(int data);
	int pop(void);
	bool empty(void) const;
private:
	list<int> m_data_queue;//一个消息只能存放一个整数
	mutex m_mutex;
};

inline void SyncQueue::push(int data)
{
	//(10) your code 接收一个数据，放入队列。别忘记并发
	lock_guard<mutex> lock(m_mutex); 

	int t = data;
	m_data_queue.push_back(t);
}

inline int SyncQueue::pop(void)
{
	lock_guard<mutex> lock(m_mutex);
	int top = m_data_queue.front();
	m_data_queue.pop_front();
	return top;
}

inline bool SyncQueue::empty(void) const
{
	return m_data_queue.empty();
}

class Consumer : public Task
{
public:
	Consumer(const string& name) :Task(name) {}
	~Consumer()
	{
		//(6) your code 消费者退出之前告诉所有人，前N向和的结果，以和生产者的相印证
		cout << "Consumer says that:" << m_total_received << endl;
	}
	void consume_one(int data);
	void receive(int data);
private:
	void run_loop(void) override;
private:
	long long m_total_received = 0;//sum of every int received.
	SyncQueue m_queue;
};
void Consumer::receive(int message)
{
	m_queue.push(message);
	//11 your code 发射信号，通知消费线程有数据来了，快来处理
	notify();
}
void Consumer::consume_one(int message)
{
	//(1) your code 
	//累加收到的所有整数到成员变量m_total_received上，准备退出的时候打印输出
	m_total_received += message;
}
void Consumer::run_loop(void)
{
	cout << "Consumer::run_loop() begin run...." << endl;

	unique_lock<std::mutex> lock(m_mutex);
	while (!have_to_exit())
	{
		
		m_condition_var.wait(lock);
		//cout << "consumer received one event" << endl;

		lock.unlock();
		if (have_to_exit())
		{
			cout << "run loop break" << endl;
			break;//received exit_task_thread_loop
		}
		while (true)//循环处理队列直到为空
		{
			lock.lock();
			if (m_queue.empty())
			{
				//cout << "run loop empty" << endl;
				break;
			}
			else
			{
				//cout << "run loop pop" << endl;
				auto front = m_queue.pop();
				consume_one(front);
			}
			lock.unlock();
		}
	}
	cout << "Consumer::run_loop() exited." << endl;
}
//生产者线程
class Producer : public Task
{
public:
	Producer(const string& name, Consumer* c)
		:Task(name), m_consumer(c)
	{}
	~Producer()
	{
		//(5) your code 生产者退出之前告诉所有人，前N向和的结果
		cout << "Producer says that:" << m_sum << endl;
	}
	void push(int message)
	{
		if (m_consumer)
		{
			//(9) your code 通过消费者的接收功能实现数据传递给消费者
			m_consumer->receive(message);
		}
	}
private:
	void run_loop(void) override;
	//从事一次生产活动：按照顺序生成自然数序列中的下一个整数，作为消息，发送给消费者
	void produce_one(void)
	{
		produce_count++;
		auto message = produce_count;
		//(2) your code 把消息message送给消费者，通过调用push方法实现
		push(message);
		//(3) your code 生产者自己要累加求和到m_sum
		m_sum += produce_count;
		//cout << "produce_one " << produce_count << endl;
		if (produce_count >= total_produce_count)
		{
			//(4) your code 设置退出条件为true
			exit_task_thread_loop();
			return;
		}

	}
private:
	long long total_produce_count = g_N;
	long long produce_count = 0;
	long long m_sum = 0;
	Consumer* m_consumer = nullptr;
};
void Producer::run_loop(void)
{
	cout << "ProduceTask::process() begin run...." << endl;
	while (!have_to_exit())
	{
		produce_one();
	}
	cout << "ProduceTask::process() exited." << endl;
}

///////////////////////////////////////////////////////

int main()
{
	Consumer consumer("consumer");
	//(7) your code 创建生产者
	Producer  producer("producer", &consumer);
	//(8) your code 启动生产者线程
	producer.start();
	consumer.start();

	cout << "wait user cin to exit main =========>" << endl;
	string s;
	getline(cin, s);

	return 0;
}