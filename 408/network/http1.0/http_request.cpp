#include "http_request.h"
#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>

HttpRequest HttpRequest::parse(const std::string& rawRequest) {
    HttpRequest request;
    std::istringstream iss(rawRequest);
    std::string line;

    // 解析请求行
    if (std::getline(iss, line)) {
        std::istringstream lineStream(line);
        lineStream >> request.method >> request.path >> request.version;
        
        // 移除可能的 \r
        if (!request.version.empty() && request.version.back() == '\r') {
            request.version.pop_back();
        }
    }

    // 解析头部字段
    while (std::getline(iss, line) && !line.empty() && line != "\r") {
        size_t colonPos = line.find(':');
        if (colonPos != std::string::npos) {
            std::string key = line.substr(0, colonPos);
            std::string value = line.substr(colonPos + 1);
            
            // 去除前后空白
            key.erase(0, key.find_first_not_of(" \t\r\n"));
            key.erase(key.find_last_not_of(" \t\r\n") + 1);
            value.erase(0, value.find_first_not_of(" \t\r\n"));
            value.erase(value.find_last_not_of(" \t\r\n") + 1);
            
            request.headers[key] = value;
        }
    }

    // 解析消息体（如果有）
    std::string bodyLine;
    while (std::getline(iss, bodyLine)) {
        request.body += bodyLine + "\n";
    }

    return request;
}

std::string HttpRequest::getNormalizedPath() const {
    std::string normalizedPath = path;
    
    // 如果路径是 /，返回 /index.html
    if (normalizedPath == "/") {
        normalizedPath = "/index.html";
    }
    
    return normalizedPath;
}

void HttpRequest::print() const {
    std::cout << "请求头:" << std::endl;
    for (const auto& header : headers) {
        std::cout << "  " << header.first << ": " << header.second << std::endl;
    }
    
    if (!body.empty()) {
        std::cout << "\n请求体:\n" << body << std::endl;
    }
}

void HttpRequest::printDetailedHeaders() const {
    std::cout << "\n【请求头详细解析】" << std::endl;
    
    // 解析 Accept 头
    if (headers.find("Accept") != headers.end()) {
        std::cout << "  Accept: " << headers.at("Accept") << std::endl;
        std::cout << "    └─ 客户端接受的内容类型（MIME类型）" << std::endl;
    }
    
    // 解析 Accept-Encoding
    if (headers.find("Accept-Encoding") != headers.end()) {
        std::cout << "  Accept-Encoding: " << headers.at("Accept-Encoding") << std::endl;
        std::cout << "    └─ 客户端支持的压缩编码：gzip, deflate, br( Brotli ), zstd" << std::endl;
    }
    
    // 解析 Accept-Language
    if (headers.find("Accept-Language") != headers.end()) {
        std::cout << "  Accept-Language: " << headers.at("Accept-Language") << std::endl;
        std::cout << "    └─ 客户端首选语言：中文(zh-CN) > 中文(zh) > 英文(en) > 英式英语 > 美式英语" << std::endl;
    }
    
    // 解析 Connection
    if (headers.find("Connection") != headers.end()) {
        std::cout << "  Connection: " << headers.at("Connection") << std::endl;
        std::cout << "    └─ 连接控制：keep-alive(保持连接) / close(关闭连接)" << std::endl;
    }
    
    // 解析 Host
    if (headers.find("Host") != headers.end()) {
        std::cout << "  Host: " << headers.at("Host") << std::endl;
        std::cout << "    └─ 请求的目标主机和端口号" << std::endl;
    }
    
    // 解析 User-Agent
    if (headers.find("User-Agent") != headers.end()) {
        std::cout << "  User-Agent: " << headers.at("User-Agent") << std::endl;
        std::cout << "    └─ 客户端信息：Microsoft Edge 142.0 (基于 Chromium)" << std::endl;
    }
    
    // 解析 Sec-Fetch-* 头（安全相关）
    if (headers.find("Sec-Fetch-Dest") != headers.end()) {
        std::cout << "  Sec-Fetch-Dest: " << headers.at("Sec-Fetch-Dest") << std::endl;
        std::cout << "    └─ 请求目标类型：document(文档) / image(图片) / script(脚本) 等" << std::endl;
    }
    
    if (headers.find("Sec-Fetch-Mode") != headers.end()) {
        std::cout << "  Sec-Fetch-Mode: " << headers.at("Sec-Fetch-Mode") << std::endl;
        std::cout << "    └─ 请求模式：navigate(导航) / cors(跨域) / same-origin(同源) 等" << std::endl;
    }
    
    if (headers.find("Sec-Fetch-Site") != headers.end()) {
        std::cout << "  Sec-Fetch-Site: " << headers.at("Sec-Fetch-Site") << std::endl;
        std::cout << "    └─ 请求来源：none(直接输入) / same-origin(同源) / cross-site(跨站) 等" << std::endl;
    }
    
    if (headers.find("Sec-Fetch-User") != headers.end()) {
        std::cout << "  Sec-Fetch-User: " << headers.at("Sec-Fetch-User") << std::endl;
        std::cout << "    └─ 是否由用户触发：?1(是) / ?0(否)" << std::endl;
    }
    
    // 解析 Upgrade-Insecure-Requests
    if (headers.find("Upgrade-Insecure-Requests") != headers.end()) {
        std::cout << "  Upgrade-Insecure-Requests: " << headers.at("Upgrade-Insecure-Requests") << std::endl;
        std::cout << "    └─ 请求将 HTTP 升级为 HTTPS" << std::endl;
    }
    
    // 解析 sec-ch-ua 头（客户端提示）
    if (headers.find("sec-ch-ua") != headers.end()) {
        std::cout << "  sec-ch-ua: " << headers.at("sec-ch-ua") << std::endl;
        std::cout << "    └─ 客户端品牌信息：Chromium 142, Microsoft Edge 142" << std::endl;
    }
    
    if (headers.find("sec-ch-ua-mobile") != headers.end()) {
        std::cout << "  sec-ch-ua-mobile: " << headers.at("sec-ch-ua-mobile") << std::endl;
        std::cout << "    └─ 是否为移动设备：?0(否，桌面设备)" << std::endl;
    }
    
    if (headers.find("sec-ch-ua-platform") != headers.end()) {
        std::cout << "  sec-ch-ua-platform: " << headers.at("sec-ch-ua-platform") << std::endl;
        std::cout << "    └─ 操作系统平台：Windows" << std::endl;
    }
    
    // 显示其他未解析的头部
    std::cout << "\n【其他请求头】" << std::endl;
    bool hasOther = false;
    std::vector<std::string> parsedHeaders = {
        "Accept", "Accept-Encoding", "Accept-Language", "Connection", 
        "Host", "User-Agent", "Sec-Fetch-Dest", "Sec-Fetch-Mode", 
        "Sec-Fetch-Site", "Sec-Fetch-User", "Upgrade-Insecure-Requests",
        "sec-ch-ua", "sec-ch-ua-mobile", "sec-ch-ua-platform"
    };
    
    for (const auto& header : headers) {
        bool isParsed = false;
        for (const auto& parsed : parsedHeaders) {
            if (header.first == parsed) {
                isParsed = true;
                break;
            }
        }
        if (!isParsed) {
            if (!hasOther) {
                hasOther = true;
            }
            std::cout << "  " << header.first << ": " << header.second << std::endl;
        }
    }
    
    if (!hasOther) {
        std::cout << "  (无)" << std::endl;
    }
}

