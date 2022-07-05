// c++11 常用单例写法


#include <iostream>
#include <mutex>


// 懒汉模式
class Singleton {
    public:
    static Singleton &getInstance(){
        // 通过局部静态变量的特性保证了线程安全 (C++11, GCC > 4.3, VS2015支持该特性);
        static Singleton s;
        return s;
    }
    private:
    Singleton(){
        std::cout << "Singleton::create singleton..." << std::endl;
    }
};


// call_once 懒汉模式
class LHSingleton
{
public:
    static LHSingleton &GetInstance(){
        static std::once_flag s_flag;
        std::call_once(s_flag,[&](){
            instance_.reset(new LHSingleton());
        });
        return *instance_;
    }

private:
    LHSingleton(){
        std::cout << "LHSingleton::create singleton..." << std::endl;
    }

private:
    static std::unique_ptr<LHSingleton> instance_;
};


std::unique_ptr<LHSingleton> LHSingleton::instance_;


int main(){
    auto s1 = Singleton::getInstance();
    auto s2 = Singleton::getInstance();
    std::cout << "s1=" << &s1 << ", s2=" << &s2 << std::endl;
}