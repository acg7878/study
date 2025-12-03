#pragma once
#include "pipe.h"

#ifdef _WIN32
#include <windows.h>

// Windows 平台的管道实现
class WinPipe : public Pipe {
public:
    // 默认构造函数，用于父进程创建管道
    WinPipe();

    // 用于子进程的构造函数，根据从父进程传递来的句柄字符串创建管道对象
    explicit WinPipe(const std::string& readHandleStr);

    // 析构函数，负责关闭打开的句柄
    ~WinPipe() override;

    // 实现基类的接口
    bool write(const std::string& message) override;
    std::string read() override;
    void closeRead() override;
    void closeWrite() override;
    void makeWriteEndNonInheritable() override;
    std::string getReadHandleAsString() const override;

private:
    HANDLE hReadPipe;
    HANDLE hWritePipe;
};

#endif // _WIN32