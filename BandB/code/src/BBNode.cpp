#include "BBNode.h"
int BBNode::UpperBound(std::vector<Node> J, std::vector<machin> M) {
	int i;
	
	std::vector<machin> Mcopy;
	for (int i = 0; i < M.size(); i++)
		Mcopy.push_back(M.at(i));

	minheap tasks = minheap(J.at(0).time * 4, 0);
	minheap* copy = &tasks;
	for (i = 1; i < J.size(); i++) {
		tasks.insert(copy, new minheap(J.at(i).time * 4, i));
	}


	int j = 0, k = 0, z = 0;
	std::pair<int, int> p;

	for (i = 0; i < J.size(); ) {
		if (j == M.size())
			j = 0;

		for (k = 0; k < M.at(j).speed && i < J.size(); k++, i++) {
			minheap* copy = &tasks;
			if (i != J.size() - 1)
				p = tasks.pop(copy);
			else {
				p.first = tasks.value;
				p.second = tasks.index;
			}

			M.at(j).TasksTime += p.first / M.at(j).speed;
			M.at(j).Tasks.insert(std::pair<int, Node>(p.second, Node(p.first / 4, p.second)));
			z++;

		}
		j++;
	}

	int minm, maxm;
	minm = M.at(0).TasksTime;
	maxm = M.at(0).TasksTime;
	for (i = 0; i < M.size(); i++) {
		if (M.at(i).TasksTime < minm)
			minm = M.at(i).TasksTime;
		if (M.at(i).TasksTime > maxm)
			maxm = M.at(i).TasksTime;
	}
	printf("minmum1 hmdan m %d", minm);
	maxheap tasks2 = maxheap(J.at(0).time * 4, 0);
	maxheap* copy2 = &tasks2;
	for (i = 1; i < J.size(); i++) {
		tasks2.insert(copy2, new maxheap(J.at(i).time * 4, i));
	}
	for (int i = 0; i < M.size(); i++)
		Mcopy.push_back(M.at(i));

	for (i = 0; i < J.size(); ) {
		if (j == M.size())
			j = 0;

		for (k = 0; k < M.at(j).speed && i < J.size(); k++, i++) {
			maxheap* copy2 = &tasks2;
			if (i != J.size() - 1)
				p = tasks2.pop(copy2);
			else {
				p.first = tasks2.value;
				p.second = tasks2.index;
			}

			M.at(j).TasksTime += p.first / M.at(j).speed;
			M.at(j).Tasks.insert(std::pair<int, Node>(p.second, Node(p.first / 4, p.second)));
			z++;

		}
		j++;
	}

	for (i = 0; i < M.size(); i++) {
		
		if (M.at(i).TasksTime > minm)
			minm = M.at(i).TasksTime;
	}
	maxm = fmin(minm, maxm);//minm now is maxmum not minmum
	printf("maximum hmdan m %d", maxm);

	return maxm;
 }

BBNode::BBNode(){}
BBNode::BBNode(std::vector<std::pair<int, int> > tasks, std::vector<machin> M, int i , BBNode* cbn, BBNode* root ,int upBound ) {
	while (!root->todelete.empty()) {
		BBNode * dd= root->todelete.front();
		//if (cbn->deapth > dd->deapth) {
		delete dd;
			root->todelete.pop();
		//}
	}

	int temp, totaltasktime = 0;
	root->nodesc++;
	if (cbn->deapth == tasks.size()-1 ) {
		root->leafs.push_back(cbn);
	}
	if (cbn->deapth < tasks.size()) {
	
		

		//cbn->machines = (BBNode**)malloc(sizeof(BBNode*)*M.size());
		cbn->ntaskidx = tasks.at(cbn->deapth).second;
		for (int k = 0; k < M.size(); k++)
		{ 
			BBNode* ek =  new BBNode();
		//	ek = (BBNode*)malloc(sizeof(BBNode));
			//cbn->machines[k]->father = cbn;
			ek->machine_index = M.at(k).index;
			ek->machine_speed = M.at(k).speed;
			ek->deapth = cbn->deapth + 1;
			ek->machinesTime = (int*)malloc(sizeof(int)*M.size());
			totaltasktime = 0;
			ek->machinesTime[k] = cbn->machinesTime[k] + (tasks.at(cbn->deapth).first) / M.at(k).speed;
			ek->taskstime = fmax(ek->machinesTime[k], cbn->taskstime);
			totaltasktime += (ek->taskstime - ek->machinesTime[k])*M.at(k).speed;

			for (int i = 0; i < k; i++) {
				ek->machinesTime[i] = cbn->machinesTime[i];
				totaltasktime += (ek->taskstime - ek->machinesTime[i])*M.at(i).speed;
			}
			for (int i = k + 1; i < M.size(); i++) {
				ek->machinesTime[i] = cbn->machinesTime[i];
				totaltasktime += (ek->taskstime - ek->machinesTime[i])*M.at(i).speed;

			}
 
 			 temp = (int)((tasks.size() - cbn->deapth - 1) / M.size());
			//if (temp < 1)
			//	temp = 1;
			 ek->taskMachineRatio = (double)temp / root->mxms;
			 ek->Tsum = cbn->Tsum - tasks.at(cbn->deapth).first;
			 ek->MinTask = cbn->MinTask;//TASKS sorted from the bigest to the smallest so the minumum will did not changed
			
			 ek->BestTiming = ek->taskstime+(int)fmax(((ek->Tsum- totaltasktime) / root->Msum), (ek->MinTask*ek->taskMachineRatio)/*should add div max machine speed*/);
			//cbn->machines[k]->BestTiming = cbn->machines[k]->BestTiming - (totaltasktime / root->Msum);
			 ek->worstTiming = ek->taskstime+(ek->Tsum / root->mms);
			if (ek->worstTiming < root->MinWorst)
				root->MinWorst = ek->worstTiming;


			ek->Mi = new std::vector<std::pair<int, int>>;
			for (int e = 0; e < cbn->Mi->size(); e++)
				ek->Mi->push_back(cbn->Mi->at(e));

			ek->Mi->push_back(std::pair<int, int>(M.at(k).index, tasks.at(cbn->deapth).second));
			root->m.push(ek);
		}
		 
		
		 
		 
			
	//	for (int k = 0; k < M.size(); k++)//we need to check all brother befor start new level for this reson we have two loops
		//{
		//	if (cbn->machines[k] != NULL) {
		bool roro = true;
		BBNode* nextcall;
		while (roro &&(!root->m.empty())) {
			nextcall = root->m.front();
			root->m.pop();
			if (nextcall->BestTiming <= fmin(root->MinWorst, upBound))
				roro = false;
			else
				root->todelete.push(nextcall);
			
				 
		}
			       
					BBNode(tasks, M, i + 1, nextcall, root, upBound);
				
					root->todelete.push(nextcall);
					//todo no recurseve constructor move to shechdulier
			}
			 

		}
		 

		 
		 
	//}




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

	 BBNode(tasks, M, 0,this,this,up);
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

	 printf("\n posible path is %d \n", leafs.size());
	 printf("nodes count %d\n", this->nodesc);
}


BBNode::~BBNode()
{
	if(Mi!= nullptr)
	delete[] Mi;
  }
 
	//for (int i = 0; i < this->machinesTime->size(); i++) {

	
