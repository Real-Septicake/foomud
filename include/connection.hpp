#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#include <cstddef>
#include <memory>
#include <string>
#include <asio/ip/tcp.hpp>

class Player;

template<typename>
class FormatEngine;

class Connection {
    private:
        static const FormatEngine<const std::nullptr_t> engine;
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
