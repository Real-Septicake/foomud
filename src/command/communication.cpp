#include "characters/character.hpp"
#include "input/arguments.hpp"
#include "mud.hpp"
#include <command/communication.hpp>
#include <memory>

void loadCommsCommands() {
    Mud::instance().addCommand(std::make_shared<Command>("say", "<message>", "say something", say));
}

bool say(std::shared_ptr<Character> c, Arguments &args) {
    std::string message = "\"";
    message += args.substr(0);
    message += "\"\r\n";
    c->sendMsg("You say " + message);
    c->current_room->send("They say " + message, {c});
    return true;
}
