#include "socket.h"
#include <exception>


#define NOOP (void)0;


namespace Network {

    Socket::Socket() 
    {
        _socket = INVALID_SOCKET;
    }

    Socket::~Socket()
    {
        close();
    }

    void Socket::close()
    {
        try {
            closesocket(_socket);
        }
        catch (std::exception e) {
            NOOP
        }
    }

    SOCKET Socket::get_socket()
    {
        return _socket;
    }

    void Socket::connect_socket(ADDRINFO *_ptr, ADDRINFO *_result)
    {
        // Attempt to connect to an address until one succeeds
        for (_ptr = _result; _ptr != NULL; _ptr = _ptr->ai_next) {

            // Create a SOCKET for connecting to server
            _socket = socket(_ptr->ai_family, _ptr->ai_socktype, _ptr->ai_protocol);
            if (_socket == INVALID_SOCKET) {
                throw "socket failed with error: " + WSAGetLastError() + '\n';
            }

            // Connect to server.
            int iResult = connect(_socket, _ptr->ai_addr, (int)_ptr->ai_addrlen);
            if (iResult == SOCKET_ERROR) {
                closesocket(_socket);
                _socket = INVALID_SOCKET;
                continue;
            }
            break;
        }
    }
}