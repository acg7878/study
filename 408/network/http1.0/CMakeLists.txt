cmake_minimum_required(VERSION 3.10)
project(HTTP10Server)

set(CMAKE_CXX_STANDARD 11)

# 添加所有源文件
add_executable(http_server 
    main.cpp
    http_server.cpp
    http_request.cpp
    http_response.cpp
    router.cpp
)

# 平台特定的链接库
if(WIN32)
    # Windows 平台需要链接 ws2_32
    target_link_libraries(http_server ws2_32)
else()
    # Linux/Unix 平台不需要额外链接库
    # socket 函数在 libc 中
endif()

