#ifndef MUD_HPP
#define MUD_HPP

#include "asio/io_context.hpp"
#include "characters/player.hpp"
#include "items/item.hpp"
#include "structure/room.hpp"
#include "updater/updater.hpp"
#include <command/command.hpp>
#include <cstddef>
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
        std::size_t max_room_vnum;
        std::size_t max_item_vnum;
        long port;
        bool running;
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
        std::size_t maxRoomVnum() const;
        std::size_t maxItemVnum() const;
        std::size_t maxBuildingVnum() const;
        static Mud& instance();
        std::map<std::size_t, std::shared_ptr<Room>> rooms;
        std::map<std::size_t, std::shared_ptr<Item>> items;
        std::map<std::string, std::shared_ptr<Command>> commands;
        bool addRoom(std::shared_ptr<Room>);
        bool addItem(std::shared_ptr<Item>);

        friend Updater;
};

#endif
