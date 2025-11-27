#include "http_server.h"
#include "http_request.h"
#include "http_response.h"
#include <iostream>
#include <cstring>
#include <iomanip>
#include <ctime>
#include <sstream>

#ifdef _WIN32
    #include <ws2tcpip.h>
#else
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
#endif

HttpServer::HttpServer(int port) : port(port), serverSocket(INVALID_SOCKET_VALUE) {
}

HttpServer::~HttpServer() {
    if (serverSocket != INVALID_SOCKET_VALUE) {
        CLOSE_SOCKET(serverSocket);
    }
    cleanupSocketLibrary();
}

bool HttpServer::initialize() {
    // 初始化 socket 库
    if (initSocketLibrary() != 0) {
        std::cerr << "Socket library initialization failed" << std::endl;
        return false;
    }

    // 创建 socket
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET_VALUE) {
        std::cerr << "Socket creation failed: " << getSocketError() << std::endl;
        cleanupSocketLibrary();
        return false;
    }

    // 设置 SO_REUSEADDR 选项
    int opt = 1;
    #ifdef _WIN32
        setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, (char*)&opt, sizeof(opt));
    #else
        setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    #endif

    // 绑定地址
    sockaddr_in serverAddr;
    std::memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(port);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR_VALUE) {
        std::cerr << "Bind failed: " << getSocketError() << std::endl;
        CLOSE_SOCKET(serverSocket);
        cleanupSocketLibrary();
        return false;
    }

    // 开始监听
    if (listen(serverSocket, 5) == SOCKET_ERROR_VALUE) {
        std::cerr << "Listen failed: " << getSocketError() << std::endl;
        CLOSE_SOCKET(serverSocket);
        cleanupSocketLibrary();
        return false;
    }

    return true;
}

std::string HttpServer::getCurrentTime() const {
    auto now = std::time(nullptr);
    std::tm tm;
    
    #ifdef _WIN32
        localtime_s(&tm, &now);
    #else
        localtime_r(&now, &tm);
    #endif
    
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y-%m-%d %H:%M:%S");
    return oss.str();
}

void HttpServer::printClientInfo(const sockaddr_in& clientAddr) const {
    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &(clientAddr.sin_addr), clientIP, INET_ADDRSTRLEN);
    int clientPort = ntohs(clientAddr.sin_port);
    std::cout << "[" << getCurrentTime() << "] 新连接来自: " << clientIP << ":" << std::to_string(clientPort) << std::endl;
}

void HttpServer::handleClient(SocketType clientSocket) {
    char buffer[4096] = {0};
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);

    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0';
        std::string rawRequest(buffer);

        // 解析请求
        HttpRequest request = HttpRequest::parse(rawRequest);
        
        // 打印请求信息（用于调试）
        std::cout << "\n[" << getCurrentTime() << "] ========== 收到请求 ==========" << std::endl;
        std::cout << "请求行: " << request.method << " " << request.path << " " << request.version << std::endl;
        request.print();
        request.printDetailedHeaders();

        // 通过路由器处理请求
        HttpResponse response = router.handleRequest(request);

        // 打印响应信息
        std::cout << "[" << getCurrentTime() << "] 响应状态: " << std::to_string(response.statusCode) << " " << response.statusText << std::endl;
        std::cout << "========================================\n" << std::endl;

        // 发送响应
        std::string responseStr = response.toString();
        send(clientSocket, responseStr.c_str(), responseStr.length(), 0);
    }

    // HTTP/1.0 每次请求后关闭连接
    CLOSE_SOCKET(clientSocket);
}

void HttpServer::run() {
    std::cout << "HTTP/1.0 服务器启动成功！" << std::endl;
    std::cout << "监听端口: " << std::to_string(port) << std::endl;
    std::cout << "在浏览器中访问: http://localhost:" << std::to_string(port) << std::endl;
    #ifdef _WIN32
        std::cout << "按 Ctrl+C 停止服务器\n" << std::endl;
    #else
        std::cout << "按 Ctrl+C 停止服务器\n" << std::endl;
    #endif

    while (true) {
        sockaddr_in clientAddr;
        #ifdef _WIN32
            int clientAddrLen = sizeof(clientAddr);
        #else
            socklen_t clientAddrLen = sizeof(clientAddr);
        #endif
        
        SocketType clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);

        if (clientSocket == INVALID_SOCKET_VALUE) {
            std::cerr << "Accept failed: " << getSocketError() << std::endl;
            continue;
        }

        printClientInfo(clientAddr);
        handleClient(clientSocket);
    }
}

