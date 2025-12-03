#include "unix_pipe.h"

#ifndef _WIN32
#include <stdexcept>
#include <iostream>
#include <vector>

UnixPipe::UnixPipe() {
    if (pipe(pipefd) == -1) {
        throw std::runtime_error("UnixPipe: pipe() failed.");
    }
}

UnixPipe::~UnixPipe() {
    closeRead();
    closeWrite();
}

bool UnixPipe::write(const std::string& message) {
    if (pipefd[1] == -1) return false;
    ssize_t bytes_written = ::write(pipefd[1], message.c_str(), message.length());
    if (bytes_written == -1) {
        perror("UnixPipe write");
        return false;
    }
    return true;
}

std::string UnixPipe::read() {
    if (pipefd[0] == -1) return "";
    
    char buffer[128];
    ssize_t bytes_read;
    std::string result;
    
    // 循环读取，直到管道中没有数据 (read 返回 0 或 -1)
    while ((bytes_read = ::read(pipefd[0], buffer, sizeof(buffer) - 1)) > 0) {
        buffer[bytes_read] = '\0';
        result += buffer;
    }

    if (bytes_read == -1) {
        perror("UnixPipe read");
    }

    return result;
}

void UnixPipe::closeRead() {
    if (pipefd[0] != -1) {
        ::close(pipefd[0]);
        pipefd[0] = -1;
    }
}

void UnixPipe::closeWrite() {
    if (pipefd[1] != -1) {
        ::close(pipefd[1]);
        pipefd[1] = -1;
    }
}

void UnixPipe::makeWriteEndNonInheritable() {
    // 在 Unix 平台，此操作为空。
    // fork() 会复制文件描述符表，父子进程通过各自的 close() 来管理描述符的生命周期。
    // 不需要像 Windows 那样在创建子进程前设置继承属性。
}

std::string UnixPipe::getReadHandleAsString() const {
    // fork() 模式下不需要此功能，但为保持接口一致性而实现
    return std::to_string(pipefd[0]);
}

#endif // !_WIN32
