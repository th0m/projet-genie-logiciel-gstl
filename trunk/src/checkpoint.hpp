/**
 * \file checkpoint.h
 * \brief Gestion des checkpoints.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 *
 * Classe qui va permettre de g�rer les checkpoints plac�s dans les diff�rentes courses.
 *
 */

#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

#include <list>
#include "iacar.hpp"

class Checkpoint
{
    public:

        /**
         * \struct Point
         * \brief desc
         *
         * breve
         * desc
         */
        struct Point{
            float x; /*!< desc */
            float y; /*!< desc */
        };


        /**
         * \enum CompetitorPosition
         * \brief desc
         *
         * breve
         * desc
         */
        enum CompetitorPosition
        {
            BeforeFinishLine, /*!< desc */
            AfterFinishLine, /*!< desc */
            Others /*!< desc */
        };

        /**
         * \fn explicit Checkpoint(float x1, float y1, float x2, float y2)
         * \brief Constructeur de la classe, avec initialisation des deux points pour former une "ligne" de checkpoint.
         *
         * \param x1 Coordonn�e x du premier point.
         * \param y1 Coordonn�e y du premier point.
         * \param x2 Coordonn�e x du second point.
         * \param y2 Coordonn�e y du second point.
         */
        explicit Checkpoint(float x1, float y1, float x2, float y2);

        /**
         * \fn bool isValidated() const
         * \brief Fonction permettant de savoir si un .
         *
         * \return Renvoit un booleen qui va nous renseigner si le checkpoint � ete valide ou non.
         */
        bool isValidated() const;

        /**
         * \fn void check(float x, float y)
         * \brief Fonction permettant de savoir si un .
         *
         * \param x desc
         * \param y desc
         * \return desc
         */
         void check(float x, float y);

        /**
         * \fn void checkC1(float x, float y)
         * \brief Fonction permettant de savoir si un .
         *
         * \param x desc
         * \param y desc
         * \return desc
         */
         void checkC1(float x, float y);

        /**
         * \fn void checkC2(float x, float y)
         * \brief Fonction permettant de savoir si un .
         *
         * \param x desc
         * \param y desc
         * \return desc
         */
        void checkC2(float x, float y);

        /**
         * \fn void checkC3(float x, float y)
         * \brief Fonction permettant de savoir si un .
         *
         * \param x desc
         * \param y desc
         * \return desc
         */
        void checkC3(float x, float y);

        /**
         * \fn void checkCF(float x, float y)
         * \brief Fonction permettant de savoir si un .
         *
         * \param x desc
         * \param y desc
         * \return desc
         */
        void checkCF(float x, float y);

        /**
         * \fn CompetitorPosition checkCFIA(float x, float y)
         * \brief desc
         *
         * \param x desc
         * \param y desc
         * \return desc
         */
        CompetitorPosition checkCFIA(float x, float y);

        /**
         * \fn void reset()
         * \brief Fonction permettant de savoir si un .
         */
        void reset();


    private:

        bool m_isValidated; /*!< Booleen qui sert � savoir si un checkpoint est valide */

        Point m_pointBegin, m_pointEnd; /*!< Les coordonn�es de nos deux points */

        int m_pixelParSeconde; /*!< hmmm TODO */
};

#endif
