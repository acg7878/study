// 多线程执行加法

#include <iostream>
#include <thread>


void add(int a, int b, int& result) {
  result = a + b;
}

void add_thread() {
  int result = 0;
  std::thread thread1(add, 1, 2, std::ref(result));
  thread1.join();
  std::cout << "result: " << result << std::endl;
}

void add_thread_lambda() {
  int result = 0;
  std::thread thread1([&result]() { result = 3 + 2; });
  thread1.join();
  std::cout << "result: " << result << std::endl;
}

int main() {
  add_thread();
  add_thread_lambda();
  return 0;
}