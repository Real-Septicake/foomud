#include "mud.hpp"
#include "utils.hpp"
#include <command/miscellaneous.hpp>
#include <memory>

void commands::loadMiscellaneousCommands() {
    Mud::instance().addCommand(std::make_shared<Command>("look", "", "look around", commands::look));
}

bool commands::look(std::shared_ptr<Character> c, Arguments &/*args*/) {
    c->sendMsg("You are in " + toString(c->current_room->vnum) + "\r\n");
    auto others = c->current_room->getCharacters({c});
    if(!others.empty()) {
        c->sendMsg("You see:\r\n");
        std::string list("");
        for(auto i = others.begin(); i != others.end(); ++i) {
            if(i != others.begin()) {
                if(others.size() != 2)
                    list += ",";
                list += " ";
            }
            if(i == others.end() - 1 && others.size() != 1)
                list += "and ";
            list += (*i)->name;
        }
        c->sendMsg("  " + list + "\r\n");
    }
    return true;
};
