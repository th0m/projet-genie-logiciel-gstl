#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

class Checkpoint
{
    public:

        /* Structure d'un point */
        struct Point{
            int x, y;
        };

        explicit Checkpoint(int x1, int y1, int x2, int y2);

        bool isValidated() const;

        void check(int x, int y);

        void checkC1(int x, int y);

        void checkC2(int x, int y);

        void checkC3(int x, int y);

        void checkCF(int x, int y);

        void reset();

    private:

        /* # Booleen qui sert à savoir si un checkpoint est valide */
        bool m_isValidated;

        Point m_pointBegin, m_pointEnd;

        int m_pixelParSeconde;
};

#endif
