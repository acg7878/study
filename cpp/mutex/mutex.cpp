#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// 共享资源
int counter = 0;
std::mutex mtx;

void increment(int id) {
  for (int i = 0; i < 1000; ++i) {
    mtx.lock();
    counter++;
    mtx.unlock();
  }
  // std::cout 也是一种共享资源，不加锁可能会输出乱序
  std::lock_guard<std::mutex> lock(mtx);
  std::cout << "Thread " << id << " finished." << std::endl;
}

int main() {
  std::vector<std::thread> threads;

  for (int i = 0; i < 10; ++i) {
    threads.emplace_back(increment, i);
  }
  for (auto& t : threads) {
    t.join();
  }

  std::cout << "Final counter value: " << counter << " (Expected: 10000)"
            << std::endl;

  return 0;
}
