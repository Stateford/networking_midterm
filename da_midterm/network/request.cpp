#include "request.h"
#include <iostream>
#include <ws2tcpip.h>
#include <vector>


namespace Network
{
    Request::Request(std::string url)
    {
        int result = WSAStartup(MAKEWORD(2, 2), &_wsaData);
        if (result != 0)
            throw "Could not open socket";

        _url = URL(url);
    }

    Request::Request(URL url)
    {
        int result = WSAStartup(MAKEWORD(2, 2), &_wsaData);
        if (result != 0)
            throw "Could not open socket";

        _url = url;
    }

    Request::~Request()
    {
        WSACleanup();
    }

    void Request::_getaddrinfo()
    {
        ZeroMemory(&_hints, sizeof(_hints));
        _hints.ai_family = AF_UNSPEC;
        _hints.ai_socktype = SOCK_STREAM;
        _hints.ai_protocol = IPPROTO_TCP;

        // Resolve the server address and port
        int iResult = GetAddrInfoA(_url.getHostname().c_str(), _url.getPort().c_str(), &_hints, &_result);
        if (iResult != 0)
            throw "getaddrinfo failed with error: " + iResult + '\n';
    }

    void Request::_buildHeader(Method method, std::string *header)
    {
        std::string _method;

        switch (method)
        {
        case GET:
            _method = "GET";
            break;
        case POST:
            _method = "POST";
            break;
        default:
            break;
        }

        *header = _method;
        *header += " " 
                + _url.getPath() 
                + " " 
                + "HTTP/1.1\r\nHost: " 
                + _url.getHostname() 
                + "\r\n" 
                + _headers.get_headers() 
                + "\r\n";
    }

    Request* Request::method(Method method)
    {
        _method = method;
        return this;
    }

    Request* Request::json(nlohmann::json json_obj)
    {
        _body.setBody(json_obj.dump());
        _headers["Content-Type"] = "application/json";
        _headers["Content-Length"] = std::to_string(_body.length());
        return this;
    }

    void Request::request(std::string *response)
    {
        int recvbuflen = DEFAULT_BUFLEN;

        _getaddrinfo();

        std::string get_http;
        _socket.connect_socket(_ptr, _result);
        _buildHeader(GET, &get_http);

        // Send an initial buffer
        int iResult = send(_socket.get_socket(), get_http.c_str(), (int)strlen(get_http.c_str()), 0);
        if (iResult == SOCKET_ERROR)
            throw TEXT("send failed with error: ") + WSAGetLastError() + TEXT('\n');

        // Receive until the peer closes the connection
        do
        {
            std::vector<char> buffer(recvbuflen+20);
            //iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
            iResult = recv(_socket.get_socket(), &buffer[0], recvbuflen, 0);
            if (iResult >= 0)
            {
                *response += std::string(buffer.cbegin(), buffer.cend());
            }
            else
                throw TEXT("recv failed with error: ") + WSAGetLastError() + TEXT('\n');

        } while (iResult > 0);
        *response += "\0";
    }

    void Request::request(nlohmann::json *response)
    {
        int recvbuflen = DEFAULT_BUFLEN;
        std::string buffer_response;
        _getaddrinfo();

        std::string get_http;
        _socket.connect_socket(_ptr, _result);
        _buildHeader(GET, &get_http);

        // Send an initial buffer
        int iResult = send(_socket.get_socket(), get_http.c_str(), (int)strlen(get_http.c_str()), 0);
        if (iResult == SOCKET_ERROR)
            throw TEXT("send failed with error: ") + WSAGetLastError() + TEXT('\n');

        // Receive until the peer closes the connection
        do
        {
            std::vector<char> buffer(recvbuflen + 20);
            //iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
            iResult = recv(_socket.get_socket(), &buffer[0], recvbuflen, 0);
            if (iResult >= 0)
            {
                buffer_response += std::string(buffer.cbegin(), buffer.cend());
            }
            else
                throw TEXT("recv failed with error: ") + WSAGetLastError() + TEXT('\n');

        } while (iResult > 0);
        buffer_response += "\0";
        response->parse(buffer_response);
    }
}