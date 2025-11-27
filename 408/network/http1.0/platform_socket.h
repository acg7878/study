#ifndef PLATFORM_SOCKET_H
#define PLATFORM_SOCKET_H

#ifdef _WIN32
    // Windows 平台
    #include <winsock2.h>
    #include <ws2tcpip.h>
    #pragma comment(lib, "ws2_32.lib")
    
    typedef SOCKET SocketType;
    #define INVALID_SOCKET_VALUE INVALID_SOCKET
    #define SOCKET_ERROR_VALUE SOCKET_ERROR
    #define CLOSE_SOCKET closesocket
    
    inline int initSocketLibrary() {
        WSADATA wsaData;
        return WSAStartup(MAKEWORD(2, 2), &wsaData);
    }
    
    inline void cleanupSocketLibrary() {
        WSACleanup();
    }
    
    inline int getSocketError() {
        return WSAGetLastError();
    }
    
#else
    // Linux/Unix 平台
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <cstring>
    #include <cerrno>
    
    typedef int SocketType;
    #define INVALID_SOCKET_VALUE -1
    #define SOCKET_ERROR_VALUE -1
    #define CLOSE_SOCKET close
    
    inline int initSocketLibrary() {
        return 0; // Linux 不需要初始化
    }
    
    inline void cleanupSocketLibrary() {
        // Linux 不需要清理
    }
    
    inline int getSocketError() {
        return errno;
    }
    
#endif

#endif // PLATFORM_SOCKET_H

