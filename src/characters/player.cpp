#include "connection.hpp"
#include <characters/player.hpp>
#include <iostream>
#include <memory>

Player::Player(std::unique_ptr<Connection> c) :
    c(std::move(c))
{
}

Player::~Player() {
    std::cout << "deleting player" << std::endl;
}
