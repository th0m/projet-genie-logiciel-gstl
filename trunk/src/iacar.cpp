#include "IACar.hpp"
#include <SDL/SDL_Image.h>

IACar::IACar(float x, float y, SDL_Surface *window)
: Shape(x, y, std::string("iacarg"), window), m_currentStep(FirstStep)
{
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
}

void IACar::move()
{
    switch(m_currentStep)
    {
        case FirstStep :
        {
            if(m_x <= m_points[0])
                m_currentStep = SecondStep, m_img = m_up;
            else
                m_x--;

            break;
        }

        case SecondStep :
        {
            if(m_y <= m_points[1])
                m_currentStep = ThirdStep, m_img = m_right;
            else
                m_y--;

            break;
        }

        case ThirdStep :
        {
            if(m_x >= m_points[2])
                m_currentStep = LastStep, m_img = m_down;
            else
                m_x++;

            break;
        }

        case LastStep :
        {
            if(m_y >= m_points[3])
                m_currentStep = FirstStep, m_img = m_left;
            else
                m_y++;

            break;
        }
    }
}

void IACar::setPoints(std::vector<float> &points)
{
    m_points = points;
}
