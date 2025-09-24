#ifndef MISCELLANEOUS_COMMANDS_HPP
#define MISCELLANEOUS_COMMANDS_HPP

#include <command/command.hpp>

namespace commands {

void loadMiscellaneousCommands();

bool look(std::shared_ptr<Character>, Arguments &);

}

#endif
