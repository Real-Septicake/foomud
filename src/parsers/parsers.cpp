#include "structure/exit.hpp"
#include "utils.hpp"
#include <parsers/parsers.hpp>
#include <lexy/action/validate.hpp>
#include <characters/character.hpp>
#include <structure/room.hpp>
#include <lexy/input/string_input.hpp>

std::shared_ptr<Character> parseCharacter(std::string name, std::shared_ptr<Character> source) {
    if(lexy::match<CharacterParser>(lexy::zstring_input(name.c_str())) == true) {
        return source->current_room->findCharacter(name.substr(1));
    }
    return nullptr;
}

Direction parseDirection(std::string input) {
    if(prefix("north", input))
        return Direction::North;
    if(prefix("south", input))
        return Direction::South;
    if(prefix("east", input))
        return Direction::East;
    if(prefix("west", input))
        return Direction::West;
    if(prefix("up", input))
        return Direction::Up;
    if(prefix("down", input))
        return Direction::Down;
    return Direction::None;
}
