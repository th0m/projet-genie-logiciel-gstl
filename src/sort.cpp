#include "sort.hpp"

bool Sort::operator()(std::pair<unsigned int, std::string> const &a, std::pair<unsigned int, std::string> const &b) const
{
    return a.first > b.first;
}
