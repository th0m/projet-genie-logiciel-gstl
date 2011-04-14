#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

#include <list>
#include "iacar.hpp"

class Checkpoint
{
    public:

        /* Structure d'un point */
        struct Point{
            int x, y;
        };

        explicit Checkpoint(float x1, float y1, float x2, float y2);

        bool isValidated() const;

        void check(float x, float y);

        void checkC1(float x, float y);

        void checkC2(float x, float y);

        void checkC3(float x, float y);

        void checkCF(float x, float y);

        int checkCFIA(float x, float y);

        void reset();


    private:

        /* # Booleen qui sert à savoir si un checkpoint est valide */
        bool m_isValidated;

        Point m_pointBegin, m_pointEnd;

        int m_pixelParSeconde;
};

#endif
