#pragma once
#include "Node.h"
#include <vector>
#include "machin.h"

class BBNode
{
public:
	int taskstime;
	int machine_index;
	BBNode* father;
	BBNode(std::vector<Node> J, std::vector<machin> M);
	BBNode(std::vector<Node> J, std::vector<machin> M,int i);

	~BBNode();
private:
	BBNode** machines;
	
};

