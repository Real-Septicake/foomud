#ifndef TRAIN_HPP
#define TRAIN_HPP

#include "transport/stop.hpp"
#include "transport/transport.hpp"
#include <memory>

class Train : Transport {
    public:
        Train();
        enum Direction {
            Reverse = -1,
            Forward = 1,
        };
        enum State {
            Stopped,
            Running
        };
        Direction d = Forward;
        State s = Stopped;
        unsigned int progress;
        std::shared_ptr<Stop> stop;
    protected:
        void tick() override;
        void hour() override;
    private:
        bool alerted = false;
};

#endif
