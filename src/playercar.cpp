#include "playercar.hpp"
#include "game.hpp"

#include <SDL/SDL_Image.h>
#include <list>


PlayerCar::PlayerCar(Sint32 x, Sint32 y, SDL_Surface *window)
: Shape(x, y, std::string("playercarg"), window), m_shapeSize(Game::getShapeSize())
{
    /* # On charge les differentes sprites */
    m_up = IMG_Load("sprites/playercarh");
    m_down = IMG_Load("sprites/playercarb");
    m_right = IMG_Load("sprites/playercard");
    m_left = m_img;

    m_currentPos = Left;
}


PlayerCar::~PlayerCar()
{
    /* # On decharge proprement les images */
    SDL_FreeSurface(m_up);
    SDL_FreeSurface(m_down);
    SDL_FreeSurface(m_right);
}

void PlayerCar::loadAnotherPosition(SDLKey key)
{
    /* # Ici on est charge de blitter le nouveau sprite de position selon la touche appuye */
    switch(key)
    {
        case SDLK_LEFT :
            m_img = m_left, m_currentPos = Left;
        break;

        case SDLK_RIGHT :
            m_img = m_right, m_currentPos = Right;
        break;

        case SDLK_DOWN :
            m_img = m_down, m_currentPos = Down;
        break;

        case SDLK_UP :
            m_img = m_up, m_currentPos = Up;
        break;

        default :
        break;
    }
}

void PlayerCar::move(SDLKey key, std::list<Limit*> &limit)
{
    bool isOk = true;
    Sint32 x = m_x, y = m_y;

    switch(key)
    {
        case SDLK_LEFT :
        {
            if(m_currentPos == Left)
                x -= m_shapeSize;
            break;
        }

        case SDLK_RIGHT :
        {
            if(m_currentPos == Right)
                x += m_shapeSize;
            break;
        }

        case SDLK_UP :
        {
            if(m_currentPos == Up)
                y -= m_shapeSize;
            break;
        }

        case SDLK_DOWN :
        {
            if(m_currentPos == Down)
                y += m_shapeSize;
            break;
        }
    }

    /* # Si les composantes sont egales ça veut dire qu'il faut que l'on charge un nouveau sprite de position */
    if(x == m_x && y == m_y)
    {
        loadAnotherPosition(key);
        return;
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
