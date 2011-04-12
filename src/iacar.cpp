#include "IACar.hpp"

IACar::IACar(float x, float y, SDL_Surface *window)
: Shape(x, y, std::string("iacarg"), window), m_currentStep(FirstStep)
{
}

IACar::~IACar()
{
}

void IACar::move()
{
    switch(m_currentStep)
    {
        case FirstStep :
        {
            if(m_x <= m_points[0])
                m_currentStep = SecondStep;
            else
                m_x--;
            break;
        }

        case SecondStep :
        {
            if(m_y <= m_points[1])
                m_currentStep = ThirdStep;
            else
                m_y--;
            break;
        }

        case ThirdStep :
        {
            if(m_x >= m_points[2])
                m_currentStep = LastStep;
            else
                m_x++;
            break;
        }

        case LastStep :
        {
            if(m_y >= m_points[3])
                m_currentStep = FirstStep;
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
