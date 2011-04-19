/**
 * \file r1.hpp
 * \brief Gestion de la course 1.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 *
 * Classe qui va permettre de g�rer la course 1 du jeux.
 *
 */

#ifndef R1_HPP
#define R1_HPP

#include "race.hpp"

class R1 : public Race
{
    public:

        /**
         * \fn explicit R1(SDL_Surface *window)
         * \brief Constructeur de la classe, avec initialisation de sa position gr�ce � x et y et passage d'un pointeur sur la fenetre du jeux (afin de s'y blitter).
         *
         * \param window Pointeur sur la fenetre principal.
         */
        explicit R1(SDL_Surface *window);

        /**
         * \fn ~R1()
         * \brief Destructeur de la classe, destruction de l'ensemble des ressources allouees.
         */
        ~R1();

        /**
         * \fn void load()
         * \brief Fonction qui va charger la course � l'ecran, initialiser les IAs et leurs trajectoires etc.
         */
        void load();
};

#endif
