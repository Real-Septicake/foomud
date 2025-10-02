#ifndef UPDATER_HPP
#define UPDATER_HPP

class Updater {
    private:
        unsigned int tickCounter;
        unsigned int hourCounter;
        Updater();
    public:
        unsigned int const tickLength; // seconds per tick
        unsigned int const hourLength; // how many ticks per hour
        static Updater& instance();
        void update();
};

#endif
