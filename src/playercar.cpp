#include "playercar.hpp"
#include "game.hpp"
#include <list>
#include "limit.hpp"


PlayerCar::PlayerCar(Sint32 x, Sint32 y, SDL_Surface *window)
: Shape(x, y, std::string("playercar"), window), m_shapeSize(Game::getShapeSize())
{
}

void PlayerCar::move(SDLKey key, std::list<Limit*> &limit)
{
    bool isOk = true;
    Sint32 x = m_x, y = m_y;


    switch(key)
    {
        case SDLK_LEFT :
        {
            x -= m_shapeSize;
            break;
        }

        case SDLK_RIGHT :
        {
            x += m_shapeSize;
            break;
        }

        case SDLK_UP :
        {
            y -= m_shapeSize;
            break;
        }

        case SDLK_DOWN :
        {
            y += m_shapeSize;
            break;
        }
    }

    /* # On verifie que l'on va pas déplacer le véhicule dans une bordure */
    for(std::list<Limit*>::iterator it = limit.begin(); it != limit.end(); it++)
    {
        if(x == (*it)->getX() && y == (*it)->getY())
        {
            isOk = false;
            break;
        }
    }

    if(isOk == true)
        m_x = x, m_y = y;
}
