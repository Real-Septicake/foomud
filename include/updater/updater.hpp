#ifndef UPDATER_HPP
#define UPDATER_HPP

class Updater {
    private:
        unsigned int tickLength; // seconds per tick
        unsigned int hourLength; // how many ticks per hour
        unsigned int tickCounter;
        unsigned int hourCounter;
        Updater();
    public:
        static Updater& instance();
        void update();
};

#endif
