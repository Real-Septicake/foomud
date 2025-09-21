#ifndef UTILS_HPP
#define UTILS_HPP

#include <memory>
#include <string>
#include <vector>
void findReplace(std::string &, const std::string &, const std::string &);
std::string trim(std::string &, const std::string & = "\r\n");
std::vector<std::string> words(std::string &);

template<typename Base>
class enable_shared_from_base : public std::enable_shared_from_this<Base> {
    protected:
        template<typename Derived>
        std::shared_ptr<Derived> shared_from_base() {
            return std::static_pointer_cast<Derived>(this->shared_from_this());
        }
};

#endif
