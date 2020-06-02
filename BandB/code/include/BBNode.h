#pragma once
#include "Node.h"
#include <vector>
#include "machin.h"
#include "maxheap.h"
#include "minheap.h"
#include <queue>          // std::queue

class BBNode
{
public:
	int deapth;
	int taskstime;
	int machine_index;
	int machine_speed;
	int worstTiming;
	int BestTiming;
	int Tsum;
	int Msum;
	int MinTask;
	int mms;
	int nodesc=0;
	int MinWorst;
	int mxms;
	int ntaskidx;
	int * machinesTime;
	double taskMachineRatio;
	BBNode();

	BBNode(std::vector<Node> J,  std::vector<machin> M,int up);
	BBNode(std::vector<std::pair<int, int> > tasks, std::vector<machin> M, int i, BBNode* cbn, BBNode* root,int upBound);
	int UpperBound(std::vector<Node> J, std::vector<machin> M);

	std::queue<BBNode*> m;
	std::queue<BBNode*> todelete;

	std::vector<BBNode*> leafs;
	std::vector<std::pair<int,int>>* Mi;//<machine_index,task_index>
	~BBNode();
private:
	int later;
	
};

