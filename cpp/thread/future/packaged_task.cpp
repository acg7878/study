// 包装任务：用 std::packaged_task 包装目标可调用对象（指定任务签名，即返回值类型 + 参数类型）；
// 关联 future：通过 get_future() 获取与任务绑定的 std::future（用于后续拿结果 / 等完成）；
// 执行任务：将包装后的任务传递给 std::thread 执行（或直接在当前线程执行）；
// 获取结果：通过 future.get() 或 wait() 操作结果。

#include <future>
#include <iostream>

int multiply(int a, int b) {
  return a * b;
}

void print_hello() {
  std::cout << "hello" << std::endl;
}

int divide(int a, int b) {
  if (b == 0) {
    throw std::runtime_error("Division by zero is not allowed!");
  }
  return a / b;
}

void packaged_task() {
  std::packaged_task<int(int, int)> task(multiply);
  std::future<int> result = task.get_future();
  // task不能复制，需要移动
  std::thread thread(std::move(task), 3, 2);
  thread.join();
  std::cout << result.get() << std::endl;
}

void packaged_task_lambda() {
  std::packaged_task<int(int, int)> task(
      [](int a, int b) -> int { return a * b; });
  std::future<int> result = task.get_future();
  std::thread thread(std::move(task), 3, 2);
  thread.join();
  std::cout << result.get() << std::endl;
}

void packaged_task_void() {
  std::packaged_task<void()> task(print_hello);
  std::future<void> result = task.get_future();
  std::thread thread(std::move(task));
  thread.join();
  result.wait();
}

void packaged_task_error() {
  std::packaged_task<int(int, int)> task(divide);
  std::future<int> result = task.get_future();
  std::thread thread(std::move(task), 3, 0);
  thread.join();
  try {
    std::cout << result.get() << std::endl;
  } catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }
}

int main() {
  packaged_task();
  packaged_task_lambda();
  packaged_task_void();
  packaged_task_error();
  return 0;
}