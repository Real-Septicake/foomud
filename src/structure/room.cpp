#include "characters/player.hpp"
#include <iostream>
#include <memory>
#include <set>
#include <structure/room.hpp>

Room::Room() :
    players()
{
}

Room::~Room() {
    std::cout << "deleted" << std::endl;
}

bool Room::addPlayer(std::shared_ptr<Player> &p) {
    if(players.contains(p))
        return false;
    p->current_room = shared_from_this();
    return players.insert(p).second;
}

bool Room::remPlayer(std::shared_ptr<Player> &p) {
    if(!players.contains(p))
        return false;
    p->current_room.reset();
    return players.erase(p) != 0;
}

void Room::send(std::string msg, std::set<std::shared_ptr<Player>> exclude) {
    for(auto &p : players) {
        if(exclude.contains(p))
            continue;
        p->sendMsg(msg);
    }
}
