#ifndef IACAR_HPP
#define IACAR_HPP

#include <SDL/SDL.h>

class IACar
{
    public:

        explicit IACar();

        virtual ~IACar();

        /* # Fonction qui permet de faire evoluer les voitures pseudo-IAs - signature d'une callback de type SDL_NewTimerCallback */
        static Uint32 move(Uint32 interval, void* param);
};

#endif
