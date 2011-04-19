/**
 * \file r2.hpp
 * \brief Gestion de la course 2.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 *
 * Classe qui va permettre de g�rer la course 2 du jeux.
 *
 */

#ifndef R2_HPP
#define R2_HPP

#include "race.hpp"

class R2 : public Race
{
    public:

        /**
         * \fn explicit R2(SDL_Surface *window)
         * \brief Constructeur de la classe, avec initialisation de sa position gr�ce � x et y et passage d'un pointeur sur la fenetre du jeux (afin de s'y blitter).
         *
         * \param window Pointeur sur la fenetre principal.
         */
        explicit R2(SDL_Surface *window);

        /**
         * \fn ~R2()
         * \brief Destructeur de la classe, destruction de l'ensemble des ressources allouees.
         */
        ~R2();

        /**
         * \fn void load()
         * \brief Fonction qui va charger la course � l'ecran, initialiser les IAs et leurs trajectoires etc.
         */
        void load();
};

#endif
