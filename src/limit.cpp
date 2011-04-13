#include "limit.hpp"

Limit::Limit(float x, float y, SDL_Surface *window)
: Shape(x, y, std::string("limit"), window)
{
}
