#include "enchantum/enchantum.hpp"
#include "mud.hpp"
#include "parsers/parsers.hpp"
#include "structure/exit.hpp"
#include "structure/room.hpp"
#include "utils.hpp"
#include <command/navigation.hpp>
#include <memory>

void commands::loadNavCommands() {
    Mud::instance().addCommand(std::make_shared<Command>("go", "<direction>", "go somewhere", commands::go));
}

bool commands::go(std::shared_ptr<Character> c, Arguments &args) {
    if(args.size() < 1) {
        c->sendMsg("Go where?\r\n");
        return false;
    }
    if(args.size() != 1) {
        c->sendMsg("You can only go one way\r\n");
        return false;
    }
    std::string d = args[0];
    auto dir = parseDirection(d);
    if(dir == Direction::None) {
        c->sendMsg("Where's that?\r\n");
        return false;
    }
    auto e = c->current_room->exits.find(dir);
    if(e == c->current_room->exits.end()) {
        switch(dir) {
            case Direction::Up:
                c->sendMsg("The ceiling? How?\r\n");
                break;
            case Direction::Down:
                c->sendMsg("No digging straight down\r\n");
                break;
            default:
                c->sendMsg("Into that wall?\r\n");
                break;
        }
        return false;
    }
    c->current_room->send(c->name + " has gone " + std::string(enchantum::to_string(dir)) + "\r\n", {c});
    c->current_room->remCharacter(c);
    e->second->to.lock()->addCharacter(c);
    c->current_room->send(c->name + " has arrived from the " + std::string(enchantum::to_string(dir)) + "\r\n", {c});
    c->sendMsg("You have entered Room " + toString(c->current_room->vnum) + "\r\n");
    return true;
}
