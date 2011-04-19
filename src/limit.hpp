/**
 * \file limit.hpp
 * \brief Classe de l'�l�ment qui d�termine une limite sur le circuit.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 *
 * Classe qui g�re l'affichage d'une limite sur la carte.
 *
 */

#ifndef LIMIT_HPP
#define LIMIT_HPP

#include "shape.hpp"

class Limit : public Shape
{
    public:

        /**
         * \fn explicit Limit(float x, float y, SDL_Surface *window)
         * \brief Constructeur de la classe, avec initialisation de sa position gr�ce � x et y et passage d'un pointeur sur la fenetre du jeux (afin de s'y blitter).
         *
         * \param x Coordonn�e x du placement de la shape.
         * \param y Coordonn�e y du placement de la shape.
         * \param window Pointeur sur la fenetre principal.
         */
        explicit Limit(float x, float y, SDL_Surface *window);
};

#endif
