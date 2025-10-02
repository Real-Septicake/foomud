#include "mud.hpp"
#include <transport/stop.hpp>

Stop::Stop() :
    vnum(Mud::instance().maxStopVnum() + 1)
{
}
