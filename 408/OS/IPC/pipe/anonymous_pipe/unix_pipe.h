#pragma once
#include "pipe.h"

#ifndef _WIN32
#include <unistd.h>

// Unix/Linux/macOS 平台的管道实现
class UnixPipe : public Pipe {
public:
    // 构造函数，自动创建管道
    UnixPipe();

    // 析构函数
    ~UnixPipe() override;

    // 实现基类的接口
    bool write(const std::string& message) override;
    std::string read() override;
    void closeRead() override;
    void closeWrite() override;
    
    // 在Unix平台，此操作为空，因为 fork() 的行为不同
    void makeWriteEndNonInheritable() override;
    
    // 在 Unix 中，子进程通过 fork() 直接继承文件描述符，
    // 不需要像 Windows 那样通过字符串传递句柄。
    std::string getReadHandleAsString() const override;

private:
    int pipefd[2];
};

#endif // !_WIN32
