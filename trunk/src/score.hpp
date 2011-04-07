#ifndef SCORE_HPP
#define SCORE_HPP

#include <set>
#include <string>

class Score
{
    public:

        explicit Score();
        ~Score();

        void ajoutScore(std::string s, unsigned int sc);

        std::set<std::pair<unsigned int, std::string> >& premiers();

    private:

        std::set<std::pair<unsigned int, std::string> > scores;

};
#endif
