// 任务是用3个线程打印，总共 打印1-100
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
std::mutex mtx;
std::condition_variable cv;

int cur_num = 1;
int cur_index = 0;

void print_num(int index) {
  while (true) {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [index]() { return cur_num > 100 || cur_index == index; });

    if (cur_num > 100) {
      cv.notify_all();
      break;
    }

    std::cout << cur_num << std::endl;
    cur_num++;
    cur_index = (cur_index + 1) % 3;
    cv.notify_all();
  }
}

int main() {
  std::vector<std::thread> vec;
  for (int i = 0; i < 3; i++) {
    // std::thread 不可拷贝，只能移动（move）
    // 方法1：使用 std::move
    // std::thread t(print_num, i);
    // vec.push_back(std::move(t));
    
    // 方法2：直接使用 emplace_back（推荐，更简洁）
    vec.emplace_back(print_num, i);
  }

  // 使用引用，避免拷贝（std::thread 不可拷贝）
  for (auto& thread : vec) {
    thread.join();
  }
  
  return 0;
}