#include "characters/player.hpp"
#include "input/handlers/handler.hpp"
#include "parsers/parsers.hpp"
#include "utils.hpp"
#include <input/handlers/name.hpp>
#include <input/handlers/commands.hpp>
#include <lexy/action/match.hpp>
#include <lexy/input/string_input.hpp>
#include <memory>

bool NameHandler::process(std::shared_ptr<Player> player, std::string input) {
    std::string trimmed = trim(input);
    if(trimmed.empty()) {
        player->sendMsg("Name cannot be blank\r\nName:");
        return false;
    }
    if(!lexy::match<CharacterParser>(lexy::zstring_input(("@"+trimmed).c_str()))) {
        player->sendMsg("Name must only consist of [A-Z], [a-z], underscore, and hyphen\r\nName:");
        return false;
    }
    player->name = trimmed;
    next(player);
    return true;
}

void NameHandler::next(std::shared_ptr<Player> player) {
    player->handler = std::static_pointer_cast<Handler>(std::make_shared<CommandHandler>());
}
