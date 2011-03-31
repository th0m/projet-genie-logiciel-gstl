#include "score.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;


Score::Score()
{
	charger_score();
}


Score::~Score()
{
	decharger_score();
}


void Score::charger_score()
{
    unsigned int a;
    string s;
    ifstream scs("scores.txt", ios::out);

    if(scs)
    {
        while(!scs.eof())
        {
            scs >> s;
            scs >> a;//on lit chaque score
            scores.insert(make_pair(s, a));
        }
        scs.close();
    }
}

void Score::decharger_score()
{
    ifstream scss("scores.txt", ios::out);
    multimap<string, unsigned int>::iterator it;
	bool boolean;

	scss >> boolean;
	scss.close();
    ofstream scs ("scores.txt", ios::out | ios::trunc); // ouverture du répertoire en écriture

    if(boolean)
    {
        it = scores.begin();
        scs << it->first << " " << it->second;
        for(it = ++scores.begin(); it != scores.end(); it++)
        {
            scs << endl << it->first << " " << it->second;
        }
    }
    else
    {
        for(it = ++scores.begin(); it != scores.end(); it++)
        {
            scs << endl << it->first << " " << it->second;
        }
    }
    scs.close();
}

void Score::ajoutScore(string s, unsigned int sc)
{
	scores.insert(make_pair(s, sc));
	//sort(scores.begin(),scores.end(),greater<int>());
}
