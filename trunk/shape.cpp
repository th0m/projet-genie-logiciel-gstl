#include "shape.hpp"
#include "game.hpp"

#include <stdexcept>
#include <SDL/SDL_image.h>

Shape::Shape(Uint32 x, Uint32 y, std::string shapeType, SDL_Surface *window)
: m_isHidden(false), m_x(x), m_y(y), m_img(NULL), m_window(window)
{
    std::string path("sprites/" + shapeType);

    /* # On charge l'image associe */
    m_img = IMG_Load(path.c_str());

    if(m_img == NULL)
    {
        /* # On renseigne les logs */
        fprintf(stderr, "[%s:%d] IMG_Load failed with this error code : %s.\n", __FUNCTION__, __LINE__, SDL_GetError());

        /* # On previent bien de l'erreur de chargement */
        throw std::runtime_error("IMG_Load failed.");
    }

    /* # On affiche notre sprite */
    actualize();
}

Shape::~Shape()
{
    SDL_Rect rec = { m_x, m_y };

    rec.h = rec.w = m_img->h;

    /* # On decharge proprement l'image */
    SDL_FreeSurface(m_img);

    /* # On y met du blanc à la place */
    SDL_FillRect(m_window, &rec, SDL_MapRGB(m_window->format, 0xff, 0xff, 0xff));
}

void Shape::actualize()
{
    SDL_Rect pos = { m_x, m_y };

    /* # On "colle" la surface sur notre window */
    SDL_BlitSurface(m_img, NULL, m_window, &pos);

    /* # On met à jour l'ecran */
    SDL_Flip(m_window);

}

bool Shape::isHidden() const
{
    return m_isHidden;
}

void Shape::hide()
{
    SDL_Rect rec = { m_x, m_y, m_img->h, m_img->h };

    if(m_isHidden == true)
        return;

    /* # On y met du blanc à la place, pour cacher le sprite */
    SDL_FillRect(m_window, &rec, SDL_MapRGB(m_window->format, 0xff, 0xff, 0xff));

    /* # On actualise */
    SDL_Flip(m_window);

    m_isHidden = true;
}

void Shape::unhide()
{
    if(m_isHidden == false)
        return;

    /* # On replace notre sprite */
    actualize();
}
