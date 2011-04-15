#ifndef TURBO_HPP
#define TURBO_HPP

#include "shape.hpp"

class Turbo : public Shape
{
    public:

        explicit Turbo(float x, float y, SDL_Surface *window);
};

#endif
