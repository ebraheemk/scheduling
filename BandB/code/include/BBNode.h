#pragma once
#include "Node.h"
#include <vector>
#include "machin.h"
#include "maxheap.h"
#include "minheap.h"

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
	int mxms;
	int ntaskidx;
	int * machinesTime;
	double taskMachineRatio;
	BBNode* ServiverPath;
	BBNode* father;
	BBNode(std::vector<Node> J,  std::vector<machin> M);
	BBNode(std::vector<std::pair<int, int> > tasks, std::vector<machin> M, int i, BBNode* cbn, BBNode* root,int upBound);
	int UpperBound(std::vector<Node> J, std::vector<machin> M);
	BBNode** machines;
	std::vector<BBNode*> leafs;
	~BBNode();
private:
	int later;
	
};

