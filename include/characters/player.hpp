#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "connection.hpp"
#include <memory>

class Room;

class Player {
    public:
        std::unique_ptr<Connection> c;
        std::shared_ptr<Room> current_room;
        Player(std::unique_ptr<Connection>);
        ~Player();
};

#endif
