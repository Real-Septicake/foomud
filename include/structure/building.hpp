#ifndef BUILDING_HPP
#define BUILDING_HPP

#include "structure/room.hpp"
#include "utils.hpp"
#include <memory>
class Building : enable_shared_from_base<Building> {
    public:
        Building(std::string, std::shared_ptr<Room>, std::shared_ptr<Building> = nullptr);
        std::size_t vnum;
        std::shared_ptr<Room> entrance_room;
        std::shared_ptr<Room> outer_room;
        std::shared_ptr<Building> outer_building;
        std::string name;
};

#endif
