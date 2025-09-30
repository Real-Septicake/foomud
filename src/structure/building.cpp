#include "mud.hpp"
#include <memory>
#include <string>
#include <structure/building.hpp>

Building::Building(std::string n, std::shared_ptr<Room> r, std::shared_ptr<Building> b) :
    vnum(Mud::instance().maxBuildingVnum() + 1), entrance_room(r), outer_building(b), name(n)
{
}
