#ifndef ITEMS_HPP
#define ITEMS_HPP

#include "../enums/article.hpp"
#include <cstddef>
#include <memory>
#include <string>

class Room;

class Character;

template<typename>
class FormatEngine;

class Item {
    private:
        const static FormatEngine<Item> engine;
    public:
        Item();
        std::shared_ptr<Room> room;
        std::shared_ptr<Character> owner;
        Article article;
        std::size_t vnum;
        std::string name;
        int count;
        // &a = article
        // &n = name
        std::string description;
        std::string gen_descriptor();
};

#endif
