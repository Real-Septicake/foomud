#include "mud.hpp"
#include <input/handlers/commands.hpp>
#include <iostream>

bool CommandHandler::process(std::shared_ptr<Player> player, std::string input) {
    if(input[0] == (char)255) {
        std::cout << "negotiations:" << std::endl;
        for(auto c : input) {
            std::cout << (int) (unsigned char) c << " ";
        }
        std::cout << std::endl;
        return true;
    } else {
        Arguments args(input);
        std::string str = args[0];
        auto command = Mud::instance().commands.find(str);
        if(command != Mud::instance().commands.end()) {
            args.erase(0);
            (*command).second->callback(player->shared_from_this(), args);
            return true;
        }
    }
    return false;
}

void CommandHandler::next(std::shared_ptr<Player> /*player*/) {
}
