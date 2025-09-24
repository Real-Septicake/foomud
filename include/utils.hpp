#ifndef UTILS_HPP
#define UTILS_HPP

#include <memory>
#include <sstream>
#include <string>
#include <type_traits>
#include <vector>
void findReplace(std::string &, const std::string &, const std::string &);
std::string trim(std::string &, const std::string & = "\r\n");
std::vector<std::string> words(std::string &);

template<typename t,
    typename = typename std::enable_if<std::is_arithmetic<t>::value>::type>
std::string toString(const t val) {
    std::stringstream ss;
    ss << val;
    return ss.str();
}

template<typename Base>
class enable_shared_from_base : public std::enable_shared_from_this<Base> {
    public:
        template<typename Derived>
        std::shared_ptr<Derived> shared_from_base() {
            return std::static_pointer_cast<Derived>(this->shared_from_this());
        }
};

#endif
