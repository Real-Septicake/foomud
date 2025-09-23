#ifndef MUD_HPP
#define MUD_HPP

#include "asio/io_context.hpp"
#include "characters/player.hpp"
#include "structure/room.hpp"
#include <command/command.hpp>
#include <map>
#include <memory>
#include <string>
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
        std::vector<std::shared_ptr<Player>> players;
        Mud();
        ~Mud();
        bool startConnection();
        void acceptConnections();
        void processConnection(std::shared_ptr<Player>);
        bool endConnection();
        void removeClosedConnections();
        void removeConnection(std::shared_ptr<Player>);
        void broadcast(const std::string &);
    public:
        bool run();
        void handleInput(std::string &, std::shared_ptr<Player>);
        void closeConnection(std::shared_ptr<Player>);
        bool addCommand(std::shared_ptr<Command>);
        void shutdown();
        static Mud& instance();
        std::map<unsigned int, std::shared_ptr<Room>> rooms;
        std::map<std::string, std::shared_ptr<Command>> commands;
};

#endif
