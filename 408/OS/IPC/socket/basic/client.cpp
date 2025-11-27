#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <cerrno>
#include <string>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int client_fd;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    // 创建 socket
    client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (client_fd < 0) {
        std::cerr << "创建 socket 失败: " << strerror(errno) << std::endl;
        return 1;
    }

    // 配置服务器地址
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
    // 将 IP 地址字符串转换为网络字节序
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        std::cerr << "无效的服务器地址: " << SERVER_IP << std::endl;
        close(client_fd);
        return 1;
    }

    // 连接到服务器
    std::cout << "正在连接到服务器 " << SERVER_IP << ":" << PORT << "..." << std::endl;
    if (connect(client_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        std::cerr << "连接失败: " << strerror(errno) << std::endl;
        close(client_fd);
        return 1;
    }

    std::cout << "已成功连接到服务器！" << std::endl;
    std::cout << "输入消息（输入 'quit' 退出）:" << std::endl;

    // 发送和接收数据
    std::string message;
    while (true) {
        // 从用户输入读取消息
        std::cout << "> ";
        std::getline(std::cin, message);

        // 检查是否退出
        if (message == "quit" || message == "exit") {
            std::cout << "正在断开连接..." << std::endl;
            break;
        }

        // 发送消息到服务器
        if (send(client_fd, message.c_str(), message.length(), 0) < 0) {
            std::cerr << "发送数据失败: " << strerror(errno) << std::endl;
            break;
        }

        // 清空缓冲区
        memset(buffer, 0, BUFFER_SIZE);

        // 接收服务器响应
        ssize_t bytes_received = recv(client_fd, buffer, BUFFER_SIZE - 1, 0);
        if (bytes_received < 0) {
            std::cerr << "接收数据失败: " << strerror(errno) << std::endl;
            break;
        } else if (bytes_received == 0) {
            std::cout << "服务器断开连接" << std::endl;
            break;
        }

        // 打印服务器响应
        std::cout << "服务器响应: " << buffer << std::endl;
    }

    // 关闭连接
    close(client_fd);
    std::cout << "客户端已关闭" << std::endl;

    return 0;
}

