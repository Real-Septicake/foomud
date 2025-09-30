#ifndef UPDATABLE_HPP
#define UPDATABLE_HPP

class Updatable {
    public:
        virtual void updateTick() = 0;
        virtual void updateHour() = 0;
};

#endif
