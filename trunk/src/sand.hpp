/**
 * \file sand.hpp
 * \brief Classe de l'élément "sable".
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 */

#ifndef SAND_HPP
#define SAND_HPP

#include "shape.hpp"

/**
 * \class Sand
 * \brief Classe qui gère l'affichage d'une shape imitation sable.
*/
class Sand : public Shape
{
    public:

        /**
         * \fn explicit Sand(float x, float y, SDL_Surface *window)
         * \brief Constructeur de la classe, avec initialisation de sa position grâce à x et y et passage d'un pointeur sur la fenetre du jeux (afin de s'y blitter).
         *
         * \param x Coordonnée x du placement de la shape.
         * \param y Coordonnée y du placement de la shape.
         * \param window Pointeur sur la fenetre principal.
         */
        explicit Sand(float x, float y, SDL_Surface *window);
};

#endif
