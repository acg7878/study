#include "win_pipe.h"

#ifdef _WIN32
#include <iostream>

WinPipe::WinPipe() : hReadPipe(INVALID_HANDLE_VALUE), hWritePipe(INVALID_HANDLE_VALUE) {
    SECURITY_ATTRIBUTES sa;
    sa.nLength = sizeof(SECURITY_ATTRIBUTES);
    sa.bInheritHandle = TRUE; // 允许句柄被继承
    sa.lpSecurityDescriptor = NULL;

    if (!CreatePipe(&hReadPipe, &hWritePipe, &sa, 0)) {
        // 在构造函数中处理错误通常不是最佳实践，这里为了示例简单直接抛出异常
        throw std::runtime_error("WinPipe: CreatePipe failed.");
    }
}

WinPipe::WinPipe(const std::string& readHandleStr) : hWritePipe(INVALID_HANDLE_VALUE) {
    // 从字符串转换回 HANDLE
    hReadPipe = (HANDLE)std::stoull(readHandleStr);
}

WinPipe::~WinPipe() {
    closeRead();
    closeWrite();
}

bool WinPipe::write(const std::string& message) {
    if (hWritePipe == INVALID_HANDLE_VALUE) return false;
    DWORD bytesWritten;
    if (!WriteFile(hWritePipe, message.c_str(), (DWORD)message.length(), &bytesWritten, NULL)) {
        std::cerr << "WinPipe: WriteFile failed. Error: " << GetLastError() << std::endl;
        return false;
    }
    return true;
}

std::string WinPipe::read() {
    if (hReadPipe == INVALID_HANDLE_VALUE) return "";
    
    char buffer[128];
    DWORD bytesRead;
    std::string result;

    // 循环读取，直到管道中没有数据
    while (ReadFile(hReadPipe, buffer, sizeof(buffer) - 1, &bytesRead, NULL) && bytesRead > 0) {
        buffer[bytesRead] = '\0';
        result += buffer;
    }
    return result;
}

void WinPipe::closeRead() {
    if (hReadPipe != INVALID_HANDLE_VALUE) {
        CloseHandle(hReadPipe);
        hReadPipe = INVALID_HANDLE_VALUE;
    }
}

void WinPipe::closeWrite() {
    if (hWritePipe != INVALID_HANDLE_VALUE) {
        CloseHandle(hWritePipe);
        hWritePipe = INVALID_HANDLE_VALUE;
    }
}

void WinPipe::makeWriteEndNonInheritable() {
    if (hWritePipe == INVALID_HANDLE_VALUE) return;
    // 设置写句柄为不可继承
    if (!SetHandleInformation(hWritePipe, HANDLE_FLAG_INHERIT, 0)) {
        throw std::runtime_error("WinPipe: SetHandleInformation for write handle failed.");
    }
}

std::string WinPipe::getReadHandleAsString() const {
    return std::to_string((unsigned long long)hWritePipe);
}

#endif // _WIN32
