#ifndef PLAYERCAR_HPP
#define PLAYERCAR_HPP

#include "limit.hpp"
#include "flaque.hpp"
#include <list>


class PlayerCar : public Shape
{
    public:

        explicit PlayerCar(Sint32 x, Sint32 y, SDL_Surface *window);

        ~PlayerCar();

        /* # Fonction qui permet de deplacer le vehicule */
        void move(SDLKey key, std::list<Limit*> &limit, std::list<Flaque*> &flaques);

        /* # Fonction qui change la position du vehicule */
        void loadAnotherPosition(SDLKey key);

        /* # Fonction qui permet d'activer le mode turbo */
        void enableTurboMode();

        /* # Fonction accesseur permettant de recupérer le score du joueur */
        Uint32 getScore();

    private:

        enum CurrentPosition
        {
            Up,
            Down,
            Left,
            Right,
            NorthWest,
            NorthEast,
            SouthWest,
            SouthEast
        };

        enum PlayerCarState
        {
            TurboMode,
            Others
        };

        float getSpeed();

        void setNormalSpeed();

        void destroyTimer();

        static Uint32 callback(Uint32 interval, void* param);



        /* # vitesse du véhicule forward : marche avant, reverse : marche arriere*/
        float m_fwdspeed, m_revspeed;

        SDL_Surface *m_up, *m_down, *m_right, *m_left, *m_northwest, *m_northeast, *m_southwest, *m_southeast;

        CurrentPosition m_currentPos;

        SDL_TimerID m_timer;

        Uint32 currentScore;

        PlayerCarState m_state;
};

#endif
