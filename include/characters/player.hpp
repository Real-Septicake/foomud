#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "connection.hpp"
#include <memory>
#include <characters/character.hpp>

class Room;


class Player : public Character {
    public:
        std::unique_ptr<Connection> c;
        std::shared_ptr<Room> current_room;
        void init(std::unique_ptr<Connection>);
        void sendMsg(std::string);
        ~Player();
};

#endif
