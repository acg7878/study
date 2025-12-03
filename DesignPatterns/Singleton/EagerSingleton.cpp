#include <iostream>

class EagerSingleton {
private:
    static EagerSingleton instance;
    EagerSingleton() {
        std::cout << "饿汉式单例构造" << std::endl;
    }
    EagerSingleton(const EagerSingleton&) = delete;
    EagerSingleton& operator=(const EagerSingleton&) = delete;

public:
    static EagerSingleton& getInstance() {
        return instance;
    }

    void doSomething() {
        std::cout << "饿汉式单例执行操作" << std::endl;
    }
};

EagerSingleton EagerSingleton::instance;

int main() {
    EagerSingleton& s1 = EagerSingleton::getInstance();
    EagerSingleton& s2 = EagerSingleton::getInstance();
    std::cout << "s1与s2是否为同一实例：" << (&s1 == &s2 ? "是" : "否") << std::endl;
    s1.doSomething();
    return 0;
}