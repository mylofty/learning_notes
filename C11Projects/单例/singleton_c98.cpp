
#include<mutex>
#include<iostream>

// 饿汉模式
class EHSingleton {
public:
    static EHSingleton * GetInstance(){
        return instance_;
    }

    static void DestoryInstance(){
        if(instance_){
            delete instance_;
        }
    }

private:
    EHSingleton(){
        std::cout << "EHSingleton::create singleton..." << std::endl;
    };
    EHSingleton(const EHSingleton&) = delete;
    EHSingleton& operator=(const EHSingleton&) = delete;
private:
    static EHSingleton *instance_;
};

EHSingleton* EHSingleton::instance_ = new EHSingleton();


// 懒汉模式
class LHSingleton {
public:
    static LHSingleton* GetInstance(){
        if(instance_==nullptr){
            std::lock_guard<std::mutex> lock(mutex_);
            if(instance_==nullptr){
                instance_ = new LHSingleton();
            }
        }
        return instance_;
        
    }

private:
    LHSingleton() {
        std::cout << "LHSingleton::create singleton..." << std::endl;
    }
    LHSingleton(const LHSingleton&) = delete;
    LHSingleton& operator=(const LHSingleton&) = delete;

private:
    static LHSingleton *instance_;
    static std::mutex mutex_;
};

LHSingleton* LHSingleton::instance_;
std::mutex LHSingleton::mutex_;


int main(){
    auto singleton1 = EHSingleton::GetInstance();
    auto singleton2 = EHSingleton::GetInstance();
    std::cout << "singleton pos=" << &singleton1 << ", " << &singleton2 << std::endl;
}