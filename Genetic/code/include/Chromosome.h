#pragma once
#include <vector>
#include "Node.h"
#include "machin.h"
class Chromosome
{
public:
	int index;
	int SolTime=0;
	//std::vector<Node> Tsx;
	std::vector<machin> Mchnz;
	Chromosome();
	~Chromosome();
};

