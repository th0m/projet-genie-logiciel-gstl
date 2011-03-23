#ifndef STARTINGFINISHLINE_HPP
#define STARTINGFINISHLINE_HPP

#include "shape.hpp"

class StartingFinishLine : public Shape
{
    public:
        explicit StartingFinishLine(Uint32 x, Uint32 y, SDL_Surface *window);
};

#endif
