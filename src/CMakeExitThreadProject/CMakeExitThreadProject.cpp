// CMakeExitThreadProject.cpp: 定义应用程序的入口点。
//

#include "CMakeExitThreadProject.h"

#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string_view>
#include <mutex>
#include <queue>
#include <sstream>

using namespace std;
class Logger
{
public:
	Logger();
	virtual ~Logger();
	Logger(const Logger& src) = delete;
	Logger& operator=(const Logger& rhs) = delete;
	void log(std::string entry);
private:
	void processLogging();
	std::mutex m_mutex;
	std::condition_variable m_condition_var;
	std::queue<std::string> m_queue;
	std::thread m_thread;
	bool m_have_to_exit = false;
};
Logger::Logger()
{
	m_thread = thread{ &Logger::processLogging, this };
	cout << "Logger::Logger()" << endl;
}

void Logger::log(std::string entry)
{
	unique_lock<std::mutex> lock(m_mutex);
	m_queue.push(entry);
	m_condition_var.notify_all();
}

Logger::~Logger()
{
	cout << "Logger::~Logger()" << endl;
	{
		unique_lock<std::mutex> lock(m_mutex);
		m_have_to_exit = true;
		m_condition_var.notify_all();
	}
	m_thread.join();//这一句不能被lock控制，否则退不出去
}

void Logger::processLogging()
{
	cout << "Logger::processLogging() begin run...." << endl;
	ofstream logFile("log.txt");

	if (logFile.fail())
	{
		cerr << "Failed to open logfile." << endl;
		return;
	}

	unique_lock<std::mutex> lock(m_mutex);
	while (true)
	{
		if (!m_have_to_exit)
		{
			m_condition_var.wait(lock);
		}
		lock.unlock();
		while (true)//循环处理队列直到为空
		{
			lock.lock();
			if (m_queue.empty())
			{
				break;
			}
			else
			{
				logFile << m_queue.front() << endl;
				m_queue.pop();
			}
			lock.unlock();
		}
		if (m_have_to_exit)
		{
			cout << "m_have_to_exit is true.\n";
			break;
		}
	}
	cout << "Logger::processLogging() exited." << endl;
}

void logSomeMessage(int id, Logger& logger)
{
	for (int i = 0; i < 5; ++i)
	{
		stringstream ss;
		ss << " Thread " << id << " log message the " << i << "th times.";
		logger.log(ss.str());
	}
}

int main()
{
	cout << "hello main.\n";
	Logger logger;
	cout << "ready to create producer" << endl;
	vector<thread> threads;
	for (int i = 0; i < 5; ++i)
	{
		cout << "times: " << i << "\n";
		threads.emplace_back(logSomeMessage, i, ref(logger));
	}
	for (auto& t : threads)
	{
		t.join();
	}
	cout << "main exited.\n";
	return 0;
}