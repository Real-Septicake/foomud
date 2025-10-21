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

Command::Command(std::string name, std::string args, std::string desc, func callback, check check_use) :
    name(name), desc(desc), args(args), callback(callback), check_use(check_use)
{
}

bool Command::operator()(std::shared_ptr<Character> character, Arguments &args) {
    if(check_use && !check_use(character))
        return false;
    return callback(character, args);
}
