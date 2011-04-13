#ifndef SAND_HPP
#define SAND_HPP

#include "shape.hpp"

class Sand : public Shape
{
    public:

        explicit Sand(float x, float y, SDL_Surface *window);

};

#endif
