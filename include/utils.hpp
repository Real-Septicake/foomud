#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <vector>
void findReplace(std::string &, const std::string &, const std::string &);
std::string trim(std::string &, const std::string & = "\r\n");
std::vector<std::string> words(std::string &);

#endif
