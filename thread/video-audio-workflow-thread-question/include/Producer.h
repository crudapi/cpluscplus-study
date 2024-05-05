#pragma once
#include "Task.h"
#include "Consumer.h"

class Producer : public Task, public Pusher
{
public:
	virtual void produce_one(void) = 0;

	//Pusher
	//void push(T data);
	//void add_consumer(Consumer* c);

	virtual ~Producer() {}

	//Task
	//void start(void);
private:
	void run_loop(void) override;
};

