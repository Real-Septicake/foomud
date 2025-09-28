#ifndef ITEMS_HPP
#define ITEMS_HPP

#include "enums/article.hpp"
#include <cstddef>
#include <memory>
#include <string>

class Room;

class Item {
    public:
        Item();
        std::shared_ptr<Room> room;
        Article article;
        const std::size_t vnum;
        std::string name;
};

#endif
