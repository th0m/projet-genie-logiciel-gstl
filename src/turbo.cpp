#include "turbo.hpp"

Turbo::Turbo(Sint32 x, Sint32 y, SDL_Surface *window)
: Shape(x, y, std::string("turbo"), window)
{
}
