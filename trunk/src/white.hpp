#ifndef WHITE_HPP
#define WHITE_HPP

#include "shape.hpp"

class White : public Shape
{
    public:

        explicit White(float x, float y, SDL_Surface *window);
};

#endif
