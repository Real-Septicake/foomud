#include "characters/character.hpp"
#include "input/arguments.hpp"
#include "mud.hpp"
#include "parsers/parsers.hpp"
#include <command/communication.hpp>
#include <iostream>
#include <memory>

void loadCommsCommands() {
    Mud::instance().addCommand(std::make_shared<Command>("say", "<message>", "say something", say));
    Mud::instance().addCommand(std::make_shared<Command>("tell", "<character> <message>", "tell someone something", tell));
}

std::string createMessage(Arguments &args) {
    std::string message = "\"";
    message += args.substr(0);
    message += "\"\r\n";
    return message;
}

bool say(std::shared_ptr<Character> c, Arguments &args) {
    if(args.size() == 0) {
        c->sendMsg("Say what?\r\n");
        return false;
    }
    std::shared_ptr<Character> recipient = parseCharacter(args[0], c);
    if(recipient) {
        args.erase(0);
        if(recipient == c) {
            c->sendMsg("Why are you talking to yourself?\r\n");
            return false;
        }
    } else {
        if(args[0][0] == '@') {
            c->sendMsg("There is nobody nearby with the name \"" + args[0].substr(1) + "\"\r\n");
            return false;
        }
    }

    std::string adverb = "";
    if(args[0][0] == '>') {
        std::string v = args[0].substr(1);
        args.erase(0);
        bool quoted = false;
        if(v[0] =='\'') {
            quoted = true;
            v = v.substr(1);
        }
        adverb += v;
        while(quoted) {
            std::string a = args[0];
            args.erase(0);
            if(a.back() == '\'') {
                a.pop_back();
                quoted = false;
            }
            if(!a.empty())
                adverb += " " + a;
        }
    }

    if(args.size() == 0) {
        c->sendMsg("Say what?\r\n");
        return false;
    }

    std::string message = ((!adverb.empty()) ? adverb + ", " : "") + createMessage(args);
    if(recipient) {
        c->sendMsg("You say to " + recipient->name + ", " + message);
        recipient->sendMsg(c->name + " says to you, " + message);
        c->current_room->send(c->name + " says to " + recipient->name + ", " + message, {c, recipient});
        return true;
    }
    c->sendMsg("You say, " + message);
    c->current_room->send(c->name + " says, " + message, {c});
    return true;
}

bool tell(std::shared_ptr<Character> c, Arguments &args) {
    if(args.size() < 2) {
        c->sendMsg("Incorrect usage: tell @<character> <message>\r\n");
        return false;
    }
    std::string name = args[0];
    auto p = parseCharacter(name, c);
    if(p == nullptr) {
        c->sendMsg("There is nobody nearby with the name \"" + name.substr(1) + "\"\r\n");
        return false;
    }
    args.erase(0);
    std::string message = createMessage(args);
    c->sendMsg("You tell " + name.substr(1) + " " + message);
    p->sendMsg(c->name + " tells you " + message);
    return true;
}
