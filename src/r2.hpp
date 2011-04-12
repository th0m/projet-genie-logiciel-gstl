#ifndef R2_HPP
#define R2_HPP

#include "race.hpp"

class R2 : public Race
{
    public:
        explicit R2(SDL_Surface *window);

        ~R2();

        void load();
};

#endif
