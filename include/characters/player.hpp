#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "connection.hpp"
#include <memory>

class Room;

class Player : public std::enable_shared_from_this<Player> {
    public:
        std::unique_ptr<Connection> c;
        std::shared_ptr<Room> current_room;
        void init(std::unique_ptr<Connection>);
        void sendMsg(std::string);
        ~Player();
};

#endif
