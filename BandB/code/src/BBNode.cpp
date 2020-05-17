#include "BBNode.h"

BBNode::BBNode(std::vector<Node> J, std::vector<machin> M, int i) {
	if (i < J.size()) {
		this->machines = (BBNode**)malloc(sizeof(BBNode*)*M.size());
	}

}


BBNode::BBNode(std::vector<Node> J, std::vector<machin> M)
{
	BBNode(J, M, 0);
	
		 


	

}


BBNode::~BBNode()
{
}
