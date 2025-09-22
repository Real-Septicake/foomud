#include "characters/character.hpp"
#include <memory>
#include <string>
#include <vector>
void loadCommsCommands();

bool say(std::shared_ptr<Character>, std::vector<std::string> &);
