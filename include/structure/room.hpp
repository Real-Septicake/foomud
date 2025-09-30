#ifndef ROOM_HPP
#define ROOM_HPP

#include "structure/exit.hpp"
#include <items/item.hpp>
#include <cstddef>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>

class Character;
class Building;

class Room : public std::enable_shared_from_this<Room> {
    private:
        std::set<std::shared_ptr<Character>> characters;
    public:
        std::map<Direction, std::shared_ptr<Exit>> exits;
        std::map<std::string, std::shared_ptr<Building>> buildings;
        std::set<std::shared_ptr<Item>> items;
        const std::size_t vnum;
        Room();
        ~Room();
        bool addCharacter(std::shared_ptr<Character>);
        bool remCharacter(std::shared_ptr<Character>);
        std::vector<std::shared_ptr<Character>> getCharacters(std::set<std::shared_ptr<Character>>);
        std::shared_ptr<Character> findCharacter(std::string);
        void send(std::string, std::set<std::shared_ptr<Character>>);
        bool addExit(std::shared_ptr<Room>, Direction);
        bool remExit(Direction);
        bool addItem(std::shared_ptr<Item>);
        bool remItem(std::shared_ptr<Item>);
        bool addBuilding(std::shared_ptr<Building>);
        bool remBuilding(std::shared_ptr<Building>);

        friend Exit;
};

#endif
