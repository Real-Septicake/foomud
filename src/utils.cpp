#include <string>
#include <utils.hpp>

void findReplace(std::string &source, const std::string &find, const std::string &replace) {
    if(source.empty())
        return;

    std::size_t pos = source.find(find);
    if(pos == std::string::npos)
        return;

    while(pos != std::string::npos) {
        source.replace(pos, find.length(), replace);
        pos = source.find(find);
    }
}
