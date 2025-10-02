#ifndef TRAIN_HPP
#define TRAIN_HPP

#include "transport/transport.hpp"

class Train : Transport {
    public:
        Train();
    protected:
        void tick() override;
        void hour() override;
};

#endif
