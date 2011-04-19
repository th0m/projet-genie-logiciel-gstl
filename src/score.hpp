/**
 * \file score.hpp
 * \brief Classe Score.
 * \author GSTL
 * \version 0.1
 * \date 19 avril 2011
 */

#ifndef SCORE_HPP
#define SCORE_HPP

#include <set>
#include <string>
#include "sort.hpp"

/**
 * \class Score
 * \brief Classe qui gère les scores du jeu, sérialisation / désérialisation.
*/
class Score
{
    public:

        /**
         * \fn explicit Score()
         * \brief Constructeur de la classe, avec chargement des scores deja enregistres.
         */
        explicit Score();

        /**
         * \fn ~Score()
         * \brief Destructeur de la classe, serialisation dans un fichier texte.
         */
        ~Score();

        /**
         * \fn void ajoutScore(std::string s, unsigned int sc)
         * \brief Fonction qui permet l'ajout d'un score dans le fichier de score.
         *
         * \param s Le pseudo du joueur.
         * \param sc Le score du joueur.
         */
        void ajoutScore(std::string s, unsigned int sc);

        /**
         * \fn std::set<std::pair<unsigned int, std::string>, Sort > premiers()
         * \brief Fonction qui permet de récupérer le top10.
         *
         * \return Un conteneur qui contient les meilleures joueurs avec les scores associés.
         */
        std::set<std::pair<unsigned int, std::string>, Sort > premiers();

    private:

        std::set<std::pair<unsigned int, std::string>, Sort> m_scores; /*!< Le conteneur des joueurs et scores. */

};

#endif
