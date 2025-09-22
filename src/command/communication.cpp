#include "characters/character.hpp"
#include "mud.hpp"
#include <command/communication.hpp>
#include <memory>
#include <vector>

void loadCommsCommands() {
    Mud::instance().addCommand(std::make_shared<Command>("say", "<message>", "say something", say));
}

bool say(std::shared_ptr<Character> c, std::vector<std::string> &args) {
    std::string message = "\"";
    for(auto i = args.begin() + 1; i != args.end(); ++i) {
        message += *i;
        if(i+1 != args.end())
            message += " ";
    }
    message += "\"\r\n";
    c->sendMsg("You say " + message);
    c->current_room->send("They say " + message, {c});
    return true;
}
