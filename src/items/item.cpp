#include "enums/article.hpp"
#include "mud.hpp"
#include "utils.hpp"
#include <items/item.hpp>

const FormatEngine<Item> Item::engine({
        {'a', [](Item& i){ return toArticle(i.article); }},
        {'n', [](Item& i){ return "\x1b[4m" + i.name + "\x1b[24m"; }}
    });

Item::Item() :
    room(), vnum(Mud::instance().maxItemVnum() + 1), name(), description("&A&n") 
{
}

std::string Item::gen_descriptor() {
//    std::string working(description);
//    findReplace(working, "&A", toCapital(toArticle(article)));
//    findReplace(working, "&a", toArticle(article));
//    findReplace(working, "&N", "\x1b[4m" + toCapital(name) + "\x1b[0m");
//    findReplace(working, "&n", "\x1b[4m" + name + "\x1b[0m");
    return engine.fmt(*this, description);
}
