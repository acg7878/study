#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include "platform_socket.h"
#include "router.h"

class HttpServer {
private:
    SocketType serverSocket;
    int port;
    Router router;

public:
    HttpServer(int port);
    ~HttpServer();

    // 初始化服务器
    bool initialize();
    
    // 运行服务器
    void run();
    
private:
    // 处理客户端连接
    void handleClient(SocketType clientSocket);
    
    // 打印客户端信息
    void printClientInfo(const sockaddr_in& clientAddr) const;
    
    // 获取当前时间字符串
    std::string getCurrentTime() const;
};

#endif // HTTP_SERVER_H

