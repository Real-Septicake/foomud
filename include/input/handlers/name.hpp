#ifndef NAME_HANDLER_HPP
#define NAME_HANDLER_HPP

#include <input/handlers/handler.hpp>

class NameHandler : public Handler {
    private:
        bool blank = false;
    public:
        bool process(std::shared_ptr<Player> player, std::string input) override;
        void next(std::shared_ptr<Player> player) override;
};

#endif
