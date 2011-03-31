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
        void move(SDLKey key, std::list<Limit*> &limitH, std::list<Limit*> &limitV, std::list<Limit*> &limitsHV);

        /* # Fonction qui permet d'activer le mode turbo */
        void enableTurboMode();

    private:

        enum CurrentPosition
        {
            Up,
            Down,
            Left,
            Right
        };

        void loadAnotherPosition(SDLKey key);


        /* # vitesse du véhicule */
        Uint32 m_speed;

        SDL_Surface *m_up, *m_down, *m_right, *m_left;

        CurrentPosition m_currentPos;
};

#endif
