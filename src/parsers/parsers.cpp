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
