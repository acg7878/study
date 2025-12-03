#pragma once
#include <string>

// 抽象基类 Pipe，定义了管道的通用接口
class Pipe {
public:
    // 虚析构函数，确保子类可以被正确销毁
    virtual ~Pipe() {}

    // 向管道写入数据
    virtual bool write(const std::string& message) = 0;

    // 从管道读取数据
    virtual std::string read() = 0;

    // 关闭管道的读取端
    virtual void closeRead() = 0;

    // 关闭管道的写入端
    virtual void closeWrite() = 0;

    // 设置写入端为不可继承 (主要用于 Windows 平台)
    virtual void makeWriteEndNonInheritable() = 0;

    // 获取读取端句柄/文件描述符的字符串表示，用于跨进程传递
    virtual std::string getReadHandleAsString() const = 0;
};