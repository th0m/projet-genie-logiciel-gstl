#ifndef SCORE_HPP
#define SCORE_HPP

#include <map>
#include <string>

using namespace std;

class Score
{
    public:

        explicit Score();
        ~Score();

        void ajoutScore(string s, unsigned int sc);

        /* # Fonction qui permet de decharger le fichier dans le vecteur */
        void charger_score();

        /* # Fonction permettant de charger le vecteur des etudiants dans un fichiers */
        void decharger_score();

    private:

        multimap<string, unsigned int> premiers();

        multimap<string, unsigned int> scores;

};
#endif
