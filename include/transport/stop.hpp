#ifndef STOP_HPP
#define STOP_HPP

#include "structure/room.hpp"
#include <memory>

class Stop : std::enable_shared_from_this<Stop> {
    public:
        Stop();

        std::size_t vnum;
        std::shared_ptr<Room> room;

        std::shared_ptr<Stop> next;
        std::size_t next_distance;

        std::shared_ptr<Stop> prev;
};

#endif
