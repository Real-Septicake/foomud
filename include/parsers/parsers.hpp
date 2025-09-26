#ifndef PARSERS_HPP
#define PARSERS_HPP

#include "lexy/dsl/literal.hpp"
#include <memory>
#include <lexy/dsl.hpp>
#include <lexy/callback/adapter.hpp>
#include <lexy/lexeme.hpp>
#include <structure/exit.hpp>

class Character;

struct CharacterParser {
    static auto constexpr rule = LEXY_LIT("@") + lexy::dsl::ascii::alpha_underscore / LEXY_LIT("-");
};

std::shared_ptr<Character> parseCharacter(std::string, std::shared_ptr<Character>);

Direction parseDirection(std::string);

#endif
