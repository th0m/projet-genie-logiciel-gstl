/**
 * \file white.hpp
 * \brief Classe de la forme blanche.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 */

#ifndef WHITE_HPP
#define WHITE_HPP

#include "shape.hpp"

/**
 * \class White
 * \brief Classe qui gère l'affichage d'un "pixel" blanc sur la carte.
*/
class White : public Shape
{
    public:

        /**
         * \fn explicit White(float x, float y, SDL_Surface *window)
         * \brief Constructeur de la classe, avec initialisation de sa position grâce à x et y et passage d'un pointeur sur la fenetre du jeu (afin de s'y blitter).
         *
         * \param x Coordonnée x du placement de la shape.
         * \param y Coordonnée y du placement de la shape.
         * \param window Pointeur sur la fenetre principal.
         */
        explicit White(float x, float y, SDL_Surface *window);
};

#endif
