#ifndef SCORE_HPP
#define SCORE_HPP

#include <set>
#include <string>
#include "sort.hpp"

class Score
{
    public:

        explicit Score();

        ~Score();

        /* # Fonction qui permet l'ajout d'un score dans le fichier de score */
        void ajoutScore(std::string s, unsigned int sc);

        /* # Fonction qui permet de récupérer le top5 */
        std::set<std::pair<unsigned int, std::string>, Sort > premiers();

    private:

        /* # Conteneur qui va gérer les scores */
        std::set<std::pair<unsigned int, std::string>, Sort> scores;

};

#endif
