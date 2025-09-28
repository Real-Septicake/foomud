#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <memory>
#include <string>
#include <asio/ip/tcp.hpp>

class Player;

class Connection {
    private:
        std::string ibuf;
        std::weak_ptr<Player> parent;
    public:
        std::string obuf;
        asio::ip::tcp::socket sock;
        bool closed;
        ~Connection();
        Connection(asio::ip::tcp::socket);
        bool pendingOutput();
        bool checkConnection();
        void read();
        void write();

    friend Player;
};


#endif
