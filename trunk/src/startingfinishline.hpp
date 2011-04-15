#ifndef STARTINGFINISHLINE_HPP
#define STARTINGFINISHLINE_HPP

#include "shape.hpp"

class StartingFinishLine : public Shape
{
    public:

        explicit StartingFinishLine(float x, float y, SDL_Surface *window);
};

#endif
