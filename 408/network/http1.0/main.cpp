#include "http_server.h"
#include <iostream>
#include <locale>

#ifdef _WIN32
#include <windows.h>
#endif

// 设置 Windows 控制台为 UTF-8 编码
void setupConsoleEncoding() {
#ifdef _WIN32
    // 设置控制台代码页为 UTF-8 (65001)
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    
    // 设置 C++ locale（Windows 10 1903+ 支持 UTF-8）
    try {
        std::locale::global(std::locale(".UTF-8"));
        std::cout.imbue(std::locale(".UTF-8"));
        std::cerr.imbue(std::locale(".UTF-8"));
    } catch (...) {
        // 如果系统不支持 UTF-8 locale，使用默认 locale
        std::locale::global(std::locale(""));
    }
#else
    // Linux 平台默认使用 UTF-8
    std::locale::global(std::locale(""));
#endif
}

int main() {
    // 设置控制台编码为 UTF-8
    setupConsoleEncoding();
    
    int port = 8080;
    
    std::cout << "========================================" << std::endl;
    std::cout << "   HTTP/1.0 服务器" << std::endl;
    std::cout << "========================================\n" << std::endl;

    HttpServer server(port);

    if (!server.initialize()) {
        std::cerr << "服务器初始化失败！" << std::endl;
        return 1;
    }

    server.run();

    return 0;
}

