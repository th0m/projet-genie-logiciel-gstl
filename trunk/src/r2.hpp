#ifndef R2_HPP
#define R2_HPP

#include "race.hpp"

class R2 : public Race
{
    public:

        explicit R2(SDL_Surface *window);

        ~R2();

        /* # Fonction qui va permettre de charger la course - celle-ci etant overide pour permettre de configurer les trajectoires des IAs specifiques à chaque course */
        void load();
};

#endif
