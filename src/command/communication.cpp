#include "characters/character.hpp"
#include "input/arguments.hpp"
#include "mud.hpp"
#include <command/communication.hpp>
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
    std::string message = createMessage(args);
    c->sendMsg("You say " + message);
    c->current_room->send(c->name + " says " + message, {c});
    return true;
}

bool tell(std::shared_ptr<Character> c, Arguments &args) {
    if(args.size() < 2) {
        c->sendMsg("Incorrect usage: tell <character> <message>");
        return false;
    }
    std::string name = args[0];
    std::shared_ptr<Character> p = c->current_room->findCharacter(name);
    if(p == nullptr) {
        c->sendMsg("There is nobody by the name of " + name);
        return false;
    }
    args.erase(0);
    std::string message = createMessage(args);
    c->sendMsg("You tell " + name + " " + message);
    p->sendMsg(c->name + " tells you " + message);
    c->current_room->send(c->name + " tells " + name + " " + message, {c, p});
    return true;
}
