#ifndef HANDLER_HPP
#define HANDLER_HPP

#include "utils.hpp"
#include <memory>

class Player;

class Handler : public enable_shared_from_base<Handler> {
    public:
        virtual bool process(std::shared_ptr<Player> player, std::string input) = 0;
        virtual void next(std::shared_ptr<Player> player) = 0;
};

#endif
