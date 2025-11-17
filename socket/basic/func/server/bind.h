#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <cerrno>

inline bool bind_socket(int fd, const char *ip, int port) {
    // 声明sockaddr_in而不是sockaddr是因为要使用具体的关联一个协议的结构体来着
    // sockaddr是抽象、通用的；而这里我们要使用ipv4就需要使用sockaddr_in
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(port);
    addr.sin_addr.s_addr = inet_addr(ip);
    int ret = bind(fd, (struct sockaddr *)&addr, sizeof(addr));
    if (ret < 0) {
        std::cerr << "bind error: " << strerror(errno) << std::endl;
        ::close(fd);
        return false;
    }
    return true;
}