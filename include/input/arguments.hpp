#ifndef ARGUMENTS_HPP
#define ARGUMENTS_HPP

#include <cstddef>
#include <string>
#include <vector>
class Arguments {
    private:
        std::vector<std::string> args;
        std::string orig_str;
        void eval();
    public:
        Arguments(std::string);
        std::size_t size() const;
        bool empty() const;
        std::string original() const;
        std::string operator[](const std::size_t idx);
        std::string erase(const std::size_t idx);
        std::string substr(const std::size_t, const std::size_t = (std::size_t)-1);
};

#endif
