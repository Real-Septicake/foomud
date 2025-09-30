#include "enums/article.hpp"
#include "mud.hpp"
#include "utils.hpp"
#include <command/miscellaneous.hpp>
#include <memory>
#include <enchantum/enchantum.hpp>

void commands::loadMiscCommands() {
    Mud::instance().addCommand(std::make_shared<Command>("look", "", "look around", commands::look));
}

bool commands::look(std::shared_ptr<Character> c, Arguments &/*args*/) {

    c->sendMsg("You are in Room " + toString(c->current_room->vnum) + "\r\n");
    auto others = c->current_room->getCharacters({c});
    bool see_msg = false;
    if(!others.empty()) {
        if(!see_msg) {
            c->sendMsg("You see:\r\n");
            see_msg = true;
        }
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
    if(!c->current_room->items.empty()) {
        if(!see_msg) {
            c->sendMsg("You see:\r\n");
            see_msg = true;
        }
        for(auto &i : c->current_room->items) {
            c->sendMsg("- " + toArticle(i->article) + i->name + "\r\n");
        }
    }
    if(!c->current_room->exits.empty()) {
        c->sendMsg("The obvious exits are:\r\n");
        for(auto i : c->current_room->exits) {
            std::string dir = std::string(enchantum::to_string(i.first));
            std::string name = "Room " + toString(i.second->to.lock()->vnum);
            c->sendMsg("  " + dir + " : " + name + "\r\n");
        }
    }
    return true;
};
