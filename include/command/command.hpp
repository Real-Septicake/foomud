#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "characters/character.hpp"
#include "input/arguments.hpp"
#include <functional>
#include <memory>
#include <string>

void loadCommands();

class Command {
    using func = std::function<bool(std::shared_ptr<Character>, Arguments &)>;
    using check = std::function<bool(std::shared_ptr<Character>)>;
    public:
        std::string name;
        std::string desc;
        std::string args;
        func callback;
        check check_use;

        Command(std::string, std::string, std::string, func, check = nullptr);

        bool operator()(std::shared_ptr<Character>, Arguments &);
};

#endif
