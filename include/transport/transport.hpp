#ifndef TRANSPORT_HPP
#define TRANSPORT_HPP

#include "structure/room.hpp"
#include "updater/updatable.hpp"
#include <memory>
#include <utils.hpp>

class Transport : public enable_shared_from_base<Transport>, Updatable {
    public:
        std::size_t vnum;
        Transport();
        std::shared_ptr<Room> internal_room;
        inline void updateHour() override {
            this->hour();
        }
        inline void updateTick() override {
            this->tick();
        }
    protected:
        virtual void tick() = 0;
        virtual void hour() = 0;
        [[nodiscard("Need to check if _actually_ arrived")]]
        bool arrive(std::shared_ptr<Room>);
        void leave();
};

#endif
