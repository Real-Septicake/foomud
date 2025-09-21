#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "characters/character.hpp"
#include <functional>
#include <memory>
#include <string>
#include <vector>
class Command {
    public:
        std::string name;
        std::function<bool(std::shared_ptr<Character>, std::vector<std::string> &)> func;
        bool operator()(std::shared_ptr<Character>, std::vector<std::string> &);
};

#endif
