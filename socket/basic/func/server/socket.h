#include <cerrno>
#include <cstring>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

inline int socket_init() {
    // socket 
    int fd = ::socket(AF_INET,SOCK_STREAM,0);
    if (fd < 0) {
        std::cerr << "socket error: " << strerror(errno) << std::endl;
        return -1;
    }

    // 设置 socket 选项，允许地址重用
    int opt = 1;
    int ret = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int));
    if (ret < 0) {
        std::cerr << "setsockopt error: " << strerror(errno) << std::endl;
        ::close(fd);
        return -1;
    }


    return fd;
}