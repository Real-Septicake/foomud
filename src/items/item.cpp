#include "mud.hpp"
#include <items/item.hpp>

Item::Item() :
    room(), vnum(Mud::instance().maxItemVnum() + 1), name() 
{
}
