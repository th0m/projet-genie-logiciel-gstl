#ifndef LIMIT_HPP
#define LIMIT_HPP

#include "shape.hpp"

class Limit : public Shape
{
    public:
        explicit Limit(Uint32 x, Uint32 y, SDL_Surface *window);
};

#endif
