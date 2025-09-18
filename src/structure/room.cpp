#include "characters/player.hpp"
#include <memory>
#include <structure/room.hpp>

Room::Room() :
    players()
{
}

bool Room::addPlayer(std::shared_ptr<Player> &p) {
    if(players.contains(p))
        return false;
    p->current_room = std::move(shared_from_this());
    return players.insert(p).second;
}

bool Room::remPlayer(std::shared_ptr<Player> &p) {
    if(!players.contains(p))
        return false;
    p->current_room.reset();
    return players.erase(p) != 0;
}
