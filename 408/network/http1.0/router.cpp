#include "router.h"
#include "http_response.h"

Router::Router() {
    initializeRoutes();
}

void Router::initializeRoutes() {
    registerRoute("/", handleIndex);
    registerRoute("/index.html", handleIndex);
    registerRoute("/test", handleTest);
    registerRoute("/hello", handleHello);
    registerRoute("/json", handleJson);
}

void Router::registerRoute(const std::string& path, Handler handler) {
    routes[path] = handler;
}

HttpResponse Router::handleRequest(const HttpRequest& request) const {
    std::string path = request.getNormalizedPath();
    
    auto it = routes.find(path);
    if (it != routes.end()) {
        return it->second(request);
    }
    
    return handleNotFound(request);
}

HttpResponse Router::handleIndex(const HttpRequest& request) {
    std::string content = R"(<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>HTTP/1.0 服务器测试</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            max-width: 800px;
            margin: 50px auto;
            padding: 20px;
            background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
            color: white;
        }
        .container {
            background: rgba(255, 255, 255, 0.1);
            padding: 30px;
            border-radius: 10px;
            backdrop-filter: blur(10px);
        }
        h1 { color: #fff; }
        .info {
            background: rgba(0, 0, 0, 0.3);
            padding: 15px;
            border-radius: 5px;
            margin: 10px 0;
        }
        a {
            color: #ffd700;
            text-decoration: none;
        }
        a:hover { text-decoration: underline; }
    </style>
</head>
<body>
    <div class="container">
        <h1>🚀 HTTP/1.0 服务器测试成功！</h1>
        <div class="info">
            <p><strong>协议版本:</strong> HTTP/1.0</p>
            <p><strong>服务器:</strong> C++ 手写服务器</p>
            <p><strong>状态:</strong> 运行正常</p>
        </div>
        <h2>测试链接：</h2>
        <ul>
            <li><a href="/test">测试页面</a></li>
            <li><a href="/hello">Hello World</a></li>
            <li><a href="/json">JSON 数据</a></li>
        </ul>
    </div>
</body>
</html>)";
    
    return HttpResponse::ok(content);
}

HttpResponse Router::handleTest(const HttpRequest& request) {
    std::string content = R"(<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>测试页面</title>
    <style>
        body {
            font-family: Arial, sans-serif;
            padding: 40px;
            background: #f0f0f0;
        }
        .box {
            background: white;
            padding: 30px;
            border-radius: 8px;
            box-shadow: 0 2px 10px rgba(0,0,0,0.1);
        }
    </style>
</head>
<body>
    <div class="box">
        <h1>这是测试页面</h1>
        <p>HTTP/1.0 请求处理成功！</p>
        <p><a href="/">返回首页</a></p>
    </div>
</body>
</html>)";
    
    return HttpResponse::ok(content);
}

HttpResponse Router::handleHello(const HttpRequest& request) {
    std::string content = R"(<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello World!</h1>
    <p>这是一个简单的 HTTP/1.0 响应</p>
    <a href="/">返回首页</a>
</body>
</html>)";
    
    return HttpResponse::ok(content);
}

HttpResponse Router::handleJson(const HttpRequest& request) {
    std::string jsonContent = R"({"status":"success","message":"HTTP/1.0 JSON响应","data":{"version":"1.0","server":"C++"}})";
    return HttpResponse::json(jsonContent);
}

HttpResponse Router::handleNotFound(const HttpRequest& request) {
    std::string content = R"(<!DOCTYPE html>
<html>
<head>
    <meta charset="UTF-8">
    <title>404 Not Found</title>
</head>
<body>
    <h1>404 - 页面未找到</h1>
    <p>请求的路径: )" + request.path + R"(</p>
    <a href="/">返回首页</a>
</body>
</html>)";
    
    return HttpResponse::error(404, "Not Found", content);
}

