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
        void setTurboMode();

        /* # Fonction accesseur permettant de recupérer le score du joueur */
        Uint32 getScore();

        /* # Fonction qui affecte l'etat recuperation de collision a la voiture */
        void setCollisionRecovering();

         /* # Fonction qui affecte l'etat normal a la voiture */
        void setNormalState();

         /* # Fonction qui affecte l'etat flaque a la voiture */
        void setFlaqueState();

        /* # Fonction qui retourne le boolean blocked */
        bool isBlocked();

        /* # Fonction qui retourne si on roule dans une flaque */
        bool isFlaque();

        /* # Fonction qui retourne si on est en mode turbo */
        bool isTurbo();

        /* # Fonction qui affecte la vitesse en fonction de l'etat actuel */
        void setSpeed();
    private:
        /* # Position actuelle du vehicule */
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

        /* # Etat actuel du vehicule */
        enum PlayerCarState
        {
            TurboMode,
            CollisionRecovering,
            FlaqueState,
            Normal
        };

        /* # Fonction qui donne la vitesse actuelle en fonction de l'etat du vehicule */
        float getSpeed();

        /* # Fonction pour savoir vers ou on souhaite se deplacer */
        float getWantedX(SDLKey key, float& fwdlatspeed, float& revlatspeed);
        float getWantedY(SDLKey key, float& fwdlatspeed, float& revlatspeed);

        /* # Vitesse du véhicule forward : marche avant, reverse : marche arriere*/
        float m_fwdspeed, m_revspeed;

        /* # Les differents sprites de la voiture charges en memoire */
        SDL_Surface *m_up, *m_down, *m_right, *m_left, *m_northwest, *m_northeast, *m_southwest, *m_southeast;

        /* # La position courante du vehicule*/
        CurrentPosition m_currentPos;

        /* # Le score courant du joueur */
        Uint32 currentScore;

        /* # L'etat courant du vehicule */
        PlayerCarState m_state;

        /* # Booleens indiquant si la voiture est bloquee, roule dans une flaque */
        bool m_blocked, m_flaque;
};

#endif
