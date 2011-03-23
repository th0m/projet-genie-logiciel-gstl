#ifndef RACE_HPP
#define RACE_HPP

#include <SDL/SDL.h>
#include <list>

#include "game.hpp"
#include "shape.hpp"
#include "playercar.hpp"

class Race
{
    public:
        explicit Race(SDL_Surface *window);
        ~Race();

        /* # Fonction qui va charge le contenu graphique du niveau */
        void load();

        /* # Fonction qui actualise la course */
        void refresh();

        PlayerCar* getPlayerCar();

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
};

#endif
