#ifndef IACAR_HPP
#define IACAR_HPP

#include <vector>
#include "shape.hpp"

class IACar : public Shape
{
    public:

        enum Step
        {
            FirstStep,
            SecondStep,
            ThirdStep,
            LastStep
        };

        explicit IACar(float x, float y, SDL_Surface *window);

        ~IACar();

        void setPoints(std::vector<float> &points);

        /* # Fonction qui permet de faire evoluer les voitures pseudo-IAs */
        void move();

    private:

        std::vector<float> m_points;

        Step m_currentStep;
};

#endif
