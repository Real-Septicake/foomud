#include "connection.hpp"
#include <characters/player.hpp>
#include <iostream>
#include <memory>

void Player::sendMsg(std::string msg) {
    c->obuf += msg;
}

void Player::init(std::unique_ptr<Connection> connection) {
    if(c.get())
        return;
    c = std::move(connection);
    c->parent = shared_from_base<Player>();
}

Player::~Player() {
    std::cout << "deleting player" << std::endl;
}
