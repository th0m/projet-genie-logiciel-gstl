#ifndef PLAYERCAR_HPP
#define PLAYERCAR_HPP

#include "shape.hpp"

class PlayerCar : public Shape
{
    public:
        explicit PlayerCar(Uint32 x, Uint32 y, SDL_Surface *window);

        void move(SDLKey key);
};

#endif
