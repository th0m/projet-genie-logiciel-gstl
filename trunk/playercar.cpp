#include "playercar.hpp"

PlayerCar::PlayerCar(Uint32 x, Uint32 y, SDL_Surface *window)
: Shape(x, y, std::string("playercar"), window)
{
}

void PlayerCar::move(SDLKey key)
{
    switch(key)
    {
        case SDLK_ESCAPE:
        {
            m_x += 10;
        }
    }
}
