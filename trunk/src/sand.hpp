/**
 * \file sand.hpp
 * \brief Classe de l'�l�ment "sable".
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 *
 * Classe qui g�re l'affichage d'une shape imitation sable.
 *
 */

#ifndef SAND_HPP
#define SAND_HPP

#include "shape.hpp"

class Sand : public Shape
{
    public:

        /**
         * \fn explicit Sand(float x, float y, SDL_Surface *window)
         * \brief Constructeur de la classe, avec initialisation de sa position gr�ce � x et y et passage d'un pointeur sur la fenetre du jeux (afin de s'y blitter).
         *
         * \param x Coordonn�e x du placement de la shape.
         * \param y Coordonn�e y du placement de la shape.
         * \param window Pointeur sur la fenetre principal.
         */
        explicit Sand(float x, float y, SDL_Surface *window);
};

#endif
