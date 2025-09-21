#include "characters/character.hpp"
#include "characters/player.hpp"
#include <iostream>
#include <memory>
#include <set>
#include <structure/room.hpp>

Room::Room() :
    characters({})
{
}

Room::~Room() {
    std::cout << "deleted" << std::endl;
}

bool Room::addCharacter(std::shared_ptr<Character> p) {
    if(characters.contains(p))
        return false;
    p->current_room = shared_from_this();
    return characters.insert(p).second;
}

bool Room::remCharacter(std::shared_ptr<Character> p) {
    if(!characters.contains(p))
        return false;
    p->current_room.reset();
    return characters.erase(p) != 0;
}

void Room::send(std::string msg, std::set<std::shared_ptr<Character>> exclude) {
    for(auto p : characters) {
        if(exclude.contains(p))
            continue;
        p->sendMsg(msg);
    }
}
