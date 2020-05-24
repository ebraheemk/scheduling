#pragma once
#include "Node.h"
#include <vector>
#include "machin.h"
#include "maxheap.h"

class BBNode
{
public:
	int taskstime;
	int machine_index;
	int machine_speed;
	int worstTiming;
	int BestTiming;
	int Tsum;
	int Msum;
	int MinTask;
	int mms;
	int MinWorst;
	double taskMachineRatio;
	BBNode* father;
	BBNode(std::vector<Node> J,  std::vector<machin> M);
	BBNode(std::vector<std::pair<int, int> > tasks, std::vector<machin> M, int i, BBNode* cbn, BBNode* root);
	BBNode** machines;
	std::vector<BBNode*> leafs;
	~BBNode();
private:
	int later;
	
};

