#pragma once
#include<map>
#include<string>
using namespace std;
class Score
{
private:
	multimap<string,int> scores;
public:
	void ajoutScore(string s,int sc);
	void charger_scor();
	void decharger_scor();
	multimap<string,int> premiers();
	Score(void);
	~Score(void);
};

