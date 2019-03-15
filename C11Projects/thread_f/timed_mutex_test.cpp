#include<iostream>
#include<mutex>
#include<thread>
#include<string>

std::timed_mutex mutex;

void function(std::string threadName)
{
	std::chrono::milliseconds timeout(200);
	while(true)
	{
		if(mutex.try_lock_for(timeout))
		{
			std::cout << threadName <<  ": now, we are do a task !" << std::endl;
			std::chrono::milliseconds duration(100);
			std::this_thread::sleep_for(duration);
			mutex.unlock();
			std::this_thread::sleep_for(duration);
		}
		else
		{
			std::chrono::milliseconds duration(100);
			std::cout << threadName << ": Do nother work" << std::endl;
			std::this_thread::sleep_for(duration);
		}
	}
}

int main(int argc, char const *argv[])
{
	std::thread t1(function, "thread1111");
	std::thread t2(function, "thread2222");
	t1.join();
	t2.join();
	return 0;
}