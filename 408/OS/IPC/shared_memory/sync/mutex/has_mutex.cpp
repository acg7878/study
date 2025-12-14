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
  pthread_mutex_t mutex;  // 互斥锁
  int counter;            // 共享计数器
};

int main() {
  const char* shm_name = "mutex_shm";
  size_t shm_size = sizeof(SharedData);

  int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
  if (shm_fd == -1) {
    perror("shm_open");
    return 1;
  }
  ftruncate(shm_fd, shm_size);

  void* ptr = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  if (ptr == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  SharedData* data = (SharedData*)ptr;

  // 初始化互斥锁
  pthread_mutexattr_t attr;
  pthread_mutexattr_init(&attr);
  // 设置互斥锁属性为“进程间共享”
  // 如果不设这个，默认是 PTHREAD_PROCESS_PRIVATE，只能在同一个进程的不同线程间用
  pthread_mutexattr_setpshared(&attr, PTHREAD_PROCESS_SHARED);

  pthread_mutex_init(&data->mutex, &attr);
  data->counter = 0;

  // 创建子进程
  pid_t pid = fork();

  if (pid == 0) {
    // Child Process
    printf("Child start incrementing...\n");
    for (int i = 0; i < 10000; ++i) {
      pthread_mutex_lock(&data->mutex);
      data->counter++;
      pthread_mutex_unlock(&data->mutex);
    }
    printf("Child done.\n");
    exit(0);
  } else if (pid > 0) {
    // Parent Process
    printf("Parent start incrementing...\n");
    for (int i = 0; i < 10000; ++i) {
      pthread_mutex_lock(&data->mutex);
      data->counter++;
      pthread_mutex_unlock(&data->mutex);
    }
    printf("Parent done.\n");

    // 等待子进程结束
    wait(NULL);

    printf("Final Counter Value: %d (Expected: 20000)\n", data->counter);

    // 清理
    pthread_mutex_destroy(&data->mutex);
    pthread_mutexattr_destroy(&attr);
    shm_unlink(shm_name);
  } else {
    perror("fork");
    return 1;
  }

  return 0;
}