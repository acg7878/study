
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>

#define SHM_NAME "/mmap_demo"
#define SHM_SIZE 1024

int main(void) {
  int fd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
  if (fd == -1) {
    perror("shm_open");
    return EXIT_FAILURE;
  }

  if (ftruncate(fd, SHM_SIZE) == -1) {
    perror("ftruncate");
    close(fd);
    shm_unlink(SHM_NAME);
    return EXIT_FAILURE;
  }

  char* data = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (data == MAP_FAILED) {
    perror("mmap");
    close(fd);
    shm_unlink(SHM_NAME);
    return EXIT_FAILURE;
  }
  close(fd);  // fd不再需要，映射仍然有效

  pid_t pid = fork();
  if (pid == -1) {
    perror("fork");
    munmap(data, SHM_SIZE);
    shm_unlink(SHM_NAME);
    return EXIT_FAILURE;
  }

  if (pid == 0) {
    // 子进程：读取父进程信息并回写
    sleep(1);
    printf("Child read: %s\n", data);
    strcpy(data, "ack from child (mmap)");
    munmap(data, SHM_SIZE);
    return EXIT_SUCCESS;
  }

  strcpy(data, "hello from parent (mmap)");
  wait(NULL);
  printf("Parent got: %s\n", data);

  munmap(data, SHM_SIZE);
  shm_unlink(SHM_NAME);
  return EXIT_SUCCESS;
}
