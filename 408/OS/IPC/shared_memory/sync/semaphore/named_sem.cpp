#include <fcntl.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

// 信号量名称
#define SEM_NAME "/my_test_sem"

// 定义放在共享内存里的数据
struct SharedData {
  int counter;
};

int main() {
  const char* shm_name = "sem_shm";
  size_t shm_size = sizeof(SharedData);

  // 创建共享内存
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
  data->counter = 0;

  // 创建并初始化有名信号量
  // 参数: 名字, 标志位, 权限, 初始值(1表示互斥锁)
  // 如果已存在则打开，否则创建
  sem_t* sem = sem_open(SEM_NAME, O_CREAT, 0666, 1);
  if (sem == SEM_FAILED) {
    perror("sem_open");
    return 1;
  }

  printf("Starting semaphore test (10000 increments per process)...\n");

  pid_t pid = fork();

  if (pid == 0) {
    // Child Process
    for (int i = 0; i < 10000; ++i) {
      // P操作 (Wait): 减1，如果为0则阻塞
      sem_wait(sem);
      
      data->counter++;
      
      // V操作 (Post): 加1，唤醒等待者
      sem_post(sem);
    }
    printf("Child done.\n");
    exit(0);
  } else if (pid > 0) {
    // Parent Process
    for (int i = 0; i < 10000; ++i) {
      sem_wait(sem);
      data->counter++;
      sem_post(sem);
    }
    printf("Parent done.\n");

    wait(NULL);

    printf("Final Counter Value: %d (Expected: 20000)\n", data->counter);

    // 清理
    sem_close(sem);
    sem_unlink(SEM_NAME); // 删除信号量文件
    shm_unlink(shm_name);
  } else {
    perror("fork");
    return 1;
  }

  return 0;
}
