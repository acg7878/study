#include <future>
#include <iostream>

void producer(std::promise<int> promise, int num) {
  int result = num * num;
  promise.set_value(result);
}

void consumer(std::future<int>& future) {
  int result = future.get();
  std::cout << "result: " << result << std::endl;
}

int main() {
  std::promise<int> promise;
  std::future<int> future = promise.get_future();
  try {
    std::thread thread(producer, std::move(promise), 10);
    thread.join();

    // 阻塞等待，直到共享状态就绪
    consumer(future);
  } catch (const std::exception& e) {
    std::cout << "Error: " << e.what() << std::endl;
  }

  return 0;
}