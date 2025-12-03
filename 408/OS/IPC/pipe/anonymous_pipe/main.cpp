/*
 * 这是一个使用 C++ 类封装的、跨平台的匿名管道 (Anonymous Pipe) 示例。
 *
 * --- 设计 ---
 * - pipe.h: 定义了抽象基类 `Pipe`，提供了统一的接口。
 * - win_pipe.h/cpp: 实现了 Windows 版本的 `WinPipe`。
 * - unix_pipe.h/cpp: 实现了 Unix/Linux 版本的 `UnixPipe`。
 *
 * --- 平台特定逻辑 ---
 * - Windows: 由于没有 fork()，子进程通过 CreateProcess() 启动。
 *   父进程通过命令行参数，将管道的读取句柄传递给子进程。
 *   程序通过检查 argc 来判断自己是父进程还是子进程。
 *
 * - Unix: 使用经典的 fork() 模型。子进程直接继承父进程的文件描述符。
 *   程序通过 fork() 的返回值来判断自己是父进程还是子进程。
 *
 * --- 编译 ---
 * - Windows (MSVC):
 *   cl main.cpp win_pipe.cpp /EHsc /o pipe_example.exe
 *
 * - Unix/Linux/WSL (g++):
 *   g++ main.cpp unix_pipe.cpp -o pipe_example
 */

#include <iostream>
#include <string>
#include <memory> // For std::unique_ptr
#include <stdexcept>

// 根据平台包含对应的头文件
#ifdef _WIN32
#include "win_pipe.h"
#else
#include "unix_pipe.h"
#endif

// =================================================================
// ================ WINDOWS IMPLEMENTATION (_WIN32) ================
// =================================================================
#ifdef _WIN32
#include <windows.h>

void ParentProcess() {
    try {
        WinPipe pipe;
        std::cout << "Parent: Pipe created." << std::endl;

        // *** 关键修复 ***
        // 在创建子进程之前，设置管道的写入端为不可继承。
        // 这样子进程就不会持有我们不希望它有的写句柄，从而避免死锁。
        pipe.makeWriteEndNonInheritable();

        // 获取当前可执行文件的路径，用于创建子进程
        char exePath[MAX_PATH];
        GetModuleFileName(NULL, exePath, MAX_PATH);
        std::string commandLine = "\"" + std::string(exePath) + "\" child " + pipe.getReadHandleAsString();
        
        STARTUPINFO si;
        PROCESS_INFORMATION pi;
        ZeroMemory(&si, sizeof(si));
        si.cb = sizeof(si);
        ZeroMemory(&pi, sizeof(pi));

        // 创建子进程，并传递读取句柄
        if (!CreateProcess(NULL, (LPSTR)commandLine.c_str(), NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
            throw std::runtime_error("Parent: CreateProcess failed.");
        }

        // 父进程关闭读取端
        pipe.closeRead();

        const std::string message = "Hello from parent (Windows)!";
        std::cout << "Parent: Writing message -> \"" << message << "\"" << std::endl;
        pipe.write(message);

        // 写完后关闭写入端，这样子进程的 ReadFile 才能结束
        pipe.closeWrite();

        // 等待子进程结束
        WaitForSingleObject(pi.hProcess, INFINITE);
        std::cout << "Parent: Child process has finished." << std::endl;

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);

    } catch (const std::exception& e) {
        std::cerr << "Error in ParentProcess: " << e.what() << std::endl;
    }
}

void ChildProcess(const char* readHandleStr) {
    try {
        // 子进程使用从命令行获取的句柄创建 Pipe 对象
        WinPipe pipe(readHandleStr);
        std::cout << "Child: Ready to read from pipe." << std::endl;
        
        std::string message = pipe.read();
        std::cout << "Child: Read message <- \"" << message << "\"" << std::endl;

        // 读取完毕后，管道对象会在析构时自动关闭句柄
        std::cout << "Child: Finishing." << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error in ChildProcess: " << e.what() << std::endl;
    }
}

int main(int argc, char* argv[]) {
    if (argc == 3 && std::string(argv[1]) == "child") {
        ChildProcess(argv[2]);
    } else {
        ParentProcess();
    }
    return 0;
}

// =================================================================
// ================= POSIX IMPLEMENTATION (Unix) ===================
// =================================================================
#else
#include <unistd.h>
#include <sys/wait.h>

int main() {
    try {
        UnixPipe pipe;
        std::cout << "Process " << getpid() << ": Pipe created." << std::endl;
        
        pid_t pid = fork();

        if (pid < 0) {
            throw std::runtime_error("fork() failed.");
        }

        if (pid > 0) {
            // --- 父进程 ---
            std::cout << "Parent " << getpid() << ": Forked child " << pid << std::endl;
            
            // 父进程关闭读取端
            pipe.closeRead();
            
            const std::string message = "Hello from parent (Unix)!";
            std::cout << "Parent " << getpid() << ": Writing message -> \"" << message << "\"" << std::endl;
            pipe.write(message);

            // 写完后关闭写入端
            pipe.closeWrite();

            // 等待子进程结束
            wait(NULL);
            std::cout << "Parent " << getpid() << ": Child process has finished." << std::endl;

        } else {
            // --- 子进程 ---
            std::cout << "Child " << getpid() << ": Ready to read." << std::endl;
            
            // 子进程关闭写入端
            pipe.closeWrite();
            
            std::string message = pipe.read();
            std::cout << "Child " << getpid() << ": Read message <- \"" << message << "\"" << std::endl;

            // 读取完毕后，管道对象会在析构时自动关闭句柄
            std::cout << "Child " << getpid() << ": Finishing." << std::endl;
        }

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

#endif
