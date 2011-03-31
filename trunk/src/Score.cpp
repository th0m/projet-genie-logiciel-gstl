#include "Score.h"
#include <iostream>
#include "utility"
#include <algorithm> 
# include <fstream>
#include"conio.h"
#include<map>
using namespace std;


Score::Score(void)
{
	charger_scor();
		
}


Score::~Score(void)
{
	decharger_scor();
}


///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Score::charger_scor()//Fonction qui permet de decharger le fichier dans le vecteur
{
int a;
string s;
ifstream scs ("scores.txt", ios::out);// ouverture du fichier en lecture
if(scs)
{
while (!scs.eof())
    {
scs >>s;
scs >>a;//on lit chaque score
this->scores.insert(make_pair(s,a));
	}
scs.close();
}
}


///////////////////////////////////////////////////////////////////////////////////////////////////////
void Score::decharger_scor()//fonction permettant de charger le vecteur des etudiants dans un fichiers
{
	

multimap<string,int>::iterator it;
	bool boolean;
	ifstream scss ("scores.txt", ios::out);
	scss>>boolean;
	scss.close();
ofstream scs ("scores.txt",ios::out|ios::trunc); // ouverture du répertoire en écriture
if(boolean) 
{
	it=scores.begin();
	scs <<it->first<<" "<<it->second;
	for(it=++scores.begin();it!=scores.end();it++)
    {
		scs <<endl<<it->first<<" "<<it->second;
		
    }
}
else
for(it=++scores.begin();it!=scores.end();it++)
    {
		scs <<endl<<it->first<<" "<<it->second;
		
    }
scs.close();
}

void Score::ajoutScore(string s,int sc)
{
	scores.insert(make_pair(s,sc));
	//sort(scores.begin(),scores.end(),greater<int>());
}