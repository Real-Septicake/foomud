#ifndef ITEMS_HPP
#define ITEMS_HPP

#include "enums/article.hpp"
#include <cstddef>
#include <memory>
#include <string>

class Room;

class Character;

class Item {
    public:
        Item();
        std::shared_ptr<Room> room;
        std::shared_ptr<Character> owner;
        Article article;
        std::size_t vnum;
        std::string name;
};

#endif
