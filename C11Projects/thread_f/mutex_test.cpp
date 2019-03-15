#include<thread>
#include<iostream>
#include<functional>
#include<mutex>
#include<string>
#include<vector>
#include<memory>

std::mutex g_lock;
// use raw lock,unlock
void fun(int i, std::string name)
{
	g_lock.lock();
	std::cout << "thread[" << i << "], name is "<< name << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "thread[" << i << "] will finish" << std::endl;
	g_lock.unlock();
}

// use lock_guard
void fun2(int i, std::string name)
{
	std::lock_guard<std::mutex> locker(g_lock);
	std::cout << "thread[" << i << "], name is "<< name << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(5));
	std::cout << "thread[" << i << "] will finish" << std::endl;
}

int main()
{
	std::vector<std::shared_ptr<std::thread>> threadPtrVec;
	std::shared_ptr<std::thread> sp1 = std::make_shared<std::thread>(std::bind(fun, std::placeholders::_1, "dingding"),1);
	std::shared_ptr<std::thread> sp2 = std::make_shared<std::thread>(std::bind(fun, std::placeholders::_1, "zhizhi"), 2);
	std::shared_ptr<std::thread> sp3 = std::make_shared<std::thread>(std::bind(fun, std::placeholders::_1, "minmin"), 3);
	threadPtrVec.push_back(sp1);
	threadPtrVec.push_back(sp2);
	threadPtrVec.push_back(sp3);

	std::cout << "show your id" << std::endl;
	for(auto sp : threadPtrVec)
	{
		std::cout << sp->get_id()<< "\t";
	}

	for(auto sp : threadPtrVec)
	{
		sp->join();
	}

	std::cout << "main thread finish" << std::endl;
	return 0;
}

