/**
 * \file iacar.hpp
 * \brief Gestion des IAs.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 *
 * Classe qui va permettre de g�rer l'ensemble des pseudo-IAs.
 *
 */

#ifndef IACAR_HPP
#define IACAR_HPP

#include <list>
#include <vector>
#include "shape.hpp"

class IACar : public Shape
{
    public:

        /**
         * \enum Step
         * \brief Nos IAs sont tr�s basiques, en effet elles suivent quatres etats.
         *
         */
        enum Step
        {
            FirstStep, /*!< Premi�re �tat, de gauche � droite (en partant de la ligne d'arrive) */
            SecondStep, /*!< Second �tat, de bas en haut */
            ThirdStep, /*!< Troisieme �tat, de droite � gauche */
            LastStep /*!< Derni�re �tat de haut en bas */
        };

        /**
         * \fn explicit IACar(float x, float y, SDL_Surface *window)
         * \brief Constructeur de la classe, avec initialisation de sa position gr�ce � x et y et passage d'un pointeur sur la fenetre du jeux (afin de s'y blitter).
         *
         * \param x Coordonn�e x du placement de la shape.
         * \param y Coordonn�e y du placement de la shape.
         * \param window Pointeur sur la fenetre principal.
         */
        explicit IACar(float x, float y, SDL_Surface *window);

        /**
         * \fn ~IACar()
         * \brief Destructeur de la classe, destruction de l'ensemble des ressources allouees.
         */
        ~IACar();

        /**
         * \fn void setPoints(std::vector<float> &points)
         * \brief Fonction qui permet de d�finir les points "d'interpolation" du mouvement.
         *
         * \param points Un vecteur qui va contenir 4 coordonn�e, une coordonn�e x en premier, une coordonn�e y en second, une coordonn�e x en troisi�me et enfin une autre coordonn�e y.
         */
        void setPoints(std::vector<float> &points);

        /**
         * \fn void move(float playerx, float playery, std::list<IACar*> &ias)
         * \brief Fonction qui permet de faire evoluer les voitures pseudo-IAs.
         *
         * \param playerx Coordonn�e x de la voiture du joueur (pour �viter les collisions).
         * \param playery Coordonn�e y de la voiture du joueur (pour �viter les collisions).
         * \param ias Liste des diff�rentes IAs encore une fois pour �viter les collisions.
         */
        void move(float playerx, float playery, std::list<IACar*> &ias);

        /**
         * \fn void setDifficulty(Uint8 diff)
         * \brief Fonction qui permet de d�finir la difficulte d'une IA � partir d'un entier de 0 � 3, il va permettre de "muter" leurs vitesses/mouvements etc.
         *
         * \param diff Difficult� de 0 � 3 de l'IA.
         */
        void setDifficulty(Uint8 diff);

    private:

        /**
         * \fn bool moveAllowed(float x, float y, float playerx, float playery, std::list<IACar*> &ias)
         * \brief Fonction qui permet de d�finir la difficulte d'une IA � partir d'un entier de 0 � 3, il va permettre de "muter" leurs vitesses/mouvements etc.
         *
         * \param x Coordonn�e x de l'IA.
         * \param y Coordonn�e y de l'IA.
         * \param playerx Coordonn�e x de la voiture du joueur pour eviter les collisions.
         * \param playery Coordonn�e y de la voiture du joueur pour eviter les collisions.
         * \param ias Liste des diff�rentes IAs encore une fois pour �viter les collisions.
         * \return Un bool�en pour savoir si le mouvement de l'IA va entrainer une collision ou non.
         */
        bool moveAllowed(float x, float y, float playerx, float playery, std::list<IACar*> &ias);


        std::vector<float> m_points; /*!< Vecteur des points d'interpolations */

        Step m_currentStep; /*!< Le mouvement s'opp�re en 4 �tapes, cet attribut indique le courant */

        Uint8 m_difficulty; /*!< Difficulte de l'IA */

        SDL_Surface *m_up, *m_down, *m_right, *m_left; /*!< Les diff�rentes surfaces de la voiture, voiture vers le haut, bas, gauche, droite */
};

#endif
