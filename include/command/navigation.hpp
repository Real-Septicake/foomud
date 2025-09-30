#ifndef NAVIGATION_COMMANDS_HPP
#define NAVIGATION_COMMANDS_HPP

#include "characters/character.hpp"
#include <memory>
#include <command/command.hpp>

namespace commands {
    void loadNavCommands();

    bool go(std::shared_ptr<Character>, Arguments &);

    bool enter(std::shared_ptr<Character>, Arguments &);
}

#endif
