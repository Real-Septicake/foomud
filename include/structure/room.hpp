#ifndef ROOM_HPP
#define ROOM_HPP

#include <memory>
#include <set>
#include <string>


class Character;

class Room : public std::enable_shared_from_this<Room> {
    private:
        std::set<std::shared_ptr<Character>> characters;
    public:
        Room();
        ~Room();
        bool addCharacter(std::shared_ptr<Character>);
        bool remCharacter(std::shared_ptr<Character>);
        void send(std::string, std::set<std::shared_ptr<Character>>);
};

#endif
