#include <characters/character.hpp>
#include <iostream>
#include <structure/room.hpp>

void Character::sendMsg(std::string /*msg*/) {
}

Character::~Character() {
    std::cout << "killing character" << std::endl;
}
