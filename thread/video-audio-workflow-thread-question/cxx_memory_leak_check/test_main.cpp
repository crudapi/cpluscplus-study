
#include "memory_leak_checker.hpp"
#include <memory>
#include <vector>
#include <thread>
#include <future>

class A
{
public:
	counter_by_copy<A> m_checker;
};

A* CreateA(void)
{
	return new A;
}

void f(void)
{
	auto p = new A;
	//do some thing

	//leaked here
}

int main(int argc, char* argv[])
{
	auto pa = new A;//leak 1
	new A[5];//leak 5

	auto p2 = CreateA();
	delete p2;

	f();//leak 1

	auto listA = std::vector<std::shared_ptr<A>>(5, std::make_shared<A>());//no leak
	for (int i = 0; i < 3; ++i)
	{
		listA.push_back(std::make_shared<A>());//no leak
	}
	std::cout << "test leack 7" << std::endl;
}