#include "BBNode.h"
 
BBNode::BBNode(std::vector<std::pair<int, int> > tasks, std::vector<machin> M, int i , BBNode* cbn, BBNode* root ) {
	if (i < tasks.size()) {
		

		cbn->machines = (BBNode**)malloc(sizeof(BBNode*)*M.size());
		if (i == tasks.size() - 1) {
			root->leafs.push_back(cbn);
		}
		for (int k = 0; k < M.size(); k++)
		{ 
			cbn->machines[k] = (BBNode*)malloc(sizeof(BBNode));
			cbn->machines[k]->father = cbn;
			cbn->machines[k]->machine_index = M.at(k).index;
			cbn->machines[k]->machine_speed = M.at(k).speed;
			cbn->machines[k]->taskstime = 0;
			cbn->machines[k]->taskstime = cbn->taskstime +(tasks.at(i).first) / M.at(k).speed;
			cbn->machines[k]->Tsum = cbn->Tsum - tasks.at(i).first;
			cbn->machines[k]->Msum = cbn->Msum;
			cbn->machines[k]->MinTask = cbn->MinTask;//TASKS sorted from the bigest to the smallest so the minumum will did not changed
		//	cbn->machines[k]->machines[k]->mms=root->mms;
			cbn->machines[k]->BestTiming = cbn->machines[k]->taskstime+fmax((cbn->machines[k]->Tsum / cbn->machines[k]->Msum), cbn->machines[k]->MinTask/4/*should add div max machine speed*/); 
			cbn->machines[k]->worstTiming = cbn->machines[k]->Tsum / root->mms;
			//BBNode(tasks, M, i + 1, cbn->machines[k],root);
			if (cbn->machines[k]->worstTiming < root->MinWorst)
				root->MinWorst = cbn->machines[k]->worstTiming;
		}
		for (int k = 0; k < M.size(); k++)//we need to check all brother befor start new level for this reson we have two loops
		{
			if(cbn->machines[k]->BestTiming< root->MinWorst)
				BBNode(tasks, M, i + 1, cbn->machines[k], root);
		}

		 
	}

}


BBNode::BBNode(std::vector<Node> J,  std::vector<machin> M)
{
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
	this->father = NULL;
	this ->machine_index =-1;
	this->machine_speed =-1;
	this->taskstime = 0;
	int temp = (int)(J.size() / M.size());
	if (temp > 4* tempmax)
		temp = 4* tempmax;
	temp = temp / tempmax;to start from here
	this->taskMachineRatio = fmax(4 - temp,1)/tempmax;
	this->BestTiming = fmax((Tsum/Msum), minTask);
	this->worstTiming = Tsum/ mmspeed;
	this->MinTask = minTask*4;
	this->Tsum = Tsum*4;
	this->Msum = Msum;
	this->mms = mmspeed;
	this->MinWorst = worstTiming;
	 
	//init maxheap
	

	 
	std::vector<std::pair<int, int> > tasks;
	std::pair<int, int> p1;
	maxheap mxhp = maxheap(J.at(0).time * 4, 0);
	for (int i = 1; i < J.size(); i++) {
		mxhp.insert(&mxhp, new maxheap(J.at(i).time * 4, i));
	}
 
	while (mxhp.GetRight() != NULL || mxhp.GetLeft() != NULL) {
 		p1 = mxhp.pop(&mxhp);
		tasks.push_back(p1);
	}
	tasks.push_back(std::pair<int, int>(mxhp.value,mxhp.index));

	 BBNode(tasks, M, 0,this,this);
	
		 


	

}


BBNode::~BBNode()
{
}
 