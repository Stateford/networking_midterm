#pragma once

#include <string>

namespace Network {
    enum Protocol{
        HTTP,
        HTTPS
    };

    class URL {
    private:
        std::string _url;
        Protocol _protocol = HTTP;
        std::string _hostname;
        std::string _path;
        std::string _port;

        void _parseUrl();
    public:
        URL();
        URL(std::string);
        URL(URL&);

        void parse(std::string url);
        std::string getUrl();
        std::string getHostname();
        std::string getPath();
        std::string getPort();
        Protocol getProtocol();
    };
}