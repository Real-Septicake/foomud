#include "command/navigation.hpp"
#include "input/arguments.hpp"
#include <command/command.hpp>
#include <command/communication.hpp>
#include <command/miscellaneous.hpp>

void loadCommands() {
    commands::loadCommsCommands();
    commands::loadMiscCommands();
    commands::loadNavCommands();
}

Command::Command(std::string name, std::string desc, std::string args, func callback) :
    name(name), desc(desc), args(args), callback(callback)
{
}

bool Command::operator()(std::shared_ptr<Character> character, Arguments &args) {
    return callback(character, args);
}
