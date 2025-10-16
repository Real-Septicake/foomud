#ifndef ARTICLES_HPP
#define ARTICLES_HPP

#include <string>

enum class Article : unsigned char {
    Vowel,
    Consonant,
    None
};

inline std::string toArticle(Article a) {
    switch(a) {
        case Article::Vowel:
            return "an ";
        case Article::Consonant:
            return "a ";
        default:
            return "";
    }
}

#endif
