/**
 * \file turbo.hpp
 * \brief Classe de la forme turbo.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 *
 * Classe qui gère l'affichage d'un turbo disponible sur la carte.
 *
 */

#ifndef TURBO_HPP
#define TURBO_HPP

#include "shape.hpp"

class Turbo : public Shape
{
    public:

        /**
         * \fn explicit Turbo(float x, float y, SDL_Surface *window)
         * \brief Constructeur de la classe, avec initialisation de sa position grâce à x et y et passage d'un pointeur sur la fenetre du jeu (afin de s'y blitter).
         *
         * \param x Coordonnée x du placement de la shape.
         * \param y Coordonnée y du placement de la shape.
         * \param window Pointeur sur la fenetre principal.
         */
        explicit Turbo(float x, float y, SDL_Surface *window);
};

#endif
