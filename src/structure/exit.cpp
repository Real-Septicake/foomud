#include <memory>
#include <structure/room.hpp>
#include <structure/exit.hpp>

std::shared_ptr<Exit> Exit::getCorresponding() {
    for(auto e : to->exits) {
        if(e.second->to == from)
            return e.second;
    }
    return nullptr;
}
