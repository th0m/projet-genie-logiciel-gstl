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

    m_northwest = IMG_Load("sprites/playercarno");
    SDL_SetColorKey(m_northwest, SDL_SRCCOLORKEY, SDL_MapRGB(m_right->format, 0xff, 0xff, 0xff));

    m_northeast = IMG_Load("sprites/playercarne");
    SDL_SetColorKey(m_northeast, SDL_SRCCOLORKEY, SDL_MapRGB(m_right->format, 0xff, 0xff, 0xff));

    m_southwest = IMG_Load("sprites/playercarso");
    SDL_SetColorKey(m_southwest, SDL_SRCCOLORKEY, SDL_MapRGB(m_right->format, 0xff, 0xff, 0xff));

    m_southeast = IMG_Load("sprites/playercarse");
    SDL_SetColorKey(m_southeast, SDL_SRCCOLORKEY, SDL_MapRGB(m_right->format, 0xff, 0xff, 0xff));

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
    /* # Ici on est charge de blitter le nouveau sprite de position selon la touche appuyee */

    switch(m_currentPos)
    {
        case Left :
        {
            if(key == SDLK_LEFT)
                m_img = m_southwest, m_currentPos = SouthWest;
            else
                m_img = m_northwest, m_currentPos = NorthWest;

            break;
        }
        case NorthWest :
        {
            if(key == SDLK_LEFT)
                m_img = m_left, m_currentPos = Left;
            else
                m_img = m_up, m_currentPos = Up;

            break;
        }
        case Up :
        {
            if(key == SDLK_LEFT)
                m_img = m_northwest, m_currentPos = NorthWest;
            else
                m_img = m_northeast, m_currentPos = NorthEast;

            break;
        }
        case NorthEast :
        {
            if(key == SDLK_LEFT)
                m_img = m_up, m_currentPos = Up;
            else
                m_img = m_right, m_currentPos = Right;

            break;
        }
        case Right :
        {
            if(key == SDLK_LEFT)
                m_img = m_northeast, m_currentPos = NorthEast;
            else
                m_img = m_southeast, m_currentPos = SouthEast;

            break;
        }
        case SouthEast :
        {
            if(key == SDLK_LEFT)
                m_img = m_right, m_currentPos = Right;
            else
                m_img = m_down, m_currentPos = Down;

            break;
        }
        case Down :
        {
            if(key == SDLK_LEFT)
                m_img = m_southeast, m_currentPos = SouthEast;
            else
                m_img = m_southwest, m_currentPos = SouthWest;

            break;
        }
        case SouthWest :
        {
            if(key == SDLK_LEFT)
                m_img = m_down, m_currentPos = Down;
            else
                m_img = m_left, m_currentPos = Left;

            break;
        }

        default :
        break;
    }
}

void PlayerCar::move(SDLKey key, std::list<Limit*> &limitsH, std::list<Limit*> &limitsV, std::list<Limit*> &limitsHV, std::list<Flaque*> &flaques)
{
    bool isOk = true;
    bool isFlaque = false;
    float x = m_x, y = m_y;

    /* # Composantes x et y pour conserver la vitesse en diagonale */
    float fwdlatspeed = sqrt((m_fwdspeed*m_fwdspeed)/2.0), revlatspeed = sqrt((m_revspeed*m_revspeed)/2.0);

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

                case NorthWest :
                    x -= fwdlatspeed;
                    y -= fwdlatspeed;
                break;

                case NorthEast :
                    x += fwdlatspeed;
                    y -= fwdlatspeed;
                break;

                case SouthEast :
                    x += fwdlatspeed;
                    y += fwdlatspeed;
                break;

                case SouthWest :
                    x -= fwdlatspeed;
                    y += fwdlatspeed;
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

                case NorthWest :
                    x += revlatspeed;
                    y += revlatspeed;
                break;

                case NorthEast :
                    x -= revlatspeed;
                    y += revlatspeed;
                break;

                case SouthEast :
                    x -= revlatspeed;
                    y -= revlatspeed;
                break;

                case SouthWest :
                    x += revlatspeed;
                    y -= revlatspeed;
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

    /* # Si on n'a pas fait bouger le véhicule, on a charge un nouveau sprite donc la fonction s'arrête ici */
    if(x == m_x && y == m_y)
        return;

    /* # On initialise diffx et diffy pour nos comparaisons pour coller au bord */
    float diffx, diffy;

    if(key == SDLK_UP)
    {
        if(m_currentPos == Left || m_currentPos == Right || m_currentPos == Up || m_currentPos == Down)
        {
            diffx = m_fwdspeed, diffy = m_fwdspeed;
        }
        else if (m_currentPos == NorthEast || m_currentPos == NorthWest || m_currentPos == SouthEast || m_currentPos == SouthWest)
        {
            diffx = fwdlatspeed, diffy = fwdlatspeed;
        }
    }

    else if(key == SDLK_DOWN)
    {
        if(m_currentPos == Left || m_currentPos == Right || m_currentPos == Up || m_currentPos == Down)
        {
            diffx = m_revspeed, diffy = m_revspeed;
        }
        else if (m_currentPos == NorthEast || m_currentPos == NorthWest || m_currentPos == SouthEast || m_currentPos == SouthWest)
        {
            diffx = revlatspeed, diffy = revlatspeed;
        }

    }


    /* # On recupere les precedentes coordonnes basses et droite de notre vehicule pour notre gestion de collision pvyh : precedent y haut, pvyb : ..., pvxg : precedent x gauche, pvxd : ... */
    float pvyh = m_y, pvyb = m_y + Game::getShapeSize(), pvxg = m_x, pvxd = m_x + Game::getShapeSize();

    /* # On prend les coordonnees du vehicule -> vxg : vehicule x gauche, vxd : vehicule x droite, vyh : vehicule y haut, vyb : vehicule y bas */
    float vxg = x, vxd = x + Game::getShapeSize(), vyh = y, vyb = y + Game::getShapeSize();

    /* # On prepare le terrain pour les coordonnes des limites -> limxg : limite x gauche, limxd : limite x droite, limyh : limite y haut, limyb : limite y bas */
    float limxg = 0, limxd = 0, limyh = 0, limyb = 0;

    /* # On test si on est dans une flaque */
    for(std::list<Flaque*>::iterator it = flaques.begin(); it != flaques.end();it++)
    {
        limxg = (*it)->getX();
        limxd = (*it)->getX() + Game::getShapeSize();

        limyh = (*it)->getY();
        limyb = (*it)->getY() + Game::getShapeSize();

        /* # Marche avant */
        if(key == SDLK_UP)
            if(m_currentPos == Left)
                if(vxg < limxd && vxg > limxg && vyh < limyb && vyb > limyh)
                    isFlaque=true;
            else if (m_currentPos == Right)
                if(vxd > limxg && vxd < limxd && vyh < limyb && vyb > limyh)
                    isFlaque=true;
            else if(m_currentPos == Up)
                if(vyh < limyb && vyh > limyh && vxg < limxd && vxd > limxg)
                    isFlaque=true;
            else if (m_currentPos == Down)
                if(vyb > limyh && vyb < limyb && vxg < limxd && vxd > limxg)
                    isFlaque=true;
            else if(m_currentPos == NorthWest)
                if(vxg < limxd && vxg > limxg && vyh < limyb && vyb > limyh)
                    isFlaque=true;
                if(vyh < limyb && vyh > limyh && vxg < limxd && vxd > limxg)
                    isFlaque=true;
            else if(m_currentPos == NorthEast)
                if(vxd > limxg && vxd < limxd && vyh < limyb && vyb > limyh)
                    isFlaque=true;
                if(vyh < limyb && vyh > limyh && vxg < limxd && vxd > limxg)
                    isFlaque=true;
            else if(m_currentPos == SouthEast)
                if(vxd > limxg && vxd < limxd && vyh < limyb && vyb > limyh)
                    isFlaque=true;
                if(vyb > limyh && vyb < limyb && vxg < limxd && vxd > limxg)
                    isFlaque=true;
            else if(m_currentPos == SouthWest)
                if(vxg < limxd && vxg > limxg && vyh < limyb && vyb > limyh)
                    isFlaque=true;
                if(vyb > limyh && vyb < limyb && vxg < limxd && vxd > limxg)
                    isFlaque=true;
        /* # Marche arriere */
        else if(key == SDLK_DOWN)
            if(m_currentPos == Right )
                if(vxg < limxd && vxg > limxg && vyh < limyb && vyb > limyh)
                    isFlaque=true;
            else if (m_currentPos == Left)
                if(vxd > limxg && vxd < limxd && vyh < limyb && vyb > limyh)
                    isFlaque=true;
            else if(m_currentPos == Down)
                if(vyh < limyb && vyh > limyh && vxg < limxd && vxd > limxg)
                    isFlaque=true;
            else if (m_currentPos == Up)
                if(vyb > limyh && vyb < limyb && vxg < limxd && vxd > limxg)
                    isFlaque=true;
            else if(m_currentPos == SouthEast)
                if(vxg < limxd && vxg > limxg && vyh < limyb && vyb > limyh)
                    isFlaque=true;
                if(vyh < limyb && vyh > limyh && vxg < limxd && vxd > limxg)
                    isFlaque=true;
            else if(m_currentPos == SouthWest)
                if(vxd > limxg && vxd < limxd && vyh < limyb && vyb > limyh)
                    isFlaque=true;
                if(vyh < limyb && vyh > limyh && vxg < limxd && vxd > limxg)
                    isFlaque=true;
            else if(m_currentPos == NorthWest)
                if(vxd > limxg && vxd < limxd && vyh < limyb && vyb > limyh)
                    isFlaque=true;
                if(vyb > limyh && vyb < limyb && vxg < limxd && vxd > limxg)
                    isFlaque=true;
            else if(m_currentPos == NorthEast)
                if(vxg < limxd && vxg > limxg && vyh < limyb && vyb > limyh)
                    isFlaque=true;
                if(vyb > limyh && vyb < limyb && vxg < limxd && vxd > limxg)
                    isFlaque=true;
    }
    if(isFlaque)
    {
        if(key == SDLK_UP)
            m_fwdspeed=Game::getFwdSpeed()/2;
        if(key == SDLK_DOWN)
            m_revspeed=Game::getRevSpeed()/2;
    }
    else
    {
        if(key == SDLK_UP)
            m_fwdspeed=Game::getFwdSpeed();
        if(key == SDLK_DOWN)
            m_revspeed=Game::getRevSpeed();
    }



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
            else if(m_currentPos == NorthWest)
            {
                if(vxg < limxd && vxg > limxg && vyh < limyb && vyb > limyh)
                {
                    diffx = fabs(pvxg - limxd);
                    isOk = false;
                }
                if(vyh < limyb && vyh > limyh && vxg < limxd && vxd > limxg)
                {
                    diffy = fabs(pvyh - limyb);
                    isOk = false;
                }
            }
            else if(m_currentPos == NorthEast)
            {
                if(vxd > limxg && vxd < limxd && vyh < limyb && vyb > limyh)
                {
                    diffx = fabs(pvxd - limxg);
                    isOk = false;
                }
                if(vyh < limyb && vyh > limyh && vxg < limxd && vxd > limxg)
                {
                    diffy = fabs(pvyh - limyb);
                    isOk = false;
                }
            }
            else if(m_currentPos == SouthEast)
            {
                if(vxd > limxg && vxd < limxd && vyh < limyb && vyb > limyh)
                {
                    diffx = fabs(pvxd - limxg);
                    isOk = false;
                }
                if(vyb > limyh && vyb < limyb && vxg < limxd && vxd > limxg)
                {
                    diffy = fabs(pvyb - limyh);
                    isOk = false;
                }

            }
            else if(m_currentPos == SouthWest)
            {
                if(vxg < limxd && vxg > limxg && vyh < limyb && vyb > limyh)
                {
                    diffx = fabs(pvxg - limxd);
                    isOk = false;
                }
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
            if(m_currentPos == Right )
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
            else if(m_currentPos == SouthEast)
            {
                if(vxg < limxd && vxg > limxg && vyh < limyb && vyb > limyh)
                {
                    diffx = fabs(pvxg - limxd);
                    isOk = false;
                }
                if(vyh < limyb && vyh > limyh && vxg < limxd && vxd > limxg)
                {
                    diffy = fabs(pvyh - limyb);
                    isOk = false;
                }
            }
            else if(m_currentPos == SouthWest)
            {
                if(vxd > limxg && vxd < limxd && vyh < limyb && vyb > limyh)
                {
                    diffx = fabs(pvxd - limxg);
                    isOk = false;
                }
                if(vyh < limyb && vyh > limyh && vxg < limxd && vxd > limxg)
                {
                    diffy = fabs(pvyh - limyb);
                    isOk = false;
                }
            }
            else if(m_currentPos == NorthWest)
            {
                if(vxd > limxg && vxd < limxd && vyh < limyb && vyb > limyh)
                {
                    diffx = fabs(pvxd - limxg);
                    isOk = false;
                }
                if(vyb > limyh && vyb < limyb && vxg < limxd && vxd > limxg)
                {
                    diffy = fabs(pvyb - limyh);
                    isOk = false;
                }

            }
            else if(m_currentPos == NorthEast)
            {
                if(vxg < limxd && vxg > limxg && vyh < limyb && vyb > limyh)
                {
                    diffx = fabs(pvxg - limxd);
                    isOk = false;
                }
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
            else if (m_currentPos == Right)
            {
                if(vxd > limxg && vxd < limxd)
                {
                    diffx = fabs(pvxd - limxg);
                    isOk = false;
                }
            }
            else if(m_currentPos == NorthWest)
            {
                if(vxg < limxd && vxg > limxg)
                {
                    diffx = fabs(pvxg - limxd);
                    isOk = false;
                }
            }
            else if(m_currentPos == NorthEast)
            {
                if(vxd > limxg && vxd < limxd)
                {
                    diffx = fabs(pvxd - limxg);
                    isOk = false;
                }
            }
            else if(m_currentPos == SouthEast)
            {
                if(vxd > limxg && vxd < limxd)
                {
                    diffx = fabs(pvxd - limxg);
                    isOk = false;
                }

            }
            else if(m_currentPos == SouthWest)
            {
                if(vxg < limxd && vxg > limxg)
                {
                    diffx = fabs(pvxg - limxd);
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
            else if(m_currentPos == SouthEast)
            {
                if(vxg < limxd && vxg > limxg)
                {
                    diffx = fabs(pvxg - limxd);
                    isOk = false;
                }
            }
            else if(m_currentPos == SouthWest)
            {
                if(vxd > limxg && vxd < limxd)
                {
                    diffx = fabs(pvxd - limxg);
                    isOk = false;
                }
            }
            else if(m_currentPos == NorthWest)
            {
                if(vxd > limxg && vxd < limxd)
                {
                    diffx = fabs(pvxd - limxg);
                    isOk = false;
                }

            }
            else if(m_currentPos == NorthEast)
            {
                if(vxg < limxd && vxg > limxg)
                {
                    diffx = fabs(pvxg - limxd);
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
            else if(m_currentPos == NorthWest)
            {
                if(vyh < limyb && vyh > limyh)
                {
                    diffy = fabs(pvyh - limyb);
                    isOk = false;
                }
            }
            else if(m_currentPos == NorthEast)
            {
                if(vyh < limyb && vyh > limyh)
                {
                    diffy = fabs(pvyh - limyb);
                    isOk = false;
                }
            }
            else if(m_currentPos == SouthEast)
            {
                if(vyb > limyh && vyb < limyb)
                {
                    diffy = fabs(pvyb - limyh);
                    isOk = false;
                }

            }
            else if(m_currentPos == SouthWest)
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
            else if(m_currentPos == SouthEast)
            {
                if(vyh < limyb && vyh > limyh)
                {
                    diffy = fabs(pvyh - limyb);
                    isOk = false;
                }
            }
            else if(m_currentPos == SouthWest)
            {
                if(vyh < limyb && vyh > limyh)
                {
                    diffy = fabs(pvyh - limyb);
                    isOk = false;
                }
            }
            else if(m_currentPos == NorthWest)
            {
                if(vyb > limyh && vyb < limyb)
                {
                    diffy = fabs(pvyb - limyh);
                    isOk = false;
                }

            }
            else if(m_currentPos == NorthEast)
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

            case NorthWest :
                if(diffx < fwdlatspeed)
                    m_x -= diffx;
                if(diffy < fwdlatspeed)
                    m_y -= diffy;
            break;

            case NorthEast :
                if(diffx < fwdlatspeed)
                    m_x += diffx;
                if(diffy < fwdlatspeed)
                    m_y -= diffy;
            break;

            case SouthEast :
                if(diffx < fwdlatspeed)
                    m_x += diffx;
                if(diffy < fwdlatspeed)
                    m_y += diffy;
            break;

            case SouthWest :
                if(diffx < fwdlatspeed)
                    m_x -= diffx;
                if(diffy < fwdlatspeed)
                    m_y += diffy;
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

            case NorthWest :
                if(diffx < revlatspeed)
                   m_x += diffx;
                if(diffy < revlatspeed)
                    m_y += diffy;
            break;

            case NorthEast :
                if(diffx < revlatspeed)
                    m_x -= diffx;
                if(diffy < revlatspeed)
                    m_y += diffy;
            break;

            case SouthEast :
                if(diffx < revlatspeed)
                    m_x -= diffx;
                if(diffy < revlatspeed)
                    m_y -= diffy;
            break;

            case SouthWest :
                if(diffx < revlatspeed)
                    m_x += diffx;
                if(diffy < revlatspeed)
                    m_y -= diffy;
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
