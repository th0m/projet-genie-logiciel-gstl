#ifndef WHITE_HPP
#define WHITE_HPP

#include "shape.hpp"

class White : public Shape
{
    public:
        explicit White(Uint32 x, Uint32 y, SDL_Surface *window);
};

#endif
