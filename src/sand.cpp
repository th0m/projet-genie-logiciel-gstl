#include "sand.hpp"

Sand::Sand(Sint32 x, Sint32 y, SDL_Surface *window)
: Shape(x, y, std::string("sand"), window)
{
}
