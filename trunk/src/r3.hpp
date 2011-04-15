#ifndef R3_HPP
#define R3_HPP

#include "race.hpp"

class R3 : public Race
{
    public:

        explicit R3(SDL_Surface *window);

        ~R3();

        /* # Fonction qui va permettre de charger la course - celle-ci etant overide pour permettre de configurer les trajectoires des IAs specifiques à chaque course */
        void load();
};

#endif
