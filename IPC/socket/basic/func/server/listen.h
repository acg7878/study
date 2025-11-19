#include <sys/socket.h>
#include <unistd.h>
#include <iostream>
#include <cerrno>
#include <cstring>
inline bool listen_socket(int fd, int backlog) {
    int ret = listen(fd, backlog);
    if (ret < 0) {
        std::cerr << "listen error: " << strerror(errno) << std::endl;
        ::close(fd);
        return false;
    }
    return true;
}