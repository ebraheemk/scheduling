#include "BBNode.h"




BBNode::BBNode(){}

BBNode::BBNode(std::vector<Node> J,  std::vector<machin> M,int up)
{
	//int up=UpperBound(J, M);
	int Tsum = 0,mmspeed,Msum;
	int maxTask= J.at(0).time;
	int minTask= J.at(0).time;
	for (int i = 0; i < J.size(); i++) {
		Tsum += J.at(i).time;
		if (J.at(i).time > maxTask)
			maxTask = J.at(i).time;
		if (J.at(i).time < minTask)
			minTask = J.at(i).time;
	}
	minTask = minTask * 4;
	maxTask = maxTask * 4;
	Tsum = Tsum * 4;
	mmspeed = M.at(0).speed;
	int tempmax = M.at(0).speed;
	Msum = M.at(0).speed;
	for (int i = 1; i < M.size(); i++) {
		Msum = Msum + M.at(i).speed;
		if (M.at(i).speed < mmspeed)
			mmspeed = M.at(i).speed;
		if (M.at(i).speed > tempmax)
			tempmax = M.at(i).speed;
	}
	this->Mi = new std::vector<std::pair<int, int>>;
	//this->Mi->push_back(std::pair<int, int>(-1, -1));
	//this->father = NULL;
	this->deapth = 0;
	this ->machine_index =-1;
	this->machine_speed =-1;
	this->taskstime = 0;
	int temp = (int)(J.size() / M.size());
	if (temp < 1)
		temp = 1;
 	this->taskMachineRatio =(double) temp / tempmax;
	this->BestTiming = fmax((Tsum/Msum), minTask*this->taskMachineRatio);
	this->worstTiming = Tsum/ mmspeed;
	this->MinTask = minTask;
	this->Tsum = Tsum;
	this->Msum = Msum;
	this->mms = mmspeed;
	this->mxms = tempmax;
	this->MinWorst = worstTiming;
	this->machinesTime = (int*)malloc(sizeof(int)*M.size());
	for (int i = 0; i < M.size(); i++)
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
	 printf("nodes count %d\n", this->nodesc);
}


BBNode::~BBNode()
{
	
  }
 
	//for (int i = 0; i < this->machinesTime->size(); i++) {

	
