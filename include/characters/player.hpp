#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "connection.hpp"
#include "input/handlers/handler.hpp"
#include <memory>
#include <characters/character.hpp>
#include <string>

class Room;


class Player : public Character {
    public:
        std::shared_ptr<Handler> handler;
        std::unique_ptr<Connection> c;
        void init(std::unique_ptr<Connection>);
        void sendMsg(std::string) override;
};

#endif
