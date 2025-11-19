#include <iostream>

#include <thread>
#include <mutex>

std::mutex mtx;
void add_accumulate(int& result,int a,int b) {
    int sum = a + b;
    mtx.lock();
    result += sum;
    mtx.unlock();
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