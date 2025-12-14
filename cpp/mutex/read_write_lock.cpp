#include <chrono>
#include <iostream>
#include <mutex>
#include <shared_mutex>  // C++17
#include <thread>
#include <vector>

std::mutex mtx;  // 保护一下std::cout

class ThreadSafeCounter {
 private:
  mutable std::shared_mutex mutex_;  // 读写锁

  int value_ = 0;

 public:
  // 读操作：使用 shared_lock (共享锁)
  // 允许多个线程同时进入
  int get() const {
    std::shared_lock<std::shared_mutex> lock(mutex_);
    // 模拟读操作耗时
    // std::this_thread::sleep_for(std::chrono::milliseconds(10));
    return value_;
  }

  // 写操作：使用 unique_lock (独占锁)
  // 同一时刻只允许一个线程进入，且不允许有读者
  void increment() {
    std::unique_lock<std::shared_mutex> lock(mutex_);
    value_++;
  }
};

ThreadSafeCounter counter;

void reader(int id) {
  for (int i = 0; i < 5; ++i) {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Reader " << id << " read: " << counter.get() << "\n";
  }
}

void writer(int id) {
  for (int i = 0; i < 5; ++i) {
    counter.increment();
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "Writer " << id << " updated value\n";
  }
}

int main() {
  std::vector<std::thread> threads;

  // 10个读者，2个写者
  // 读写锁的优势在于：这10个读者可以并发执行，不用排队
  for (int i = 0; i < 10; ++i)
    threads.emplace_back(reader, i);
  for (int i = 0; i < 2; ++i)
    threads.emplace_back(writer, i);

  for (auto& t : threads)
    t.join();

  return 0;
}