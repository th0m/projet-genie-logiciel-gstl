/**
 * \file r3.hpp
 * \brief Gestion de la course 3.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 *
 * Classe qui va permettre de gérer la course 3 du jeux.
 *
 */

#ifndef R3_HPP
#define R3_HPP

#include "race.hpp"

class R3 : public Race
{
    public:

        /**
         * \fn explicit R3(SDL_Surface *window)
         * \brief Constructeur de la classe, avec initialisation de sa position grâce à x et y et passage d'un pointeur sur la fenetre du jeux (afin de s'y blitter).
         *
         * \param window Pointeur sur la fenetre principal.
         */
        explicit R3(SDL_Surface *window);

        /**
         * \fn ~R3()
         * \brief Destructeur de la classe, destruction de l'ensemble des ressources allouees.
         */
        ~R3();

        /**
         * \fn void load()
         * \brief Fonction qui va charger la course à l'ecran, initialiser les IAs et leurs trajectoires etc.
         */
        void load();
};

#endif
