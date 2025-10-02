#include "mud.hpp"
#include <transport/stop.hpp>

Stop::Stop() :
    vnum(Mud::instance().maxStopVnum() + 1)
{
}


Stop::Stop(unsigned int distance, std::shared_ptr<Room> room, std::shared_ptr<Stop> next, std::shared_ptr<Stop> prev) :
    vnum(Mud::instance().maxStopVnum() + 1), room(room), next(next), next_distance(distance), prev(prev)
{
}
