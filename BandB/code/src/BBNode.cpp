#include "BBNode.h"
 
BBNode::BBNode(std::vector<std::pair<int, int> > tasks, std::vector<machin> M, int i , BBNode* cbn, BBNode* root ) {
	int temp;
	if (i < tasks.size()) {
		

		cbn->machines = (BBNode**)malloc(sizeof(BBNode*)*M.size());
		 
		for (int k = 0; k < M.size(); k++)
		{ 
			cbn->machines[k] = (BBNode*)malloc(sizeof(BBNode));
			cbn->machines[k]->father = cbn;
			cbn->machines[k]->machine_index = M.at(k).index;
			cbn->machines[k]->machine_speed = M.at(k).speed;
		
			cbn->machines[k]->machinesTime = (int*)malloc(sizeof(int)*M.size());
			for (int i = 0; i < k; i++)
				cbn->machines[k]->machinesTime[i] = cbn->machinesTime[i];
			for (int i = k + 1; i < M.size(); i++)
				cbn->machines[k]->machinesTime[i] = cbn->machinesTime[i];
			cbn->machines[k]->machinesTime[k] = cbn->machinesTime[k]+(tasks.at(i).first) / M.at(k).speed;

			cbn->machines[k]->taskstime = fmax(cbn->machines[k]->machinesTime[k], cbn->taskstime);
			 temp = (int)((tasks.size() - i - 1) / M.size());
			if (temp < 1)
				temp = 1;
			cbn->machines[k]->taskMachineRatio = (double)temp / root->mxms;
			cbn->machines[k]->Tsum = cbn->Tsum - tasks.at(i).first;
			cbn->machines[k]->MinTask = cbn->MinTask;//TASKS sorted from the bigest to the smallest so the minumum will did not changed
			cbn->machines[k]->BestTiming = cbn->machines[k]->taskstime+(int)fmax((cbn->machines[k]->Tsum / root->Msum), (cbn->machines[k]->MinTask*cbn->machines[k]->taskMachineRatio)/*should add div max machine speed*/);
			cbn->machines[k]->worstTiming = cbn->machines[k]->taskstime+(cbn->machines[k]->Tsum / root->mms);
			if (cbn->machines[k]->worstTiming < root->MinWorst)
				root->MinWorst = cbn->machines[k]->worstTiming;
		}
		if (i == tasks.size() - 1) {
			root->leafs.push_back(cbn);
		}
		for (int k = 0; k < M.size(); k++)//we need to check all brother befor start new level for this reson we have two loops
		{
			if (cbn->machines[k]->BestTiming <= fmin(root->MinWorst, root->BestTiming*2))
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
	this->father = NULL;
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
	 int min = leafs.at(0)->machines[0]->taskstime;
	 int mmtime;
	 for (int i = 0; i < leafs.size(); i++) {
		 for (int j = 0; j < M.size(); j++)
			 if (leafs.at(i)->machines[j]->taskstime < min) {
				 min = leafs.at(i)->machines[j]->taskstime;
				 ServiverPath = leafs.at(i)->machines[j];
			 }
	 }
	 min = min + 0;

	

}


BBNode::~BBNode()
{
}
 