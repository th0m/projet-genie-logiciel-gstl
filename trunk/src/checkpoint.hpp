#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

class Checkpoint
{
    public:

        explicit Checkpoint(int x1, int y1, int x2, int y2);

        bool isValidated() const;

        void check(int x, int y);

        void reset();

        /* Structure d'un point */
        struct m_point{
            int x,y;
        };

    private:

        /* # Booleen qui sert à savoir si un checkpoint est valide */
        bool m_isValidated;
        m_point m_pointBegin, m_pointEnd;
};

#endif
