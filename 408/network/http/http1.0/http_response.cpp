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

HttpResponse HttpResponse::redirect(int code, const std::string& location) {
    HttpResponse response;
    
    // 根据状态码设置状态文本
    std::string statusText;
    switch (code) {
        case 301:
            statusText = "Moved Permanently";
            break;
        case 302:
            statusText = "Found";
            break;
        case 303:
            statusText = "See Other";
            break;
        case 307:
            statusText = "Temporary Redirect";
            break;
        case 308:
            statusText = "Permanent Redirect";
            break;
        default:
            statusText = "Redirect";
            break;
    }
    
    response.setStatus(code, statusText);
    response.setHeader("Location", location);
    
    // 重定向响应通常包含一个简单的 HTML 提示（可选）
    std::string body = "<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\">\n"
                      "<meta http-equiv=\"refresh\" content=\"0; url=" + location + "\">\n"
                      "<title>重定向</title>\n</head>\n<body>\n"
                      "<h1>" + std::to_string(code) + " " + statusText + "</h1>\n"
                      "<p>正在重定向到: <a href=\"" + location + "\">" + location + "</a></p>\n"
                      "</body>\n</html>";
    
    response.setBody(body);
    return response;
}

HttpResponse HttpResponse::redirect301(const std::string& location) {
    return redirect(301, location);
}

HttpResponse HttpResponse::redirect302(const std::string& location) {
    return redirect(302, location);
}

