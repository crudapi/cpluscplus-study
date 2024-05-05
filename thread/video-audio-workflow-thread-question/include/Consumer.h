#pragma once
#include "Queue.h"
#include "Task.h"
#include <functional>
#include <thread>
#include <mutex>
#include <memory>
#include "Data.h"

class IConsumer
{
public:
	virtual ~IConsumer(){}
	virtual void receive(T data) = 0;
	virtual void consume_one(T data) = 0;
};

class Consumer;
class ConsumerSet
{
public:
	void push(T data);
	void add_consumer(Consumer* c);
private:
	mutex m_mutex_for_set;
	list<Consumer*> m_consumer_set;
};
class Pusher
{
public:
	virtual ~Pusher(){}
	void push(T data);
	void add_consumer(Consumer* c);
private:
	ConsumerSet m_consumerSet;
};
class Consumer : public IConsumer, public Task, public Pusher
{
public:
	//IConsumer
	//virtual void consume_one(T data) = 0;
	void receive(T data) override;

	//Pusher
	//void push(T data);
	//void add_consumer(Consumer* c);
protected:
	//for ConsumerBase receive
	SyncQueue m_queue;

	//Task
	//void start(void);
private:
	void run_loop(void) override;
};


