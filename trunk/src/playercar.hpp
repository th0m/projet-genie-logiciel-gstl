/**
 * \file playercar.hpp
 * \brief Gestion de la voiture du joueur.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 *
 * Classe qui va permettre de gérer la voiture du joueur.
 *
 */

#ifndef PLAYERCAR_HPP
#define PLAYERCAR_HPP

#include "limit.hpp"
#include "flaque.hpp"
#include "iacar.hpp"

#include <list>


class PlayerCar : public Shape
{
    public:

        /**
         * \fn explicit PlayerCar(float x, float y, SDL_Surface *window)
         * \brief Constructeur de la classe, avec initialisation de sa position grâce à x et y et passage d'un pointeur sur la fenetre du jeux (afin de s'y blitter).
         *
         * \param x Coordonnée x du placement de la shape.
         * \param y Coordonnée y du placement de la shape.
         * \param window Pointeur sur la fenetre principal.
         */
        explicit PlayerCar(float x, float y, SDL_Surface *window);

        /**
         * \fn ~PlayerCar()
         * \brief Destructeur de la classe, destruction de l'ensemble des ressources allouees.
         */
        ~PlayerCar();

        /**
         * \fn void move(SDLKey key, std::list<Limit*> &limit, std::list<Flaque*> &flaques, std::list<IACar*> &iacars)
         * \brief Fonction qui permet de faire bouger la voiture du joueur, et de chargé les shapes correspondantes.
         *
         * \param key Touche de direction qui a été frappé par l'utilisateur.
         * \param limit Liste des différentes limites, pour éviter les collisions.
         * \param flaques Liste des différentes flaques d'eau, pour ralentir la vitesse de croisière.
         * \param iacars Liste des différentes IAs encore une fois pour éviter les collisions.
         */
        void move(SDLKey key, std::list<Limit*> &limit, std::list<Flaque*> &flaques, std::list<IACar*> &iacars);

        /**
         * \fn void loadAnotherPosition(SDLKey key)
         * \brief Fonction qui change la position du vehicule.
         *
         * \param key Touche de direction qui a été frappé par l'utilisateur.
         */
        void loadAnotherPosition(SDLKey key);

        /**
         * \fn void setTurboMode()
         * \brief Fonction qui permet d'activer le mode turbo.
         */
        void setTurboMode();

        /**
         * \fn void setCollisionRecovering()
         * \brief Fonction qui affecte l'etat recuperation de collision a la voiture.
         */
        void setCollisionRecovering();

        /**
         * \fn void setNormalState()
         * \brief Fonction qui affecte l'etat normal a la voiture.
         */
        void setNormalState();

        /**
         * \fn void setNormalState()
         * \brief Fonction qui affecte l'etat flaque a la voiture.
         */
        void setFlaqueState();

        /**
         * \fn bool isBlocked()
         * \brief Fonction qui retourne le boolean blocked.
         *
         * \return Un booléen qui nous renseigne sur la question suivante : "La voiture est-elle bloquée ?"
         */
        bool isBlocked();

        /**
         * \fn bool isFlaque()
         * \brief Fonction qui retourne si on roule dans une flaque.
         *
         * \return Un booléen qui nous renseigne sur la question suivante : "La voiture est-elle dans une flaque d'eau ?"
         */
        bool isFlaque();

        /**
         * \fn bool isTurbo()
         * \brief Fonction qui retourne si on est en mode turbo.
         *
         * \return Un booléen qui nous renseigne sur la question suivante : "La voiture est-elle en mode turbo ?"
         */
        bool isTurbo();

        /**
         * \fn void setSpeed()
         * \brief Fonction qui affecte la vitesse en fonction de l'etat actuel.
         */
        void setSpeed();

    private:

        /**
         * \enum CurrentPosition
         * \brief Indique la position actuelle du véhicule.
         *
         */
        enum CurrentPosition
        {
            Up, /*!< Voiture vers le haut */
            Down, /*!< Voiture vers le bas */
            Left, /*!< Voiture vers la gauche */
            Right, /*!< Voiture vers la droite */
            NorthWest, /*!< Voiture vers le haut-droit */
            NorthEast, /*!< Voiture vers le haut-gauche */
            SouthWest, /*!< Voiture vers le bas-droit */
            SouthEast /*!< Voiture vers le bas-gauche */
        };

        /**
         * \enum PlayerCarState
         * \brief Indique l'etat de la voiture.
         *
         */
        enum PlayerCarState
        {
            TurboMode, /*!< Voiture en mode turbo */
            CollisionRecovering, /*!< Voiture en mode sortie de collision */
            FlaqueState, /*!< Voiture traverse une flaque */
            Normal /*!< Voiture est en mode normal */
        };

        /**
         * \fn float getSpeed()
         * \brief Fonction qui donne la vitesse actuelle en fonction de l'etat du vehicule.
         *
         * \return La vitesse actuelle du véhicule (qui change en fonction de son état bien sur).
         */
        float getSpeed();

        /**
         * \fn float getWantedX()
         * \brief Fonction pour savoir vers ou on souhaite se deplacer.
         *
         * \param key Touche de direction qui a été frappé par l'utilisateur.
         * \param fwdlatspeed Projection sur x et y du deplacement en diagonale en marche avant.
         * \param revlatspeed Projection sur x et y du deplacement en diagonale en marche arriere.
         * \return Abscisse visee apres deplacement.
         */
        float getWantedX(SDLKey key, float& fwdlatspeed, float& revlatspeed);

        /**
         * \fn float getWantedY()
         * \brief Fonction pour savoir vers ou on souhaite se deplacer.
         *
         * \param key Touche de direction qui a été frappé par l'utilisateur.
         * \param fwdlatspeed Projection sur x et y du deplacement en diagonale en marche avant.
         * \param revlatspeed Projection sur x et y du deplacement en diagonale en marche arriere.
         * \return Ordonnee visee apres deplacement
         */
        float getWantedY(SDLKey key, float& fwdlatspeed, float& revlatspeed);


        float m_fwdspeed, m_revspeed; /*!< Vitesse du véhicule en marche avant et arrière */

        SDL_Surface *m_up, *m_down, *m_right, *m_left, *m_northwest, *m_northeast, *m_southwest, *m_southeast; /*!< Les différentes surfaces du véhicule, voiture en haut, bas, gauche, droite etc */

        CurrentPosition m_currentPos; /*!< La position courante du vehicule */

        PlayerCarState m_state; /*!< L'etat courant du vehicule */

        bool m_blocked, m_flaque; /*!< La voiture est-elle bloquée ? La voiture est-elle dans une flaque ? */
};

#endif
