#ifndef ROOM_HPP
#define ROOM_HPP

#include <memory>
#include <set>
#include <string>

class Player;

class Room : public std::enable_shared_from_this<Room> {
    private:
        std::set<std::shared_ptr<Player>> players;
    public:
        Room();
        ~Room();
        bool addPlayer(std::shared_ptr<Player> &);
        bool remPlayer(std::shared_ptr<Player> &);
        void send(std::string, std::set<std::shared_ptr<Player>>);
};

#endif
