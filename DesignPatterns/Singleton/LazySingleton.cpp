#include <iostream>

class LazySingleton {
private:
    LazySingleton() {
        std::cout << "LazySingleton constructor" << std::endl;
    }
    LazySingleton(const LazySingleton&) = delete;
    LazySingleton& operator=(const LazySingleton&) = delete;

public:
    static LazySingleton& getInstance() {
        static LazySingleton instance;
        return instance;
    }

    void doSomething() {
        std::cout << "doSomething" << std::endl;
    }
};

int main() {
    LazySingleton& s1 = LazySingleton::getInstance();
    LazySingleton& s2 = LazySingleton::getInstance();
    std::cout << "s1 and s2 is same ? " << (&s1 == &s2 ? "yes" : "no") << std::endl;
    s1.doSomething();
    return 0;
}