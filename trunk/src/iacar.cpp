#include "iacar.hpp"
#include "game.hpp"

#include <SDL/SDL_Image.h>

IACar::IACar(float x, float y, SDL_Surface *window)
: Shape(x, y, std::string("iacarg"), window), m_currentStep(FirstStep), m_difficulty(0)
{
    /* # On veut controler completement la destruction de l'objet */
    m_free = false;

    /* # On charge les differentes sprites */
    m_up = IMG_Load("sprites/iacarh");
    SDL_SetColorKey(m_up, SDL_SRCCOLORKEY, SDL_MapRGB(m_up->format, 0xff, 0xff, 0xff));

    m_down = IMG_Load("sprites/iacarb");
    SDL_SetColorKey(m_down, SDL_SRCCOLORKEY, SDL_MapRGB(m_down->format, 0xff, 0xff, 0xff));

    m_right = IMG_Load("sprites/iacard");
    SDL_SetColorKey(m_right, SDL_SRCCOLORKEY, SDL_MapRGB(m_right->format, 0xff, 0xff, 0xff));

    m_left = m_img;
}

IACar::~IACar()
{
    /* # On oublie pas de décharger proprement nos shapes */
    SDL_FreeSurface(m_up);
    SDL_FreeSurface(m_down);
    SDL_FreeSurface(m_right);
    SDL_FreeSurface(m_left);
}

void IACar::move(float playerx, float playery, std::list<IACar*> &ias)
{
    float fact = Game::getSpeedFactorIA();
    float x = m_x, y = m_y;

    switch(m_currentStep)
    {
        case FirstStep :
        {
            if(x <= m_points[0])
                m_currentStep = SecondStep, m_img = m_up;
            else
            {
                x -= fact + (m_difficulty * Game::getDifficultyIAPercentage());
                if(x < m_points[0])
                    x = m_points[0];
            }

            break;
        }

        case SecondStep :
        {
            if(y <= m_points[1])
                m_currentStep = ThirdStep, m_img = m_right;
            else
            {
                y -= fact + (m_difficulty * Game::getDifficultyIAPercentage());
                if(y < m_points[1])
                    y = m_points[1];
            }

            break;
        }

        case ThirdStep :
        {
            if(x >= m_points[2])
                m_currentStep = LastStep, m_img = m_down;
            else
            {
                x += fact + (m_difficulty * Game::getDifficultyIAPercentage());
                if(x > m_points[2])
                    x = m_points[2];
            }

            break;
        }

        case LastStep :
        {
            if(y >= m_points[3])
                m_currentStep = FirstStep, m_img = m_left;
            else
            {
                y += fact + (m_difficulty * Game::getDifficultyIAPercentage());
                if(y > m_points[3])
                    y = m_points[3];
            }

            break;
        }
    }

    if(moveAllowed(x, y, playerx, playery, ias))
        m_x = x, m_y = y;
}

bool IACar::moveAllowed(float x, float y, float playerx, float playery, std::list<IACar*> &ias)
{
    bool isAllowed = true;

     /* # On prend les coordonnees souhaitees du vehicule -> vxg : vehicule x gauche, vxd : vehicule x droite, vyh : vehicule y haut, vyb : vehicule y bas */
    float vxg = x, vxd = x + Game::getShapeSize(), vyh = y, vyb = y + Game::getShapeSize();

    /* # On prepare le terrain pour les coordonnees des limites -> limxg : limite x gauche, limxd : limite x droite, limyh : limite y haut, limyb : limite y bas */
    float limxg = playerx, limxd = playerx + Game::getShapeSize(), limyh = playery, limyb = playery + Game::getShapeSize();

    /* # On check si l'IA ne va pas foncer dans notre vehicule */
    if(vxg < limxd && vxd > limxg && vyh < limyb && vyb > limyh)
        isAllowed = false;

    /* # On check si les IAs ne vont pas s'entre foncer dedans, bien faire attention à exclure notre IA des tests, sinon on risque d'etre en collision avec *nous-même* */
    for(std::list<IACar*>::iterator it = ias.begin(); isAllowed == true && (*it) != this && it != ias.end(); it++)
    {
        limxg = (*it)->getX(), limxd = (*it)->getX() + Game::getShapeSize(), limyh = (*it)->getY(), limyb = (*it)->getY() + Game::getShapeSize();
        if(vxg < limxd && vxd > limxg && vyh < limyb && vyb > limyh)
        {
            isAllowed = false;
            break;
        }
    }

    return isAllowed;
}

void IACar::setPoints(std::vector<float> &points)
{
    m_points = points;
}

void IACar::setDifficulty(Uint8 diff)
{
    m_difficulty = diff;
}
