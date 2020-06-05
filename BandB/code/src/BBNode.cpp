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
	//init maxheap
	

	

	
/*	 int min = leafs.at(0)->machines[0]->taskstime;
	 ServiverPath = leafs.at(0)->machines[0];
	 int mmtime;
	 for (int i = 0; i < leafs.size(); i++) {
		 for (int j = 0; j < M.size(); j++) {
			 if (leafs.at(i)->machines[j]->taskstime < min) {
				 min = leafs.at(i)->machines[j]->taskstime;
				 ServiverPath = leafs.at(i)->machines[j];
			 }
		 }
	 }
	 min = min + 0;*/

//	 printf("\n posible path is %d \n", leafs.size());
	// printf("nodes count %d\n", this->nodesc);
}


BBNode::~BBNode()
{
	
	//delete machinesTime;
	
  }
 
	//for (int i = 0; i < this->machinesTime->size(); i++) {

	
