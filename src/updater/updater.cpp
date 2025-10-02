#include "mud.hpp"
#include <updater/updater.hpp>

Updater& Updater::instance() {
    static Updater i;
    return i;
}

Updater::Updater() :
    tickCounter(), hourCounter(), tickLength(5), hourLength(12)
{
}

void Updater::update() {
    tickCounter++;
    if(tickCounter >= tickLength * 20) {
        tickCounter = 0;
        for(auto i : Mud::instance().transes) {
            i.second->updateTick();
        }
        hourCounter++;
        if(hourCounter >= hourLength) {
            hourCounter = 0;
            for(auto i : Mud::instance().transes) {
                i.second->updateHour();
            }
        }
    }
}
