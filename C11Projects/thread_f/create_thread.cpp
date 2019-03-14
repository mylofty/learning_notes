#include<thread>
#include<iostream>
#include<string>
#include<functional>

void fun(int i, std::string s)
{
	std::cout << "now you run the thread " << i << " function" <<  s <<std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "this_thread id is " << std::this_thread::get_id()<<std::endl;
	std::this_thread::yield();
}

int main()
{
	std::function<void(int)> func  = std::bind(fun, std::placeholders::_1, "string");
	std::thread threads[10];
	for(int i = 0; i < 10; i++)
	{
		threads[i] = std::thread(func, i);
		std::cout << "threads[" << i << "] thread id is " << threads[i].get_id() << std::endl;
	}
	std::cout << "run all threads" << std::endl;
	for(auto& t: threads)
	{
		t.join();
	}
	return 0;
}
