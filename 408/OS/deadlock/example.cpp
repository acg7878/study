#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

std::mutex m1;
std::mutex m2;

void task1() {
  std::cout << "task1: try to get m1" << std::endl;
  std::lock_guard<std::mutex> lock1(m1);
  std::cout << "task1: get m1 successfully" << std::endl;

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  std::cout << "task1: try to get m2" << std::endl;
  std::lock_guard<std::mutex> lock2(m2);
  std::cout << "task1: get m2 successfully" << std::endl;
}

void task2() {
  std::cout << "task2: try to get m2" << std::endl;
  std::lock_guard<std::mutex> lock2(m2);
  std::cout << "task2: get m2 successfully" << std::endl;

  std::this_thread::sleep_for(std::chrono::milliseconds(100));

  std::cout << "task2: try to get m1" << std::endl;
  std::lock_guard<std::mutex> lock1(m1);
  std::cout << "task2: get m1 successfully" << std::endl;
}

int main() {
  std::thread t1(task1);
  std::thread t2(task2);

  t1.join();
  t2.join();

  std::cout << "Main finished" << std::endl;
  return 0;
}
