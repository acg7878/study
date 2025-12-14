#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

struct SharedData {
  sem_t sem;     // 直接把信号量放在共享内存里
  int counter;
};

int main() {
  const char* shm_name = "unnamed_sem_shm";
  size_t shm_size = sizeof(SharedData);

  // 创建共享内存
  int shm_fd = shm_open(shm_name, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, shm_size);
  void* ptr = mmap(0, shm_size, PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
  
  SharedData* data = (SharedData*)ptr;
  data->counter = 0;

  // 初始化无名信号量
  // 参数: 信号量指针, pshared(1表示进程间共享), value(初始值)
  // 注意：macOS 不支持无名信号量 (sem_init)！这个例子在 macOS 上会报错或行为异常。
  // 在 Linux 上是标准的用法。
  if (sem_init(&data->sem, 1, 1) == -1) {
      perror("sem_init (Might not be supported on macOS)");
      // 继续运行可能会崩溃，但在 Linux 上是没问题的
  }

  printf("Starting unnamed semaphore test (Linux Only)...\n");

  pid_t pid = fork();

  if (pid == 0) {
    for (int i = 0; i < 10000; ++i) {
      sem_wait(&data->sem);
      data->counter++;
      sem_post(&data->sem);
    }
    exit(0);
  } else if (pid > 0) {
    for (int i = 0; i < 10000; ++i) {
      sem_wait(&data->sem);
      data->counter++;
      sem_post(&data->sem);
    }
    wait(NULL);
    printf("Final Counter Value: %d\n", data->counter);

    sem_destroy(&data->sem);
    shm_unlink(shm_name);
  }

  return 0;
}
