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

    int shm_fd = shm_open(shm_name, O_RDWR, 0666);
    if (shm_fd == -1) {
        std::cerr << "Run writer first!" << std::endl;
        return 1;
    }

    void* ptr = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    if (ptr == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    SharedData* data = (SharedData*)ptr;

    std::cout << "=== Reader Process ===" << std::endl;
    std::cout << "Shared Memory Mapped Address: " << ptr << std::endl;
    
    // 这里 data->vec 的内容（那几个指针）是从共享内存读来的
    // 但是这些指针指向的地址（数据区）是 Writer 进程里的地址！
    std::cout << "Attempting to read vector..." << std::endl;
    
    // 尝试访问
    // 此时 vec 内部的指针指向的是 Writer 进程的虚拟地址空间
    // 在 Reader 进程中，这个地址通常是无效的 (Segmentation Fault)
    // 或者指向了 Reader 自己的某个随机数据
    std::cout << "Vector size (read from raw memory): " << data->vec.size() << std::endl;
    std::cout << "Vector capacity (read from raw memory): " << data->vec.capacity() << std::endl;
    
    std::cout << "Trying to access data[0]..." << std::endl;
    std::cout << "Value: " << data->vec[0] << std::endl; // CRASH EXPECTED HERE

    return 0;
}
