#include "http_response.h"
#include <sstream>

void HttpResponse::setStatus(int code, const std::string& text) {
    statusCode = code;
    statusText = text;
}

void HttpResponse::setHeader(const std::string& key, const std::string& value) {
    headers[key] = value;
}

void HttpResponse::setBody(const std::string& content, const std::string& contentType) {
    body = content;
    setHeader("Content-Type", contentType);
    setHeader("Content-Length", std::to_string(content.length()));
}

std::string HttpResponse::toString() const {
    std::ostringstream oss;
    
    // 状态行
    oss << "HTTP/1.0 " << statusCode << " " << statusText << "\r\n";
    
    // 头部字段
    for (const auto& header : headers) {
        oss << header.first << ": " << header.second << "\r\n";
    }
    
    // 空行
    oss << "\r\n";
    
    // 消息体
    oss << body;
    
    return oss.str();
}

HttpResponse HttpResponse::ok(const std::string& content, const std::string& contentType) {
    HttpResponse response;
    response.setBody(content, contentType);
    return response;
}

HttpResponse HttpResponse::error(int code, const std::string& message, const std::string& content) {
    HttpResponse response;
    response.setStatus(code, message);
    
    std::string errorContent = content;
    if (errorContent.empty()) {
        errorContent = "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n<title>" +
                      std::to_string(code) + " " + message + "</title>\n</head>\n<body>\n<h1>" +
                      std::to_string(code) + " - " + message + "</h1>\n</body>\n</html>";
    }
    
    response.setBody(errorContent);
    return response;
}

HttpResponse HttpResponse::json(const std::string& jsonContent) {
    HttpResponse response;
    response.setBody(jsonContent, "application/json");
    return response;
}

