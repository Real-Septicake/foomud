#include <cctype>
#include <map>
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

std::map<std::string, Direction> dirs {
    {"north", Direction::North},
    {"south", Direction::South},
    {"east", Direction::East},
    {"west", Direction::West},
    {"up", Direction::Up},
    {"down", Direction::Down},
    {"in", Direction::In},
    {"out", Direction::Out}
};

Direction parseDirection(std::string input) {
    input = toLower(input);
    for(auto i = dirs.begin(); i != dirs.end(); ++i) {
        if(i->first.starts_with(input))
            return (*i).second;
    }
    return Direction::None;
}
