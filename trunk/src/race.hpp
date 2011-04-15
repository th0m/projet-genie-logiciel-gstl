#ifndef RACE_HPP
#define RACE_HPP

#include <SDL/SDL.h>
#include <list>
#include <map>

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

        virtual ~Race();

        /* # Fonction qui va charge le contenu graphique du niveau */
        virtual void load();

        /* # Fonction qui actualise la course */
        void actualize();

        /* # Fonction qui gere les turbos, qui nous previent si tous les turbos ont ete consomme ou non */
        bool useTurbo();

        /* # Fonction qui est capable de faire bouger la voiture du joueur */
        void movePlayerCar(SDLKey key);

        /* # Fonction qui s'occupe du deplacement de l'IA */
        void moveIAs();

        /* # Verification des 3 checkpoints*/
        Lap checkCheckPoint();

        /* # Verification fin de tours de chaque IA*/
        void checkCheckPointIA();

        /* # initialisation du nombre de tours de chaque adversaires */
        void initNbLapCompetitors();

        /* # verification fin de tour, renvoi la place du joueur */
        int checkSuccessRace();

        /* # Getter qui recupere la voiture du joueur */
        PlayerCar *getPlayerCar();


    protected:

         /* # Fonction qui va réaliser des fonctions d'initialisation sur les IAs */
         void initIAs();


        /* # La fenetre du jeu */
        SDL_Surface *m_window;

        /* # La voiture du joueur */
        PlayerCar *m_playercar;

        /* # Le nombre de ligne et de colonne de la fenetre */
        Uint32 m_nbRows, m_nbLines;

        /* # Le contenu visuel du niveau */
        Uint8 **m_map;

        /* # Les voitures des IAs */
        std::list<IACar*> m_iacars;

        /* # Un conteneur qui stock l'ensemble des formes presentes sur l'ecran */
        std::list<Shape*> m_surfaces;

        /* # Un conteneur qui stock l'ensemble des limites verticales et horizontales */
        std::list<Limit*> m_limits;

        /* # Un conteneur qui stock l'ensemble des flaques */
        std::list<Flaque*> m_flaques;

        /* # Les checkpoints que l'on a besoin de placer sur la map dont la ligne d'arrivee */
        Checkpoint *m_c1, *m_c2, *m_c3, *m_csfl;

        /* # Les points de base du mouvement des IAs */
        std::vector<float> m_pts;

        /* # Le classement */
        std::map<IACar*, std::pair<int, int> > m_ranking;
};

#endif
