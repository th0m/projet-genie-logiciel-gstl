#include "sort.hpp"

bool Sort::operator()(std::pair<unsigned int, std::string> const &a, std::pair<unsigned int, std::string> const &b) const
{
    /* # Si les scores sont identiques, on trie par rapport au pseudo */
    if(a.first == b.first)
        return a.second > b.second;

    /* # Sinon classement par rapport au score */
    return a.first > b.first;
}
