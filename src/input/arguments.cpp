#include "utils.hpp"
#include <input/arguments.hpp>
#include <iterator>

Arguments::Arguments(std::string str) :
    orig_str(str)
{
    eval();
}

void Arguments::eval() {
    args = words(orig_str);
}

std::size_t Arguments::size() const {
    return args.size();
}

bool Arguments::empty() const {
    return args.empty();
}

std::string Arguments::original() const {
    return orig_str;
}

std::string Arguments::operator[](const std::size_t idx) {
    return args[idx];
}

std::string Arguments::erase(const std::size_t idx) {
    if(idx < args.size()) {
        auto i = args.begin();
        std::advance(i, idx);
        std::string r = *i;
        args.erase(i);
        return r;
    }
    return "";
}

std::string Arguments::substr(const std::size_t begin, const std::size_t end) {
    if(begin > end)
        return "";
    std::string s;
    for(auto i = begin; i < end && i < args.size(); i++) {
        if(!s.empty())
            s += " ";
        s += args[i];
    }
    return s;
}
