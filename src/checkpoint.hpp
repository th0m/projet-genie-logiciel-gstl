/**
 * \file checkpoint.hpp
 * \brief Gestion des checkpoints
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 */

#ifndef CHECKPOINT_HPP
#define CHECKPOINT_HPP

#include <list>
#include "iacar.hpp"

/**
 * \class Checkpoint
 * \brief Classe qui va permettre de gérer les checkpoints placés dans les différentes courses
*/
class Checkpoint
{
    public:

        /**
         * \struct Point
         * \brief Un point est une extremité d'un checkpoint, chaque point a ses coordonnées x et y
         */
        struct Point{
            float x; /*!< Abscisse */
            float y; /*!< Ordonnée */
        };

        /**
         * \enum CompetitorPosition
         * \brief Position d'un adversaire
         */
        enum CompetitorPosition
        {
            BeforeFinishLine, /*!< Juste avant le checkpoint de fin de tour ie. la ligne d'arrivée */
            AfterFinishLine, /*!< Juste après le checkpoint de fin de tour ie. la ligne d'arrivée */
            Others /*!< Ailleurs sur la carte */
        };

        /**
         * \fn explicit Checkpoint(float x1, float y1, float x2, float y2)
         * \brief Constructeur de la classe, avec initialisation des deux points pour former une "ligne" constituant le checkpoint.
         *
         * \param x1 Coordonnée en abscisse du premier point
         * \param y1 Coordonnée en ordonnée du premier point
         * \param x2 Coordonnée en abscisse du second point
         * \param y2 Coordonnée en ordonnée du second point
         */
        explicit Checkpoint(float x1, float y1, float x2, float y2);

        /**
         * \fn bool isValidated() const
         * \brief Fonction permettant de savoir si un checkpoint est validé ou non.
         *
         * \return Retourne un booleen qui va nous renseigner si le checkpoint a été validé ou non
         */
        bool isValidated() const;

        /**
         * \fn void checkC1(float x, float y)
         * \brief Fonction permettant de vérifier si le checkpoint 1 est validé ou non
         *
         * \param x Abscisse de la shape de la voiture du joueur
         * \param y Ordonnée de la shape de la voiture du joueur
         */
         void checkC1(float x, float y);

        /**
         * \fn void checkC2(float x, float y)
         * \brief Fonction permettant de vérifier si le checkpoint 2 est validé ou non
         *
         * \param x Abscisse de la shape de la voiture du joueur
         * \param y Ordonnée de la shape de la voiture du joueur
         */
        void checkC2(float x, float y);

        /**
         * \fn void checkC3(float x, float y)
         * \brief Fonction permettant de vérifier si le checkpoint 3 est validé
         *
         * \param x Abscisse de la shape de la voiture du joueur
         * \param y Ordonnée de la shape de la voiture du joueur
         */
        void checkC3(float x, float y);

        /**
         * \fn void checkCF(float x, float y)
         * \brief Fonction permettant de vérifier si le checkpoint de fin de tour est validé
         *
         * \param x Abscisse de la shape de la voiture du joueur
         * \param y Ordonnée de la shape de la voiture du joueur
         * \return Retourne true si le joueur est actuellement sur le checkpoint de fin
         */
        void checkCF(float x, float y);

        /**
         * \fn CompetitorPosition checkCFIA(float x, float y)
         * \brief Retourne la position de l'adversaire (IA) relativement au checkpoint de fin de tour.
         *
         * \param x Abscisse de la shape de la voiture de l'adversaire
         * \param y Ordonnée de la shape de la voiture de l'adversaire
         * \return BeforeFinishLine si l'adversaire est juste avant le checkpoint de fin de tour ie. la ligne d'arrivée
         *         AfterFinishLine si l'adversaire est juste après le checkpoint de fin de tour ie. la ligne d'arrivée
         *         Others si l'adversaire est ailleurs sur la carte
         */
        CompetitorPosition checkCFIA(float x, float y);

        /**
         * \fn void reset()
         * \brief Fonction qui réinitialise tous les checkpoints ie. ils sont tous invalidés.
         */
        void reset();


    private:

        bool m_isValidated; /*!< Booleen qui sert à savoir si un checkpoint est validé ou non */

        Point m_pointBegin, m_pointEnd; /*!< Les coordonnées de nos deux points */

        int m_pixelParRaffraichissement; /*!< Le nombre de pixels que le joueur peut parcourir au maximum entre 2 rafraîchissements */
};

#endif
