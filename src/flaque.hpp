/**
 * \file flaque.hpp
 * \brief Classe de l'�l�ment flaque d'eau.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 *
 * Classe qui g�re l'affichage d'une flaque d'eau sur la carte.
 *
 */

#ifndef FLAQUE_HPP
#define FLAQUE_HPP

#include "shape.hpp"

class Flaque : public Shape
{
    public:

        /**
         * \fn explicit Flaque(float x, float y, SDL_Surface *window)
         * \brief Constructeur de la classe, avec initialisation de sa position gr�ce � x et y et passage d'un pointeur sur la fenetre du jeux (afin de s'y blitter).
         *
         * \param x Coordonn�e x du placement de la shape.
         * \param y Coordonn�e y du placement de la shape.
         * \param window Pointeur sur la fenetre principal.
         */
        explicit Flaque(float x, float y, SDL_Surface *window);
};

#endif
