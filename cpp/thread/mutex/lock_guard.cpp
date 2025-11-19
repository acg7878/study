#include <iostream>
#include <mutex>
#include <thread>

std::mutex mtx;
void add_accumulate(int& result, int a, int b) {
  int sum = a + b;
  {
    std::lock_guard<std::mutex> lock(mtx);  // 自动加锁和解锁
    result += sum;
  }
}

void add_accumulate_thread() {
  int result = 0;
  std::thread thread1(add_accumulate, std::ref(result), 1, 2);
  std::thread thread2(add_accumulate, std::ref(result), 3, 4);
  thread1.join();
  thread2.join();
  std::cout << "result: " << result << std::endl;
}

int main() {
  add_accumulate_thread();
  return 0;
}