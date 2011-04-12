#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <SDL/SDL.h>
#include <string>

class Shape
{
    public:

        enum shape_type
        {
            SAND,
            WHITE,
            TURBO,
            LIMIT,
            STARTINGFINISHLINE,
            PLAYERCAR,
            FLAQUE,
            IACAR
        };

        explicit Shape(float x, float y, std::string type, SDL_Surface *window);

        ~Shape();

        /* # Fonction qui nous renvoit l'etal visuel de la forme */
        bool isHidden() const;

        /* # Fonction qui permet de cacher une forme */
        void hide();

        /* # Fonction qui revele une shape */
        void unhide();

        /* # Fonction qui repositionne la forme selon ses coordonnées */
        void actualize();

        /* # Fonction qui renvoit le coordonne x de la forme */
        float getX() const;

        /* # Fonction qui renvoit le coordonne y de la forme */
        float getY() const;

        /* # Fonction qui renvoit le type du sprite */
        std::string getType() const;

        /* # Factory design pattern - fonction d'instanciation */
        static Shape* getInstance(Shape::shape_type type, float x, float y, SDL_Surface *window);

    protected:

        /* # Le type de sprite */
        std::string m_type;

        /* # Le sprite est-il visible ? */
        bool m_isHidden;

        /* # Coordonnées de la forme */
        float m_x, m_y;

        /* # Notre sprite, et la fenetre */
        SDL_Surface *m_img, *m_window;
};

#endif
