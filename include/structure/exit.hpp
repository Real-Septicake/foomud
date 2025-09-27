#ifndef EXIT_HPP
#define EXIT_HPP

#include <memory>
class Room;

enum Direction {
    None,
    North,
    South,
    East,
    West,
    Up,
    Down
};

class Exit : std::enable_shared_from_this<Exit> {
    public:
        std::weak_ptr<Room> to; // where the exit leads to
        std::weak_ptr<Room> from; // the room the exit belongs to
        Direction direction = Direction::None; // the direction the exit goes in
        std::shared_ptr<Exit> getCorresponding();
};

#endif
