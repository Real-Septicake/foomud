#include <updater/updater.hpp>

Updater& Updater::instance() {
    static Updater i;
    return i;
}

Updater::Updater() :
    tickLength(5), hourLength(12), tickCounter(), hourCounter()
{
}

void Updater::update() {
    tickCounter++;
    if(tickCounter >= tickLength * 20) {
        tickCounter = 0;
        hourCounter++;
        if(hourCounter >= hourLength) {
            hourCounter = 0;
        }
    }
}
