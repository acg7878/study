// [](参数列表) { 函数体 }
// 参数列表: 可以省略参数类型，编译器会自动推导
// 捕获：可以捕获外部的变量，捕获方式有：按值捕获、按引用捕获、按地址捕获


#include <iostream>
#include <vector>
#include <algorithm>
void lambda1() {
    auto func = [](int a, int b) -> int {
        return a + b;
    };
    int result = func(1, 2);
    std::cout << result << std::endl;
}

void sort_lambda() {
    std::vector<int> vec = {51, 12, 33, 44, 55};
    std::sort(vec.begin(), vec.end(), [](int a, int b) -> bool {
        return a < b;
    });
    for (auto &v : vec) {
        std::cout << v << " ";
    }
    std::cout << std::endl;
}

void mutable_lambda() {
    int a = 10;
    // lambda 默认是 const 的，不能修改捕获的变量
    // 加上 mutable 关键字后，可以修改捕获的变量
    auto func = [a]() mutable -> int {
        a++;
        return a + 1;
    };
    std::cout << func() << std::endl;
    std::cout << a << std::endl;
}


int main() {
    lambda1();
    sort_lambda();
    return 0;
}