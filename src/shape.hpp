#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <SDL/SDL.h>
#include <string>

class Shape
{
    public:
        enum
        {
            Sand,
            White,
            Turbo,
            Limit,
            StartingFinishLine,
            PlayerCar
        } shape_type;

        explicit Shape(Uint32 x, Uint32 y, std::string shapeType, SDL_Surface *window);
        ~Shape();

        bool isHidden() const;

        void hide();
        void unhide();

        void actualize();

        std::string getType() const;

    protected:

        /* # Le sprite est-il visible ? */
        bool m_isHidden;

        /* # Coordonnées de la forme */
        Uint32 m_x, m_y;

        /* # Notre sprite, et la fenetre */
        SDL_Surface *m_img, *m_window;

        /* # Le type de sprite */
        std::string type;
};

#endif
