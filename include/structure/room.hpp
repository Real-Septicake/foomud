#ifndef ROOM_HPP
#define ROOM_HPP

#include <cstddef>
#include <memory>
#include <set>
#include <string>
#include <vector>


class Character;

class Room : public std::enable_shared_from_this<Room> {
    private:
        std::set<std::shared_ptr<Character>> characters;
    public:
        const std::size_t vnum;
        Room(std::size_t);
        ~Room();
        bool addCharacter(std::shared_ptr<Character>);
        bool remCharacter(std::shared_ptr<Character>);
        std::vector<std::shared_ptr<Character>> getCharacters(std::set<std::shared_ptr<Character>>);
        std::shared_ptr<Character> findCharacter(std::string);
        void send(std::string, std::set<std::shared_ptr<Character>>);
};

#endif
