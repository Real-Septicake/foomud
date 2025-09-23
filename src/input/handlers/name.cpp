#include "characters/player.hpp"
#include "input/handlers/handler.hpp"
#include "utils.hpp"
#include <input/handlers/name.hpp>
#include <input/handlers/commands.hpp>
#include <iostream>
#include <memory>

bool NameHandler::process(std::shared_ptr<Player> player, std::string input) {
    std::string trimmed = trim(input);
    player->name = trimmed;
    std::cout << trimmed << " has been chosen as the name" << std::endl;
    next(player);
    return true;
}

void NameHandler::next(std::shared_ptr<Player> player) {
    std::cout << "setting handler" << std::endl;
    player->handler = std::static_pointer_cast<Handler>(std::make_shared<CommandHandler>());
}
