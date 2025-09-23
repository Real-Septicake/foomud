#include "characters/character.hpp"
#include "input/arguments.hpp"
#include <memory>

void loadCommsCommands();

bool say(std::shared_ptr<Character>, Arguments &);

bool tell(std::shared_ptr<Character>, Arguments &);
