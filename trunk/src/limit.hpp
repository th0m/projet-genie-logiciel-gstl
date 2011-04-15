#ifndef LIMIT_HPP
#define LIMIT_HPP

#include "shape.hpp"

class Limit : public Shape
{
    public:

        explicit Limit(float x, float y, SDL_Surface *window);
};

#endif
