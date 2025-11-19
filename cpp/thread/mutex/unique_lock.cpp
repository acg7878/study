#include <mutex>
#include <thread>
#include <iostream>

std::mutex mtx;
void add_accumulate(int& result,int a,int b) {
    int sum = a + b;
    std::unique_lock<std::mutex> lock(mtx); // 自动加锁和解锁
    result += sum;
}

void add_accumulate_defer(int& result, int a, int b) {
  int sum = a + b;
  std::unique_lock<std::mutex> lock(mtx,std::defer_lock);  // 延迟加锁
  lock.lock();
  result += sum;
  // 自动解锁，无需lock.unlock()
}

void add_accumulate_adopt(int& result, int a, int b) {
  int sum = a + b;
  mtx.lock();
  std::unique_lock<std::mutex> lock(mtx,std::adopt_lock);  // 已经加锁，无需再加锁
  result += sum;
}

int main() {
    int result = 0;
    std::thread thread1(add_accumulate, std::ref(result), 1, 2);
    std::thread thread2(add_accumulate, std::ref(result), 3, 4);
    thread1.join();
    thread2.join();
    std::thread thread3(add_accumulate_defer, std::ref(result), 5, 6);
    thread3.join();
    std::thread thread4(add_accumulate_adopt, std::ref(result), 7, 8);
    thread4.join();
    std::cout << "result: " << result << std::endl;
    return 0;
}