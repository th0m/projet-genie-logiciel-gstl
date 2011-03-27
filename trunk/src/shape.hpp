#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <SDL/SDL.h>
#include <string>

class Shape
{
    public:

        enum shape_type
        {
            Sand,
            White,
            Turbo,
            Limits,
            StartingFinishLine,
            PlayerCar
        };

        explicit Shape(Sint32 x, Sint32 y, std::string type, SDL_Surface *window);

        ~Shape();

        /* # Fonction qui nous renvoit l'etal visuel de la forme */
        bool isHidden() const;

        /* # Fonction qui permet de cacher une forme */
        void hide();

        /* # Fonction qui revele une shape */
        void unhide();

        /* # Fonction qui repositionne la forme selon ses coordonn�es */
        void actualize();

        /* # Fonction qui renvoit le coordonne x de la forme */
        Sint32 getX() const;

        /* # Fonction qui renvoit le coordonne y de la forme */
        Sint32 getY() const;

        /* # Fonction qui renvoit le type du sprite */
        std::string getType() const;

    protected:

        /* # Le type de sprite */
        std::string m_type;

        /* # Le sprite est-il visible ? */
        bool m_isHidden;

        /* # Coordonn�es de la forme */
        Sint32 m_x, m_y;

        /* # Notre sprite, et la fenetre */
        SDL_Surface *m_img, *m_window;
};

#endif