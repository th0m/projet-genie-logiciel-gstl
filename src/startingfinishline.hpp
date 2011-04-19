/**
 * \file startingfinishline.hpp
 * \brief Gestion de la ligne d'arrive/depart.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 *
 * Classe qui va permettre de gérer l'affichage de la ligne d'arrivé/départ.
 *
 */

#ifndef STARTINGFINISHLINE_HPP
#define STARTINGFINISHLINE_HPP

#include "shape.hpp"

class StartingFinishLine : public Shape
{
    public:

        /**
         * \fn explicit StartingFinishLine(float x, float y, SDL_Surface *window)
         * \brief Constructeur de la classe, avec initialisation de sa position grâce à x et y et passage d'un pointeur sur la fenetre du jeux (afin de s'y blitter).
         *
         * \param x Coordonnée x du placement de la shape.
         * \param y Coordonnée y du placement de la shape.
         * \param window Pointeur sur la fenetre principal.
         */
        explicit StartingFinishLine(float x, float y, SDL_Surface *window);
};

#endif
