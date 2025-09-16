#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <string>
#include <asio.hpp>

class Connection {
    private:
        std::string ibuf;
        std::string obuf;
    public:
        asio::ip::tcp::socket sock;
        bool closed;
        ~Connection();
        Connection(asio::ip::tcp::socket);
        bool pendingOutput();
        bool checkConnection();
        void read();
        void write();
};


#endif
