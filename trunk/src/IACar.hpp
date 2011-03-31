#ifndef IACAR_HPP
#define IACAR_HPP

class IACar
{
    public:

        explicit IACar();

        virtual ~IACar();

        /* # Fonction qui permet de faire evoluer les voitures pseudo-IAs */
        virtual void move() = 0;
};

#endif
