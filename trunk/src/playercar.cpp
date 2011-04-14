#include "playercar.hpp"
#include "game.hpp"
#include "iacar.hpp"

#include <SDL/SDL_Image.h>
#include <cmath>
#include <list>


PlayerCar::PlayerCar(Sint32 x, Sint32 y, SDL_Surface *window)
: Shape(x, y, std::string("playercarg"), window), m_fwdspeed(Game::getFwdSpeed()), m_revspeed(m_fwdspeed / 2), m_state(Normal), m_blocked(false), m_flaque(false)
{
    /* # On veut contrôler completement la destruction de l'objet */
    m_free = false;

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
    SDL_FreeSurface(m_left);
    SDL_FreeSurface(m_northwest);
    SDL_FreeSurface(m_northeast);
    SDL_FreeSurface(m_southwest);
    SDL_FreeSurface(m_southeast);
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

template <typename T> bool isMoveAllowed (Uint32 x, Uint32 y, std::list<T*> &lists)
{
    /* # On prepare les coordonnees des limites : limxg : limite x gauche, limxd : limite x droite, limyh : limite y haut, limyb : limite y bas */
    float limxg = 0, limxd = 0, limyh = 0, limyb = 0;
    /* # On prepare les coordonnes du vehicule : vxg : x gauche, vxd : x droite, vyh : y haut, vyb : y bas */
    float vxg = x, vxd = x + Game::getShapeSize(), vyh = y, vyb = y + Game::getShapeSize();

    /* # On test si on est dans une limite le mouvement n'est pas autorisé */
    for(typename std::list<T*>::iterator it = lists.begin(); it != lists.end();it++)
    {
        limxg = (*it)->getX();
        limxd = (*it)->getX() + Game::getShapeSize();

        limyh = (*it)->getY();
        limyb = (*it)->getY() + Game::getShapeSize();

        if(vxg < limxd && vxd > limxg && vyh < limyb && vyb > limyh)
            return false;
    }
    return true;
}

float PlayerCar::getWantedX(SDLKey key, float& fwdlatspeed, float& revlatspeed)
{
    /* # Suivant la position actuelle notre deplacement s'affichera differement */
    switch(key)
    {
        case SDLK_UP :
        {
            switch(m_currentPos)
            {
                case Left :
                    return m_x - m_fwdspeed;
                break;

                case Right :
                    return m_x + m_fwdspeed;
                break;

                case NorthWest:
                case SouthWest:
                    return m_x - fwdlatspeed;
                break;

                case NorthEast :
                case SouthEast :
                    return m_x + fwdlatspeed;
                break;
            }
            break;
        }

        case SDLK_DOWN :
        {
            switch(m_currentPos)
            {
                case Left :
                    return m_x + m_revspeed;
                break;

                case Right :
                    return m_x - m_revspeed;
                break;

                case NorthWest :
                case SouthWest :
                    return m_x + revlatspeed;
                break;

                case SouthEast :
                case NorthEast :
                    return m_x - revlatspeed;
                break;
            }
            break;
        }
        default :
        break;
    }
    return m_x;
}

float PlayerCar::getWantedY(SDLKey key, float& fwdlatspeed, float& revlatspeed)
{
    /* # Suivant la position actuelle notre deplacement s'affichera differement */
    switch(key)
    {
        case SDLK_UP :
        {
            switch(m_currentPos)
            {
                case Up :
                    return m_y - m_fwdspeed;
                break;

                case Down :
                    return m_y + m_fwdspeed;
                break;

                case NorthWest :
                case NorthEast :
                    return m_y - fwdlatspeed;
                break;

                case SouthWest :
                case SouthEast :
                    return m_y + fwdlatspeed;
                break;
            }
            break;
        }
        case SDLK_DOWN :
        {
            switch(m_currentPos)
            {
                case Up :
                    return m_y + m_revspeed;
                break;

                case Down :
                    return m_y - m_revspeed;
                break;

                case NorthWest :
                case NorthEast :
                    return m_y + revlatspeed;
                break;

                case SouthEast :
                case SouthWest :
                    return m_y - revlatspeed;
                break;
            }
            break;
        }
        default :
        break;
    }
    return m_y;
}

void PlayerCar::move(SDLKey key, std::list<Limit*> &limits, std::list<Flaque*> &flaques, std::list<IACar*> &iacars)
{
    /* # On calcule les vecteurs de deplacement lateraux */
    float fwdlatspeed = sqrt((m_fwdspeed*m_fwdspeed)/2.0), revlatspeed = sqrt((m_revspeed*m_revspeed)/2.0);

    /* # On prend les coordonnees souhaitees du vehicule -> vxg : vehicule x gauche, vxd : vehicule x droite, vyh : vehicule y haut, vyb : vehicule y bas */
    float vxg = getWantedX(key,fwdlatspeed,revlatspeed), vxd = vxg + Game::getShapeSize(), vyh = getWantedY(key,fwdlatspeed,revlatspeed), vyb = vyh + Game::getShapeSize();

    /* # On test si on roule dans une flaque */
    m_flaque = !isMoveAllowed(vxg,vyh,flaques);

    /* # On test si on fonce dans une ia ou une limite */
    m_blocked = !(isMoveAllowed(vxg,vyh,iacars) && isMoveAllowed(vxg,vyh,limits));

    /* # Si on ne fonce pas dans une bordure on bouge le vehicule */
    if(!m_blocked)
        m_x = vxg, m_y = vyh;
}

void PlayerCar::setTurboMode()
{
    m_state = TurboMode;
}

void PlayerCar::setCollisionRecovering()
{
    m_state = CollisionRecovering;
}

void PlayerCar::setFlaqueState()
{
    m_state = FlaqueState;
}

void PlayerCar::setNormalState()
{
    m_state = Normal;
}

void PlayerCar::setSpeed()
{
    m_fwdspeed = getSpeed();
}

float PlayerCar::getSpeed()
{
    if(m_state == TurboMode)
    {
        return Game::getFwdSpeed() * 3;
    }
    else if(m_state == FlaqueState || m_state == CollisionRecovering)
    {
        return Game::getFwdSpeed() / 2;
    }
    else
    {
        return Game::getFwdSpeed();
    }
}

bool PlayerCar::isBlocked()
{
    return m_blocked;
}

bool PlayerCar::isFlaque()
{
    return m_flaque;
}

bool PlayerCar::isTurbo()
{
    return m_state == TurboMode;
}
