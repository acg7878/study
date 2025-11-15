#include <iostream>

// 1. 编译器为 Lambda 生成的【匿名闭包类】（实际类名由编译器分配，如
// _ZNK3$_0clEii） 类名格式：编译器自动生成唯一标识（避免冲突），这里简化为
// _Lambda_Func
class _Lambda_Func {
public:
  // 2. 重载 operator()（函数调用运算符）—— Lambda 的核心实现
  // 特征完全匹配原 Lambda：
  // - 参数列表：(int a, int b)（与原 Lambda 一致）
  // - 返回值：int（原 Lambda 显式指定的 -> int）
  // - const 限定：默认添加（无 mutable 时，operator() 是 const 成员函数）
  int operator()(int a, int b) const {
    return a + b; // 原 Lambda 的函数体，直接照搬
  }
};

void lambda1() {
    auto func = [](int a, int b) -> int {
        return a + b;
    };
    int result = func(1, 2);
    std::cout << result << std::endl;
}

void gcc_create_lambda() {
    // 3. Lambda 定义 → 创建闭包类的临时实例（func 是闭包对象）
    // 等价于原代码的 auto func = [](int a, int b) -> int { return a + b; };
    _Lambda_Func func; 

    // 4. Lambda 调用 → 调用闭包对象的 operator()
    // 等价于原代码的 func(1, 2)
    int result = func.operator()(1, 2); 

    std::cout << result << std::endl; // 输出 3
}

int main() {
    lambda1();
    gcc_create_lambda();
    return 0;
}
