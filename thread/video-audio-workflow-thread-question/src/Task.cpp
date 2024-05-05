#include "Task.h"
#include <iostream>
using namespace std;

//start thread
void Task::start(void)
{
	cout << get_name() << " started." << endl;
	function<void()> work_fun = std::bind(&Task::run_loop, this);
	m_thread = make_unique<thread>(work_fun);//start thread here
}

Task::~Task()
{
	cout << "~Task() "<<m_name<<" begin" << endl;
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
	if (m_thread->joinable()/*(4) your code*/)/*the exit_task_thread_loop has already been called*/
	{
		m_have_to_exit = true;
		m_condition_var.notify_one();//sent event to thread loop for break thread loop
		// (5) your code. wait for the thread return

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
