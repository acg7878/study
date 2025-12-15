// 异步 IO：Asynchronous IO (AIO)
// 核心思想：发起 IO 请求后立刻返回，当 IO 完成时通过信号或回调通知进程

#include <aio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// 模拟正在进行的计算任务
void do_heavy_computation() {
    printf("CPU is busy calculating...");
    for(int i=0; i<5; ++i) {
        printf(".");
        fflush(stdout);
        sleep(1); // 模拟耗时操作
    }
    printf(" Done!\n");
}

int main() {
    const char* filename = "test_aio.txt";
    const char* data = "This is written asynchronously via POSIX AIO.\n";
    size_t len = strlen(data);

    // 打开文件（注意：不能使用 O_APPEND，AIO 需要指定具体 offset）
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 准备 aiocb (AIO Control Block) 结构体
    struct aiocb cb;
    memset(&cb, 0, sizeof(cb));
    
    cb.aio_fildes = fd;      // 文件描述符
    cb.aio_buf = (void*)data;// 数据缓冲区
    cb.aio_nbytes = len;     // 要写的字节数
    cb.aio_offset = 0;       // 写入文件的偏移量

    // 发起异步写请求
    // 这里的 aio_write 会立刻返回，不会阻塞等待写操作完成
    printf("[AIO] Submitting write request...\n");
    if (aio_write(&cb) == -1) {
        perror("aio_write");
        close(fd);
        return 1;
    }

    // 在 IO 进行的同时，CPU 可以去干别的事
    printf("[CPU] Request submitted. Now I can do other work without blocking!\n");
    do_heavy_computation();

    // 检查 IO 是否完成
    // aio_error 返回 0 表示完成，EINPROGRESS 表示正在进行
    printf("[AIO] Checking status...\n");
    while (aio_error(&cb) == EINPROGRESS) {
        printf("[AIO] Still writing...\n");
        usleep(100000); // 稍微等一下
    }

    // 获取最终结果
    // aio_return 返回实际写入的字节数
    int ret = aio_return(&cb);
    if (ret != -1) {
        printf("[AIO] Write completed successfully! Written %d bytes.\n", ret);
    } else {
        perror("aio_return");
    }

    close(fd);
    return 0;
}
