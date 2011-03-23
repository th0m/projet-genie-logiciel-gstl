#include "turbo.hpp"

Turbo::Turbo(Uint32 x, Uint32 y, SDL_Surface *window)
: Shape(x, y, std::string("turbo"), window)
{
}
