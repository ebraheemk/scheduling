#include "BBNode.h"




 
BBNode::BBNode(int dep,double tmratio,int ttime,int btime,int tsm,int mms,int msize)
{
	
 	this->deapth = dep;//0
	this->taskstime = ttime;

 	this->taskMachineRatio = tmratio;
	this->BestTiming = btime;
	this->worstTiming = tsm/mms;
	this->Tsum = tsm;
	this->machinesTime = (int*)malloc(sizeof(int)*msize);
	for (int i = 0; i < msize; i++)
		this->machinesTime[i] = 0;
 	
}


BBNode::~BBNode()
{
	
	//delete machinesTime;
	delete[] machinesTime;
	Mi.clear();
	Mi.shrink_to_fit();
	 
	while (!m.empty())
		m.pop();
 

	

  }
 
	//for (int i = 0; i < this->machinesTime->size(); i++) {

	
