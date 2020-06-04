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
	int worstTiming;
	int BestTiming;
	int Tsum;
 	int * machinesTime;
	double taskMachineRatio;
	BBNode() {}

	BBNode(int dep, int tmratio, int ttime, int btime, int tsm, int mms, int msize);//(int dep, int midx, int ms, int tmratio, int ttime, int btime, int tsm, int msm, int mms, int mint, int mxms,int msize);

	 

	std::vector<std::pair<int,int>> Mi;//<machine_index,task_index>
	virtual ~BBNode();


};

