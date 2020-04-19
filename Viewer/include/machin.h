#pragma once
#include "Node.h"
#include <vector>
class machin
{
public:
	machin(int val,int inx):TasksTime(0),speed(val),index(inx){}
	~machin();
 	int speed;
	int TasksTime;
	int index;
	std::vector<Node> Tasks;
private:
	int later;

};

