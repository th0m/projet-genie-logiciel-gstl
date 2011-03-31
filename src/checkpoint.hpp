#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

class Checkpoint
{
    public:

        explicit Checkpoint();

        bool isValidated() const;

    private:

        /* # Booleen qui sert � savoir si un checkpoint est valide */
        bool m_isValidated;
};

#endif
