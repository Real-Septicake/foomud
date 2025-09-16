#ifndef MUD_HPP
#define MUD_HPP

#include "asio/io_context.hpp"
#include <vector>
#include <connection.hpp>
#include <asio/ip/tcp.hpp>

class Mud {
    private:
        asio::io_context context;
        asio::ip::tcp::acceptor acceptor;
        long port;
        bool running;
        int max_sock;
        std::vector<Connection *> connections;
        Mud();
        ~Mud();
    public:
        bool run();
        void shutdown();
        bool startConnection();
        bool acceptConnections();
        void processConnection(Connection *);
        bool checkConnection(const int &);
        bool closeConnection(const int &);
        bool endConnection();
        void removeClosedConnections();
        void removeConnection(Connection *);
        static Mud& instance();
};

#endif
