#include "flaque.hpp"

Flaque::Flaque(Sint32 x, Sint32 y, SDL_Surface *window)
: Shape(x, y, std::string("flaque"), window)
{
}
