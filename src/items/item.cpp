#include "enums/article.hpp"
#include <print/engine.hpp>
#include "mud.hpp"
#include <items/item.hpp>

const FormatEngine<Item> Item::engine({
        {'a', [](Item& i){ return toArticle(i.article); }},
        {'n', [](Item& i){ return i.name; }},
    }, true);

Item::Item() :
    room(), vnum(Mud::instance().maxItemVnum() + 1), name(), count(), description("&A&n") 
{
}

std::string Item::gen_descriptor() {
    return engine.fmt(*this, description);
}
