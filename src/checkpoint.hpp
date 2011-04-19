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
         *  Un point est une extremit� d'un checkpoint.
         *  Chaque point a ses coordonn�es x et y.
         *
         */
        struct Point{
            float x; /*!< Abscisse */
            float y; /*!< Ordonnee */
        };


        /**
         * \enum CompetitorPosition
         * \brief desc
         *
         * position d'un adversaire
         *
         */
        enum CompetitorPosition
        {
            BeforeFinishLine, /*!< juste avant le checkpoint de fin de tour (finish line) */
            AfterFinishLine, /*!< juste apr�s le checkpoint de fin de tour (finish line) */
            Others /*!< ailleurs sur la carte */
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
         * \brief Fonction permettant de savoir si un checkpoint est valid�.
         *
         * \return Renvoit un booleen qui va nous renseigner si le checkpoint � ete valid� ou non.
         */
        bool isValidated() const;

        /**
         * \fn void checkC1(float x, float y)
         * \brief Fonction permettant de savoir si le checkpoint 1 est valid�.
         *
         * \param x absisse de la shape de la voiture du joueur
         * \param y ordonn�e de la shape de la voiture du joueur
         * \return renvoi true si le joueur est actuellement sur le checkpoint 1
         */
         void checkC1(float x, float y);

        /**
         * \fn void checkC1(float x, float y)
         * \brief Fonction permettant de savoir si le checkpoint 2 est valid�.
         *
         * \param x absisse de la shape de la voiture du joueur
         * \param y ordonn�e de la shape de la voiture du joueur
         * \return renvoi true si le joueur est actuellement sur le checkpoint 2
         */
        void checkC2(float x, float y);

        /**
         * \fn void checkC1(float x, float y)
         * \brief Fonction permettant de savoir si le checkpoint 3 est valid�.
         *
         * \param x absisse de la shape de la voiture du joueur
         * \param y ordonn�e de la shape de la voiture du joueur
         * \return renvoi true si le joueur est actuellement sur le checkpoint 3
         */
        void checkC3(float x, float y);

        /**
         * \fn void checkC1(float x, float y)
         * \brief Fonction permettant de savoir si le checkpoint de fin est valid�.
         *
         * \param x absisse de la shape de la voiture du joueur
         * \param y ordonn�e de la shape de la voiture du joueur
         * \return renvoi true si le joueur est actuellement sur le checkpoint de fin
         */
        void checkCF(float x, float y);

        /**
         * \fn CompetitorPosition checkCFIA(float x, float y)
         * \brief Renvoi la position de l'adversaire (IA) relativement au checkpoint de fin de tour.
         *
         * \param x absisse de la shape de la voiture de l'adversaire
         * \param y ordonn�e de la shape de la voiture de l'adversaire
         * \return BeforeFinishLine si l'adversaire est juste avant le checkpoint de fin de tour (finish line)
         *         AfterFinishLine si l'adversaire est juste apr�s le checkpoint de fin de tour (finish line)
         *         Others si l'adversaire est ailleurs sur la carte
         */
        CompetitorPosition checkCFIA(float x, float y);

        /**
         * \fn void reset()
         * \brief Fonction remet au false tous les checkpoint pour dire qu'ils ne sont pas valid�s.
         */
        void reset();


    private:

        bool m_isValidated; /*!< Booleen qui sert � savoir si un checkpoint est valide */

        Point m_pointBegin, m_pointEnd; /*!< Les coordonn�es de nos deux points */

        int m_pixelParRaffraichissement; /*!< nombre de pixels que le joueur peut parcourrir au maximum entre 2 raffraichissements */
};

#endif
