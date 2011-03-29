#include "playercar.hpp"
#include "game.hpp"

#include <SDL/SDL_Image.h>
#include <list>


PlayerCar::PlayerCar(Sint32 x, Sint32 y, SDL_Surface *window)
: Shape(x, y, std::string("playercarg"), window), m_speed(5)
{
    /* # On charge les differentes sprites */
    m_up = IMG_Load("sprites/playercarh");
    SDL_SetColorKey(m_up, SDL_SRCCOLORKEY, SDL_MapRGB(m_up->format, 0xff, 0xff, 0xff));

    m_down = IMG_Load("sprites/playercarb");
    SDL_SetColorKey(m_down, SDL_SRCCOLORKEY, SDL_MapRGB(m_down->format, 0xff, 0xff, 0xff));

    m_right = IMG_Load("sprites/playercard");
    SDL_SetColorKey(m_right, SDL_SRCCOLORKEY, SDL_MapRGB(m_right->format, 0xff, 0xff, 0xff));

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

    switch(m_currentPos)
    {
        case Left :
        {
            if(key == SDLK_LEFT)
                m_img = m_down, m_currentPos = Down;
            else
                m_img = m_up, m_currentPos = Up;

            break;
        }

        case Right :
        {
            if(key == SDLK_LEFT)
                m_img = m_up, m_currentPos = Up;
            else
                m_img = m_down, m_currentPos = Down;

            break;
        }

        case Up :
        {
            if(key == SDLK_LEFT)
                m_img = m_left, m_currentPos = Left;
            else
                m_img = m_right, m_currentPos = Right;

            break;
        }

        case Down :
        {
            if(key == SDLK_LEFT)
                m_img = m_right, m_currentPos = Right;
            else
                m_img = m_left, m_currentPos = Left;

            break;
        }

        default :
        break;
    }
}

void PlayerCar::move(SDLKey key, std::list<Limit*> &limit)
{
    bool isOk = true;
    Sint32 x = m_x, y = m_y;

    /* # Suivant la touche appuyer soit on fait avancer le vehicule (fleche haut) soit on change la position (fleche droite ou gauche) */
    switch(key)
    {
        case SDLK_UP :
        {
            switch(m_currentPos)
            {
                case Left :
                    x -= m_speed;
                break;

                case Right :
                    x += m_speed;
                break;

                case Up :
                    y -= m_speed;
                break;

                case Down :
                    y += m_speed;
                break;
            }

            break;
        }

        case SDLK_LEFT :
        case SDLK_RIGHT :
            loadAnotherPosition(key);
        break;

        default :
            break;

    }

    /* # Si on a pas fait bouger le véhicule, on a chargé un nouveau sprite donc la fonction s'arrête ici */
    if(x == m_x && y == m_y)
        return;

    fprintf(stdout, "CoordV : %d %d\n", x, y);

    /* # On verifie que l'on va pas déplacer le véhicule dans une bordure */
    for(std::list<Limit*>::iterator it = limit.begin(); it != limit.end(); it++)
    {
        int cordxmax = (*it)->getX() + Game::getShapeSize();
        int cordymax = (*it)->getY() + Game::getShapeSize();

        fprintf(stdout, "CoordLimit : %d-%d %d-%d\n", (*it)->getX(), cordxmax, (*it)->getY(), cordymax);


        if( (x >= (*it)->getX() && x <= cordxmax) &&
            (y >= (*it)->getY() && y <= cordymax) )
        {
            isOk = false;
            break;
        }
    }

    if(isOk == true)
        m_x = x, m_y = y;
}

void PlayerCar::enableTurboMode()
{
    m_speed *= 2;
}
