#pragma once

#include <WinSock2.h>
#include <ws2tcpip.h>

namespace Network {

    class Socket {

    private:
        SOCKET _socket;
    public:
        Socket();
        ~Socket();

        void connect_socket(ADDRINFO*, ADDRINFO*);
        void close();
        SOCKET get_socket();
    };

}