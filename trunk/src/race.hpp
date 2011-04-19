/**
 * \file race.hpp
 * \brief Gestion des courses.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 */

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

/**
 * \class Race
 * \brief Classe qui va permettre de gérer génériquement les courses.
*/
class Race
{
    public:
        /**
         * \enum Lap
         * \brief Indique l'etat du tour.
         *
         */
        enum Lap
        {
            Finished, /*!< Tour termine */
            InProgress /*!< Tour en cours */
        };
        /**
         * \fn explicit Race(SDL_Surface *window)
         * \brief Constructeur de la classe, passage d'un pointeur sur la fenetre du jeu (afin de s'y blitter).
         *
         * \param window Pointeur sur la fenetre principal.
         */
        explicit Race(SDL_Surface *window);

        /**
         * \fn virtual ~Race()
         * \brief Destructeur de la classe, destruction de l'ensemble des ressources allouees.
         */
        virtual ~Race();

        /**
         * \fn void load()
         * \brief Fonction qui va charger le contenu graphique du niveau
         */
        virtual void load();

        /**
         * \fn void actualize()
         * \brief Fonction qui actualise la course.
         */
        void actualize();

        /**
         * \fn bool useTurbo()
         * \brief Fonction qui gere les turbos, qui nous previent si tous les turbos ont ete consommes ou non.
         *
         * \return Un booleen qui definit si on a encore des turbos a consommer
         */
        bool useTurbo();

        /**
         * \fn void movePlayerCar(SDLKey key)
         * \brief Fonction qui est capable de faire bouger la voiture du joueur
         *
         * \param key Touche de direction qui a été frappée par l'utilisateur.
         */
        void movePlayerCar(SDLKey key);

        /**
         * \fn void moveIAs()
         * \brief Fonction qui s'occupe du deplacement de l'IA.
         */
        void moveIAs();

        /**
         * \fn Lap checkCheckPoint()
         * \brief Verification des 3 checkpoints
         *
         * \return Un element de l'enum Lap indiquant l'etat du tour.
         */
        Lap checkCheckPoint();

        /**
         * \fn void checkCheckPointIA()
         * \brief Verification fin de tours de chaque IA.
         */
        void checkCheckPointIA();

        /**
         * \fn void initNbLapCompetitors()
         * \brief Initialisation du nombre de tours de chaque adversaire.
         */
        void initNbLapCompetitors();

        /**
         * \fn int checkSuccessRace()
         * \brief Verification de fin de tour.
         *
         * \return La place du joueur.
         */
        int checkSuccessRace();

        /**
         * \fn PlayerCar *getPlayerCar()
         * \brief Getter qui recupere la voiture du joueur.
         *
         * \return La voiture du joueur.
         */
        PlayerCar *getPlayerCar();


    protected:

        /**
         * \fn void initIAs()
         * \brief Fonction qui va réaliser des fonctions d'initialisation sur les IAs.
         */
        void initIAs();

        SDL_Surface *m_window; /*!< La fenetre du jeu */

        PlayerCar *m_playercar; /*!< La voiture du joueur */

        Uint32 m_nbRows; /*!< Le nombre de colonnes de la fenetre */

        Uint32 m_nbLines; /*!< Le nombre de lignes de la fenetre */

        Uint8 **m_map; /*!< Le contenu visuel du niveau */

        std::list<IACar*> m_iacars; /*!< Les voitures des IAs */

        std::list<Shape*> m_surfaces; /*!< Un conteneur qui stock l'ensemble des formes presentes sur l'ecran */

        std::list<Limit*> m_limits; /*!< Un conteneur qui stock l'ensemble des limites verticales et horizontales */

        std::list<Flaque*> m_flaques; /*!< Un conteneur qui stock l'ensemble des flaques */

        Checkpoint *m_c1; /*!< Premier checkpoint */

        Checkpoint *m_c2; /*!< Second checkpoint */

        Checkpoint *m_c3; /*!< Troisième checkpoint */

        Checkpoint *m_csfl; /*!< Checkpoint de la ligne d'arrivée */

        std::vector<float> m_pts; /*!< Les points de base du mouvement des IAs */

        std::map<IACar*, std::pair<int, int> > m_ranking; /*!< Le classement */
};

#endif
