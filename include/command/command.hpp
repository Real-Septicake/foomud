#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "characters/character.hpp"
#include <functional>
#include <memory>
#include <string>
#include <utility>
#include <vector>

class Command {
    using func = std::function<bool(std::shared_ptr<Character>, std::vector<std::string> &)>;
    public:
        std::string name;
        std::string desc;
        std::vector<std::pair<std::string, std::string>> args;
        func callback;

        Command(std::string, std::string, std::vector<std::pair<std::string, std::string>>, func);

        bool operator()(std::shared_ptr<Character>, std::vector<std::string> &);
};

#endif
