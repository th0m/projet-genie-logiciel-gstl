#ifndef R3_HPP
#define R3_HPP

#include "race.hpp"

class R3 : public Race
{
    public:
        explicit R3(SDL_Surface *window);

        ~R3();

        void load();
};

#endif
