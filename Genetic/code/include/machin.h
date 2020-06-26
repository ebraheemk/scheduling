#pragma once
#include "Node.h"
#include <vector>
#include <map>
class machin
{
public:
	machin(const machin& old);
	machin(int val,int inx):TasksTime(0),speed(val),index(inx){}
	~machin();
 	int speed;
	int TasksTime;
	int index;
	std::map<int,Node> Tasks;
	std::vector<int> tasksidx;
	 
	
private:
	int later;

};

