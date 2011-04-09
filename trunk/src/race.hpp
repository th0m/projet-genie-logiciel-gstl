#ifndef RACE_HPP
#define RACE_HPP

#include <SDL/SDL.h>
#include <list>

#include "game.hpp"
#include "shape.hpp"
#include "playercar.hpp"
#include "limit.hpp"
#include "checkpoint.hpp"
#include "iacar.hpp"
#include "flaque.hpp"

class Race
{
    public:

        typedef enum Lap
        {
            Finished,
            InProgress
        };

        explicit Race(SDL_Surface *window);

        ~Race();

        /* # Fonction qui va charge le contenu graphique du niveau */
        void load();

        /* # Fonction qui actualise la course */
        void refresh();

        /* # Fonction qui gere les turbos */
        void useTurbo();

        /* # Fonction qui est capable de faire bouger la voiture du joueur */
        void movePlayerCar(SDLKey key);

        /* # Fonction qui change la position de la voiture du joueur */
        void changePlayerCarPosition(SDLKey key);

        /* # Verification des 3 checkpoints*/
        Lap checkCheckPoint();

    protected:

        /* # La fenetre du jeu */
        SDL_Surface *m_window;

        /* # La voiture du joueur */
        PlayerCar *m_playercar;

        /* # Le nombre de ligne et de colonne de la fenetre */
        Uint32 m_nbRows, m_nbLines;

        /* # Le contenu visuel du niveau */
        Uint8 **m_map;

        /* # Un conteneur qui stock l'ensemble des formes presentes sur l'ecran */
        std::list<Shape*> m_surfaces;

        /* # Un conteneur qui stock l'ensemble des limites verticales et horizontales */
        //std::list<Limit*> m_limitsH, m_limitsV, m_limitsHV;
        std::list<Limit*> m_limits;

        /* # Un conteneur qui stock l'ensemble des flaques */
        std::list<Flaque*> m_flaques;

        /* # Les checkpoints que l'on a besoin de placer sur la map dont la ligne d'arrivee */
        Checkpoint *m_c1, *m_c2, *m_c3, *m_csfl;

        /* # Timer */
        SDL_TimerID m_IATimer;

        bool isAlreadyLoaded;

};

#endif
