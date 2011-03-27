#ifndef PLAYERCAR_HPP
#define PLAYERCAR_HPP

#include "limit.hpp"
#include <list>


class PlayerCar : public Shape
{
    public:

        explicit PlayerCar(Sint32 x, Sint32 y, SDL_Surface *window);

        void move(SDLKey key, std::list<Limit*> &limit);

    private:

        Uint32 m_shapeSize;
};

#endif
