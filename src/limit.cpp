#include "limit.hpp"

Limit::Limit(Sint32 x, Sint32 y, SDL_Surface *window)
: Shape(x, y, std::string("limit"), window)
{
}
