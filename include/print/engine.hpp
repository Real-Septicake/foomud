#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <map>
#include <functional>
#include <string>
#include "../utils.hpp"
#include "../items/item.hpp"
#include <cctype>

template<typename T>
class FormatEngine {
    std::map<char, std::function<std::string(T&)>> formats;
    std::function<bool(T&)> is_plural;
    bool capitalize;
    char escape;
    public:
    std::string fmt(T& obj, std::string format) const {
        std::string working;
        working.resize(format.size());
        for(size_t i = 0; i < format.size(); i++) {
            if(format[i] == escape) {
                i++;
                if(format[i] == escape) {
                    working += escape;
                    continue;
                }
                auto f = formats.find(std::tolower(format[i]));
                if(f == formats.end())
                    working += format[i];
                else {
                    std::string v = f->second(obj);
                    if(capitalize && format[i] >= 'A' && format[i] <= 'Z')
                        v = toCapital(v);
                    if(v.contains('&'))
                        v = fmt(obj, v);
                    working += v;
                }
            } else
                working += format[i];
        }
        return working;
    }

    FormatEngine(std::map<char, std::function<std::string(T&)>> formats, bool capitalize = false, std::function<bool(T&)> is_plural = nullptr, char escape = '&') :
        formats(formats), is_plural(is_plural), capitalize(capitalize), escape(escape) {}
};

#endif
