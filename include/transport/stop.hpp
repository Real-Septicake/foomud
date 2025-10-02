#ifndef STOP_HPP
#define STOP_HPP

#include "structure/room.hpp"
#include <memory>

class Stop : std::enable_shared_from_this<Stop> {
    public:
        Stop();
        Stop(unsigned int, std::shared_ptr<Room>, std::shared_ptr<Stop> next = nullptr, std::shared_ptr<Stop> prev = nullptr);

        std::size_t vnum;
        std::shared_ptr<Room> room;

        std::shared_ptr<Stop> next;
        unsigned int next_distance;

        std::shared_ptr<Stop> prev;
};

#endif
