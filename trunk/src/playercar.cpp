#include "playercar.hpp"
#include "game.hpp"

#include <SDL/SDL_Image.h>
#include <cmath>
#include <list>


PlayerCar::PlayerCar(Sint32 x, Sint32 y, SDL_Surface *window)
: Shape(x, y, std::string("playercarg"), window), m_fwdspeed(Game::getFwdSpeed()), m_revspeed(m_fwdspeed / 2), m_timer(0)
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

void PlayerCar::move(SDLKey key, std::list<Limit*> &limitsH, std::list<Limit*> &limitsV, std::list<Limit*> &limitsHV)
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
                    x -= m_fwdspeed;
                break;

                case Right :
                    x += m_fwdspeed;
                break;

                case Up :
                    y -= m_fwdspeed;
                break;

                case Down :
                    y += m_fwdspeed;
                break;
            }

            break;
        }
        case SDLK_DOWN :
        {
            switch(m_currentPos)
            {
                case Left :
                    x += m_revspeed;
                break;

                case Right :
                    x -= m_revspeed;
                break;

                case Up :
                    y += m_revspeed;
                break;

                case Down :
                    y -= m_revspeed;
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

    /* # Si on n'a pas fait bouger le véhicule, on a chargé un nouveau sprite donc la fonction s'arrête ici */
    if(x == m_x && y == m_y)
        return;

    /* # On initialise diffx et diffy pour nos comparaisons pour coller au bord */
    int diffx, diffy;

    if(key == SDLK_UP)
    {
        diffx = m_fwdspeed, diffy = m_fwdspeed;
    }

    else if(key== SDLK_DOWN)
    {
        diffx = m_revspeed, diffy = m_revspeed;
    }


    /* # On recupere les precedentes coordonnes basses et droite de notre vehicule pour notre gestion de collision */
    int pvyh = m_y, pvyb = m_y + Game::getShapeSize(), pvxg = m_x, pvxd = m_x + Game::getShapeSize();

    /* # On prend les coordonnees du vehicule -> vxg : vehicule x gauche, vxd : vehicule x droite */
    int vxg = x;
    int vxd = x + Game::getShapeSize();

    /* # On prend les coordonnees du vehicule -> vyh : vehicule y haut, vyb : vehicule y bas */
    int vyh = y;
    int vyb = y + Game::getShapeSize();

    /* # On prepare le terrain pour les coordonnes des limites -> limxg : limite x gauche, limxd : limite x droite, limyh : limite y haut, limyb : limite y bas */
    int limxg =0, limxd=0, limyh=0, limyb = 0;

    /* # On commence par tester si on veut se deplacer dans une limite HV Horizontale Verticale : limite dans laquelle on peut entrer en collision verticalement ou horizontalement (Haut, Bas, Gauche, Droite) */
    for(std::list<Limit*>::iterator it = limitsHV.begin(); it != limitsHV.end();it++)
    {
        limxg = (*it)->getX();
        limxd = (*it)->getX() + Game::getShapeSize();

        limyh = (*it)->getY();
        limyb = (*it)->getY() + Game::getShapeSize();

        /* # Marche avant */
        if(key == SDLK_UP)
        {
            if(m_currentPos == Left)
            {
                if(vxg < limxd && vxg > limxg && vyh < limyb && vyb > limyh)
                {
                    diffx = fabs(pvxg - limxd);
                    isOk = false;
                }
            }
            else if (m_currentPos == Right)
            {
                if(vxd > limxg && vxd < limxd && vyh < limyb && vyb > limyh)
                {
                    diffx = fabs(pvxd - limxg);
                    isOk = false;
                }
            }
            else if(m_currentPos == Up)
            {
                if(vyh < limyb && vyh > limyh && vxg < limxd && vxd > limxg)
                {
                    diffy = fabs(pvyh - limyb);
                    isOk = false;
                }
            }
            else if (m_currentPos == Down)
            {
                if(vyb > limyh && vyb < limyb && vxg < limxd && vxd > limxg)
                {
                    diffy = fabs(pvyb - limyh);
                    isOk = false;
                }
            }
        }
        /* # Marche arriere */
        else if(key == SDLK_DOWN)
        {
            if(m_currentPos == Right)
            {
                if(vxg < limxd && vxg > limxg && vyh < limyb && vyb > limyh)
                {
                    diffx = fabs(pvxg - limxd);
                    isOk = false;
                }
            }
            else if (m_currentPos == Left)
            {
                if(vxd > limxg && vxd < limxd && vyh < limyb && vyb > limyh)
                {
                    diffx = fabs(pvxd - limxg);
                    isOk = false;
                }
            }
            else if(m_currentPos == Down)
            {
                if(vyh < limyb && vyh > limyh && vxg < limxd && vxd > limxg)
                {
                    diffy = fabs(pvyh - limyb);
                    isOk = false;
                }
            }
            else if (m_currentPos == Up)
            {
                if(vyb > limyh && vyb < limyb && vxg < limxd && vxd > limxg)
                {
                    diffy = fabs(pvyb - limyh);
                    isOk = false;
                }
            }
        }
    }

    /* # On commence par tester si on veut se deplacer dans une limite verticale : limite dans laquelle on peut entrer en collision horizontalement (Droite, Gauche) */
    for(std::list<Limit*>::iterator it = limitsV.begin(); it != limitsV.end(); it++)
    {
        limxg = (*it)->getX();
        limxd = (*it)->getX() + Game::getShapeSize();

        limyh = (*it)->getY();
        limyb = (*it)->getY() + Game::getShapeSize();

        /* # Marche avant */
        if(key == SDLK_UP)
        {
            if(m_currentPos == Left)
            {
                if(vxg < limxd && vxg > limxg)
                {
                    diffx = fabs(pvxg - limxd);
                    isOk = false;
                }
            }
            else if (m_currentPos == Right )
            {
                if(vxd > limxg && vxd < limxd)
                {
                    diffx = fabs(pvxd - limxg);
                    isOk = false;
                }
            }
        }
        /* # Marche arriere */
        else if(key == SDLK_DOWN)
        {
            if(m_currentPos == Right)
            {
                if(vxg < limxd && vxg > limxg)
                {
                    diffx = fabs(pvxg - limxd);
                    isOk = false;
                }
            }
            else if (m_currentPos == Left )
            {
                if(vxd > limxg && vxd < limxd)
                {
                    diffx = fabs(pvxd - limxg);
                    isOk = false;
                }
            }
        }
    }

    /* # On commence par tester si on veut se deplacer dans une limite horizontale : limite dans laquelle on peut entrer en collision verticalement (Haut, Bas) */
    for(std::list<Limit*>::iterator it = limitsH.begin(); it != limitsH.end(); it++)
    {
        limxg = (*it)->getX();
        limxd = (*it)->getX() + Game::getShapeSize();

        limyh = (*it)->getY();
        limyb = (*it)->getY() + Game::getShapeSize();

        /* # Marche avant */
        if(key == SDLK_UP)
        {
            if(m_currentPos == Up)
            {
                if(vyh < limyb && vyh > limyh)
                {
                    diffy = fabs(pvyh - limyb);
                    isOk = false;
                }
            }
            else if (m_currentPos == Down)
            {
                if(vyb > limyh && vyb < limyb)
                {
                    diffy = fabs(pvyb - limyh);
                    isOk = false;
                }
            }
        }
        /* # Marche arriere */
        else if(key == SDLK_DOWN)
        {
            if(m_currentPos == Down)
            {
                if(vyh < limyb && vyh > limyh)
                {
                    diffy = fabs(pvyh - limyb);
                    isOk = false;
                }
            }
            else if (m_currentPos == Up)
            {
                if(vyb > limyh && vyb < limyb)
                {
                    diffy = fabs(pvyb - limyh);
                    isOk = false;
                }
            }
        }
    }

    /* # Si on ne fonce pas dans une bordure on bouge le vehicule */
    if(isOk == true)
    {
        m_x = x, m_y = y;
    }
    /* # Si on fonce dans une bordure on va coller le vehicule a la bordure en marche avant */
    else if(key == SDLK_UP)
    {
        switch(m_currentPos)
        {
            case Left :
                if(diffx < m_fwdspeed)
                    m_x -=diffx;
            break;

            case Right :
                if(diffx < m_fwdspeed)
                    m_x +=diffx;
            break;

            case Up :
                if(diffy < m_fwdspeed)
                    m_y -=diffy;
            break;

            case Down :
                if(diffy < m_fwdspeed)
                    m_y +=diffy;
            break;
        }
    }
    /* # En marche arriere */
    else if(key == SDLK_DOWN)
    {
        switch(m_currentPos)
        {
            case Left :
                if(diffx < m_revspeed)
                if(diffx < m_revspeed)
                    m_x +=diffx;
            break;

            case Right :
                if(diffx < m_revspeed)
                    m_x -=diffx;
            break;

            case Up :
                if(diffy < m_revspeed)
                    m_y +=diffy;
            break;

            case Down :
                if(diffy < m_revspeed)
                    m_y -=diffy;
            break;
        }
    }
}

void PlayerCar::enableTurboMode()
{
    m_timer = SDL_AddTimer(Game::getTurboTime(), &PlayerCar::callback, this);
    m_fwdspeed = Game::getFwdSpeed() * 2;
}

void PlayerCar::setNormalSpeed()
{
    m_fwdspeed = Game::getFwdSpeed();
}

Uint32 PlayerCar::callback(Uint32 interval, void* param)
{
    PlayerCar* inst = (PlayerCar*)param;
    inst->setNormalSpeed();
    inst->destroyTimer();
}

void PlayerCar::destroyTimer()
{
    if(m_timer != 0)
    {
        SDL_RemoveTimer(m_timer);
        m_timer = 0;
    }
}
