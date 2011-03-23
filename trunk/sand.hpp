#ifndef SAND_HPP
#define SAND_HPP

#include "shape.hpp"

class Sand : public Shape
{
    public:
        explicit Sand(Uint32 x, Uint32 y, SDL_Surface *window);

};

#endif
