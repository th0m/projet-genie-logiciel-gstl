#ifndef SORT_HPP
#define SORT_HPP

#include <utility>
#include <string>

class Sort
{
    public:

        bool operator()(std::pair<unsigned int, std::string> const &a, std::pair<unsigned int, std::string> const &b) const;
};

#endif
