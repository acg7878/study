// 同步阻塞 IO：Synchronous Blocking IO (SIO)
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main() {
  const char* filename = "test_io.txt";
  const char* data = "Hello, OS World!\n";
  size_t len = strlen(data);
  // 使用标准库 IO (Standard IO) - 全缓冲/行缓冲 (Buffered)
  // 数据先写到用户态缓冲区，缓冲区满了或手动 flush 才会陷入内核
  // 优点：减少系统调用次数，吞吐量高
  // 缺点：如果程序崩溃，缓冲区数据可能丢失
  FILE* fp = fopen(filename, "a");  // append mode
  if (!fp) {
    perror("fopen");
    return 1;
  }
  printf("Writing with Standard Library (fwrite)...\n");
  for (int i = 0; i < 3; ++i) {
    fwrite(data, 1, len, fp);
    // 此时数据可能还在内存缓冲区里，没写到磁盘
  }
  // 强制刷新缓冲区到内核
  fflush(fp);
  fclose(fp);  // close 也会触发 flush
  printf("Done. Check content of %s\n", filename);
  return 0;
}
