#include "utils.hpp"
#include <iostream>
#include <transport/train.hpp>

Train::Train()
{
}

void Train::tick() {
    static auto get_next = [this]() {
                bool tried = false;
next:
                auto next = (d == Forward) ? stop->next : stop->prev;
                if(!next) {
                    if(tried) {
                        std::cout << "train " << toString(vnum) << " is stuck" << std::endl;
                        progress = 0;
                        return (std::shared_ptr<Stop>)nullptr;
                    }
                    tried = true;
                    std::cout << "reversing" << std::endl;
                    d = (d == Forward) ? Reverse : Forward;
                    goto next;
                }
                return next;
    };
    progress++;
    std::cout << progress << std::endl;
    switch(s) {
        case Running:
            if(progress >= stop->next_distance) {
                auto next = get_next();
                if(!next) return;
                if(d == Forward) {
                    bool r = arrive(next->room);
                    if(!(r || alerted)) {
                        alerted = true;
                        internal_room->send("Could not arrive at station, please be patient\r\n");
                        return;
                    }
                    std::cout << "arrived at room " << next->room->vnum << std::endl;
                    next->room->send("Train has arrived from Room " + toString(stop->room->vnum) + "\r\n");
                    internal_room->send("Train has arrived at Room " + toString(next->room->vnum) + "\r\n");
                    stop = next;
                } else {
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
                }
                s = Stopped;
                progress = 0;
            }
            break;
        case Stopped:
            if(progress >= 5) {
                auto next = get_next();
                if(d == Forward) {
                    std::cout << "leaving" << std::endl;
                    std::cout << "ttn: " << stop->next_distance << std::endl;
                    stop->room->send("Train leaving for Room " + toString(next->room->vnum) + "\r\n");
                    internal_room->send("Train leaving for Room " + toString(next->room->vnum) + "\r\n");
                } else {
                    stop = next;
                    std::cout << "leaving" << std::endl;
                    std::cout << "ttn: " << stop->next_distance << std::endl;
                    stop->room->send("Train leaving for Room " + toString(stop->room->vnum) + "\r\n");
                    internal_room->send("Train leaving for Room " + toString(stop->room->vnum) + "\r\n");
                }
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
