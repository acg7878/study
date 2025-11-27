#ifndef ROUTER_H
#define ROUTER_H

#include "http_request.h"
#include "http_response.h"
#include <functional>
#include <map>

class Router {
public:
    using Handler = std::function<HttpResponse(const HttpRequest&)>;

private:
    std::map<std::string, Handler> routes;

public:
    Router();
    
    // 注册路由
    void registerRoute(const std::string& path, Handler handler);
    
    // 处理请求
    HttpResponse handleRequest(const HttpRequest& request) const;
    
private:
    // 初始化默认路由
    void initializeRoutes();
    
    // 路由处理函数
    static HttpResponse handleIndex(const HttpRequest& request);
    static HttpResponse handleTest(const HttpRequest& request);
    static HttpResponse handleHello(const HttpRequest& request);
    static HttpResponse handleJson(const HttpRequest& request);
    static HttpResponse handleRedirect301(const HttpRequest& request);
    static HttpResponse handleRedirect302(const HttpRequest& request);
    static HttpResponse handleRedirectTarget(const HttpRequest& request);
    static HttpResponse handleNotFound(const HttpRequest& request);
};

#endif // ROUTER_H

