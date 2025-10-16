#include <iostream>

class LazySingleton {
private:
    // 私有构造函数
    LazySingleton() {
        std::cout << "懒汉式单例构造" << std::endl;
    }

    // 禁止拷贝和赋值
    LazySingleton(const LazySingleton&) = delete;
    LazySingleton& operator=(const LazySingleton&) = delete;

public:
    // 全局访问点：局部静态变量实现懒加载，且线程安全（C++11+）
    static LazySingleton& getInstance() {
        static LazySingleton instance;  // 首次调用时初始化
        return instance;
    }

    void doSomething() {
        std::cout << "懒汉式单例执行操作" << std::endl;
    }
};

// 测试
int main() {
    LazySingleton& s1 = LazySingleton::getInstance();
    LazySingleton& s2 = LazySingleton::getInstance();
    std::cout << "s1与s2是否为同一实例：" << (&s1 == &s2 ? "是" : "否") << std::endl;
    s1.doSomething();
    return 0;
}