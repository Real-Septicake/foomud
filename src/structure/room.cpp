#include "characters/character.hpp"
#include "characters/player.hpp"
#include "mud.hpp"
#include <iostream>
#include <memory>
#include <set>
#include <structure/room.hpp>

Room::Room() :
    characters(), vnum(Mud::instance().maxRoomVnum() + 1)
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

std::vector<std::shared_ptr<Character>> Room::getCharacters(std::set<std::shared_ptr<Character>> exclude) {
    std::vector<std::shared_ptr<Character>> result;
    for(auto c : characters) {
        if(!exclude.contains(c))
            result.push_back(c);
    }
    return result;
}

void Room::send(std::string msg, std::set<std::shared_ptr<Character>> exclude) {
    for(auto p : characters) {
        if(exclude.contains(p))
            continue;
        p->sendMsg(msg);
    }
}

std::shared_ptr<Character> Room::findCharacter(std::string name) {
    for(auto c : characters) {
        if(c->name == name)
            return c;
    }
    return nullptr;
}

bool Room::addExit(std::shared_ptr<Room> to, Direction dir) {
    if(exits.contains(dir))
        return false;
    auto e = std::make_shared<Exit>();
    e->to = to;
    e->from = shared_from_this();
    e->direction = dir;
    exits.insert({dir, e});
    return true;
}
