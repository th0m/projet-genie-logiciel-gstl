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

        /* # Fonction qui permet de définir les points "d'interpolation" du mouvement */
        void setPoints(std::vector<float> &points);

        /* # Fonction qui permet de faire evoluer les voitures pseudo-IAs */
        void move();

    private:

        /* # Vecteur des points d'interpolations */
        std::vector<float> m_points;

        /* # Le mouvement s'oppère en 4 étapes, cet attribut indique le courant */
        Step m_currentStep;

        /* # Les différentes surfaces de la voiture */
        SDL_Surface *m_up, *m_down, *m_right, *m_left;
};

#endif
