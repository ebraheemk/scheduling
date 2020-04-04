#pragma once
#include "Node.h"
#include <vector>
class machin
{
public:
	machin(int val):TasksTime(0),speed(val){}
	~machin();
 	int speed;
private:
	int TasksTime;
	std::vector<Node> Tasks;

};

