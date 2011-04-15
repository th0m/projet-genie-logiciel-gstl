#ifndef R1_HPP
#define R1_HPP

#include "race.hpp"

class R1 : public Race
{
    public:

        explicit R1(SDL_Surface *window);

        ~R1();

        /* # Fonction qui va permettre de charger la course - celle-ci etant overide pour permettre de configurer les trajectoires des IAs specifiques à chaque course */
        void load();
};

#endif
