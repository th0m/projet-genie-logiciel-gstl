/**
 * \file iacar.hpp
 * \brief Gestion des IAs.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 *
 * Classe qui va permettre de gérer l'ensemble des pseudo-IAs.
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
         * \brief Nos IAs sont très basiques, en effet elles suivent quatres etats.
         *
         */
        enum Step
        {
            FirstStep, /*!< Première état, de gauche à droite (en partant de la ligne d'arrive) */
            SecondStep, /*!< Second état, de bas en haut */
            ThirdStep, /*!< Troisieme état, de droite à gauche */
            LastStep /*!< Dernière état de haut en bas */
        };

        /**
         * \fn explicit IACar(float x, float y, SDL_Surface *window)
         * \brief Constructeur de la classe, avec initialisation de sa position grâce à x et y et passage d'un pointeur sur la fenetre du jeux (afin de s'y blitter).
         *
         * \param x Coordonnée x du placement de la shape.
         * \param y Coordonnée y du placement de la shape.
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
         * \brief Fonction qui permet de définir les points "d'interpolation" du mouvement.
         *
         * \param points Un vecteur qui va contenir 4 coordonnée, une coordonnée x en premier, une coordonnée y en second, une coordonnée x en troisième et enfin une autre coordonnée y.
         */
        void setPoints(std::vector<float> &points);

        /**
         * \fn void move(float playerx, float playery, std::list<IACar*> &ias)
         * \brief Fonction qui permet de faire evoluer les voitures pseudo-IAs.
         *
         * \param playerx Coordonnée x de la voiture du joueur (pour éviter les collisions).
         * \param playery Coordonnée y de la voiture du joueur (pour éviter les collisions).
         * \param ias Liste des différentes IAs encore une fois pour éviter les collisions.
         */
        void move(float playerx, float playery, std::list<IACar*> &ias);

        /**
         * \fn void setDifficulty(Uint8 diff)
         * \brief Fonction qui permet de définir la difficulte d'une IA à partir d'un entier de 0 à 3, il va permettre de "muter" leurs vitesses/mouvements etc.
         *
         * \param diff Difficulté de 0 à 3 de l'IA.
         */
        void setDifficulty(Uint8 diff);

    private:

        /**
         * \fn bool moveAllowed(float x, float y, float playerx, float playery, std::list<IACar*> &ias)
         * \brief Fonction qui permet de définir la difficulte d'une IA à partir d'un entier de 0 à 3, il va permettre de "muter" leurs vitesses/mouvements etc.
         *
         * \param x Coordonnée x de l'IA.
         * \param y Coordonnée y de l'IA.
         * \param playerx Coordonnée x de la voiture du joueur pour eviter les collisions.
         * \param playery Coordonnée y de la voiture du joueur pour eviter les collisions.
         * \param ias Liste des différentes IAs encore une fois pour éviter les collisions.
         * \return Un booléen pour savoir si le mouvement de l'IA va entrainer une collision ou non.
         */
        bool moveAllowed(float x, float y, float playerx, float playery, std::list<IACar*> &ias);


        std::vector<float> m_points; /*!< Vecteur des points d'interpolations */

        Step m_currentStep; /*!< Le mouvement s'oppère en 4 étapes, cet attribut indique le courant */

        Uint8 m_difficulty; /*!< Difficulte de l'IA */

        SDL_Surface *m_up, *m_down, *m_right, *m_left; /*!< Les différentes surfaces de la voiture, voiture vers le haut, bas, gauche, droite */
};

#endif
