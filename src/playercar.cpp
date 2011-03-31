#include "playercar.hpp"
#include "game.hpp"

#include <SDL/SDL_Image.h>
#include <cmath>
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

void PlayerCar::move(SDLKey key, std::list<Limit*> &limitsH, std::list<Limit*> &limitsV)
{
    bool isOk = true;
    Sint32 x = m_x, y = m_y;

    /* # Suivant la touche appuyee soit on fait avancer le vehicule (fleche haut) soit on change la position (fleche droite ou gauche) */
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

    int diffx, diffy = m_speed+1;
    int vxg = x;
    int vxd = x + Game::getShapeSize();

    int vyh = y;
    int vyb = y + Game::getShapeSize();
    fprintf(stdout, "CoordVehicule : hg(%d,%d) hd(%d,%d) bg (%d,%d) bd(%d,%d)\n", vxg, vyh, vxd, vyh, vxg, vyb, vxd, vyb);

    /* # On verifie que l'on va pas déplacer le véhicule dans une bordure */
    for(std::list<Limit*>::iterator it = limitsH.begin(); it != limitsH.end(); it++)
    {

        int limxg = (*it)->getX();
        int limxd = (*it)->getX() + Game::getShapeSize();

        int limyh = (*it)->getY();
        int limyb = (*it)->getY() + Game::getShapeSize();
        fprintf(stdout, "CoordLimit : hg(%d,%d) hd(%d,%d) bg (%d,%d) bd(%d,%d)\n",limxg, limyh, limxd, limyh, limxg, limyb, limxd, limyb);


        fflush(stdout);

        //Vehicule haut a gauche dans le limit
        if(((vxg > limxg && vxg < limxd) && (vyh > limyh && vyh < limyb)) ||
        //Vehicule bas a gauche dans le limit
        ((vxg > limxg && vxg < limxd) && (vyb > limyh && vyb < limyb)) ||
        //Vehicule haut a droite dans le limit
        ((vxd > limxg && vxd < limxd) && (vyh > limyh && vyh < limyb)) ||
        //Vehicule bas a droite dans le limit
        ((vxd > limxg && vxd < limxd) && (vyb > limyh && vyb < limyb)))
        {
            fprintf(stdout,"False");
            isOk = false;
            switch(m_currentPos)
            {
                case Left :
                    diffx = fabs(m_x - limxd);
                break;

                case Right :
                    diffx = fabs(m_x - limxg);
                break;

                case Up :
                    diffy = fabs(m_y - limyb);
                break;

                case Down :
                    diffy = fabs(m_y - limyh);
                break;
            }

            fprintf(stdout,"%d %d \n",diffx,diffy);
            fflush(stdout);

            break;
        }
    }



    if(isOk == true)
    {
        m_x = x, m_y = y;
    }

    switch(m_currentPos)
    {
        case Left :
            if(diffx < m_speed)
            m_x -=diffx;
        break;

        case Right :
            if(diffx < m_speed)
            m_x +=diffx;
        break;

        case Up :
            if(diffy < m_speed)
            m_y -=diffy;
        break;

        case Down :
            if(diffy < m_speed)
            m_y +=diffy;
        break;
    }


}

void PlayerCar::enableTurboMode()
{
    m_speed *= 2;
}
