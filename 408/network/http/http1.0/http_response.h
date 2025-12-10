#ifndef HTTP_RESPONSE_H
#define HTTP_RESPONSE_H

#include <string>
#include <map>

class HttpResponse {
public:
    int statusCode;
    std::string statusText;
    std::map<std::string, std::string> headers;
    std::string body;

    HttpResponse() : statusCode(200), statusText("OK") {}

    // 设置状态码
    void setStatus(int code, const std::string& text);
    
    // 设置头部字段
    void setHeader(const std::string& key, const std::string& value);
    
    // 设置消息体
    void setBody(const std::string& content, const std::string& contentType = "text/html; charset=UTF-8");
    
    // 生成完整的 HTTP/1.0 响应字符串
    std::string toString() const;
    
    // 创建成功响应
    static HttpResponse ok(const std::string& content, const std::string& contentType = "text/html; charset=UTF-8");
    
    // 创建错误响应
    static HttpResponse error(int code, const std::string& message, const std::string& content = "");
    
    // 创建 JSON 响应
    static HttpResponse json(const std::string& jsonContent);
    
    // 创建重定向响应
    static HttpResponse redirect(int code, const std::string& location);
    
    // 便捷方法：301 永久重定向
    static HttpResponse redirect301(const std::string& location);
    
    // 便捷方法：302 临时重定向
    static HttpResponse redirect302(const std::string& location);
};

#endif // HTTP_RESPONSE_H

