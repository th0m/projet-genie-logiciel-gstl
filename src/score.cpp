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
	scss.close();

	std::ofstream scs ("scores.txt", std::ios::out | std::ios::trunc); // ouverture du répertoire en écriture
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

void Score::ajoutScore(std::string s, unsigned int sc)
{
    scores.insert(std::make_pair(sc, s));
}

std::set<std::pair<unsigned int, std::string> >& Score::premiers()
{
	std::set<std::pair<unsigned int, std::string> > se;
	std::set<std::pair<unsigned int, std::string> >::iterator it;
	std::set<std::pair<unsigned int, std::string> >::iterator it1;
	std::set<std::pair<unsigned int, std::string> >::iterator it2;

    it = scores.begin();
	for(unsigned int i = 0; i < scores.size() - 1; i++,it++); //it pointe sur le dernier element du set

	if(scores.size() <= 5) //cela veut dire qu'on va ajouter tous les element du set
	{
		for(it1 = it; it1 != scores.begin(); it1--)
			se.insert(*it1);

		it1 = scores.begin(); //on pointe sur le dernier element qui n'a pas ete stock'e pour l'inserer
		se.insert(*it1);
	}
	else //on fait pointer it1 sur le 5eme plus petit element
	{
		unsigned int nbr = scores.size() - 5;
		it1 = scores.begin();

		for(unsigned int i = 0; i < nbr; i++, it1++);
		for(it2 = it; it2 != it1; it2--) //on affiche les element du plus grand au plus petit et on stok en meme temps
            se.insert(*it2);
		it2 = it1; //on pointe sur le dernier element qui n'a pas ete stock'e pour l'inserer
		se.insert(*it2);
	}

	return se;
}
