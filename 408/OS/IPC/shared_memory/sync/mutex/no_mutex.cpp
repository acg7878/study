#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

// 定义放在共享内存里的结构体
struct SharedData {
  int counter;            // 共享计数器
};

int main() {
  const char* shm_name = "no_mutex_shm";
  size_t shm_size = sizeof(SharedData);

  // 创建共享内存
  int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
  if (shm_fd == -1) {
    perror("shm_open");
    return 1;
  }
  ftruncate(shm_fd, shm_size);

  // 映射
  void* ptr = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (ptr == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  SharedData* data = (SharedData*)ptr;

  data->counter = 0;

  printf("Starting race condition test (NO MUTEX)...\n");

  // 创建子进程
  pid_t pid = fork();

  if (pid == 0) {
    // Child Process
    printf("Child start incrementing...\n");
    for (int i = 0; i < 100000; ++i) { // 增加次数以提高冲突概率
      data->counter++;
    }
    printf("Child done.\n");
    exit(0);
  } else if (pid > 0) {
    // Parent Process
    printf("Parent start incrementing...\n");
    for (int i = 0; i < 100000; ++i) {
      data->counter++;
    }
    printf("Parent done.\n");

    // 等待子进程结束
    wait(NULL);

    printf("Final Counter Value: %d (Expected: 200000)\n", data->counter);
    if (data->counter != 200000) {
        printf("RACE CONDITION DETECTED! Value is not 200000.\n");
    } else {
        printf("Lucky run? Value is 200000. Try increasing loop count.\n");
    }

    // 清理
    shm_unlink(shm_name);
  } else {
    perror("fork");
    return 1;
  }

  return 0;
}
