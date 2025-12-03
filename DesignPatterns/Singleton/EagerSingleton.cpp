#include <iostream>

class EagerSingleton {
private:
    static EagerSingleton instance;
    EagerSingleton() {
        std::cout << "EagerSingleton constructor" << std::endl;
    }
    EagerSingleton(const EagerSingleton&) = delete;
    EagerSingleton& operator=(const EagerSingleton&) = delete;

public:
    static EagerSingleton& getInstance() {
        return instance;
    }

    void doSomething() {
        std::cout << "doSomething" << std::endl;
    }
};

EagerSingleton EagerSingleton::instance;

int main() {
    EagerSingleton& s1 = EagerSingleton::getInstance();
    EagerSingleton& s2 = EagerSingleton::getInstance();
    std::cout << "s1 and s2 is same ? " << (&s1 == &s2 ? "yes" : "no") << std::endl;
    s1.doSomething();
    return 0;
}