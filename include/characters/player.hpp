#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "connection.hpp"
#include <memory>
#include <characters/character.hpp>

class Room;


class Player : public Character {
    public:
        std::unique_ptr<Connection> c;
        void init(std::unique_ptr<Connection>);
        void sendMsg(std::string) override;
        ~Player();
};

#endif
