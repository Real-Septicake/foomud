#include <algorithm>
#include <cctype>
#include <cstddef>
#include <iterator>
#include <sstream>
#include <string>
#include <utils.hpp>
#include <vector>

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

std::string trim(std::string &source, const std::string &remove) {
    std::string s = source;
    auto f = s.find_first_not_of(remove);
    auto l = s.find_last_not_of(remove);
    s.erase(l+1).erase(0, f);
    return s;
}

std::vector<std::string> words(std::string &s) {
    std::istringstream iss(s);
    std::istream_iterator<std::string> b(iss);
    std::istream_iterator<std::string> e;
    return std::vector<std::string>(b, e);
}

bool prefix(std::string source, std::string prefix) {
    return std::mismatch(prefix.begin(), prefix.end(), source.begin()).first == prefix.end();
}


std::string toLower(std::string s) {
    std::string l = s;
    for(unsigned int i = 0; i < l.size(); i++) {
        l[i] = std::tolower(l[i]);
    }
    return l;
}

std::string toCapital(std::string s) {
    std::string c = s;
    if(c.size() == 0)
        return "";
    c[0] = std::toupper(c[0]);
    bool seen_space = false;
    for(size_t i = 1; i < c.size(); i++) {
        if(c[i] == ' ') {
            seen_space = true;
            continue;
        }
        if(seen_space) {
            c[i] = std::toupper(c[i]);
        }
    }
    return c;
}
