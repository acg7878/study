#include <iostream>
#include <mutex>
#include <thread>
#include <vector>

// 使用递归锁 std::recursive_mutex
// 允许同一个线程多次获取同一把锁
std::recursive_mutex r_mtx;

void recursive_function(int level, int id) {
  if (level <= 0) {
    return;
  }

  // 第一次加锁
  // 如果这里用普通的 std::mutex，第二次进入时就会死锁！
  r_mtx.lock();

  std::cout << "Level " << level << " locked by thread " << id << std::endl;

  // 递归调用（第二次加锁）
  recursive_function(level - 1, id);

  // 解锁
  r_mtx.unlock();
}

int main() {
  std::thread t1(recursive_function, 3, 1);
  std::thread t2(recursive_function, 3, 2);

  t1.join();
  t2.join();

  return 0;
}
