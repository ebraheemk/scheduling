#pragma once
#include "Node.h"
#include <vector>
#include <map>
class machin
{
public:
	machin(int val,int inx):TasksTime(0),speed(val),index(inx){}
	~machin();
 	int speed;
	int TasksTime;
	int index;
	std::map<int,Node> Tasks;

	



};

