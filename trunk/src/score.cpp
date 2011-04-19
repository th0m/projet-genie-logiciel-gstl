#include "score.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>

Score::Score()
{
    std::string a;
    unsigned int s;
    std::ifstream scs("scores.txt", std::ios::out);

    if(scs)
    {
        while(!scs.eof())
        {
            scs >> s >> a;
            m_scores.insert(std::make_pair(s, a));
        }
        scs.close();
    }
}

Score::~Score()
{
    if(m_scores.size() == 0)
        return;

	std::ofstream scss("scores.txt", std::ios::out);

	if(scss)
	{
	    for(std::set<std::pair<unsigned int, std::string>, Sort >::iterator it = m_scores.begin(); it != m_scores.end(); it++)
	    {
            scss << it->first << " " << it-> second;
            if(++it != m_scores.end()) /* # c'est pas le dernier element, on place un carriage return */
                scss << std::endl;
            it--; /* # On replace l'iterator comme il faut */
	    }
	    scss.close();
	}
}

void Score::ajoutScore(std::string s, unsigned int sc)
{
    m_scores.insert(std::make_pair(sc, s));
}

std::set<std::pair<unsigned int, std::string>, Sort > Score::premiers()
{
    std::set<std::pair<unsigned int, std::string>, Sort > ret;
    unsigned int i = 0;

    for(std::set<std::pair<unsigned int, std::string> >::iterator it = m_scores.begin(); it != m_scores.end() && i < 10; it++, i++)
        ret.insert(std::make_pair(it->first, it->second));

	return ret;
}
