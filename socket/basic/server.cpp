#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>

#define PORT 8080
#define MAX_CONNECTIONS 5
#define BUFFER_SIZE 1024

int main() {
    int server_fd, client_fd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // 创建 socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "创建 socket 失败: " << strerror(errno) << std::endl;
        return 1;
    }

    // 设置 socket 选项，允许地址重用
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        std::cerr << "设置 socket 选项失败: " << strerror(errno) << std::endl;
        close(server_fd);
        return 1;
    }

    // 配置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;  // 监听所有网络接口
    server_addr.sin_port = htons(PORT);

    // 绑定 socket 到地址和端口
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "绑定失败: " << strerror(errno) << std::endl;
        close(server_fd);
        return 1;
    }

    // 开始监听连接
    if (listen(server_fd, MAX_CONNECTIONS) < 0) {
        std::cerr << "监听失败: " << strerror(errno) << std::endl;
        close(server_fd);
        return 1;
    }

    std::cout << "服务器启动成功，监听端口 " << PORT << "..." << std::endl;
    std::cout << "等待客户端连接..." << std::endl;

    // 接受客户端连接
    client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
    if (client_fd < 0) {
        std::cerr << "接受连接失败: " << strerror(errno) << std::endl;
        close(server_fd);
        return 1;
    }

    // 打印客户端信息
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, INET_ADDRSTRLEN);
    std::cout << "客户端已连接: " << client_ip << ":" << ntohs(client_addr.sin_port) << std::endl;

    // 接收和发送数据
    while (true) {
        // 清空缓冲区
        memset(buffer, 0, BUFFER_SIZE);

        // 接收客户端数据
        ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received < 0) {
            std::cerr << "接收数据失败: " << strerror(errno) << std::endl;
            break;
        } else if (bytes_received == 0) {
            std::cout << "客户端断开连接" << std::endl;
            break;
        }

        std::cout << "收到消息: " << buffer << std::endl;

        // 回显消息给客户端
        std::string response = "服务器收到: ";
        response += buffer;
        if (send(client_fd, response.c_str(), response.length(), 0) < 0) {
            std::cerr << "发送数据失败: " << strerror(errno) << std::endl;
            break;
        }
    }

    // 关闭连接
    close(client_fd);
    close(server_fd);
    std::cout << "服务器已关闭" << std::endl;

    return 0;
}

