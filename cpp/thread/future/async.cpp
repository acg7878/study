#include <future>
#include <iostream>
int add(int a, int b) {
  return a + b;
}

void print_hello() {
  std::cout << "hello" << std::endl;
}

void void_async() {
  std::future<void> result = std::async(print_hello);
  result.wait();
}

void int_async() {
  std::future<int> result = std::async(add, 1, 2);
  // get()只能调用一次，调用第二次会抛出std::future_error异常
  std::cout << result.get() << std::endl;
}

void lambda_async() {
  std::future<int> result = std::async([](int a, int b) -> int {
    return a + b;
  }, 1, 2);
  std::cout << result.get() << std::endl;
}

void policy_async() {
  // std::launch::async: 异步执行，创建新的线程
  // std::launch::deferred: 延迟执行，直到调用get()或wait()
  // (默认)std::launch::async | std::launch::deferred: 异步执行，如果可以的话，创建新的线程
  std::future<int> result = std::async(std::launch::async, add, 1, 2);
  std::cout << result.get() << std::endl;
}

void error_async() {
  std::future<int> result = std::async(add, 1, 2);
  // get()只能调用一次，调用第二次会抛出std::future_error异常
  std::cout << result.get() << std::endl;
  try {
    std::cout << result.get() << std::endl;
  } catch (const std::future_error& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
}

int main() {
  void_async();
  int_async();
  lambda_async();
  policy_async();
  error_async();
  return 0;
}