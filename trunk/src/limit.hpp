/**
 * \file limit.hpp
 * \brief Classe de l'élément qui détermine une limite sur le circuit
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 */

#ifndef LIMIT_HPP
#define LIMIT_HPP

#include "shape.hpp"

/**
 * \class Limit
 * \brief Classe qui gère l'affichage d'une limite sur la carte
*/
class Limit : public Shape
{
    public:

        /**
         * \fn explicit Limit(float x, float y, SDL_Surface *window)
         * \brief Constructeur de la classe, avec initialisation de sa position grâce à x et y et passage d'un pointeur sur la fenêtre du jeu (afin de s'y blitter)
         *
         * \param x Coordonnée en abscisse du placement de la shape
         * \param y Coordonnée en ordonnée du placement de la shape
         * \param window Pointeur sur la fenetre principale
         */
        explicit Limit(float x, float y, SDL_Surface *window);
};

#endif
