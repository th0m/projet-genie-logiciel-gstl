#ifndef TURBO_HPP
#define TURBO_HPP

#include "shape.hpp"

class Turbo : public Shape
{
    public:
        explicit Turbo(Uint32 x, Uint32 y, SDL_Surface *window);
};

#endif
