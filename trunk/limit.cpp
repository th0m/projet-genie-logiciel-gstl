#include "limit.hpp"

Limit::Limit(Uint32 x, Uint32 y, SDL_Surface *window)
: Shape(x, y, std::string("limit"), window)
{
}
