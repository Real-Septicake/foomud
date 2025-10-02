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
                    internal_room->send("Could not arrive at station, please be patient\r\n");
                    return;
                }
                std::cout << "arrived at room " << stop->room->vnum << std::endl;
                auto prev = (d == Forward) ? stop->prev : stop->next;
                stop->room->send("Train has arrived from Room " + toString(prev->room->vnum) + "\r\n");
                internal_room->send("Train has arrived at Room " + toString(stop->room->vnum) + "\r\n");
                s = Stopped;
                progress = 0;
            }
            break;
        case Stopped:
            if(progress >= Updater::instance().hourLength / 4) {
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
                    std::cout << "reversing" << std::endl;
                    d = (d == Forward) ? Reverse : Forward;
                    goto next;
                }
                stop->room->send("Train leaving for Room " + toString(next->room->vnum) + "\r\n");
                internal_room->send("Train leaving for Room " + toString(next->room->vnum) + "\r\n");
                leave();
                stop = next;
                s = Running;
                progress = 0;
            }
            break;
        }
}

void Train::hour() {
    alerted = false;
}
