#pragma once
#include "Node.h"
#include <vector>
class machin
{
public:
	machin();
	~machin();
private:
	int TasksTime;
	int speed;
	std::vector<Node> Tasks;

};

