#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include "asio/io_context.hpp"
#include <string>
#include <asio.hpp>

class Connection {
    private:
        std::string ibuf;
        std::string obuf;
    public:
        asio::ip::tcp::socket sock;
        bool closing;
        ~Connection();
        Connection(asio::io_context &);
        bool pendingOutput();
        bool checkConnection();
        void read();
        void write();
};


#endif
