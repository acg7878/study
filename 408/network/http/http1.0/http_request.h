#ifndef HTTP_REQUEST_H
#define HTTP_REQUEST_H

#include <string>
#include <map>

class HttpRequest {
public:
    std::string method;
    std::string path;
    std::string version;
    std::map<std::string, std::string> headers;
    std::string body;

    HttpRequest() = default;
    
    // 从原始请求字符串解析
    static HttpRequest parse(const std::string& rawRequest);
    
    // 获取请求路径（规范化）
    std::string getNormalizedPath() const;
    
    // 打印请求信息（用于调试）
    void print() const;
    
    // 详细解析并打印请求头信息
    void printDetailedHeaders() const;
};

#endif // HTTP_REQUEST_H

