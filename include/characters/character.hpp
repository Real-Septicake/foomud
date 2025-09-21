#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include <memory>
#include <utils.hpp>

class Room;

class Character : public enable_shared_from_base<Character>{
    public:
        std::shared_ptr<Room> current_room;
        void sendMsg(std::string);
};

#endif
