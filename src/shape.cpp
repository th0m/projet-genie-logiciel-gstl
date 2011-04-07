#include "shape.hpp"
#include "game.hpp"

#include "sand.hpp"
#include "white.hpp"
#include "turbo.hpp"
#include "limit.hpp"
#include "startingfinishline.hpp"
#include "playercar.hpp"

#include <stdexcept>
#include <SDL/SDL_image.h>

Shape::Shape(float x, float y, std::string type, SDL_Surface *window)
: m_type(type), m_isHidden(false), m_x(x), m_y(y), m_img(NULL), m_window(window)
{
    std::string path("sprites/" + m_type);

    /* # On charge l'image associe */
    m_img = IMG_Load(path.c_str());

    if(m_img == NULL)
    {
        /* # On renseigne les logs */
        fprintf(stderr, "[%s:%d] IMG_Load failed with this error code : %s.\n", __FUNCTION__, __LINE__, SDL_GetError());

        /* # On previent bien de l'erreur de chargement */
        throw std::runtime_error("IMG_Load failed.");
    }

    /* # Si il s'agit d'une voiture on active la transparence */
    if(m_type == "playercarg")
        SDL_SetColorKey(m_img, SDL_SRCCOLORKEY, SDL_MapRGB(m_img->format, 0xff, 0xff, 0xff));


    /* # On affiche notre sprite */
    actualize();

    SDL_Flip(m_window);
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

Shape* Shape::getInstance(shape_type type, float x, float y, SDL_Surface *window)
{
    Shape *ptr = NULL;

    switch(type)
    {
            case LIMITHV :
            case LIMITV :
            case LIMITH :
            {
                ptr = new Limit(x, y, window);
                break;
            }

            case SAND :
            {
                ptr = new Sand(x, y, window);
                break;
            }

            case WHITE :
            {
                ptr = new White(x, y, window);
                break;
            }

            case TURBO :
            {
                ptr = new Turbo(x, y, window);
                break;
            }

            case STARTINGFINISHLINE :
            {
                ptr = new StartingFinishLine(x, y, window);
                break;
            }

            case PLAYERCAR :
            {
                ptr = new PlayerCar(x, y, window);
                break;
            }
    }

    return ptr;
}


void Shape::actualize()
{
    SDL_Rect pos = { m_x, m_y };

    /* # On "colle" la surface sur notre window */
    SDL_BlitSurface(m_img, NULL, m_window, &pos);
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

float Shape::getX() const
{
    return m_x;
}

float Shape::getY() const
{
    return m_y;
}

std::string Shape::getType() const
{
    return m_type;
}
