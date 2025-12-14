#include <iostream>
#include <vector>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

struct SharedData {
    std::vector<int> vec;
};

int main() {
    const char* shm_name = "shm_vector";
    size_t shm_size = sizeof(SharedData);

    // 创建共享内存
    // macOS 对 shm_open 的名字要求比较严格，最好不要太长
    int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
    if (shm_fd == -1) {
        perror("shm_open");
        return 1;
    }
    // 设置大小
    if (ftruncate(shm_fd, shm_size) == -1) {
        perror("ftruncate");
        return 1;
    }

    // 映射
    void* ptr = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    // 在共享内存上构造 vector (Placement New)
    // 这一步把 vector 的“头部”（包含指针和size等信息）放在了共享内存里
    SharedData* data = new (ptr) SharedData();

    // 4. 操作 vector
    std::cout << "=== Writer Process ===" << std::endl;
    std::cout << "Shared Memory Address: " << data << std::endl;
    
    // 关键点：push_back 会在堆(Heap)上分配内存来存数据
    // 这个堆是 Writer 进程私有的！Reader 进程无法访问！
    data->vec.push_back(10);
    data->vec.push_back(20);
    data->vec.push_back(30);

    std::cout << "Pushed 10, 20, 30." << std::endl;
    std::cout << "Vector internal data pointer: " << data->vec.data() << " (Private Heap Address)" << std::endl;
    std::cout << "Waiting 30 seconds... Run reader now." << std::endl;
    sleep(30); // 等待

    // 清理
    // 注意：正常应该析构，但在演示中我们看看强行结束会怎样
    // data->~SharedData(); 
    shm_unlink(shm_name);
    return 0;
}
