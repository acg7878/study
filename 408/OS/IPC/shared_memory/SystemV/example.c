/* shm_demo.c */
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_SIZE 1024

// ftok: 生成共享内存Key
// shmget: 创建或获取共享内存
// shmat: 将共享内存映射到当前进程地址空间
// shmdt: 分离共享内存
// shmctl: 控制共享内存


int main(void) {
  key_t key = ftok(".", 0x42);  // 生成共享内存Key

  // 创建或获取大小 1024 的共享内存，权限为可读写（0666）
  int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);

  // 将共享内存映射到当前进程地址空间，得到可直接读写的指针
  char* data = (char*)shmat(shmid, NULL, 0);

  pid_t pid = fork();
  if (pid == 0) {
    // 子进程：读取父进程写入的数据
    sleep(1);  // 等待父进程写
    printf("Child read: %s\n", data);
    strcpy(data, "ack from child");  // 回写
    shmdt(data); // 分离共享内存
    return 0;
  } else {
    // 父进程：写入数据
    strcpy(data, "hello from parent");
    wait(NULL); // 等待子进程结束
    printf("Parent got: %s\n", data);
    shmdt(data); // 分离共享内存
    shmctl(shmid, IPC_RMID, NULL);  // 删除共享内存
  }
  return 0;
}