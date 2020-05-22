#include "BBNode.h"
 
BBNode::BBNode(std::vector<std::pair<int, int> > tasks, std::vector<machin> M, int i , BBNode* cbn, BBNode* root) {
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
			
			BBNode(tasks, M, i + 1, cbn->machines[k],root);
		}
		 
	}

}


BBNode::BBNode(std::vector<Node> J,  std::vector<machin> M)
{
	this->father = NULL;
	this ->machine_index =-1;
	this->machine_speed =-1;
	this->taskstime = 0;
	this->BestTiming = -1;
	this->worstTiming = -1;
	 
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
