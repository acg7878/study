# 设置所需的最低 CMake 版本
cmake_minimum_required(VERSION 3.10)

# 定义项目名称
project(PipeExample CXX)

# 设置 C++ 标准为 C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加主可执行文件，源文件为 main.cpp
add_executable(pipe_example main.cpp)

# ==========================================================
# ==        根据平台链接特定的源文件        ==
# ==========================================================

# 检查是否为 Windows 平台 (WIN32 是 CMake 的内置变量)
if(WIN32)
    # 如果是 Windows，则将 win_pipe.cpp 添加到可执行文件的源列表中
    target_sources(pipe_example PRIVATE win_pipe.cpp)
    message(STATUS "Configuring for Windows")
else()
    # 如果不是 Windows (即 Linux, macOS 等)，则添加 unix_pipe.cpp
    target_sources(pipe_example PRIVATE unix_pipe.cpp)
    message(STATUS "Configuring for Unix-like system")
endif()

# ==========================================================
# ==                   如何使用此文件                   ==
# ==========================================================
#
# 1. 创建一个构建目录并进入:
#    mkdir build
#    cd build
#
# 2. 运行 CMake 来生成构建系统:
#    cmake ..
#    (在 Windows 上，你可能需要指定一个生成器, e.g., cmake .. -G "Visual Studio 17 2022")
#
# 3. 编译项目:
#    cmake --build .
#    (或者在 Linux/macOS 上直接运行 make, 或在 Windows 上打开生成的 .sln 文件)
#
# 4. 运行可执行文件:
#    - Windows: ./Debug/pipe_example.exe
#    - Linux/macOS: ./pipe_example
#
# ==========================================================
