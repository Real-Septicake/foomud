#include "enums/directions.hpp"
#include "mud.hpp"
#include <memory>
#include <transport/transport.hpp>

Transport::Transport()
    : vnum(Mud::instance().maxTransVnum() + 1), internal_room()
{
}

bool Transport::arrive(std::shared_ptr<Room> r) {
    if(r->exits.contains(Direction::In))
        return false;
    r->addExit(internal_room, Direction::In);
    internal_room->addExit(r, Direction::Out);
    return true;
}

void Transport::leave() {
    if(internal_room->exits.contains(Direction::Out)) {
        auto exit = internal_room->exits[Direction::Out];
        auto other = exit->to.lock();
        other->remExit(exit->getCorresponding()->direction);
        internal_room->remExit(Direction::Out);
    }
}
