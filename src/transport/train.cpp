#include "updater/updater.hpp"
#include "utils.hpp"
#include <iostream>
#include <transport/train.hpp>

Train::Train()
{
}

void Train::tick() {
    progress++;
    switch(s) {
        case Running:
            if(progress >= stop->next_distance) {
                bool r = arrive(stop->room);
                if(!(r || alerted)) {
                    alerted = true;
                    internal_room->send("Could not arrive at station, please be patient");
                    return;
                }
                auto prev = (d == Forward) ? stop->prev : stop->next;
                stop->room->send("Train has arrived from Room " + toString(prev->room->vnum));
                internal_room->send("Train has arrived at Room " + toString(stop->room->vnum));
                s = Stopped;
                progress = 0;
            }
            break;
            break;
        case Stopped:
            if(progress >= Updater::instance().hourLength / 2) {
                bool tried = false;
next:
                auto next = (d == Forward) ? stop->next : stop->prev;
                if(!next) {
                    if(tried) {
                        std::cout << "train " << toString(vnum) << " is stuck" << std::endl;
                        progress = 0;
                        return;
                    }
                    tried = true;
                    d = (d == Forward) ? Reverse : Forward;
                    goto next;
                }
                stop->room->send("Train leaving for Room " + toString(stop->room->vnum));
                internal_room->send("Train leaving for Room " + toString(stop->room->vnum));
                leave();
                s = Running;
                progress = 0;
            }
            break;
        }
}

void Train::hour() {
    alerted = false;
}
