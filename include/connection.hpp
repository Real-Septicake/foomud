#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>
#include <asio.hpp>

class Connection {
    public:
        std::string ibuf;
        std::string obuf;
        asio::ip::tcp::socket sock;
        bool closed;
        ~Connection();
        Connection(asio::ip::tcp::socket);
        bool pendingOutput();
        bool pendingInput();
        bool checkConnection();
        void read();
        void write();
};


#endif
