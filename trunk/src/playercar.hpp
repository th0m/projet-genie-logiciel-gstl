#ifndef PLAYERCAR_HPP
#define PLAYERCAR_HPP

#include "limit.hpp"
#include "flaque.hpp"
#include "iacar.hpp"

#include <list>


class PlayerCar : public Shape
{
    public:

        explicit PlayerCar(Sint32 x, Sint32 y, SDL_Surface *window);

        ~PlayerCar();

        /* # Fonction qui permet de deplacer le vehicule */
        void move(SDLKey key, std::list<Limit*> &limit, std::list<Flaque*> &flaques, std::list<IACar*> &iacars);

        /* # Fonction qui change la position du vehicule */
        void loadAnotherPosition(SDLKey key);

        /* # Fonction qui permet d'activer le mode turbo */
        void enableTurboMode();

        /* # Fonction accesseur permettant de recupérer le score du joueur */
        Uint32 getScore();

        /* # Fonction qui retablit la vitesse de croisiere du vehicule */
        void setNormalSpeed();

        /* # Fonction qui baisse la voiture du vehicule apres une collision */
        void collisionRecovering();

        /* # Fonction qui retourne le boolean blocked */
        bool isBlocked(){return m_blocked;};

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
            CollisionRecovering,
            Others
        };

        float getSpeed();

        /* # vitesse du véhicule forward : marche avant, reverse : marche arriere*/
        float m_fwdspeed, m_revspeed;

        SDL_Surface *m_up, *m_down, *m_right, *m_left, *m_northwest, *m_northeast, *m_southwest, *m_southeast;

        CurrentPosition m_currentPos;

        Uint32 currentScore;

        PlayerCarState m_state;

        /* # boolean indiquant si la voiture est bloquee */
        bool m_blocked;
};

#endif
