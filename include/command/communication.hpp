#ifndef COMMUNICATION_COMMANDS_HPP
#define COMMUNICATION_COMMANDS_HPP

#include "characters/character.hpp"
#include "input/arguments.hpp"
#include <memory>

namespace commands {
void loadCommsCommands();

bool say(std::shared_ptr<Character>, Arguments &);

bool tell(std::shared_ptr<Character>, Arguments &);
}

#endif
