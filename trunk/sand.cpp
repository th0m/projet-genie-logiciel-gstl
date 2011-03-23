#include "sand.hpp"

Sand::Sand(Uint32 x, Uint32 y, SDL_Surface *window)
: Shape(x, y, std::string("sand"), window)
{
}
