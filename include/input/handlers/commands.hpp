#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include <input/handlers/handler.hpp>

class CommandHandler : public Handler {
    public:
        bool process(std::shared_ptr<Player> player, std::string input) override;
        void next(std::shared_ptr<Player> player) override;
};

#endif
