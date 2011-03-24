#ifndef SAND_HPP
#define SAND_HPP

#include "shape.hpp"

class Sand : public Shape
{
    public:

        explicit Sand(Sint32 x, Sint32 y, SDL_Surface *window);

};

#endif
