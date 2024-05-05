#pragma once
#include<functional>
#include <thread>
#include <mutex>
#include <memory>
#include <string>
using namespace std;

class Task
{
public:
	//start thread
	void start(void);
	virtual ~Task();
	virtual void run_loop(void) = 0;
	void set_name(const string& name);
	const string& get_name(void) const;
protected:
	void exit_thread(void);
	void exit_task_thread_loop(void);
	bool have_to_exit(void) const;
	void notify(void);
protected:
	//for Task run loop
	std::condition_variable m_condition_var;
	std::mutex m_mutex;
	string m_name;
private:
	unique_ptr<thread> m_thread;
	bool m_have_to_exit = false;
};


