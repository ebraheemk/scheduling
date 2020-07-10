#include "Chromosome.h"


Chromosome::Chromosome(Chromosome& old)
{
	int i;
	this->index = old.index;
	this->SolTime = old.SolTime;
	for (i = 0; i < old.Mchnz.size(); i++) {
		machin * c = new  machin(*old.Mchnz.at(i));
		this->Mchnz.push_back(c);
	}
	this->Tsx = old.Tsx;
}
Chromosome::Chromosome()
{
	 
}


Chromosome::~Chromosome()
{
	//if(Mchnz!=NULL)
		//delete[] &Mchnz;
	for(int i=0;i< Mchnz.size();i++)
		delete Mchnz.at(i);
	Tsx.clear();
	Mchnz.clear();
	Mchnz.shrink_to_fit();

//	for (std::map<int, int>::iterator it = Tsx.begin(); it != Tsx.end(); it++)
	//	Tsx.erase(it);
}
