#include "score.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>

Score::Score()
{
    std::string a="";
    unsigned int s=0;
    std::ifstream scs("scores.txt", std::ios::out);

    if(scs)
    {
        while(!scs.eof())
        {
            scs >> s;
            scs >> a;//on lit chaque score
            scores.insert(std::make_pair(s, a));
        }
        scs.close();
    }
}

Score::~Score()
{
    std::set<std::pair<unsigned int, std::string> >::iterator it;
	bool boolean;
	std::ifstream scss ("scores.txt", std::ios::out);
	scss >> boolean;

	if(scss || scores.size() != 0 )
	{
		std::ofstream scs ("scores.txt", std::ios::out /*| std::ios::trunc*/); // ouverture du répertoire en écriture
		if(scs)
		{
			if(boolean) //vide
			{
				it = scores.begin();
				scs << it->first << " " << it->second;
				for(it = ++scores.begin(); it != scores.end(); it++)
                    scs << std::endl << it->first << " " << it->second;
			}
			else
				for(it = ++scores.begin(); it != scores.end(); it++)
                    scs << std::endl << it->first << " " << it->second;

			scs.close();
		}
	}
	scss.close();
}

void Score::ajoutScore(std::string s, unsigned int sc)
{
    scores.insert(std::make_pair(sc, s));
}

std::set<std::pair<unsigned int, std::string> >& Score::premiers()
{
    std::set<std::pair<unsigned int, std::string> >::iterator it;
	bool boolean;
	std::ifstream scss ("scores.txt", std::ios::out);
	scss >> boolean;

	if(scss || scores.size()!=0 )
	{
		std::ofstream scs ("scores.txt", std::ios::out); // ouverture du répertoire en écriture
		if(scs)
		{
			if(boolean) //vide
			{
				it = scores.begin();
				scs << it->first << " " << it->second;
				for(it = ++scores.begin(); it != scores.end(); it++)
                    scs << std::endl << it->first << " " << it->second;
			}
			else
				for(it = ++scores.begin(); it != scores.end(); it++)
                    scs << std::endl << it->first << " " << it->second;

			scs.close();
		}
	}
	scss.close();
}
