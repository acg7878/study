#include <iostream>

class EagerSingleton {
private:
    // 静态实例（类加载时初始化，C++中全局/静态变量初始化在main前）
    static EagerSingleton instance;

    // 私有构造函数：禁止外部实例化
    EagerSingleton() {
        std::cout << "饿汉式单例构造" << std::endl;
    }

    // 禁止拷贝和赋值（防复制）
    EagerSingleton(const EagerSingleton&) = delete;
    EagerSingleton& operator=(const EagerSingleton&) = delete;

public:
    // 全局访问点
    static EagerSingleton& getInstance() {
        return instance;
    }

    void doSomething() {
        std::cout << "饿汉式单例执行操作" << std::endl;
    }
};

// 类外初始化静态成员（触发实例创建）
EagerSingleton EagerSingleton::instance;

// 测试
int main() {
    EagerSingleton& s1 = EagerSingleton::getInstance();
    EagerSingleton& s2 = EagerSingleton::getInstance();
    std::cout << "s1与s2是否为同一实例：" << (&s1 == &s2 ? "是" : "否") << std::endl;
    s1.doSomething();
    return 0;
}