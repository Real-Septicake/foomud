#include <memory>
#include <structure/room.hpp>
#include <structure/exit.hpp>

std::shared_ptr<Exit> Exit::getCorresponding() {
    for(auto e : to.lock()->exits) {
        if(e.second->to.lock() == from.lock())
            return e.second;
    }
    return nullptr;
}
