#include <characters/character.hpp>
#include <structure/room.hpp>

void Character::sendMsg(std::string msg) {
    this->current_room->send(msg, {shared_from_this()});
}
