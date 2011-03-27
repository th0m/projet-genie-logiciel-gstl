#ifndef PLAYERCAR_HPP
#define PLAYERCAR_HPP

#include "limit.hpp"
#include <list>


class PlayerCar : public Shape
{
    public:

        explicit PlayerCar(Sint32 x, Sint32 y, SDL_Surface *window);

        ~PlayerCar();

        /* # Fonction qui permet de deplacer le vehicule */
        void move(SDLKey key, std::list<Limit*> &limit);

    private:

        enum CurrentPosition
        {
            Up,
            Down,
            Left,
            Right
        };

        void loadAnotherPosition(SDLKey key);

        /* # Taille des sprites */
        Uint32 m_shapeSize;

        SDL_Surface *m_up, *m_down, *m_right, *m_left;

        CurrentPosition m_currentPos;
};

#endif
